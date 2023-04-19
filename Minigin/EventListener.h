#pragma once


namespace Monke
{
	template <class T>
	class EventListener
	{
		virtual ~EventListener() = default;

		virtual void OnEvent(T* object) = 0;
	};
}
