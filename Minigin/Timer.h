#pragma once

#include <chrono>
#include "Singleton.h"

namespace Monke
{
	class Timer final : public Singleton<Timer>
	{
	public:

		Timer();

		void Update();

		float GetElapsed() const { return m_DeltaTime; }
		float GetTotal() const { return m_TotalTime; }

		std::chrono::steady_clock::time_point GetLastTime() const { return m_LastTime; }

		virtual ~Timer() override = default;
		Timer(const Timer& other) = delete;
		Timer(Timer&& other) = delete;
		Timer& operator=(const Timer& other) = delete;
		Timer& operator=(Timer&& other) = delete;

	private:

		std::chrono::steady_clock::time_point m_LastTime{};

		float m_DeltaTime{};
		float m_TotalTime{};

	};
}



