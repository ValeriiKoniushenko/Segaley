#pragma once

#include "Rect.h"
#include "Vao.h"
#include "Vbo.h"
#include "Color.h"

#include "glm/glm.hpp"

class GuiShader;

namespace gui
{

class Rectangle
{
public:
	Rectangle() = default;
	~Rectangle() = default;
	Rectangle( const Rectangle& ) = default;
	Rectangle( Rectangle&& ) = default;
	Rectangle& operator=( const Rectangle& ) = default;
	Rectangle& operator=( Rectangle&& ) = default;

	void draw( GuiShader& shader );

	void setFrom( glm::vec2 from ) noexcept;
	void setTo( glm::vec2 from ) noexcept;
	void setRect( FFRect rect ) noexcept;
	void setSize( FSize size ) noexcept;
	void setPosition( glm::vec2 position ) noexcept;

	glm::vec2 getFrom() const noexcept;
	glm::vec2 getTo() const noexcept;
	FFRect getRect() const noexcept;
	FSize getSize() const noexcept;
	glm::vec2 getPosition() const noexcept;

	void setColor( RGBA rgba ) noexcept;
	RGBA getColor() const noexcept;

private:
	void configureShader();

private:
	FFRect rect_ = { {}, { 100.f, 100.f } };
	static Vao vao_;
	static Vbo vbo_;
	RGBA color_ = { 255, 0, 0, 255 };
};

} // namespace gui
