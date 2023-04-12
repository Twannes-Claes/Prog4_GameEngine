#pragma once
#include <vector>

#include "BaseComponent.h"

namespace Monke
{
	class TrashTheCache final : public BaseComponent
	{
	public:

		explicit TrashTheCache(std::weak_ptr<GameObject> parent);
		virtual ~TrashTheCache() override = default;

		virtual void Initialize() override {}

		TrashTheCache(const TrashTheCache& other) = delete;
		TrashTheCache(TrashTheCache&& other) = delete;
		TrashTheCache& operator=(const TrashTheCache& other) = delete;
		TrashTheCache& operator=(TrashTheCache&& other) = delete;

		virtual void OnGUI() override;

		virtual void Render() const override {}

	private:

		void CalcEx1();
		void CalcEx2();
		void CalcEx2_NoPointer();

		void RenderEx1();
		void RenderEx2();

		void RenderPlot(const std::vector<float>& recordedTimes, const size_t verticalLineIndex) const;

		struct Transform
		{
			float matrix[16] =
			{
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1
			};
		};

		class GameObject3D_NoPointer
		{
		public:
			Transform transform{};
			int ID{};
		};

		class GameObject3D
		{
		public:
			Transform* transform{};
			int ID{};
		};

		int m_AmountTimesEx1{ 10 };
		int m_AmountTimesEx2{ 10 };

		const unsigned int m_AmountSamples{ 1'000'000 };

		std::vector<float> m_TimesEx1{};
		std::vector<float> m_TimesEx2{};
		std::vector<float> m_TimesEx2_NoPointer{};

	};

}


