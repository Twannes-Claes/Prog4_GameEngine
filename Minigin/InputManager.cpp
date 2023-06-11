#include "InputManager.h"
#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>

bool Monke::InputManager::ProcessInput()
{

	//update all controllers
	for (size_t i = 0; i < m_Gamepads.size(); ++i)
	{
		m_Gamepads[i]->Update();
	}

	for(const auto& command : m_ControllerCommands)
	{
		bool canExecute{false};

		switch(command.first.type)
		{
			case InputType::OnDown:
			{
				canExecute = m_Gamepads[command.first.id]->IsDown(command.first.buttons[0]);
			}
			break;
			case InputType::OnRelease:
			{
				canExecute = m_Gamepads[command.first.id]->IsUp(command.first.buttons[0]);
			}
			break;
			case InputType::OnPress:
			{
				canExecute = m_Gamepads[command.first.id]->IsPressed(command.first.buttons[0]);
			}
			break;
			case InputType::Axis:
			{
				AxisCommand* axis = dynamic_cast<AxisCommand*>(command.second.get());

				glm::vec2 inputAxis{};

				if(command.first.buttons.size() > 1)
				{
					int index{ -1 };

					inputAxis.y -= static_cast<float>(m_Gamepads[command.first.id]->IsPressed(command.first.buttons[++index]));
					inputAxis.x += static_cast<float>(m_Gamepads[command.first.id]->IsPressed(command.first.buttons[++index]));
					inputAxis.y += static_cast<float>(m_Gamepads[command.first.id]->IsPressed(command.first.buttons[++index]));
					inputAxis.x -= static_cast<float>(m_Gamepads[command.first.id]->IsPressed(command.first.buttons[++index]));
				}
				else
				{
					inputAxis = m_Gamepads[command.first.id]->GetAxis(command.first.buttons[0]);
				}


				axis->SetInput(inputAxis);

				//std::cout << inputAxis.x << "  -  " << inputAxis.y << '\n';

				canExecute = true;
				
			}
			break;
		}

		if (canExecute)
		{
			command.second->Execute();

			if (m_ClearCommands) break;
		}
	}

	m_ClearCommands = false;

	//update keyboard

	//clear keys down and keys released
		m_KeysDown.clear();
	m_KeysReleased.clear();

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}

		const SDL_Keycode key = e.key.keysym.sym;

		//fill in keyboard state keys

		if (e.type == SDL_KEYDOWN)
		{
			m_KeysDown.insert(key);
			m_KeysPressed.insert(key);
		}
		if (e.type == SDL_KEYUP)
		{
			m_KeysReleased.insert(key);
			m_KeysPressed.erase(key);
		}
		if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
		{
			m_KeysPressed.clear();
		}
		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	for (const auto& command : m_KeyboardCommands)
	{
		bool canExecute{};
		switch (command.first)
		{
			case InputType::OnDown:
			{
				canExecute = m_KeysDown.contains(command.second.first[0]);
			}
			break;
			case InputType::OnRelease:
			{
				canExecute = m_KeysReleased.contains(command.second.first[0]);
			}
			break;
			case InputType::OnPress:
			{
				canExecute = m_KeysPressed.contains(command.second.first[0]);
			}
			break;
			case InputType::Axis:
			{
				AxisCommand* axis = dynamic_cast<AxisCommand*>(command.second.second.get());

				glm::vec2 inputAxis{};

				int index{ -1 };

				inputAxis.y -= static_cast<float>(m_KeysPressed.contains(command.second.first[++index]));
				inputAxis.x += static_cast<float>(m_KeysPressed.contains(command.second.first[++index]));
				inputAxis.y += static_cast<float>(m_KeysPressed.contains(command.second.first[++index]));
				inputAxis.x -= static_cast<float>(m_KeysPressed.contains(command.second.first[++index]));

				axis->SetInput(inputAxis);

				canExecute = true;
			}
			break;
		}

		if (canExecute) command.second.second->Execute();

		if (m_ClearCommands) break;
	}

	m_ClearCommands = false;

	return true;
}

void Monke::InputManager::ClearCommands()
{
	m_ControllerCommands.clear();

	m_KeyboardCommands.clear();

	m_ClearCommands = true;
}
