#include "Gl.h"

#include <stdexcept>

void Gl::gladInitialization()
{
	if ( !glfwGetCurrentContext() )
		throw std::runtime_error( "Impossible to initialize a GLAD without the choosed context" );

	if ( !gladLoadGLLoader( reinterpret_cast< GLADloadproc >( glfwGetProcAddress ) ) )
		throw std::runtime_error( "Failed to initialize GLAD" );
}

GLFWwindow* Gl::createWindow( unsigned short width, unsigned short height, const std::string& title )
{
	if ( !Glfw::isInit() )
		throw std::runtime_error( "Impossible to create new window without a GLFW initialization" );

	if ( !glfwCreateWindow( width, height, title.c_str(), nullptr, nullptr ) )
		throw std::runtime_error( "Failed to create new window" );
}

GLuint Gl::createShader( Shader type ) noexcept
{
	return glCreateShader( static_cast< GLenum >( type ) );
}

void Gl::shaderSource( GLuint shader, GLsizei count, const std::string& string )
{
	if ( string.empty() )
		throw std::runtime_error( "Was passed an empty string" );

	auto source = string.c_str();
	glShaderSource( shader, count, &source, nullptr );
}

void Gl::compileShader( GLuint shader )
{
	glCompileShader( shader );

	if ( getShaderiv( shader, Parameter::CompileStatus ) != GL_TRUE )
		throw std::runtime_error( "Shader can not be compiled: " + getShaderInfoLog( shader ) );
}

GLint Gl::getShaderiv( GLuint shader, Parameter parameter ) noexcept
{
	GLint status = 0;
	glGetShaderiv( shader, static_cast< GLenum >( parameter ), &status);
	return status;
}

std::string Gl::getShaderInfoLog( GLuint shader ) noexcept
{
	GLsizei logLength = 0;
	GLsizei bufferLength = getShaderiv( shader, Parameter::InfoLogLength );
	std::unique_ptr< GLchar[] > message( new GLchar[ bufferLength ] );
	glGetShaderInfoLog( shader, bufferLength, &logLength, message.get() );
	return message.get();
}
