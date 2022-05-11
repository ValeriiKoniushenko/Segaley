#include "Vbo.h"

#include <stdexcept>

Vbo::Vbo( Gl::Vbo::Target target, bool isGenerateAndBind/* = false*/ ) noexcept :
	target_( target )
{
	generate();
	bind();
}

Vbo::~Vbo()
{
	release();
}

void Vbo::generate()
{
	if ( !isEmpty() )
		throw std::runtime_error( "Impossible to generate the same VBO twice." );

	id_ = Gl::Vbo::generate();
}

void Vbo::bind() noexcept
{
	Gl::Vbo::bind( target_, id_ );
}

bool Vbo::isBind() const noexcept
{
	return Gl::Vbo::isSetBuffer( target_ );
}

bool Vbo::isEmpty() const noexcept
{
	return id_ == 0u;
}

void Vbo::reset() noexcept
{
	Gl::Vbo::bind( target_, 0 );
}

void Vbo::release() noexcept
{
	Gl::Vbo::deleteBuffer( id_ );
}

void Vbo::bufferData( GLsizeiptr size, const void* data, Gl::Vbo::DrawType drawType )
{
	Gl::Vbo::bufferData( target_, size, data, drawType );
}
