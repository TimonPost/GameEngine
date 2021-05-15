#include "epch.h"
#include "OpenGLContext.h"

#include "Engine/Core.h"
#include "Engine/Log.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace  Engine
{
	OpenGLContext::OpenGLContext(struct GLFWwindow* windowHandle): _windowHandle(windowHandle)
	{
	
	}

	inline void OpenGLContext::Init()
	{
		/* Make the window's context current */
		glfwMakeContextCurrent(_windowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_CORE_ASSERT(status, "Failed to initialize glad!")

		int major;
		int minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);

		ENGINE_CORE_INFO("OpenGL Info: ")
		ENGINE_CORE_INFO("	Vendor: {0}", glGetString(GL_VENDOR))
		ENGINE_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER))
		ENGINE_CORE_INFO("	Version: {0}", glGetString(GL_VERSION))
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(_windowHandle);
	}
}
