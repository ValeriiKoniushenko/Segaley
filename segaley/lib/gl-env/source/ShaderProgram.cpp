#include "ShaderProgram.h"

#include "Shader.h"

#include <stdexcept>

ShaderProgram::ShaderProgram( bool isCreate/* = false*/ )
{
	if ( isCreate )
		create();
}

ShaderProgram::~ShaderProgram()
{
	release();
}

void ShaderProgram::create()
{
	if ( !isEmpty() )
		throw std::runtime_error( "Impossible to recreate a shader program. It is possible to do only one time." );
	
	id_ = Gl::createProgram();
}

bool ShaderProgram::isEmpty() const noexcept
{
	return id_ == 0;
}

void ShaderProgram::link()
{
	Gl::linkProgram( id_ );
}

void ShaderProgram::attachShader( Shader& shader )
{
	if ( isEmpty() )
		throw std::runtime_error( "Impossible to attach a shader to not created shader program" );

	Gl::attachShader( id_, shader.data() );
}

void ShaderProgram::use()
{
	if ( isEmpty() )
		throw std::runtime_error( "Impossible to use not created shader program" );

	Gl::useProgram( id_ );
}

void ShaderProgram::release()
{
	Gl::deleteProgram( id_ );
	id_ = 0;
}

GLuint ShaderProgram::data() noexcept
{
	return id_;
}
