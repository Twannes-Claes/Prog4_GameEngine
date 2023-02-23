#include "Time.h"

namespace Monke
{
	Time::Time()
	{
		//set the start time
		m_LastTime = std::chrono::high_resolution_clock::now();
	}

	void Time::Update()
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
