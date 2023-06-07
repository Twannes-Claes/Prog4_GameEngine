#pragma once

#include <memory>

#include "AudioSystem.h"
#include "Singleton.h"

namespace Monke
{
	class DefaultAudioSystem;
	class AudioSystem;

	class ServiceLocator final
	{
	public:

		static AudioSystem& GetSoundSystem()
		{
			return m_pAudioSystem == nullptr ? *m_pDefaultAudioSystem : *m_pAudioSystem;
		}

		template <typename T>
		static void RegisterAudioSystem()
		{
			static_assert(std::is_base_of_v<AudioSystem, T>);
			m_pAudioSystem = std::make_unique<T>();
		}

	private:

		inline static std::unique_ptr<AudioSystem> m_pAudioSystem{};
		inline static std::unique_ptr<DefaultAudioSystem> m_pDefaultAudioSystem = std::make_unique<DefaultAudioSystem>();

	};
}

