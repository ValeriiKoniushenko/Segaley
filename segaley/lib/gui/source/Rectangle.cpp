#include "Rectangle.h"

#include "GuiShader.h"
#include "Window.h"

namespace gui
{

Rectangle::Rectangle() : 
	vbo_( Gl::Vbo::Target::Array )
{ }

void Rectangle::draw( GuiShader& shader )
{
	shader.use();

	configureShader();

	vao_.bind();
	auto wndSize = Window::instance().getSize();
	shader.uniform( "uResolution", glm::vec2( wndSize.width, wndSize.height ) );
	shader.uniform( "uRectColor", Color::convertToF( color_ ) );
	shader.uniform( "uRectFrom", glm::vec2( rect_.position.x, rect_.position.y ) );
	shader.uniform( "uRectTo", glm::vec2( rect_.position.x + rect_.size.width, rect_.position.y + rect_.size.height ) );
	Gl::drawArrays( Gl::DrawMode::Triangles, 0, 6 );
}

void Rectangle::setFrom( glm::vec2 from ) noexcept
{
	rect_.position = { from.x, from.y };
}

void Rectangle::setTo( glm::vec2 from ) noexcept
{
	rect_.size = {
		rect_.position.x - from.x,
		rect_.position.y - from.y
	};
}

void Rectangle::setRect( FFRect rect ) noexcept
{
	rect_ = rect_;
}

void Rectangle::setSize( FSize size ) noexcept
{
	rect_.size = size;
}

glm::vec2 Rectangle::getFrom() const noexcept
{
	return {
		rect_.position.x,
		rect_.position.y
	};
}

glm::vec2 Rectangle::getTo() const noexcept
{	
	return {
		rect_.position.x + rect_.size.width,
		rect_.position.y + rect_.size.height
	};
}

FFRect Rectangle::getRect() const noexcept
{
	return rect_;
}

void Rectangle::setColor( RGBA rgba ) noexcept
{
	color_ = rgba;
}

RGBA Rectangle::getColor() const noexcept
{
	return color_;
}

FSize Rectangle::getSize() const noexcept
{
	return rect_.size;
}

void Rectangle::configureShader()
{
	if ( static bool isInit = false; !isInit )
	{
		vao_.generate();
		vao_.bind();

		vbo_.generate();
		vbo_.bind();
		vbo_.bufferData< float >( {
		   -1.f, -1.f, 0.f,
			1.f, -1.f, 0.f,
			1.f,  1.f, 0.f,
			1.f,  1.f, 0.f,
		   -1.f, -1.f, 0.f,
		   -1.f,  1.f, 0.f,
		}, Gl::Vbo::DrawType::StaticDraw );

		Gl::enableVertexAttribArray( 0 );
		Gl::vertexAttribPointer( 0, 3, Gl::DataType::Float, false, 0, nullptr );
		isInit = true;
	}
}

} // namespace gui