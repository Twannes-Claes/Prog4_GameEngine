#pragma once

#include "BaseComponent.h"

namespace Monke
{
	class UpdateComponent : public BaseComponent
	{

	public:

		UpdateComponent() = default;
		virtual ~UpdateComponent() override = default;

		virtual void Initialize() override = 0;
		virtual void Update() = 0;

		//	todo: make new updates
		//virtual void LateUpdate() = 0;
		//virtual void FixedUpdate() = 0;

		UpdateComponent(const UpdateComponent& other) = delete;
		UpdateComponent(UpdateComponent&& other) = delete;
		UpdateComponent& operator=(const UpdateComponent& other) = delete;
		UpdateComponent& operator=(UpdateComponent&& other) = delete;

	};
}