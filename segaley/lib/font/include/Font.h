#pragma once

#include "Texture2D.h"

#include "ft2build.h"
#include FT_FREETYPE_H

#include <filesystem>
#include <map>

class FontHolder
{
public:
	FontHolder() = default;
	~FontHolder();
	FontHolder( const FontHolder& ) = delete;
	FontHolder( FontHolder&& ) = delete;
	FontHolder& operator=( const FontHolder& ) = delete;
	FontHolder& operator=( FontHolder&& ) = delete;

	static FontHolder& initialize();
	FT_Face generateFace( std::filesystem::path path ) const;
private:
	void initialize_();
	void realize() noexcept;

private:
	FT_Library ft_;
};

struct Character {
	Texture2D    texture;  // ID handle of the glyph texture
	glm::ivec2   size;       // Size of glyph
	glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
	unsigned int advance;    // Offset to advance to next glyph
};

class Font final
{
public:
	Font() = default;
	~Font() = default;
	Font( const Font& ) = delete;
	Font( Font&& ) = delete;
	Font& operator=( const Font& ) = delete;
	Font& operator=( Font&& ) = delete;

	void loadFromFile( std::filesystem::path pathToFont );
	const Character& operator[]( char i ) const;

private:
	FT_Face face_ = nullptr;
	std::map< char, Character > characters_;
};
