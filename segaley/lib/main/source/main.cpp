
#include "Window.h"
#include "DebugActions.h"
#include "Gl.h"
#include "Utils.h"

#include <iostream>

int main()
{
	DebugActions::copyAssets();

	Window::instance();

	using namespace std::string_literals;

	auto vertexShader = Gl::createShader( Gl::Shader::Vertex );
	auto vertexShaderSource = utils::getFileContent( ASSETS_DIR_NAME + "/shaders/main.vert"s );
	Gl::shaderSource( vertexShader, 1, vertexShaderSource );
	Gl::compileShader( vertexShader );

	auto fragmentShader = Gl::createShader( Gl::Shader::Fragment );
	auto fragmentShaderSource = utils::getFileContent( ASSETS_DIR_NAME + "/shaders/main.frag"s );
	Gl::shaderSource( fragmentShader, 1, fragmentShaderSource );
	Gl::compileShader( fragmentShader );

	auto shaderProgram = Gl::createProgram();

	Gl::attachShader( shaderProgram, vertexShader );
	Gl::attachShader( shaderProgram, fragmentShader );
	Gl::linkProgram( shaderProgram );
	
	Gl::deleteShader( shaderProgram, vertexShader );
	Gl::deleteShader( shaderProgram, fragmentShader );
	Gl::detachShader( shaderProgram, vertexShader );
	Gl::detachShader( shaderProgram, fragmentShader);

	float verticies[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	auto vbo = Gl::Vbo::generate();
	Gl::Vbo::bind( Gl::Vbo::Target::Array, vbo );
	Gl::Vbo::bufferData( Gl::Vbo::Target::Array, sizeof( verticies ), verticies, Gl::Vbo::DrawType::StaticDraw );

	GLuint vao = Gl::Vao::generate();
	Gl::Vao::bind( vao );

	Gl::vertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void* )0 );
	Gl::enableVertexAttribArray( 0 );


	auto& wnd = Window::instance();
	while ( wnd.isOpen() )
	{
		wnd.pollEvents();
		wnd.clearScreen( Window::Buffer::Color, RGBAf( 0.2f, 0.3f, 0.3f, 1.f ) );
		
		Gl::drawArrays( Gl::DrawMode::Triangles, 0, 3 );

		wnd.swapBuffers();
	}

	Gl::deleteProgram( shaderProgram );
	Gl::Vbo::deleteBuffer( vbo );
	Gl::Vao::deleteBuffer( vao );

	return 0;
}
