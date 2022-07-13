#include "Program.h"

#include "Window.h"
#include "Vbo.h"
#include "Texture2D.h"
#include "Shader.h"
#include "Font.h"
#include "Text.h"
#include "TextLine.h"

#include <iostream>

void Program::launch()
{
	setUpShaders();

	Window::instance().disableCursor();

    guiShader_.setConfigureCallback( []( auto& program ) {
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

	Texture2D texture( true );
	texture.loadFromFile( ASSETS_DIR_NAME + "/images/brickwall.jpg"s );	

    Font font;
	font.loadFromFile( DEFAULT_FONT );

    gui::TextLine frame;
    frame.setFont( font );
    frame.setTexture2D( texture );
    frame.move( { 100.f, -100.f } );
    frame.setString( "Hello world" );
	frame.setSize( { 400.f, 400.f } );
	frame.setTextHorizontalAlign( gui::TextLine::Align::Center );

	while ( Window::instance().isOpen() )
	{
		preDraw();
        frame.draw( guiShader_, textProgram_ );

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
