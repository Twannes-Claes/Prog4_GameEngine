#pragma once

#include "BaseComponent.h"

namespace Monke
{
	class DataComponent : public BaseComponent
	{

	public:

		DataComponent() = default;

		virtual ~DataComponent() override = default;

		DataComponent(const DataComponent& other) = delete;
		DataComponent(DataComponent&& other) = delete;
		DataComponent& operator=(const DataComponent& other) = delete;
		DataComponent& operator=(DataComponent&& other) = delete;

	};
}



