#pragma once

#include "Image.h"
#include "Gl.h"

#include <filesystem>

class Texture2D final
{
public:
	Texture2D( bool isGenerateAndBind = false );
	~Texture2D();
	Texture2D( const Texture2D& ) = delete;
	Texture2D( Texture2D&& ) noexcept;
	Texture2D& operator=( const Texture2D& ) = delete;
	Texture2D& operator=( Texture2D&& ) noexcept;

	void generate();
	void bind() const noexcept;
	bool isBind() const noexcept;
	void reset() noexcept;
	void release() noexcept;

	void setMinFilter( Gl::Texture::MinFilter filter );
	void setMagFilter( Gl::Texture::MagFilter filter );
	void setWrapS( Gl::Texture::Wrap wrap );
	void setWrapT( Gl::Texture::Wrap wrap );
	void setWrapR( Gl::Texture::Wrap wrap );
	void setImage( const Image& image );
	void generateMipmap();
	void loadFromFile( std::filesystem::path path );
	GLuint data() noexcept;

private:
	GLuint id_ = 0;
	static const Gl::Texture::Target target_;
};
