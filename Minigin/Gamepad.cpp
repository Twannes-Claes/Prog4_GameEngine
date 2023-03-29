#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "xinput.lib")

#include "Gamepad.h"
#include  <cmath>

namespace Monke
{

	class Gamepad::GamepadImple
	{

	public:

		explicit GamepadImple(const unsigned int controllerIndex)
		:m_ControllerIndex(controllerIndex)
		{
			ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		}

		~GamepadImple() = default;

		GamepadImple(const GamepadImple&) = delete;
		GamepadImple(GamepadImple&&) = delete;
		GamepadImple& operator= (const GamepadImple&) = delete;
		GamepadImple& operator= (const GamepadImple&&) = delete;

		void Update()
		{
			CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

			XInputGetState(m_ControllerIndex, &m_CurrentState);

			const auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;

			m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
			m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
		}

		bool IsDown(const unsigned int button) const
		{
			return m_ButtonsPressedThisFrame & button;
		}

		bool IsUp(const unsigned int button) const
		{
			return m_ButtonsReleasedThisFrame & button;
		}

		bool IsPressed(const unsigned int button) const
		{
			return m_CurrentState.Gamepad.wButtons & button;
		}

		glm::vec2 GetAxis(const bool isLeftJoyStick)
		{
			return
		{
					(isLeftJoyStick ? m_CurrentState.Gamepad.sThumbLX : m_CurrentState.Gamepad.sThumbRX),
					(isLeftJoyStick ? m_CurrentState.Gamepad.sThumbLY : m_CurrentState.Gamepad.sThumbRY)
			};
		}

		void DeadZoneClamp(float& input) const
		{
			const float absInput { abs(input) };

			if (absInput <= m_Deadzone)
			{
				input = 0.f;
				return;
			}

			if(absInput > m_CeilZone)
			{
				if (input < 0) input = -1.f;
				else input = 1.f;
				return;
			}

			//value between 0 and 1 between deadzone and ceilzone
			input = input / m_CeilZone;
		}

	private:

		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};

		WORD m_ButtonsPressedThisFrame{};
		WORD m_ButtonsReleasedThisFrame{};

		const unsigned int m_ControllerIndex;

		//float m_Deadzone{};
		const float m_Deadzone{0.2f * MAXSHORT};
		const float m_CeilZone{0.9f * MAXSHORT};
	};

	Gamepad::Gamepad(const unsigned gamepadIndex)
	{
		//m_pImpl = new GamepadImple(gamepadIndex);
		m_pImpl = std::make_unique<GamepadImple>(gamepadIndex);
	}

	Gamepad::~Gamepad() = default;

	void Gamepad::Update()
	{
		m_pImpl->Update();
	}
	
	bool Gamepad::IsDown(const GamepadButton button) const
	{
		return m_pImpl->IsDown(static_cast<unsigned int>(button));
	}
	
	bool Gamepad::IsUp(const GamepadButton button) const
	{
		return m_pImpl->IsUp(static_cast<unsigned int>(button));
	}
	
	bool Gamepad::IsPressed(const GamepadButton button) const
	{
		return m_pImpl->IsPressed(static_cast<unsigned int>(button));
	}

	glm::vec2 Gamepad::GetAxis(const GamepadButton button) const
	{
		glm::vec2 input = m_pImpl->GetAxis(button == GamepadButton::Left_Joystick);

		m_pImpl->DeadZoneClamp(input.x);
		m_pImpl->DeadZoneClamp(input.y);

		input.y *= -1;

		return input;
	}
}
