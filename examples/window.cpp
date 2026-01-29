//
// Created by kassie on 21/01/2026.
//

#include <GAL/gal.hpp>

int main()
{
	gal::init();

	gal::Window window{800, 600, "Window Example"};
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	while (!window.shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		window.swapBuffers();
		window.pollEvents();
	}

	gal::terminate();
	return 0;
}