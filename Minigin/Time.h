#pragma once

#include <chrono>
#include "Singleton.h"

namespace Monke
{
	class Time final : public Singleton<Time>
	{
	public:

		Time();

		void Update();

		float GetElapsed() const { return m_DeltaTime; }
		float GetTotal() const { return m_TotalTime; }

		virtual ~Time() override = default;
		Time(const Time& other) = delete;
		Time(Time&& other) = delete;
		Time& operator=(const Time& other) = delete;
		Time& operator=(Time&& other) = delete;

	private:

		std::chrono::steady_clock::time_point m_LastTime{};

		float m_DeltaTime{};
		float m_TotalTime{};

	};
}



