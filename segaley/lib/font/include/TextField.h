#pragma once

#include "Color.h"
#include "glm/glm.hpp"

class Font;

class TextField final
{
public:
	TextField( Font& font );
	~TextField() = default;
	TextField( const TextField& ) = delete;
	TextField( TextField&& ) = delete;
	TextField& operator=( const TextField& ) = delete;
	TextField& operator=( TextField&& ) = delete;

	void setPosition( glm::vec2 position ) noexcept;
	glm::vec2 getPosition() const noexcept;

	void setFontSize( std::size_t size ) noexcept;
	std::size_t getFontSize() const noexcept;

	void setColor( RGB color ) noexcept;
	RGB getColor() const noexcept;


private:
	Font& font_;
	std::string text_;
	glm::vec2 position_ = glm::vec2( 0.f );
	float size_ = 48u;
};
