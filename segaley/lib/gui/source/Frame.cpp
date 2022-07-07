#include "Frame.h"

#include "GuiShader.h"
#include "Window.h"

namespace gui
{

Camera2D Frame::camera_;

void Frame::setPosition( glm::vec2 position ) noexcept
{
    sprite_.setPosition( position );
}

void Frame::move( glm::vec2 position ) noexcept
{
    sprite_.move( position );
}

glm::vec2 Frame::getPosition() const noexcept
{
	return sprite_.getPosition();
}

void Frame::setTexture2D( Texture2D &texture ) noexcept
{
    sprite_.setTexture2D( texture );
}

void Frame::draw( GuiShader& shader )
{
    shader.use();

    auto wndSize = ::Window::instance().getSize();
    shader.uniform( "uResolution", glm::vec2( wndSize.width, wndSize.height ) );
    shader.uniform( "uModelSize", sprite_.getSize() );

    sprite_.draw( shader, camera_ );
}

void Frame::setSize( glm::vec2 size ) noexcept
{
    sprite_.setSize( size );
}

glm::vec2 Frame::getSize() const noexcept
{
    return sprite_.getSize();
}

void Frame::setOrigin( glm::vec2 origin ) noexcept
{
    sprite_.setOrigin( origin );
}

glm::vec2 Frame::getOrigin() const noexcept
{
    return sprite_.getOrigin();
}

void Frame::setRotation( float radian ) noexcept
{
    sprite_.setRotation( radian );
}

void Frame::rotate( float radian ) noexcept
{
    sprite_.rotate( radian );
}

float Frame::getRotation() const noexcept
{
    return sprite_.getRotation();
}

}