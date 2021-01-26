#include "testClearColor.h"


#include "Renderer.h"
#include "vendor/imgui/imgui.h"

test::TestClearColor::TestClearColor(): m_ClearColor{ 0.2f,0.3,0.8f,1.0f }
{


}

test::TestClearColor::~TestClearColor()
{
}

void test::TestClearColor::OnUpdate(float deltatime)
{
}

void test::TestClearColor::OnRender()
{
	GLLogCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	GLLogCall(glClear(GL_COLOR_BUFFER_BIT));

}

void test::TestClearColor::OnImguiRender()
{
	ImGui::ColorEdit4("Clear Color", m_ClearColor);

}
