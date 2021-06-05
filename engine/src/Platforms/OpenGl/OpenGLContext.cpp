#include "epch.h"
#include "OpenGLContext.h"

#include "Engine/Core/Core.h"
#include "Engine/Core/Log.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace  Engine
{
	OpenGLContext::OpenGLContext(struct GLFWwindow* windowHandle): _windowHandle(windowHandle)
	{
	
	}

	inline void OpenGLContext::Init()
	{
		ENGINE_PROFILE_FUNCTION();
		
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

			ENGINE_ASSERT((major > 4 || (major == 4 && minor >= 5)), "Engine requires at least OpenGL version 4.5!")
	}

	void OpenGLContext::SwapBuffers()
	{
		ENGINE_PROFILE_FUNCTION();
		glfwSwapBuffers(_windowHandle);
	}
}
