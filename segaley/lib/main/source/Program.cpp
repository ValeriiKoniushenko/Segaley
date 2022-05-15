#include "Window.h"
#include "DebugActions.h"
#include "Vbo.h"
#include "Vao.h"
#include "Texture2D.h"
#include "Shader.h"
#include "Utils.h"
#include "Image.h"
#include "Sprite.h"

#include "Program.h"

void Program::launch()
{
	setUpShaders();

	draw();
}

void Program::preDraw()
{
	auto& wnd = Window::instance();

	wnd.pollEvents();
	wnd.clearScreen( Window::Buffer::Color, RGBAf( 0.2f, 0.3f, 0.3f, 1.f ) );
}

void Program::draw()
{
	using namespace std::string_literals;


	Sprite::setConfigureShaderCallback( []( auto& program ) {
		program.vertexAttribPointer( "aPos", 3, Gl::DataType::Float, false, 5 * sizeof( float ), ( void* )0 );
		program.vertexAttribPointer( "aTexturePos", 2, Gl::DataType::Float, false, 5 * sizeof( float ), ( void* )( sizeof( float ) * 3 ) );
	} );

	Texture2D texture( true );
	texture.loadFromFile( ASSETS_DIR_NAME + "/images/brickwall.jpg"s );	

	Sprite sprite;
	sprite.setTexture2D( texture );
	while ( Window::instance().isOpen() )
	{
		preDraw();
		sprite.rotate( 0.001f );
		sprite.move( { 0.001f, 0.f } );
		
		sprite.draw( program_ );

		postDraw();
	}
}

void Program::postDraw()
{
	auto& wnd = Window::instance();

	wnd.swapBuffers();
	#ifdef DEBUG
		Gl::requireValidGl();
	#endif
}

void Program::setUpShaders()
{
	using namespace std::string_literals;

	program_.create();

	Shader fragmentShader( Gl::Shader::Vertex, program_ );
	fragmentShader.loadFromFile( ASSETS_DIR_NAME + "/shaders/main.vert"s );
	fragmentShader.compile();

	Shader vertexShader( Gl::Shader::Fragment, program_ );
	vertexShader.loadFromFile( ASSETS_DIR_NAME + "/shaders/main.frag"s );
	vertexShader.compile();

	program_.attachShader( fragmentShader );
	program_.attachShader( vertexShader );
	program_.link();

}
