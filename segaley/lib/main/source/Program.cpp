#include "Program.h"

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
#include "Font.h"
#include "Text.h"
#include "Rectangle.h"

#include <iostream>
#include <map>

void Program::launch()
{
	setUpShaders();

	Window::instance().disableCursor();

	Sprite::setConfigureShaderCallback( []( auto& program ) {
		program.vertexAttribPointer( "aPos", 3, Gl::DataType::Float, false, 5 * sizeof( float ), ( void* )0 );
		program.vertexAttribPointer( "aTexturePos", 2, Gl::DataType::Float, false, 5 * sizeof( float ), ( void* )( sizeof( float ) * 3 ) );
	} );

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

	Font font;
	font.loadFromFile( DEFAULT_FONT );

	Text text( font );
	text.setString( "Hello world" );

	gui::Rectangle rect;
	rect.setSize( { 200.f, 400.f } );

	while ( Window::instance().isOpen() )
	{
		camera.updateControl();
		camera.updateImpulse();

		preDraw();
		sprite.draw( program_, camera );
		
		text.draw( textProgram_ );
		rect.draw( guiShader_ );

		postDraw();
	}
}

void Program::postDraw()
{
	auto& wnd = Window::instance();

	wnd.swapBuffers();
	#ifdef DEBUG_LVL
		Gl::requireValidGl();
	#endif
}

void Program::setUpShaders()
{
	using namespace std::string_literals;
	program_.setup( ASSETS_DIR_NAME + "/shaders/main.vert"s, ASSETS_DIR_NAME + "/shaders/main.frag"s );
	textProgram_.setup( ASSETS_DIR_NAME + "/shaders/text.vert"s, ASSETS_DIR_NAME + "/shaders/text.frag"s );
	guiShader_.setup( ASSETS_DIR_NAME + "/shaders/gui.vert"s, ASSETS_DIR_NAME + "/shaders/gui.frag"s );
}
