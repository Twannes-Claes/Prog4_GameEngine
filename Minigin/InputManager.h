#pragma once
#include "Singleton.h"

namespace Monke
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
