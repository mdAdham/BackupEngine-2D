#include "bcpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BackupEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		//BC_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		//BC_CORE_ASSERT(status, "Failed to initialize Glad!");
		//
		//BC_CORE_INFO("OpenGL Info:");
		//BC_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR));
		//BC_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		//BC_CORE_INFO("	Version: {0}", glGetString(GL_VERSION));
		//
		//BC_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "BackupEngine requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}