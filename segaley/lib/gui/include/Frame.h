#pragma once

#include "Rectangle.h"

namespace gui
{

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
	void setColor( RGBA color ) noexcept;
	void setBorderTop( float size );
	void setBorderBottom( float size );
	void setBorderLeft( float size );
	void setBorderRight( float size );
	void setBorderColor( RGBA color ) noexcept;

	glm::vec2 getPosition() const noexcept;
	RGBA getColor() const noexcept;
	float getBorderTop() const noexcept;
	float getBorderBottom() const noexcept;
	float getBorderLeft() const noexcept;
	float getBorderRight() const noexcept;
	RGBA getBorderColor() const noexcept;

	void draw( GuiShader& shader );

private:
	FFRect rect_ = { {}, { 100.f, 100.f } };
	RGBA color_ = { 255, 255, 255, 255 };

	float borderBottom_ = 0.f;
	float borderTop_ = 0.f;
	float borderLeft_ = 0.f;
	float borderRight_ = 0.f;
	RGBA borderColor_ = { 0, 0, 0, 255 };

	Rectangle main_;
	Rectangle back_;
};

} // namespace gui

