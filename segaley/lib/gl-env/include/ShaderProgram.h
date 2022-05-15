#pragma once

#include "Gl.h"
#include "glm/glm.hpp"

#include <filesystem>
#include <unordered_map>

class Shader;

class ShaderProgram
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
	void use() const;
	void release();
	GLuint data() noexcept;
	void vertexAttribPointer( const std::string& attribute, GLint size, Gl::DataType type, bool normalized, GLsizei stride, const void* pointer );
	
	void uniform( const std::string& name, float data );
	void uniform( const std::string& name, glm::vec2 data );
	void uniform( const std::string& name, glm::vec3 data );
	void uniform( const std::string& name, const glm::mat3& data );
	void uniform( const std::string& name, const glm::mat4& data );

private:
	GLuint id_ = 0;
	std::unordered_map< std::string, GLuint > attributes_;
	std::unordered_map< std::string, GLuint > uniforms_;
};
