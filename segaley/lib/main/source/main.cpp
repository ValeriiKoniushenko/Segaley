#include "Window.h"
#include "DebugActions.h"
#include "Vbo.h"
#include "Vao.h"
#include "Texture2D.h"
#include "Shader.h"
#include "Utils.h"
#include "Image.h"

#include <iostream>

void launch()
{
	#ifdef DEBUG
	DebugActions::copyAssets();
	#endif

	Window::instance();

	using namespace std::string_literals;

	auto program = Gl::createProgram();

	Shader fragmentShader( Gl::Shader::Vertex, program );
	fragmentShader.loadFromFile( ASSETS_DIR_NAME + "/shaders/main.vert"s );
	fragmentShader.compile();

	Shader vertexShader( Gl::Shader::Fragment, program );
	vertexShader.loadFromFile( ASSETS_DIR_NAME + "/shaders/main.frag"s );
	vertexShader.compile();

	Gl::attachShader( program, vertexShader.data() );
	Gl::attachShader( program, fragmentShader.data() );
	Gl::linkProgram( program );

	Gl::useProgram( program );

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

	Gl::deleteProgram( program );
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
