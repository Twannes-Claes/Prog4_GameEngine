#include "Timer.h"

namespace Monke
{
	Timer::Timer()
	{
		//set the start time
		m_LastTime = std::chrono::high_resolution_clock::now();
	}

	void Timer::Update()
	{
		//get the current time
		const auto currentTime{ std::chrono::high_resolution_clock::now() };

		//calculate the delta time
		m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();

		//calculate the total time
		m_TotalTime += m_DeltaTime;

		//reset the lastTime
		m_LastTime = currentTime;
	}
}
