#include "Test.h"
#include "vendor/imgui/imgui.h"

namespace test {
	TestMenu::TestMenu(Test *& m_CurrentTestPointer)
		:m_Current_Test(m_CurrentTestPointer)
	{

	}

	
	void TestMenu::OnImguiRender()
	{
		for (auto &test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_Current_Test = test.second();
			}
		}
	}

}

