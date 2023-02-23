#pragma once

#include "BaseComponent.h"

namespace Monke
{
	class UpdateComponent : public BaseComponent
	{
		public:

		explicit UpdateComponent(std::weak_ptr<GameObject>& pParent);

		virtual void Update() = 0;

		//	todo: make new updates

		//virtual void LateUpdate() = 0;
		//virtual void FixedUpdate() = 0;


		virtual ~UpdateComponent() override = default;

		UpdateComponent(const UpdateComponent& other) = delete;
		UpdateComponent(UpdateComponent&& other) = delete;
		UpdateComponent& operator=(const UpdateComponent& other) = delete;
		UpdateComponent& operator=(UpdateComponent&& other) = delete;
	};
}