#pragma once

#include "Gl.h"

class Vao final
{
public:
	Vao( bool isGenerateAndBind = false ) noexcept;

	void generate();
	void bind() noexcept;
	bool isBind() noexcept;
	bool isEmpty() noexcept;
	void reset() noexcept;
	void deleteBuffer() noexcept;

private:
	GLuint id_ = 0;
};
