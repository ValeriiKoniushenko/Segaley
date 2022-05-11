#include "Window.h"
#include "DebugActions.h"
#include "Vbo.h"
#include "Vao.h"
#include "Texture2D.h"
#include "Utils.h"
#include "Image.h"

#include <iostream>

void launch()
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
	Gl::detachShader( shaderProgram, fragmentShader );

	Gl::useProgram( shaderProgram );

	Vbo vbo( Gl::Vbo::Target::Array, true );
	Vao vao( true );
	
	vbo.bufferData( std::vector< float >{
		-0.5f, -0.5f, 0.0f,	  0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,	  1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,   0.5f, 1.0f
	}, Gl::Vbo::DrawType::StaticDraw );

	Texture2D texture( true );
	texture.loadFromFile( ASSETS_DIR_NAME + "/images/brickwall.jpg"s );
	texture.setWrapS( Gl::Texture::Wrap::Repeat );
	texture.setWrapT( Gl::Texture::Wrap::Repeat );
	texture.setMinFilter( Gl::Texture::MinFilter::Nearest );
	texture.setMagFilter( Gl::Texture::MagFilter::Nearest );
	texture.generateMipmap();

	Texture2D texture2( true );
	texture2.loadFromFile( ASSETS_DIR_NAME + "/images/gravel.jpg"s );
	texture2.setWrapS( Gl::Texture::Wrap::Repeat );
	texture2.setWrapT( Gl::Texture::Wrap::Repeat );
	texture2.setMinFilter( Gl::Texture::MinFilter::Nearest );
	texture2.setMagFilter( Gl::Texture::MagFilter::Nearest );
	texture2.generateMipmap();	

	Gl::vertexAttribPointer( 0, 3, Gl::DataType::Float, false, 5 * sizeof( float ), ( void* )0 );
	Gl::vertexAttribPointer( 1, 2, Gl::DataType::Float, false, 5 * sizeof( float ), ( void* )( sizeof( float ) * 3 ) );
	Gl::enableVertexAttribArray( 0 );
	Gl::enableVertexAttribArray( 1 );

	auto& wnd = Window::instance();
	while ( wnd.isOpen() )
	{
		wnd.pollEvents();
		wnd.clearScreen( Window::Buffer::Color, RGBAf( 0.2f, 0.3f, 0.3f, 1.f ) );

		Gl::drawArrays( Gl::DrawMode::Triangles, 0, 3 );

		wnd.swapBuffers();
		#ifdef DEBUG
		Gl::requireValidGl();
		#endif
	}

	Gl::deleteProgram( shaderProgram );
}

int main()
{
	try
	{
		launch();
	}
	catch ( const std::runtime_error& ex )
	{
		std::cout << "Fatal error: " << ex.what() << std::endl;
	}

	return 0;
}
