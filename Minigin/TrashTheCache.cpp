#include "TrashTheCache.h"
#include <numeric>
#include <chrono>

#include "imgui.h"
#include <imgui_plot.h>

namespace Monke
{
	Monke::TrashTheCache::TrashTheCache(std::weak_ptr<GameObject> parent)
		:RenderComponent(parent)
	{

	}

	void TrashTheCache::OnGUI()
	{
        RenderEx1();
        RenderEx2();
	}

	void TrashTheCache::CalcEx1()
	{
        m_TimesEx1.clear();

        const unsigned int size{ m_AmountSamples * 10 };

        int* buffer = new int[size]{};

        for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
        {
            std::vector<int> vTemp{};

            for (int amountOfTimes{}; amountOfTimes < m_AmountTimesEx1; ++amountOfTimes)
            {
                auto start = std::chrono::high_resolution_clock::now();

                for (unsigned int i{}; i < size; i += stepSize)
                {
                    buffer[i] *= 2;
                }

                auto end = std::chrono::high_resolution_clock::now();
                const int elapsedTime = static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
                vTemp.push_back(elapsedTime);
            }

            for (int amountDeletes{}; amountDeletes < m_AmountTimesEx1/10; ++amountDeletes)
            {
                //min - max erase
                const auto max = std::ranges::max_element(vTemp);
                vTemp.erase(max);
                const auto min = std::ranges::min_element(vTemp);
                vTemp.erase(min);
            }

            //average
            const float average = std::accumulate(vTemp.begin(), vTemp.end(), 0.f) / static_cast<float>(vTemp.size());
            m_TimesEx1.push_back(average);
        }

        delete[] buffer;
	}

	void TrashTheCache::CalcEx2()
	{
        m_TimesEx2.clear();

        const unsigned int size{ m_AmountSamples };

        GameObject3D* buffer = new GameObject3D[size] {};

        for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
        {
            std::vector<int> vTemp{};

            for (int amountOfTimes{}; amountOfTimes < m_AmountTimesEx2; ++amountOfTimes)
            {
                auto start = std::chrono::high_resolution_clock::now();

                for (unsigned int i{}; i < size; i += stepSize)
                {
                    buffer[i].ID *= 2;
                }

                auto end = std::chrono::high_resolution_clock::now();
                const int elapsedTime = static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
                vTemp.push_back(elapsedTime);
            }

            for (int amountDeletes{}; amountDeletes < m_AmountTimesEx2 / 10; ++amountDeletes)
            {
                //min - max erase
                const auto max = std::ranges::max_element(vTemp);
                vTemp.erase(max);
                const auto min = std::ranges::min_element(vTemp);
                vTemp.erase(min);
            }

            //average
            const float average = std::accumulate(vTemp.begin(), vTemp.end(), 0.f) / static_cast<float>(vTemp.size());
            m_TimesEx2.push_back(average);
        }

        delete[] buffer;
	}

	void TrashTheCache::CalcEx2_NoPointer()
	{
        m_TimesEx2_NoPointer.clear();

        const unsigned int size{ m_AmountSamples };

        GameObject3D_NoPointer* buffer = new GameObject3D_NoPointer[size]{};

        for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
        {
            std::vector<int> vTemp{};

            for (int amountOfTimes{}; amountOfTimes < m_AmountTimesEx2; ++amountOfTimes)
            {
                auto start = std::chrono::high_resolution_clock::now();

                for (unsigned int i{}; i < size; i += stepSize)
                {
                    buffer[i].ID *= 2;
                }

                auto end = std::chrono::high_resolution_clock::now();
                const int elapsedTime = static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
                vTemp.push_back(elapsedTime);
            }

            for (int amountDeletes{}; amountDeletes < m_AmountTimesEx2 / 10; ++amountDeletes)
            {
                //min - max erase
                const auto max = std::ranges::max_element(vTemp);
                vTemp.erase(max);
                const auto min = std::ranges::min_element(vTemp);
                vTemp.erase(min);
            }

            //average
            const float average = std::accumulate(vTemp.begin(), vTemp.end(), 0.f) / static_cast<float>(vTemp.size());
            m_TimesEx2_NoPointer.push_back(average);
        }

        delete[] buffer;
	}

