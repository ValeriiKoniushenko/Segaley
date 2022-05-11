#include "Color.h"
#include "Color.h"
#include "Color.h"
#include <boost/format.hpp>

unsigned char RGB::limit8bit = 255;
unsigned char RGBA::limit8bit = RGB::limit8bit;

RGB Color::convertFromF( const RGBf& rgbf )
{
	return {
		static_cast< unsigned char >( rgbf.r * static_cast< float >( RGB::limit8bit ) ),
		static_cast< unsigned char >( rgbf.g * static_cast< float >( RGB::limit8bit ) ),
		static_cast< unsigned char >( rgbf.b * static_cast< float >( RGB::limit8bit ) )
	};
}

RGBf Color::convertToF( const RGB& rgbf )
{
	return {
			static_cast< float >( static_cast< float >( rgbf.r ) / RGB::limit8bit ),
			static_cast< float >( static_cast< float >( rgbf.g ) / RGB::limit8bit ),
			static_cast< float >( static_cast< float >( rgbf.b ) / RGB::limit8bit )
	};
}

RGBA Color::convertFromF( const RGBAf& rgbf )
{
	return {
		static_cast< unsigned char >( rgbf.r * static_cast< float >( RGB::limit8bit ) ),
		static_cast< unsigned char >( rgbf.g * static_cast< float >( RGB::limit8bit ) ),
		static_cast< unsigned char >( rgbf.b * static_cast< float >( RGB::limit8bit ) ),
		static_cast< unsigned char >( rgbf.a * static_cast< float >( RGB::limit8bit ) )
	};
}

RGBAf Color::convertToF( const RGBA& rgbf )
{
	return {
			static_cast< float >( static_cast< float >( rgbf.r ) / RGB::limit8bit ),
			static_cast< float >( static_cast< float >( rgbf.g ) / RGB::limit8bit ),
			static_cast< float >( static_cast< float >( rgbf.b ) / RGB::limit8bit ),
			static_cast< float >( static_cast< float >( rgbf.a ) / RGB::limit8bit )
	};
}

RGBAf::RGBAf( float r, float g, float b, float a ) :
	r( r ),
	g( g ),
	b( b ),
	a( a )
{
}

RGBAf::RGBAf( RGBf rgb, float a ) :
	r( rgb.r ),
	g( rgb.g ),
	b( rgb.b ),
	a( a )
{
}

bool RGBAf::isValid( const RGBAf& color )
{
	static const float E = 0.000001f;
	if ( color.r < 0.f || color.r > 1.f + E )
		return false;
	if ( color.g < 0.f || color.g > 1.f + E )
		return false;
	if ( color.b < 0.f || color.b > 1.f + E )
		return false;
	if ( color.a < 0.f || color.a > 1.f + E )
		return false;

	return true;
}

bool RGBAf::isValid() const
{
	return RGBAf::isValid( *this );
}

bool RGBf::isValid( const RGBf& color )
{
	static const float E = 0.000001f;
	if ( color.r < 0.f || color.r > 1.f + E )
		return false;
	if ( color.g < 0.f || color.g > 1.f + E )
		return false;
	if ( color.b < 0.f || color.b > 1.f + E )
		return false;

	return true;
}

bool RGBf::isValid() const
{
	return RGBf::isValid( *this );
}

RGBA::RGBA( unsigned char r, unsigned char g, unsigned char b, unsigned char a ) :
	r( r ),
	g( g ),
	b( b ),
	a( a )
{
}

RGBA::RGBA( RGB rgb, unsigned char a ) :
	r( rgb.r ),
	g( rgb.g ),
	b( rgb.b ),
	a( a )
{
}

std::string Color::toString( const RGBA& color )
{
	boost::format format( "RGBA(%d, %d, %d, %d)" );
	int r = color.r;
	int g = color.g;
	int b = color.b;
	int a = color.a;
	return ( format % r % g % b % a ).str();
}

std::string Color::toString( const RGBAf& color )
{
	boost::format format( "RGBA(%d, %d, %d, %d)" );
	return ( format % color.r % color.g % color.b % color.a ).str() +
		"[" + Color::toString( Color::convertFromF( color ) ) + "]";
}

std::string Color::toString( const RGB& color )
{
	boost::format format( "RGB(%d, %d, %d)" );
	int r = color.r;
	int g = color.g;
	int b = color.b;
	return ( format % r % g % b ).str();
}

std::string Color::toString( const RGBf& color )
{
	boost::format format( "RGB(%d, %d, %d)" );
	return ( format % color.r % color.g % color.b ).str() +
		"[" + Color::toString( Color::convertFromF( color ) ) + "]";
}

RGB Color::white()
{
	return { 255, 255, 255 };
}

RGB Color::black()
{
	return { 0, 0, 0 };
}

RGB Color::red()
{
	return { 255, 0, 0 };
}

RGB Color::green()
{
	return { 0, 255, 0 };
}

RGB Color::blue()
{
	return { 0, 0, 255 };
}
