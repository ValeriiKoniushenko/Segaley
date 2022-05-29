#include "Texture2D.h"

const Gl::Texture::Target Texture2D::target_ = Gl::Texture::Target::Texture2d;

Texture2D::Texture2D( bool isGenerateAndBind/* = false*/ )
{
	if ( isGenerateAndBind )
	{
		generate();
		bind();
	}
}

Texture2D::~Texture2D()
{
	release();
}

Texture2D::Texture2D( Texture2D&& other ) noexcept
{
	*this = std::move( other );
}

Texture2D& Texture2D::operator=( Texture2D&& other ) noexcept
{
	id_ = other.id_;

	other.id_ = 0;

	return *this;
}

void Texture2D::generate()
{
	id_ = Gl::Texture::generate();
}

void Texture2D::bind() const noexcept
{
	Gl::Texture::bind( target_, id_ );
}

bool Texture2D::isBind() const noexcept
{
	return Gl::Texture::isBind( target_ );
}

void Texture2D::reset() noexcept
{
	Gl::Texture::reset( target_ );
}

void Texture2D::release() noexcept
{
	Gl::Texture::deleteBuffer( id_ );
}

void Texture2D::setMinFilter( Gl::Texture::MinFilter filter )
{
	Gl::Texture::setMinFilter( filter, target_ );
}

void Texture2D::setMagFilter( Gl::Texture::MagFilter filter )
{
	Gl::Texture::setMagFilter( filter, target_ );
}

void Texture2D::setWrapS( Gl::Texture::Wrap wrap )
{
	Gl::Texture::setWrapS( wrap, target_ );
}

void Texture2D::setWrapT( Gl::Texture::Wrap wrap )
{
	Gl::Texture::setWrapT( wrap, target_ );
}

void Texture2D::setWrapR( Gl::Texture::Wrap wrap )
{
	Gl::Texture::setWrapR( wrap, target_ );
}

void Texture2D::setImage( const Image& image )
{
	Gl::Texture::texImage2D(
		Gl::Texture::Target::Texture2d,
		0,
		Image::toGlFormat( image.getChannel() ),
		image.getWidth(),
		image.getHeight(),
		0,
		Image::toGlFormat( image.getChannel() ),
		Gl::DataType::UnsignedByte,
		image.data() );
}

void Texture2D::generateMipmap()
{
	Gl::Texture::generateMipmap( target_ );
}

void Texture2D::loadFromFile( std::filesystem::path path )
{
	Image image;
	image.loadImage( path );
	setImage( image );
	generateMipmap();
}

GLuint Texture2D::data() noexcept
{
	return id_;
}