	void TrashTheCache::RenderEx1()
	{

        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 20, main_viewport->WorkPos.y + 60));
        ImGui::SetNextWindowSize(ImVec2(280, 400));

        if (!ImGui::Begin("Exercise 1"))
        {
            //when collapsed return
            ImGui::End();
            return;
        }

        ImGui::InputInt("samples", &m_AmountTimesEx1);

        if (ImGui::Button("Trash the cache"))
        {
            CalcEx1();
        }

        if (!m_TimesEx1.empty())
        {
            RenderPlot(m_TimesEx1, 5);
        }

        ImGui::End();
	}

	void TrashTheCache::RenderEx2()
	{

        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 320, main_viewport->WorkPos.y + 60));
        ImGui::SetNextWindowSize(ImVec2(280, 400));

        

        if (!ImGui::Begin("Exercise 2",nullptr, ImGuiWindowFlags_NoScrollbar))
        {
            //when collapsed return
            ImGui::End();
            return;
        }

        ImGui::InputInt("samples", &m_AmountTimesEx2);

        if (ImGui::Button("Trash the cache - Transform"))
        {
            CalcEx2_NoPointer();
        }

        if (!m_TimesEx2_NoPointer.empty())
        {
            RenderPlot(m_TimesEx2_NoPointer, 3);
        }

        if (ImGui::Button("Trash the cache - Transform*"))
        {
            CalcEx2();
        }

        if (!m_TimesEx2.empty())
        {
            RenderPlot(m_TimesEx2, 3);
        }

        if (!m_TimesEx2_NoPointer.empty() && !m_TimesEx2.empty())
        {
            ImGui::Text("Combined:");

            const float* doubleValues[2]{ m_TimesEx2_NoPointer.data(), m_TimesEx2.data() };
            ImU32 colors[2]{ ImColor{ 1.0f, 0.0f, 0.0f }, ImColor{ 0.0f, 1.0f, 0.0f } };

            const ImGui::PlotConfig::Values plotValues{ nullptr, nullptr, static_cast<int>(m_TimesEx2_NoPointer.size()), 0, 0, doubleValues, 2, colors };

            const float maxElement{ *std::ranges::max_element(m_TimesEx2_NoPointer) };

            ImGui::PlotConfig plot{};
            plot.frame_size = ImVec2{ 200, 100 };
            plot.values = plotValues;
            constexpr size_t lineIndex{ 3 };
            plot.v_lines = ImGui::PlotConfig::VerticalLines{ true, &lineIndex, 1 };
            plot.scale = ImGui::PlotConfig::Scale{ 0, maxElement };
            plot.grid_y = ImGui::PlotConfig::Grid{ true, maxElement / 10 };

            ImGui::Plot("doubleplotter", plot);
        }

        ImGui::End();
	}

	void TrashTheCache::RenderPlot(const std::vector<float>& recordedTimes, const size_t verticalLineIndex) const
	{
		const ImGui::PlotConfig::Values plotValues{ nullptr, recordedTimes.data(), static_cast<int>(recordedTimes.size()), 0, ImColor{ 1.0f, 0.5f, 1.0f } };

        const float maxElement{ *std::ranges::max_element(recordedTimes) };

        ImGui::PlotConfig plot{};

        plot.frame_size = ImVec2{ 150, 80 };
        plot.values = plotValues;
        plot.scale = ImGui::PlotConfig::Scale{ 0, maxElement };
        plot.v_lines = ImGui::PlotConfig::VerticalLines{ true, &verticalLineIndex, 1 };
        plot.grid_y = ImGui::PlotConfig::Grid{ true, maxElement / 10 };

		ImGui::Plot("plot", plot);
	}

}


