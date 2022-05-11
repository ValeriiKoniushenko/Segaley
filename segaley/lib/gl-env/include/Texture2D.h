#pragma once

#include "Image.h"
#include "Gl.h"

class Texture2D final
{
public:
	Texture2D( bool isGenerateAndBind = false );
	~Texture2D();
	Texture2D( const Texture2D& ) = delete;
	Texture2D( Texture2D&& ) = delete;
	Texture2D& operator=( const Texture2D& ) = delete;
	Texture2D& operator=( Texture2D&& ) = delete;

	void generate();
	void bind() noexcept;
	bool isBind() noexcept;
	void reset() noexcept;
	void release(  ) noexcept;

	void setMinFilter( Gl::Texture::MinFilter filter );
	void setMagFilter( Gl::Texture::MagFilter filter );
	void setWrapS( Gl::Texture::Wrap wrap );
	void setWrapT( Gl::Texture::Wrap wrap );
	void setWrapR( Gl::Texture::Wrap wrap );
	void setImage( const Image& image );
	void generateMipmap();
private:
	GLuint id_ = 0;
	static const Gl::Texture::Target target_;
};
