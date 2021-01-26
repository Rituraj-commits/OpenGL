#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include"texture.h"

#include"vendor/glm/glm.hpp"
#include"vendor/glm/gtc/matrix_transform.hpp"

#include"vendor/imgui/imgui.h"
#include"vendor/imgui/imgui_impl_glfw_gl3.h"

#include "test/testClearColor.h"
#include "test/testTexture2D.h"

/* Deploy the code in the NVidea GPU */
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}




int main(void)
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);

	if (!window)
	{

		glfwTerminate();
		return -1;
	}

	
	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (GLEW_OK != glewInit()) {
		std::cout << "Error" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		
		
		Renderer renderer;

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		
		test::Test* CurrentTest=nullptr;
		test::TestMenu* menu = new test::TestMenu(CurrentTest);
		CurrentTest = menu;

		menu->RegisterTest<test::TestClearColor>("Clear Color");
		menu->RegisterTest<test::TestTexture2D>("2D Texture");




		

		
		


		


		

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			GLLogCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

			/* Render here */
			renderer.Clear();

			

			ImGui_ImplGlfwGL3_NewFrame();
			
			if (CurrentTest)
			{
				CurrentTest->OnUpdate(0.0f);
				CurrentTest->OnRender();
				ImGui::Begin("Test");
				if (CurrentTest != menu && ImGui::Button("<-"))
				{
					delete CurrentTest;
					CurrentTest = menu;

				}
				CurrentTest->OnImguiRender();
				ImGui::End();

			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());






			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		delete CurrentTest;
		if (CurrentTest != menu)
		{
			delete menu;
		}

		
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}