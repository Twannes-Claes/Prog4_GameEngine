#pragma once

namespace Monke
{
	template <typename T>
	class Observer
	{
		public:

		Observer() = default;
		virtual ~Observer() = default;

		virtual void Notify(const unsigned int eventID, T* object) = 0;

		Observer(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator= (const Observer&) = delete;
		Observer& operator= (const Observer&&) = delete;
	};
}
