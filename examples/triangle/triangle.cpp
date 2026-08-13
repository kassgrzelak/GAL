//
// Created by kassie on 12/08/2026.
//

#include "GAL/gal.hpp"

int main()
{
	// Initialize the gal library.
	gal::init();

	// Create the window, as well as an OpenGL context to go with it.
	gal::Window window{800, 600, "Triangle Example"};
	// Make the window's OpenGL context current and do more gal initialization that can only be done with a context.
	window.makeContextCurrent();
	// Set the viewport to cover the entire window.
	window.setFullViewport();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	
	// Compile shaders.
	gal::Shader vertexShader{gal::ShaderType::Vertex};
	vertexShader.sourceFile("assets/shaders/vert.vert");
	vertexShader.compile();
	
	gal::Shader fragmentShader{gal::ShaderType::Fragment};
	fragmentShader.sourceFile("assets/shaders/frag.frag");
	fragmentShader.compile();
	
	// Attach shaders and link program.
	gal::Program shaderProgram;
	
	shaderProgram.attachShader(vertexShader);
	shaderProgram.attachShader(fragmentShader);
	
	shaderProgram.link();
	shaderProgram.use();
	
	// Destroy unneeded shaders.
	vertexShader.destroy();
	fragmentShader.destroy();
	
	// Triangle vertices.
	const std::vector vertices = {
		-0.5f, -0.5f, 0.0f, // left
		 0.5f, -0.5f, 0.0f, // right
		 0.0f,  0.5f, 0.0f  // top
	};
	
	// Allocate and write vertex data to vertex buffer.
	gal::Buffer vertexBuffer;
	vertexBuffer.allocateAndWrite(vertices, gal::BufferUsage::StaticDraw);

	// Bind vertex data to vertex array object and define position attribute.
	gal::VertexArray vertexArray;
	vertexArray.bindVertexBuffer(vertexBuffer, 0, 0, 3 * sizeof(float));
	vertexArray.vertexAttributeFormat(0, 0, 3, GL_FLOAT, false, 0);
	vertexArray.bind();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// Window loop.
	while (!window.shouldClose())
	{
		window.pollEvents(); // Poll for window events (button presses, pressing the close button, etc.).
		
		glClear(GL_COLOR_BUFFER_BIT);
		// Draw triangle.
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		window.swapBuffers(); // Swap window buffers (i.e., update the screen).
	}

	// Free all of gal's allocated resources.
	gal::terminate();
	return 0;
}