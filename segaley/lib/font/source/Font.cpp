#include "Font.h"

#include "Gl.h"

#include <memory>
#include <stdexcept>

FontHolder::~FontHolder()
{
	realize();
}

FontHolder& FontHolder::initialize()
{
	static std::unique_ptr< FontHolder > ptr;

	if ( !ptr )
	{
		ptr = std::unique_ptr< FontHolder >( new FontHolder );
		ptr->initialize_();
	}

	return *ptr.get();
}

void FontHolder::initialize_()
{
	if ( FT_Init_FreeType( &ft_ ) )
		throw std::runtime_error( "ERROR::FREETYPE: Could not init FreeType Library" );
}

void FontHolder::realize() noexcept
{
	FT_Done_FreeType( ft_ );
}

FT_Face FontHolder::generateFace( std::filesystem::path path ) const
{
	FT_Face face;
	if ( FT_New_Face( ft_, path.string().c_str(), 0, &face) )
		throw std::runtime_error( "ERROR::FREETYPE: Failed to load font" );

	return face;
}

void Font::loadFromFile( std::filesystem::path pathToFont )
{
	face_ = FontHolder::initialize().generateFace( pathToFont );

	FT_Set_Pixel_Sizes( face_, 0, 100 );

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	for ( unsigned char c = 0; c < 128; c++ )
	{
		if ( FT_Load_Char( face_, c, FT_LOAD_RENDER ) )
			throw std::runtime_error( "ERROR::FREETYTPE: Failed to load Glyph" );

		Texture2D texture( true );
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face_->glyph->bitmap.width,
			face_->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face_->glyph->bitmap.buffer
		);

		texture.setMagFilter( Gl::Texture::MagFilter::Linear );
		texture.setMinFilter( Gl::Texture::MinFilter::Linear );
		texture.setWrapS( Gl::Texture::Wrap::Clamp2Edge );
		texture.setWrapT( Gl::Texture::Wrap::Clamp2Edge );

		Character character = {
			std::move( texture ),
			glm::ivec2( face_->glyph->bitmap.width, face_->glyph->bitmap.rows ),
			glm::ivec2( face_->glyph->bitmap_left, face_->glyph->bitmap_top ),
			static_cast< unsigned int >( face_->glyph->advance.x )
		};
		characters_.insert( std::pair<char, Character>( c, std::move( character ) ) );
	}

	FT_Done_Face( face_ );
}

const Character& Font::operator[]( char i ) const
{
	return characters_.at( i );
}
