#pragma once

namespace Monke
{
	template <typename T>
	class Observer
	{
		public:

		virtual ~Observer() = default;

		virtual void Notify(const unsigned int eventID, const T* object) = 0;
	};
}
