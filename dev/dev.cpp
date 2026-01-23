//
// Created by kassie on 21/01/2026.
//

#define GAL_VERBOSE
#define GAL_DEV_TESTING

#include <glad/glad.h>
#include <GAL/gal.hpp>

int main()
{
	glfwInit();
	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

	{
		gal::Window window{};

		while (!window.shouldClose())
		{
			glfwPollEvents();
		}

		gal::detail::resourceRegistry.destroyAll();
	}

	return 0;
}
