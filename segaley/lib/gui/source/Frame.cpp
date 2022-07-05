#include "Frame.h"

#include "GuiShader.h"

namespace gui
{

Camera2D Frame::camera_;

void Frame::setPosition( glm::vec2 position ) noexcept
{

}

void Frame::move( glm::vec2 position ) noexcept
{

}

glm::vec2 Frame::getPosition() const noexcept
{
	return {  };
}

void Frame::setTexture2D( Texture2D &texture ) noexcept
{
    sprite_.setTexture2D( texture );
}

void Frame::draw( GuiShader& shader )
{
    sprite_.draw( shader, camera_ );
}

}