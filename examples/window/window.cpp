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
	// Make the window's OpenGL context current and do more gal initialization that can only be done with a context.
	window.makeContextCurrent();
	// Set the viewport to cover the entire window.
	window.setFullViewport();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Window loop.
	while (!window.shouldClose())
	{
		window.pollEvents(); // Poll for window events (button presses, pressing the close button, etc.).
		glClear(GL_COLOR_BUFFER_BIT);
		window.swapBuffers(); // Swap window buffers (i.e., update the screen).
	}

	// Free all of gal's allocated resources.
	gal::terminate();
	return 0;
}