#pragma once
#include <memory>
#include <glm/vec2.hpp>

namespace Monke
{
	class Gamepad final
	{

	public:

		enum class GamepadButton
		{
			DPad_Up = 0x0001,
			DPad_Down = 0x0002,
			DPad_Left = 0x0004,
			Dpad_Right = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			Left_Joystick = 0x0040,
			Right_Joystick = 0x0080,
			Left_Shoulder = 0x0100,
			Right_Shoulder = 0x0200,
			Button_South = 0x1000,
			Button_East = 0x2000,
			Button_West = 0x4000,
			Button_North = 0x8000,
		};

		//big six
		explicit Gamepad(const unsigned int gamepadIndex);

		~Gamepad();

		Gamepad(const Gamepad&) = delete;
		Gamepad(Gamepad&&) = delete;
		Gamepad& operator= (const Gamepad&) = delete;
		Gamepad& operator= (const Gamepad&&) = delete;

		void Update();

		bool IsDown(const GamepadButton button) const;

		bool IsUp(const GamepadButton button) const;

		bool IsPressed(const GamepadButton button) const;

		glm::vec2 GetAxis(const GamepadButton button) const;

	private:

		class GamepadImple;

		std::unique_ptr<GamepadImple> m_pImpl ;

	};
}



