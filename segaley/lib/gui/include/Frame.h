#pragma once

#include "Sprite.h"
#include "Camera2D.h"

#include "glm/glm.hpp"

class Texture2D;

namespace gui
{

class GuiShader;

class Frame
{
public:
	Frame() = default;
	~Frame() = default;
	Frame( const Frame& ) = delete;
	Frame( Frame&& ) = delete;
	Frame& operator=( const Frame& ) = delete;
	Frame& operator=( Frame&& ) = delete;

    void setSize( glm::vec2 size ) noexcept;
    glm::vec2 getSize() const noexcept;

    void setPosition( glm::vec2 size ) noexcept;
    void move( glm::vec2 size ) noexcept;
    glm::vec2 getPosition() const noexcept;

    void setOrigin( glm::vec2 origin ) noexcept;
    glm::vec2 getOrigin() const noexcept;

    void setRotation( float radian ) noexcept;
    void rotate( float radian ) noexcept;
    float getRotation() const noexcept;

	void draw(GuiShader& shader );

    void setTexture2D( Texture2D& texture ) noexcept;

private:
    Sprite sprite_;
    static Camera2D camera_;
};

} // namespace gui

