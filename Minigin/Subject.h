#pragma once
#include <vector>

#include "Observer.h"

namespace Monke
{
	template <class T>
	class Subject final
	{
	public:

		Subject() = default;
		~Subject() = default;

		void AddObserver(Observer<T>* observer)
		{
			m_Observers.push_back(observer);
		}

		void RemoveObserver(Observer<T>* observer)
		{
			m_Observers.erase(std::ranges::find(m_Observers, observer));
		}

		void Notify(const unsigned int eventID, T* object)
		{
			for (const auto& observer : m_Observers)
			{
				observer->Notify(eventID, object);
			}
		}

	private:

		std::vector<Observer<T>*> m_Observers{};

	};
}
