#pragma once

#include "Gl.h"

#include <filesystem>

class ShaderProgram;

class Shader final
{
public:
	Shader( Gl::Shader type, ShaderProgram& program );
	~Shader();
	Shader( const Shader& ) = delete;
	Shader( Shader&& ) = delete;
	Shader& operator=( const Shader& ) = delete;
	Shader& operator=( Shader&& ) = delete;

	void setShaderSource( const std::string& source ) noexcept;
	void loadFromFile( std::filesystem::path path );
	void compile();
	bool isEmpty() const noexcept;
	GLuint data() const noexcept;
	void release();
	void detach();

private:
	GLuint id_ = 0;
	const Gl::Shader type_;
	const GLuint program_ = 0;
};
