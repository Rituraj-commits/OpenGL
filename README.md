# OpenGL
This project implements a menu-based GUI for testing the Color Rendering and Texture Rendering in OpenGL 3.x.

Abstraction is used to make the code more cleaner and tight.

Libraries used in this project are:

# GLFW
# GLEW
# ImGui
# STBI
# GLM

System using two GPU's such as NVidea/AMD , the code will be run on the Integrated Graphics by default.

To use the Dedicated GPU just paste the following MSVC code before the main() in the Application.cpp

# For NVIDIA

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

# For AMD Radeon

extern "C"
{
  __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
