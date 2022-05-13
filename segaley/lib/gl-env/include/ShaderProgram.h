#pragma once

#include "Gl.h"

#include <filesystem>

class Shader;

class ShaderProgram final
{
public:
	ShaderProgram( bool isCreate = false );
	~ShaderProgram();
	ShaderProgram( const ShaderProgram& ) = delete;
	ShaderProgram( ShaderProgram&& ) = delete;
	ShaderProgram& operator=( const ShaderProgram& ) = delete;
	ShaderProgram& operator=( ShaderProgram&& ) = delete;

	void create();
	bool isEmpty() const noexcept;
	void link();
	void attachShader( Shader& shader );
	void use();
	void release();
	GLuint data() noexcept;

private:
	GLuint id_ = 0;
};
