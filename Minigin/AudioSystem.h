#pragma once
#include <string>
namespace Monke
{
	using SoundID = unsigned short;

	class AudioSystem
	{
	public:

		AudioSystem() = default;
		virtual ~AudioSystem() = default;

		virtual void Play(const SoundID id, const float volume) = 0;
		virtual void Play(const SoundID id, const std::string& path, const float volume) = 0;

		virtual void LoadSound( const SoundID id, const std::string& path) = 0;

		virtual void Stop(const SoundID id) = 0;
		virtual void StopAll() = 0;

		virtual void Pause(const SoundID id) = 0;
		virtual void PauseAll() = 0;

		virtual void Resume(const SoundID id) = 0;
		virtual void ResumeAll() = 0;

		virtual void Mute(bool mute) = 0;
	};

	class DefaultAudioSystem final : public AudioSystem
	{
	public:

		DefaultAudioSystem() = default;

		virtual void Play(const SoundID, const float) override {}
		virtual void Play(const SoundID, const std::string&, const float) override {}

		virtual void LoadSound(const SoundID, const std::string&) override {}

		virtual void Stop(const SoundID) override {}
		virtual void StopAll() override {}

		virtual void Pause(const SoundID) override {}
		virtual void PauseAll() override {}

		virtual void Resume(const SoundID) override {}
		virtual void ResumeAll() override {}

		virtual void Mute(bool) override{};
	};
}
