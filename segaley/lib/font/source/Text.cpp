#include "Text.h"

#include "ShaderProgram.h"
#include "Window.h"

#include "glm/gtc/matrix_transform.hpp"

Text::Text( Font& font ) :
	font_( font ),
	vbo_( Gl::Vbo::Target::Array )
{
}

void Text::setString( const std::string& text ) noexcept
{
	text_ = text;
}

void Text::setPosition( glm::vec2 position ) noexcept
{
	position_ = position;
}

glm::vec2 Text::getPosition() const noexcept
{
	return position_;
}

void Text::setSize( std::size_t size ) noexcept
{
	size_ = size;
}

std::size_t Text::getSize() const noexcept
{
	return size_;
}

void Text::setColor( RGB color ) noexcept
{
	color_ = color;
}

RGB Text::getColor() const noexcept
{
	return color_;
}

void Text::draw( ShaderProgram& shader )
{
	initGl( shader );

	shader.use();

	glDisable( GL_CULL_FACE );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	auto wndSize = Window::instance().getSize();
	auto projection = glm::ortho( 0.0f, static_cast< float >( wndSize.width ), 
		0.0f, static_cast< float >( wndSize.height ) );
	shader.uniform( "projection", projection );

	auto color = Color::convertToF( color_ );
	shader.uniform( "uTextColor", glm::vec3( color.r, color.g, color.b ) );
	Gl::Texture::active( 0 );
	vao_.bind();

	auto scale = static_cast< float >( size_ ) / globalSacle;
	auto x = position_.x;
	auto y = position_.y;

	for ( auto c : text_ )
	{
		auto& ch = font_[ c ];

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
		vbo_.bind();
		glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( vertices ), vertices );

		Gl::drawArrays( Gl::DrawMode::Triangles, 0, 6 );
		x += ( ch.advance >> 6 ) * scale;
	}
}

float Text::getWidth() const noexcept
{
	float width = 0;
	auto scale = static_cast< float >( size_ ) / globalSacle;

	for ( auto c : text_ )
	{
		auto& ch = font_[ c ];
		width += ( ch.advance >> 6 ) * scale;
	}

	return width;
}

void Text::initGl( ShaderProgram& shader )
{
	static bool isInit = false;

	if ( !isInit )
	{
		shader.use();

		vbo_.generate();
		vbo_.bind();
		vbo_.bufferData( sizeof( float ) * 6 * 4, nullptr, Gl::Vbo::DrawType::DynamicDraw );

		vao_.generate();
		vao_.bind();

		Gl::enableVertexAttribArray( 0 );
		Gl::vertexAttribPointer( 0, 4, Gl::DataType::Float, false, 4 * sizeof( float ), 0 );
		isInit = true;
	}
}
