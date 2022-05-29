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
#include "glm/gtc/matrix_transform.hpp"

#include "Font.h"

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

Vao vao;
Vbo vbo( Gl::Vbo::Target::Array );

void RenderText( Font& font, MainShader& shader, std::string text, float x, float y, float scale, glm::vec3 color )
{
	shader.use();

	glDisable( GL_CULL_FACE );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	shader.uniform( "uTextColor", glm::vec3( 1,0,0 ) );
	Gl::Texture::active( 0 );
	vao.bind();

	for ( auto c = text.begin(); c != text.end(); c++ )
	{
		auto& ch = font[ *c ];

		float xpos = x + ch.bearing.x * scale;
		float ypos = y - ( ch.size.y - ch.bearing.y ) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		
		float vertices[ 6 ][ 4 ] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		
		ch.texture.bind();
		vbo.bind();
		glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( vertices ), vertices );

		Gl::drawArrays( Gl::DrawMode::Triangles, 0, 6 );
		x += ( ch.advance >> 6 ) * scale;
	}


	glDisable( GL_BLEND );
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

	textProgram_.use();
	auto projection = glm::ortho( 0.0f, 1024.f, 0.0f, 768.f );
	textProgram_.uniform( "projection", projection );

	vbo.generate();
	vbo.bind();
	vbo.bufferData( sizeof( float ) * 6 * 4, nullptr, Gl::Vbo::DrawType::DynamicDraw );	
	
	vao.generate();
	vao.bind();
	
	Gl::enableVertexAttribArray( 0 );
	Gl::vertexAttribPointer( 0, 4, Gl::DataType::Float, false, 4 * sizeof( float ), 0 );

	while ( Window::instance().isOpen() )
	{
		camera.updateControl();
		camera.updateImpulse();

		preDraw();
		sprite.draw( program_, camera );
		
		RenderText( font, textProgram_, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3( 0.5, 0.8f, 0.2f ) );

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
}
