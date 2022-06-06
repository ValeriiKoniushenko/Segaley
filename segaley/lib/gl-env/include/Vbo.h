#pragma once

#include "Gl.h"

#include <vector>

class Vbo final
{
public:
	Vbo( Gl::Vbo::Target target, bool isGenerateAndBind = false ) noexcept;
	~Vbo();
	Vbo( const Vbo& ) = delete;
	Vbo( Vbo&& ) = delete;
	Vbo& operator=( const Vbo& ) = delete;
	Vbo& operator=( Vbo&& ) = delete;

	void generate();
	void bind() noexcept;
	bool isBind() const noexcept;
	bool isEmpty() const noexcept;
	void reset() noexcept;
	void release() noexcept;
	void bufferData( GLsizeiptr size, const void* data, Gl::Vbo::DrawType drawType );
	void bufferSubData( GLintptr offset, GLsizeiptr size, const void* data );
	template< class T >
	void bufferData( const std::vector< T >& data, Gl::Vbo::DrawType drawType );

private:
	GLuint id_ = 0;
	const Gl::Vbo::Target target_;
};

template< class T >
void Vbo::bufferData( const std::vector< T >& data, Gl::Vbo::DrawType drawType )
{
	Gl::Vbo::bufferData( target_, sizeof( T ) * data.size(), data.data(), drawType );
}
