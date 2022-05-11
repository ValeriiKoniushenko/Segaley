#include "WindowSize.h"

bool WindowSize::operator==( const WindowSize& other ) const
{
	return height == other.height && width == other.width;
}

bool WindowSize::operator!=( const WindowSize& other ) const
{
	return !( *this == other );
}

float WindowSize::getRatio() const
{
	return static_cast< float >( width ) / static_cast< float >( height );
}
