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
	if ( bufferLength == 0u )
		return {};

	std::unique_ptr< GLchar[] > message( new GLchar[ bufferLength ] );
	glGetShaderInfoLog( shader, bufferLength, &logLength, message.get() );
	return message.get();
}

GLint Gl::getProgramiv( GLuint program, Parameter parameter ) noexcept
{
	GLint status = 0;
	glGetProgramiv( program, static_cast< GLenum >( parameter ), &status );
	return status;
}

std::string Gl::getProgramInfoLog( GLuint program ) noexcept
{
	GLsizei logLength = 0;
	GLsizei bufferLength = getProgramiv( program, Parameter::InfoLogLength );
	if ( bufferLength == 0u )
		return {};

	std::unique_ptr< GLchar[] > message( new GLchar[ bufferLength ] );
	glGetProgramInfoLog( program, bufferLength, &logLength, message.get() );
	return message.get();
}

GLuint Gl::createProgram() noexcept
{
	return glCreateProgram();
}

void Gl::attachShader( GLuint program, GLuint shader ) noexcept
{
	glAttachShader( program, shader );
}

void Gl::linkProgram( GLuint program )
{
	glLinkProgram( program );

	if ( getProgramiv( program, Parameter::LinkStatus ) == GL_FALSE )
		throw std::runtime_error( "Can not compile shader program: " + getProgramInfoLog( program ) );
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
	bound_.setBuffer( target, buffer );
}

void Gl::Vbo::bufferData( Target target, GLsizeiptr size, const void* data, DrawType drawType )
{
	if ( !bound_.isSetBuffer( target ) )
		throw std::runtime_error( "Can not to put data to the buffer without bound target. Try to bind a buffer and try again" );

	glBufferData( static_cast< GLenum >( target ), size, data, static_cast< GLenum >( drawType ) );
}

void Gl::Vbo::BoundBuffer::setBuffer( Target target, GLuint buffer ) noexcept
{
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

bool Gl::Vbo::BoundBuffer::isSetBuffer( Target target ) noexcept
{
	switch ( target )
	{
	case Gl::Vbo::Target::Array:
		return static_cast< bool >( bound_.arrayBuffer );
	case Gl::Vbo::Target::AtomicCounter:
		return static_cast< bool >( bound_.atomicCounterBuffer );
	case Gl::Vbo::Target::CopyRead:
		return static_cast< bool >( bound_.copyReadBuffer );
	case Gl::Vbo::Target::CopyWrite:
		return static_cast< bool >( bound_.copyWriteBuffer );
	case Gl::Vbo::Target::DispatchIndirect:
		return static_cast< bool >( bound_.dispatchIndirectBuffer );
	case Gl::Vbo::Target::DrawIndirect:
		return static_cast< bool >( bound_.drawIndirectBuffer );
	case Gl::Vbo::Target::ElementArray:
		return static_cast< bool >( bound_.elementArrayBuffer );
	case Gl::Vbo::Target::PixelPack:
		return static_cast< bool >( bound_.pixelPackBuffer );
	case Gl::Vbo::Target::PixelUnpack:
		return static_cast< bool >( bound_.pixelUnpackBuffer );
	case Gl::Vbo::Target::Query:
		return static_cast< bool >( bound_.queryBuffer );
	case Gl::Vbo::Target::ShaderStorage:
		return static_cast< bool >( bound_.shaderStorageBuffer );
	case Gl::Vbo::Target::Texture:
		return static_cast< bool >( bound_.textureBuffer );
	case Gl::Vbo::Target::TransformFeedback:
		return static_cast< bool >( bound_.transformFeedbackBuffer );
	case Gl::Vbo::Target::Uniform:
		return static_cast< bool >( bound_.uniformBuffer );
	}
}
