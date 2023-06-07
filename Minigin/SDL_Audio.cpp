#include "SDL_Audio.h"

#include <iostream>
#include <ranges>
#include <sstream>

#include "ResourceManager.h"
#include "SDL.h"
#include "SDL_mixer.h"

namespace Monke
{
	SDL_Audio::SDL_Audio()
	{
		//https://gist.github.com/armornick/3497064

		//initialize sdl mixxer
		if (Mix_Init(MIX_INIT_MP3) < 0)
		{
			std::cout << "Error in initializing SDL Mixer: " << Mix_GetError() << '\n';
		}
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0)
		{
			std::cout << "Error in opening audio: " << Mix_GetError() << '\n';
		}

		//start the thread
		m_Thread = std::jthread{ [this] { Run(); } };
	}

	SDL_Audio::~SDL_Audio()
	{
		//stop the thread
		m_Thread.request_stop();

		//notify condidtion
		m_Condition.notify_all();

		//lock the mutex
		std::unique_lock lock{ m_Mutex };

		//resharper suggestion to get value out of map
		//release data
		for (const auto& val : m_Sounds | std::views::values)
		{
			Mix_FreeChunk(val.pData);
		}

		lock.unlock();

		Mix_CloseAudio();
		Mix_Quit();
	}

	void SDL_Audio::Play(const SoundID id, const float volume)
	{
		AudioEvent temp{ play, id, volume, "NoPathBecausePlayEvent"};

		//if sounds is empty of sounds doesnt contain the id dont play sound
		if(m_Sounds.empty() || m_Sounds.contains(id) == false)
		{
			std::cout << "Sound with ID: " << id << " doesnt exist\n";
			return;
		}

		//notify condition and add to queue

		std::lock_guard lock{ m_Mutex };

		m_SoundQueue.emplace(temp);
		m_Condition.notify_one();

		//std::cout << "public Play sound with id: " << id << '\n';
	}
	
	void SDL_Audio::Play(const SoundID id, const std::string& path, const float volume)
	{

		std::stringstream ss{};
		ss << ResourceManager::Get().GetPath() << path;

		AudioEvent temp{ play_name, id, volume, ss.str() };

		//notify condition and add to queue

		std::lock_guard lock{ m_Mutex };

		m_SoundQueue.emplace(temp);
		m_Condition.notify_one();

		//std::cout << "public Play sound with path: " << path << '\n';
	}

	void SDL_Audio::LoadSound(const SoundID id, const std::string& path)
	{
		std::stringstream ss{};
		ss << ResourceManager::Get().GetPath() << path;

		AudioEvent temp{ load, id, 0.f, ss.str() };

		//notify condition and add to queue

		std::lock_guard lock{ m_Mutex };

		m_SoundQueue.emplace(temp);
		m_Condition.notify_one();

		//std::cout << "public Load sound with path: " << path << '\n';
	}

	void SDL_Audio::Run()
	{
		// gets stopen token
		const std::stop_token& stopToken{ m_Thread.get_stop_token() };

		//make lock

		//check if thread hanst stopped
		while (!stopToken.stop_requested())
		{
			//make the lock
			std::unique_lock lock{ m_Mutex };

			//if no events or stop requested have happened wait
			m_Condition.wait(lock, [&]() { return !m_SoundQueue.empty() || stopToken.stop_requested(); });

			//lock the event being popped
			//lock.lock();

			if (stopToken.stop_requested()) break;

			const auto event = m_SoundQueue.back();
			m_SoundQueue.pop();

			lock.unlock();

			//do the correct action based on the event
			switch (event.type)
			{
				case play:
				{
					//check if sound id exist to play sound
					if (!m_Sounds.contains(event.ID))
					{
						std::cout << "ID of sound not found, make sure sound is loaded OR use play with path name: " << event.ID << '\n';
						break;
					}

					//play sound
					const auto sound = m_Sounds.at(event.ID);

					const int channel{ Mix_PlayChannel(-1, sound.pData, 0) };

					if (channel == -1) return;

					Mix_Volume(channel, static_cast<int>(event.volume * MIX_MAX_VOLUME));

					//std::cout << "Play sound with id: " << event.ID << '\n';
				}
				break;

				case play_name:
				{
					//this events loads a sound when it hasnt been found
					//if its found it can play wihtout loading

					//check if sound with that path doesnt exist already
					const auto& soundIt{ std::ranges::find_if(m_Sounds, [&](const std::pair<SoundID, SoundData>& sound) { return event.path == sound.second.path; }) };

					//if it doesnt load it and add it to the sounds
					if(soundIt == m_Sounds.end())
					{
						const auto sound = Mix_LoadWAV(event.path.c_str());
						if (!sound)
						{
							std::cout << "Couldnt load sound: " << event.path << ' ' << Mix_GetError() << '\n';
							break;
						}

						SoundData tempSound;
						tempSound.pData = sound;
						tempSound.path = event.path;

						m_Sounds.emplace(std::pair{ event.ID, tempSound });
					}

					//play sound
					const auto& sound = m_Sounds.at(event.ID);

					const int channel{ Mix_PlayChannel(-1, sound.pData, 0) };

					if (channel == -1) return;

					Mix_Volume(channel, static_cast<int>(event.volume * MIX_MAX_VOLUME));

					//std::cout << "Play sound with path: " << event.path << '\n';
				}
				break;

				case load:
				{
					//check if sound hasnt been loaded yet
					const auto& soundIt{ std::ranges::find_if(m_Sounds, [&](const std::pair<SoundID, SoundData>& sound) { return event.path == sound.second.path; }) };

					//if it hasnt load sound
					if (soundIt == m_Sounds.end())
					{
						const auto sound = Mix_LoadWAV(event.path.c_str());

						if (!sound)
						{
							std::cout << "Couldnt load sound: " << event.path << ' ' << Mix_GetError() << '\n';
							break;
						}

						SoundData tempSound;
						tempSound.pData = sound;
						tempSound.path = event.path;

						m_Sounds.emplace(std::pair{ event.ID, tempSound });
						//std::cout << "Loaded sound with path: " << event.path << '\n';
						break;
					}

					//std::cout << "Already Loaded sound with path: " << event.path << '\n';
				}
				break;

				default:
				break;
			}

			
		}
	}
}
