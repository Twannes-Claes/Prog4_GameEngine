#pragma once

#include "BaseComponent.h"

namespace Monke
{
	class DataComponent : public BaseComponent
	{

	public:

		explicit DataComponent(const std::weak_ptr<GameObject>& pParent);

		virtual ~DataComponent() override = default;

		DataComponent(const DataComponent& other) = delete;
		DataComponent(DataComponent&& other) = delete;
		DataComponent& operator=(const DataComponent& other) = delete;
		DataComponent& operator=(DataComponent&& other) = delete;

	};
}



