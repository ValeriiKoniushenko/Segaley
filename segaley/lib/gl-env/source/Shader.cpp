#include "Shader.h"

#include "ShaderProgram.h"
#include "Utils.h"

Shader::Shader( Gl::Shader type, ShaderProgram& program ) :
	type_( type ),
	program_( program.data() )
{
	id_ = Gl::createShader( type );
}

Shader::~Shader()
{
	release();
}

void Shader::setShaderSource( const std::string& source ) noexcept
{
	Gl::shaderSource( id_, 1, source );
}

void Shader::loadFromFile( std::filesystem::path path )
{
	setShaderSource( utils::getFileContent( path ) );
}

void Shader::compile()
{
	Gl::compileShader( id_ );
}

bool Shader::isEmpty() const noexcept
{
	return id_ == 0u;
}

GLuint Shader::data() const noexcept
{
	return id_;
}

void Shader::release()
{
	Gl::deleteShader( program_, id_ );
	detach();
}

void Shader::detach()
{
	Gl::detachShader( program_, id_ );
}
