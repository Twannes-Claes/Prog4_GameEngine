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

		if (Mix_Init(MIX_INIT_MP3) < 0)
		{
			std::cout << "Error in initializing SDL Mixer: " << Mix_GetError() << '\n';
		}
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0)
		{
			std::cout << "Error in opening audio: " << Mix_GetError() << '\n';
		}

		m_Thread = std::jthread{ [this] { Run(); } };
	}

	SDL_Audio::~SDL_Audio()
	{
		m_Thread.request_stop();

		m_Condition.notify_all();

		//resharper suggestion
		for (const auto& val : m_Sounds | std::views::values)
		{
			Mix_FreeChunk(val.pData);
		}

		Mix_CloseAudio();
		Mix_Quit();
	}

	void SDL_Audio::Play(const SoundID id, const float volume)
	{
		SDL_AudioEvent temp{ play, id, volume };

		m_SoundQueue.emplace(temp);
		m_Condition.notify_one();
	}
	
	void SDL_Audio::Play(const SoundID id, const std::string& path, const float volume)
	{

		std::stringstream ss{};
		ss << ResourceManager::Get().GetPath() << path;

		SDL_AudioEvent temp{ play_name, id, volume, ss.str() };

		m_SoundQueue.emplace(temp);
		m_Condition.notify_one();
	}

	void SDL_Audio::LoadSound(const SoundID id, const std::string& path)
	{
		std::stringstream ss{};
		ss << ResourceManager::Get().GetPath() << path;

		SDL_AudioEvent temp{ load, id, 0.f, ss.str() };

		m_SoundQueue.emplace(temp);
		m_Condition.notify_one();
	}

	void SDL_Audio::Run()
	{
		const std::stop_token& stopToken{ m_Thread.get_stop_token() };
		std::unique_lock lock{ m_Mutex };

		while (!stopToken.stop_requested())
		{
			if (m_SoundQueue.empty())
			{
				m_Condition.wait(lock);
			}

			while (!m_SoundQueue.empty() && !stopToken.stop_requested())
			{

				lock.lock();

				const auto& event = m_SoundQueue.back();
				m_SoundQueue.pop();

				lock.unlock();

				switch (event.type)
				{
					case play:
					{
						if (m_Sounds.contains(event.ID))
						{
							std::cout << "ID of sound not found, make sure sound is loaded OR use play with path name: " << event.ID << '\n';
							break;
						}

						const auto sound = m_Sounds.at(event.ID);

						const int channel{ Mix_PlayChannel(-1, sound.pData, 0) };

						if (channel == -1) return;

						Mix_Volume(channel, static_cast<int>(event.volume * MIX_MAX_VOLUME));
					}
					break;

					case play_name:
					{
						const auto& soundIt{ std::ranges::find_if(m_Sounds, [&](const std::pair<SoundID, SDL_Sound>& sound) { return event.path == sound.second.name; }) };

						if(soundIt == m_Sounds.end())
						{
							const auto sound = Mix_LoadWAV(event.path.c_str());
							if (!sound)
							{
								std::cout << "Couldnt load sound: " << event.path << ' ' << Mix_GetError() << '\n';
								break;;
							}

							m_Sounds.emplace(std::pair{ event.ID, sound });
						}

						const auto sound = m_Sounds.at(event.ID);

						const int channel{ Mix_PlayChannel(-1, sound.pData, 0) };

						if (channel == -1) return;

						Mix_Volume(channel, static_cast<int>(event.volume * MIX_MAX_VOLUME));
					}
					break;

					case load:
					{
						const auto& soundIt{ std::ranges::find_if(m_Sounds, [&](const std::pair<SoundID, SDL_Sound>& sound) { return event.path == sound.second.name; }) };

						if (soundIt == m_Sounds.end())
						{
							const auto sound = Mix_LoadWAV(event.path.c_str());

							if (!sound)
							{
								std::cout << "Couldnt load sound: " << event.path << ' ' << Mix_GetError() << '\n';
								break;
							}

							m_Sounds.emplace(std::pair{ event.ID, sound });
						}
					}
					break;

					default:
					break;
				}

			}
		}
	}
}
