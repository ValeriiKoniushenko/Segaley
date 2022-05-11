#pragma once

#include <string>

struct RGBf
{
	float r = 0.f;
	float g = 0.f;
	float b = 0.f;
	static bool isValid( const RGBf& color );
	bool isValid() const;
}; 

struct RGBAf
{
	RGBAf() = default;
	RGBAf( float r, float g, float b, float a );
	explicit RGBAf( RGBf rgb, float a = 1.f );

	float r = 0.f;
	float g = 0.f;
	float b = 0.f;
	float a = 0.f;
	static bool isValid( const RGBAf& color );
	bool isValid() const;
};

struct RGB
{
	static unsigned char limit8bit;
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
};

struct RGBA
{
	static unsigned char limit8bit;

	RGBA() = default;
	RGBA( unsigned char r, unsigned char g, unsigned char b, unsigned char a );
	explicit RGBA( RGB rgb, unsigned char a = 255 );

	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 0;
};

class Color final
{
public:
	static RGB convertFromF( const RGBf& rgbf );
	static RGBf convertToF( const RGB& rgbf );	
	static RGBA convertFromF( const RGBAf& rgbf );
	static RGBAf convertToF( const RGBA& rgbf );

	static std::string toString( const RGBA& color );
	static std::string toString( const RGBAf& color );
	static std::string toString( const RGB& color );
	static std::string toString( const RGBf& color );

	Color() = delete;

	static RGB white();
	static RGB black();
	static RGB red();
	static RGB green();
	static RGB blue();

private:
};
