#pragma once

#include "Font.h"
#include "Vbo.h"
#include "Vao.h"
#include "Color.h"

class ShaderProgram;

class Text final
{
public:
	Text( Font& font );
	~Text() = default;
	Text( const Text& ) = delete;
	Text( Text&& ) = delete;
	Text& operator=( const Text& ) = delete;
	Text& operator=( Text&& ) = delete;

	void setString( const std::string& text ) noexcept;
	
	void setPosition( glm::vec2 position ) noexcept;
	glm::vec2 getPosition() const noexcept;

	void setSize( std::size_t size ) noexcept;
	std::size_t getSize() const noexcept;

	void setColor( RGB color ) noexcept;
	RGB getColor() const noexcept;

	void draw( ShaderProgram& shader );

	float getWidth() const noexcept;

private:
	Font& font_;
	std::string text_;
	glm::vec2 position_ = glm::vec2( 0.f );
	std::size_t size_ = 48u;
	Vao vao_;
	Vbo vbo_;
	RGB color_;
};
