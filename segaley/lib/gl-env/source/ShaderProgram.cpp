#include "ShaderProgram.h"

#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"

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

void ShaderProgram::setup( std::filesystem::path pathToVertex, std::filesystem::path pathToFragment )
{
	release();

	create();

	Shader fragmentShader( Gl::Shader::Vertex, *this );
	fragmentShader.loadFromFile( pathToVertex );
	fragmentShader.compile();

	Shader vertexShader( Gl::Shader::Fragment, *this );
	vertexShader.loadFromFile( pathToFragment );
	vertexShader.compile();

	attachShader( fragmentShader );
	attachShader( vertexShader );
	link();
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

void ShaderProgram::use() const
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

void ShaderProgram::uniform( const std::string& name, const glm::mat3& data )
{
	auto uniformId = uniforms_.at( name );
	glUniformMatrix3fv( uniformId, 1, GL_FALSE, glm::value_ptr( data ) );
}

void ShaderProgram::uniform( const std::string& name, const glm::mat4& data )
{
	auto uniformId = uniforms_.at( name );
	glUniformMatrix4fv( uniformId, 1, GL_FALSE, glm::value_ptr( data ) );
}
