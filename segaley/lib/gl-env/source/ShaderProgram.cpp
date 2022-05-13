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
	
	for ( auto& attribute : Gl::getAtrributes( id_ ) )
		attributes_.emplace( attribute.name, attribute.id );

	for ( auto& uniform : Gl::getUniforms( id_ ) )
		uniforms_.emplace( uniform.name, uniform.id );
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
	attributes_.clear();
	uniforms_.clear();
}

GLuint ShaderProgram::data() noexcept
{
	return id_;
}

void ShaderProgram::vertexAttribPointer( const std::string& attribute, GLint size, Gl::DataType type, bool normalized, GLsizei stride, const void* pointer )
{
	auto attributeId = attributes_.at( attribute );

	Gl::vertexAttribPointer(
		attributeId,
		size,
		type,
		normalized,
		stride,
		pointer
	);

	Gl::enableVertexAttribArray( attributeId );
}

void ShaderProgram::uniform( const std::string& name, float data )
{
	auto uniformId = uniforms_.at( name );
	glUniform1f( uniformId, data );
}

void ShaderProgram::uniform( const std::string& name, glm::vec2 data )
{
	auto uniformId = uniforms_.at( name );
	glUniform2f( uniformId, data.x, data.y );
}

void ShaderProgram::uniform( const std::string& name, glm::vec3 data )
{
	auto uniformId = uniforms_.at( name );
	glUniform3f( uniformId, data.x, data.y, data.z );
}