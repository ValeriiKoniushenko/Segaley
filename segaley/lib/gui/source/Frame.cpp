#include "Frame.h"

#include "GuiShader.h"

namespace gui
{

void Frame::setPosition( glm::vec2 position ) noexcept
{
	rect_.position = { position.x, position.y };
}

void Frame::move( glm::vec2 position ) noexcept
{
	rect_.position.x += position.x;
	rect_.position.y += position.y;
}

void Frame::setColor( RGBA color ) noexcept
{
	color_ = color;
}

void Frame::setBorderTop( float size )
{
	if ( size < 0.f )
		throw std::runtime_error( "The border size can not be less then 0.0" );
	borderTop_ = size;
}

void Frame::setBorderBottom( float size )
{
	if ( size < 0.f )
		throw std::runtime_error( "The border size can not be less then 0.0" );
	borderBottom_ = size;
}

void Frame::setBorderLeft( float size )
{
	if ( size < 0.f )
		throw std::runtime_error( "The border size can not be less then 0.0" );
	borderLeft_ = size;
}

void Frame::setBorderRight( float size )
{
	if ( size < 0.f )
		throw std::runtime_error( "The border size can not be less then 0.0" );
	borderRight_ = size;
}

void Frame::setBorderColor( RGBA color ) noexcept
{
	borderColor_ = color;
}

glm::vec2 Frame::getPosition() const noexcept
{
	return { rect_.size.width, rect_.size.height };
}

RGBA Frame::getColor() const noexcept
{
	return color_;
}

float Frame::getBorderTop() const noexcept
{
	return borderTop_;
}

float Frame::getBorderBottom() const noexcept
{
	return borderBottom_;
}

float Frame::getBorderLeft() const noexcept
{
	return borderLeft_;
}

float Frame::getBorderRight() const noexcept
{
	return borderRight_;
}

RGBA Frame::getBorderColor() const noexcept
{
	return borderColor_;
}

void Frame::draw( GuiShader& shader )
{
	auto backRect = rect_;
	backRect.size.width += borderRight_ + borderLeft_;
	backRect.size.height += borderTop_ + borderBottom_;
	backRect.position.x -= borderLeft_;
	backRect.position.y -= borderTop_;

	back_.setRect( backRect );
	back_.setColor( borderColor_ );
	back_.draw( shader );

	main_.setRect( rect_ );
	main_.setColor( color_ );
	main_.draw( shader );
}


}

