#include "Vao.h"

#include <stdexcept>

Vao::Vao( bool isGenerateAndBind/* = false*/ ) noexcept
{
	if ( isGenerateAndBind )
	{
		generate();
		bind();
	}
}

Vao::~Vao()
{
	release();
}

void Vao::generate()
{
	if ( !isEmpty() )
		throw std::runtime_error( "Impossible to generate the same VBO twice." );

	id_ = Gl::Vao::generate();
}

void Vao::bind() noexcept
{
	Gl::Vao::bind( id_ );
}

bool Vao::isBind() noexcept
{
	return Gl::Vao::isBind();
}

bool Vao::isEmpty() noexcept
{
	return id_ == 0;
}

void Vao::reset() noexcept
{
	Gl::Vao::reset();
}

void Vao::release() noexcept
{
	Gl::Vao::deleteBuffer( id_ );
}
