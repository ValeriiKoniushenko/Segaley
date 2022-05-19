#include "Window.h"
#include "DebugActions.h"
#include "Vbo.h"
#include "Vao.h"
#include "Texture2D.h"
#include "Shader.h"
#include "Utils.h"
#include "Image.h"
#include "Sprite.h"
#include "Camera3D.h"

#include "Program.h"

#include <iostream>

void Program::launch()
{
	setUpShaders();

	Window::instance().disableCursor();

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

	Camera3D camera;

	Window::instance().setMousePosEventCallback( [ &camera ]( float x, float y ){
		static auto last = glm::vec2( x, y );

		auto delta = glm::vec2( x, y ) - last;
		delta /= glm::vec2( 400.f, 500.f );

		camera.rotate( { delta.y, delta.x } );

		last = glm::vec2( x, y );
	} );

	Texture2D texture( true );
	texture.loadFromFile( ASSETS_DIR_NAME + "/images/brickwall.jpg"s );	

	Sprite sprite;
	sprite.setTexture2D( texture );

	while ( Window::instance().isOpen() )
	{
		preDraw();

		sprite.draw( program_, camera );

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
	program_.setup( ASSETS_DIR_NAME + "/shaders/main.vert"s, ASSETS_DIR_NAME + "/shaders/main.frag"s );
}
