
#include "Window.h"
#include "DebugActions.h"
#include "Gl.h"
#include "Utils.h"

#include <iostream>

int main()
{
	DebugActions::copyAssets();

	Window::instance();

	GLuint vertexShader = Gl::createShader( Gl::Shader::Vertex );
	auto vertexShaderSource = utils::getFileContent( "shaders/main.vert" );
	Gl::shaderSource( vertexShader, 1, vertexShaderSource );
	Gl::compileShader( vertexShader );

	float verticies[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	GLuint vbo;
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( verticies ), verticies, GL_STATIC_DRAW );

	auto& wnd = Window::instance();
	while ( wnd.isOpen() )
	{
		wnd.pollEvents();
		wnd.clearScreen( Window::Buffer::Color, RGBAf( 0.2f, 0.3f, 0.3f, 1.f ) );
		
		

		wnd.swapBuffers();
	}

	return 0;
}
