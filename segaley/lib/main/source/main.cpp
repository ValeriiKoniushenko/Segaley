#include "Window.h"
#include "DebugActions.h"
#include "Vbo.h"
#include "Vao.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Utils.h"
#include "Image.h"

#include <iostream>

void launch()
{
	using namespace std::string_literals;

	ShaderProgram program( true );

	Shader fragmentShader( Gl::Shader::Vertex, program );
	fragmentShader.loadFromFile( ASSETS_DIR_NAME + "/shaders/main.vert"s );
	fragmentShader.compile();

	Shader vertexShader( Gl::Shader::Fragment, program );
	vertexShader.loadFromFile( ASSETS_DIR_NAME + "/shaders/main.frag"s );
	vertexShader.compile();

	program.attachShader( fragmentShader );
	program.attachShader( vertexShader );
	program.link();

	program.use();

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

	program.vertexAttribPointer( "aPos", 3, Gl::DataType::Float, false, 5 * sizeof( float ), ( void* )0 );
	program.vertexAttribPointer( "aTexturePos", 2, Gl::DataType::Float, false, 5 * sizeof( float ), ( void* )( sizeof( float ) * 3 ) );

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
}

int main()
{
	try
	{
		#ifdef DEBUG
		DebugActions::copyAssets();
		#endif

		Window::instance();

		launch();
	}
	catch ( const std::runtime_error& ex )
	{
		std::cout << "Fatal error: " << ex.what() << std::endl;
	}
	catch ( const std::out_of_range& ex )
	{
		std::cout << "Our of range: " << ex.what() << std::endl;
	}

	return 0;
}
