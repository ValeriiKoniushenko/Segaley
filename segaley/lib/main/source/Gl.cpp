#include "Gl.h"

#include <stdexcept>

Gl::Vbo::BoundBuffer Gl::Vbo::bound_;

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

GLuint Gl::Vbo::genBuffer() noexcept
{
	GLuint vbo = 0;
	glGenBuffers( 1, &vbo );
	return vbo;
}

void Gl::Vbo::bindBuffer( Target target, GLuint buffer ) noexcept
{
	glBindBuffer( static_cast< GLenum >( target ), buffer );

	switch ( target )
	{
	case Gl::Vbo::Target::Array:
		bound_.arrayBuffer = buffer;
		break;
	case Gl::Vbo::Target::AtomicCounter:
		bound_.atomicCounterBuffer = buffer;
		break;
	case Gl::Vbo::Target::CopyRead:
		bound_.copyReadBuffer = buffer;
		break;
	case Gl::Vbo::Target::CopyWrite:
		bound_.copyWriteBuffer = buffer;
		break;
	case Gl::Vbo::Target::DispatchIndirect:
		bound_.dispatchIndirectBuffer = buffer;
		break;
	case Gl::Vbo::Target::DrawIndirect:
		bound_.drawIndirectBuffer = buffer;
		break;
	case Gl::Vbo::Target::ElementArray:
		bound_.elementArrayBuffer = buffer;
		break;
	case Gl::Vbo::Target::PixelPack:
		bound_.pixelPackBuffer = buffer;
		break;
	case Gl::Vbo::Target::PixelUnpack:
		bound_.pixelUnpackBuffer = buffer;
		break;
	case Gl::Vbo::Target::Query:
		bound_.queryBuffer = buffer;
		break;
	case Gl::Vbo::Target::ShaderStorage:
		bound_.shaderStorageBuffer = buffer;
		break;
	case Gl::Vbo::Target::Texture:
		bound_.textureBuffer = buffer;
		break;
	case Gl::Vbo::Target::TransformFeedback:
		bound_.transformFeedbackBuffer = buffer;
		break;
	case Gl::Vbo::Target::Uniform:
		bound_.uniformBuffer = buffer;
		break;
	}
}
