#pragma once

#include "Command.h"
#include "Gamepad.h"
#include "Singleton.h"
#include <map>
#include <vector>
#include <set>
#include <stdexcept>


namespace Monke
{

	class InputManager final : public Singleton<InputManager>
	{

	public:

		enum class InputType
		{
			OnDown,
			OnRelease,
			OnPress,
			Axis
		};

		bool ProcessInput();

		//controller addcommand
		template <class T>
		T* AddCommand(const unsigned int id, Gamepad::GamepadButton button, InputType inputType, GameObject* pGameObject)
		{
			static_assert(std::is_base_of<Command, T>(), "T needs to be derived from command");

			if(id >= static_cast<unsigned int>(m_Gamepads.size()))
			{
				m_Gamepads.push_back( std::make_unique<Gamepad>(static_cast<unsigned int>(m_Gamepads.size())));
			}

			ControllerInfo controller
			{
				std::vector{button},
				inputType,
				static_cast<unsigned int>(m_Gamepads.size()-1)
			};

			//todo do constructor shit here

			auto command = std::make_unique<T>(pGameObject);

			auto cache = command.get();

			m_ControllerCommands.emplace(controller, std::move(command));

			return cache;
		}

		template <class T>
		T* AddCommand(const unsigned int id, Gamepad::GamepadButton up, Gamepad::GamepadButton right, Gamepad::GamepadButton bottom, Gamepad::GamepadButton left, GameObject* pGameObject)
		{

			static_assert(std::is_base_of<AxisCommand, T>(), "T needs to be derived from axiscommand");

			if (id >= static_cast<unsigned int>( m_Gamepads.size()))
			{
				m_Gamepads.push_back(std::make_unique<Gamepad>(static_cast<unsigned int>(m_Gamepads.size())));
			}

			ControllerInfo controller
			{
				std::vector{up, right, bottom, left},
				InputType::Axis,
				static_cast<unsigned int>(m_Gamepads.size() - 1)
			};

			auto command = std::make_unique<T>(pGameObject);

			auto cache = command.get();

			m_ControllerCommands.emplace(controller, std::move(command));

			return cache;
		}

		//keyboard addcommand
		template <class T>
		T* AddCommand(const unsigned int keyValue, InputType inputType, GameObject* pGameObject)
		{
			static_assert(std::is_base_of<Command, T>(), "T needs to be derived from command");

			if (inputType == InputType::Axis)
			{
				throw std::invalid_argument("Cannot use axis with one value in AddCommand on keyboard");
			}

			auto command = std::make_unique<T>(pGameObject);

			auto cache = command.get();

			m_KeyboardCommands.emplace(inputType, std::make_pair(std::vector{ keyValue }, std::move(command)));

			return cache;
		}

		template <class T>
		T* AddCommand(const unsigned int keyUp, const unsigned int keyRight, const unsigned int keyDown, const unsigned int keyLeft, GameObject* pGameObject)
		{
			static_assert(std::is_base_of<Command, T>(), "T needs to be derived from command");

			auto command = std::make_unique<T>(pGameObject);

			auto cache = command.get();

			m_KeyboardCommands.emplace(InputType::Axis,  std::make_pair( std::vector{ keyUp, keyRight, keyDown, keyLeft }, std::move(command)));

			return cache;
		}

	private:

		//controllers
		struct ControllerInfo
		{
			std::vector<Gamepad::GamepadButton> buttons;
			InputType type;
			unsigned int id;

			//added operator to disable error
			bool operator<(const ControllerInfo& other) const { return other.id < id; }
		};

		using ControllerCommandsMap = std::multimap<ControllerInfo, std::unique_ptr<Command>>;

		ControllerCommandsMap m_ControllerCommands{};

		std::vector<std::unique_ptr<Gamepad>> m_Gamepads{};


		//keyboards
		using KeyboardInfo = std::pair<std::vector<unsigned int>, std::unique_ptr<Command>>;

		using KeyboardCommandsMap = std::multimap<InputType, KeyboardInfo>;

		KeyboardCommandsMap m_KeyboardCommands{};

		std::set<unsigned int> m_KeysDown{};
		std::set<unsigned int> m_KeysReleased{};
		std::set<unsigned int> m_KeysPressed{};
	};

}
