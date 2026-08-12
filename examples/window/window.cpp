//
// Created by kassie on 21/01/2026.
//

#include <GAL/gal.hpp>

int main()
{
	// Initialize the gal library.
	gal::init();

	// Create the window, as well as an OpenGL context to go with it.
	gal::Window window{800, 600, "Window Example"};
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Window loop.
	while (!window.shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		window.swapBuffers(); // Swap window buffers (i.e., update the screen).
		window.pollEvents(); // Poll for window events (button presses, pressing the close button, etc.).
	}

	// Free all of gal's allocated resources.
	gal::terminate();
	return 0;
}