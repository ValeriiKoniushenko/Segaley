#pragma once

#include "Rectangle.h"

namespace gui
{

class Frame : public Rectangle
{
public:
	Frame() = default;
	~Frame() = default;
	Frame( const Frame& ) = delete;
	Frame( Frame&& ) = delete;
	Frame& operator=( const Frame& ) = delete;
	Frame& operator=( Frame&& ) = delete;

private:

};

} // namespace gui

