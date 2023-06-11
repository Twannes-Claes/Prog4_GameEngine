#pragma once
#include <memory>
#include <glm/vec2.hpp>

#include <functional>

namespace Monke
{
	class Transform;
	class GameObject;

	class Command
	{

	public:

		explicit Command() = default;
		virtual ~Command() = default;

		virtual void Execute() = 0;

		Command(const Command&) = delete;
		Command(Command&&) = delete;
		Command& operator= (const Command&) = delete;
		Command& operator= (const Command&&) = delete;

	};

	class AxisCommand : public Command
	{

	public:

		explicit AxisCommand() = default;
		virtual ~AxisCommand() override = default;

		virtual void Execute() override = 0;

		void SetInput(const glm::vec2& input) { m_Input = input; }

		AxisCommand(const AxisCommand&) = delete;
		AxisCommand(AxisCommand&&) = delete;
		AxisCommand& operator= (const AxisCommand&) = delete;
		AxisCommand& operator= (const AxisCommand&&) = delete;

	protected:

		glm::vec2& GetInput() { return m_Input; }

	private:

		glm::vec2 m_Input{};

	};

	class FunctionCommand : public Command
	{
	public:

		explicit FunctionCommand(const std::function<void()>& function):m_FunctionCall(function){}
		virtual ~FunctionCommand() override = default;

		virtual void Execute() override
		{
			m_FunctionCall();
		}

		FunctionCommand(const FunctionCommand&) = delete;
		FunctionCommand(FunctionCommand&&) = delete;
		FunctionCommand& operator= (const FunctionCommand&) = delete;
		FunctionCommand& operator= (const FunctionCommand&&) = delete;

	private:

		std::function<void()> m_FunctionCall{};

	};
}



