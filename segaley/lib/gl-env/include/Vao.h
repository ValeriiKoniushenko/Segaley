#pragma once

#include "Gl.h"

class Vao final
{
public:
	Vao( bool isGenerateAndBind = false ) noexcept;
	~Vao();
	Vao( const Vao& ) = delete;
	Vao( Vao&& ) = delete;
	Vao& operator=( const Vao& ) = delete;
	Vao& operator=( Vao&& ) = delete;

	void generate();
	void bind() noexcept;
	bool isBind() noexcept;
	bool isEmpty() noexcept;
	void reset() noexcept;
	void release() noexcept;

private:
	GLuint id_ = 0;
};
