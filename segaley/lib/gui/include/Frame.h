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

	void setPosition( glm::vec2 position ) noexcept;
	void move( glm::vec2 position ) noexcept;
	glm::vec2 getPosition() const noexcept;

	void draw(GuiShader& shader );

    void setTexture2D( Texture2D& texture ) noexcept;

private:
    Sprite sprite_;
    static Camera2D camera_;
};

} // namespace gui

