#include "Gl.h"

#include <stdexcept>

Gl::Vbo::BoundBuffer Gl::Vbo::bound_;
GLuint Gl::Vao::boundVao_ = 0;
Gl::Texture::BoundTexture Gl::Texture::boundTexture_;

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

	auto* window = glfwCreateWindow( width, height, title.c_str(), nullptr, nullptr );
	if ( !window )
		throw std::runtime_error( "Failed to create new window" );

	return window;
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

void Gl::deleteShader( GLuint program, GLuint shader )
{
	if ( !isAttachedShader( program, shader ) )
		throw std::runtime_error( "The shader cannot be deleted as it was detached." );

	glDeleteShader( shader );

	if ( getShaderiv( shader, Parameter::DeleteStatus ) == GL_FALSE )
		throw std::runtime_error( "Can not delete the shader: " + getShaderInfoLog( shader ) );
}

void Gl::detachShader( GLuint program, GLuint shader ) noexcept
{
	glDetachShader( program, shader );
}

bool Gl::isAttachedShader( GLuint program, GLuint shader ) noexcept
{
	auto shaders = getAttachedShaders( program );
	return std::find( shaders.begin(), shaders.end(), shader ) != shaders.end();
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

void Gl::deleteProgram( GLuint program ) noexcept
{
	glDeleteProgram( program );
}

std::vector< GLuint > Gl::getAttachedShaders( GLuint program ) noexcept
{
	std::vector< GLuint > shaders;
	shaders.resize( static_cast< std::size_t >( getProgramiv( program, Parameter::AttachedShaders ) ) );
	
	if ( shaders.empty() )
		return {};

	glGetAttachedShaders( program, static_cast< GLsizei >( shaders.size() ), nullptr, shaders.data() );
	
	return shaders;
}

std::vector< Gl::Attribute > Gl::getAtrributes( GLuint program ) noexcept
{
	std::vector< Gl::Attribute > attributes;
	attributes.resize( getProgramiv( program, Parameter::ActiveAttributes ) );
	for ( GLuint i = 0; i < attributes.size(); ++i )
	{
		char name[ 128 ];
		GLenum type;
		glGetActiveAttrib( program, i, 128, nullptr, nullptr, &type, name );
		attributes[ i ].name = name;
		attributes[ i ].type = static_cast< DataType >( type );
	}

	return attributes;
}

std::vector< Gl::Uniform > Gl::getUniforms( GLuint program ) noexcept
{
	std::vector< Gl::Uniform > uniforms;
	uniforms.resize( getProgramiv( program, Parameter::ActiveUniforms ) );
	for ( GLuint i = 0; i < uniforms.size(); ++i )
	{
		char name[ 128 ];
		GLenum type;
		glGetActiveUniform( program, i, 128, nullptr, nullptr, &type, name );
		uniforms[ i ].name = name;
		uniforms[ i ].type = static_cast< DataType >( type );
	}

	return uniforms;
}

void Gl::useProgram( GLuint program ) noexcept
{
	glUseProgram( program );
}

void Gl::vertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer )
{
	if ( !Vao::isBind() )
		throw std::runtime_error( "Impossible to configure the vertex attribute pointer without a bound VAO. Try to bind a VAO and try again." );

	glVertexAttribPointer( index, size, type, normalized, stride, pointer );
}

void Gl::enableVertexAttribArray( GLuint index ) noexcept
{
	glEnableVertexAttribArray( index );
}

void Gl::drawArrays( DrawMode mode, GLint first, GLsizei count )
{
	if ( !Vao::isBind() )
		throw std::runtime_error( "Impossible to draw without a bound VAO. Bind a VAO and try again." );

	glDrawArrays( static_cast< GLenum >( mode ), first, count );
}

void Gl::requireValidGl()
{
	switch ( glGetError() )
	{
	case GL_INVALID_ENUM:
		throw std::runtime_error( "Given when an enumeration parameter is not a legal enumeration for that function. This is given only for local problems; if the spec allows the enumeration in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead." );
	case GL_INVALID_VALUE:
		throw std::runtime_error( "Given when a value parameter is not a legal value for that function. This is only given for local problems; if the spec allows the value in certain circumstances, where other parameters or state dictate those circumstances, then GL_INVALID_OPERATION is the result instead." );
	case GL_INVALID_OPERATION:
		throw std::runtime_error( "Given when the set of state for a command is not legal for the parameters given to that command. It is also given for commands where combinations of parameters define what the legal parameters are." );
	case GL_STACK_OVERFLOW:
		throw std::runtime_error( "Given when a stack pushing operation cannot be done because it would overflow the limit of that stack's size." );
	case GL_STACK_UNDERFLOW:
		throw std::runtime_error( "Given when a stack popping operation cannot be done because the stack is already at its lowest point." );
	case GL_OUT_OF_MEMORY:
		throw std::runtime_error( "Given when performing an operation that can allocate memory, and the memory cannot be allocated. The results of OpenGL functions that return this error are undefined; it is allowable for partial execution of an operation to happen in this circumstance." );
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		throw std::runtime_error( "Given when doing anything that would attempt to read from or write/render to a framebuffer that is not complete." );
	case GL_CONTEXT_LOST:
		throw std::runtime_error( "Given if the OpenGL context has been lost, due to a graphics card reset." );
	}
}

GLuint Gl::Vbo::generate() noexcept
{
	GLuint vbo = 0;
	glGenBuffers( 1, &vbo );
	return vbo;
}

void Gl::Vbo::bind( Target target, GLuint buffer ) noexcept
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

void Gl::Vbo::deleteBuffer( GLuint buffer ) noexcept
{
	glDeleteBuffers( 1, &buffer );
}

bool Gl::Vbo::isSetBuffer( Target target )
{
	return bound_.isSetBuffer( target );
}

void Gl::Vbo::BoundBuffer::setBuffer( Target target, GLuint buffer )
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
	default:
		throw std::runtime_error( "Invalid argument. Not implemented." );
	}
}

bool Gl::Vbo::BoundBuffer::isSetBuffer( Target target )
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
	default:
		throw std::runtime_error( "Invalid argument. Not implemented." );
	}
	
	return false;
}

GLuint Gl::Vao::generate() noexcept
{
	GLuint vao = 0;
	glGenVertexArrays( 1, &vao );
	return vao;
}

void Gl::Vao::bind( GLuint vao ) noexcept
{
	glBindVertexArray( vao );
	boundVao_ = vao;
}

bool Gl::Vao::isBind() noexcept
{
	return boundVao_ != 0;
}

void Gl::Vao::reset() noexcept
{
	bind( 0 );
}

void Gl::Vao::deleteBuffer( GLuint buffer ) noexcept
{
	glDeleteVertexArrays( 1, &buffer );
}

GLuint Gl::Texture::generate() noexcept
{
	GLuint texture = 0;
	glGenTextures( 1, &texture );
	return texture;
}

void Gl::Texture::bind( Target target, GLuint texture ) noexcept
{
	glBindTexture( static_cast< GLenum >( target ), texture );
	boundTexture_.setBuffer( target, texture );
}

bool Gl::Texture::isBind( Target target ) noexcept
{
	return boundTexture_.isSetBuffer( target );
}

void Gl::Texture::reset( Target target ) noexcept
{
	bind( target, 0 );
}

void Gl::Texture::deleteBuffer( GLuint texture ) noexcept
{
	glDeleteTextures( 1, &texture );
}

void Gl::Texture::BoundTexture::setBuffer( Target target, GLuint buffer )
{
	switch ( target )
	{
	case Gl::Texture::Target::Texture1d:
		texture1d = buffer;
		break;
	case Gl::Texture::Target::Texture2d:
		texture2d = buffer;
		break;
	case Gl::Texture::Target::Texture3d:
		texture3d = buffer;
		break;
	case Gl::Texture::Target::Texture1dArray:
		texture1dArray = buffer;
		break;
	case Gl::Texture::Target::Texture2dArray:
		texture2dArray = buffer;
		break;
	case Gl::Texture::Target::TextureRectangle:
		textureRectangle = buffer;
		break;
	case Gl::Texture::Target::TextureCubeMap:
		textureCubeMap = buffer;
		break;
	case Gl::Texture::Target::TextureCubeMapArray:
		textureCubeMapArray = buffer;
		break;
	case Gl::Texture::Target::TextureBuffer:
		textureBuffer = buffer;
		break;
	case Gl::Texture::Target::Texture2dMultisample:
		texture2dMultisample = buffer;
		break;
	case Gl::Texture::Target::Texture2dMultisampleArray:
		texture2dMultisampleArray = buffer;
		break;
	default:
		throw std::runtime_error( "Invalid argument. Not implemented." );
	}
}

bool Gl::Texture::BoundTexture::isSetBuffer( Target target )
{
	switch ( target )
	{
	case Gl::Texture::Target::Texture1d:
		return static_cast< bool >( texture1d );
	case Gl::Texture::Target::Texture2d:
		return static_cast< bool >( texture2d );
	case Gl::Texture::Target::Texture3d:
		return static_cast< bool >( texture3d );
	case Gl::Texture::Target::Texture1dArray:
		return static_cast< bool >( texture1dArray );
	case Gl::Texture::Target::Texture2dArray:
		return static_cast< bool >( texture2dArray );
	case Gl::Texture::Target::TextureRectangle:
		return static_cast< bool >( textureRectangle );
	case Gl::Texture::Target::TextureCubeMap:
		return static_cast< bool >( textureCubeMap );
	case Gl::Texture::Target::TextureCubeMapArray:
		return static_cast< bool >( textureCubeMapArray );
	case Gl::Texture::Target::TextureBuffer:
		return static_cast< bool >( textureBuffer );
	case Gl::Texture::Target::Texture2dMultisample:
		return static_cast< bool >( texture2dMultisample );
	case Gl::Texture::Target::Texture2dMultisampleArray:
		return static_cast< bool >( texture2dMultisampleArray );
	default:
		throw std::runtime_error( "Invalid argument. Not implemented." );
	}

	return false;
}

Gl::Texture::MagFilter Gl::Texture::stringToMagFilter( const std::string& filter )
{
	if ( filter == "Linear" ) return MagFilter::Linear;
	else if ( filter == "Nearest" ) return MagFilter::Nearest;

	throw std::runtime_error( "Invalid mag-filter name." );
}

Gl::Texture::MinFilter Gl::Texture::stringToMinFilter( const std::string& filter )
{
	if ( filter == "Linear" ) return MinFilter::Linear;
	else if ( filter == "Nearest" ) return MinFilter::Nearest;
	else if ( filter == "NearestMipmapNearest" ) return MinFilter::NearestMipmapNearest;
	else if ( filter == "LinearMipmapNearest" ) return MinFilter::LinearMipmapNearest;
	else if ( filter == "NearestMipmapLinear" ) return MinFilter::NearestMipmapLinear;
	else if ( filter == "LinearMipmapLinear" ) return MinFilter::LinearMipmapLinear;

	throw std::runtime_error( "Invalid min-filter name." );
}

void Gl::Texture::setMinFilter( MinFilter filter, Target target )
{
	requireBind( target );
	glTexParameteri( static_cast< GLenum >( target ), GL_TEXTURE_MIN_FILTER, static_cast< GLint >( filter ) );
}

void Gl::Texture::setMagFilter( MagFilter filter, Target target )
{
	requireBind( target );
	glTexParameteri( static_cast< GLenum >( target ), GL_TEXTURE_MAG_FILTER, static_cast< GLint >( filter ) );
}

void Gl::Texture::setWrapS( Wrap wrap, Target target )
{
	requireBind( target );
	glTexParameteri( static_cast< GLenum >( target ), GL_TEXTURE_WRAP_S, static_cast< GLint >( wrap ) );
}

void Gl::Texture::setWrapT( Wrap wrap, Target target )
{
	requireBind( target );
	glTexParameteri( static_cast< GLenum >( target ), GL_TEXTURE_WRAP_T, static_cast< GLint >( wrap ) );
}

void Gl::Texture::setWrapR( Wrap wrap, Target target )
{
	requireBind( target );
	glTexParameteri( static_cast< GLenum >( target ), GL_TEXTURE_WRAP_R, static_cast< GLint >( wrap ) );
}

void Gl::Texture::active( GLenum num )
{
	static const size_t maxCountActiveTextures = Texture::getMaxCountActiveTextures();
	
	using namespace std::string_literals;
	if ( num >= maxCountActiveTextures )
		throw std::runtime_error( "Your device does not support such count of textures. Impossible to active "s + std::to_string( num ) + "th texture." );

	glActiveTexture( GL_TEXTURE0 + num );
}

size_t Gl::Texture::getMaxCountActiveTextures() noexcept
{
	GLint total_units = 0;
	glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &total_units );
	return static_cast< size_t >( total_units );
}

void Gl::Texture::texImage2D( Target target, GLint level, Format internalformat, GLsizei width, GLsizei height, GLint border, Format format, DataType type, const void* pixels )
{
	requireBind( target );

	glTexImage2D(
		static_cast< GLenum >( target ),
		level,
		static_cast< GLint >( internalformat ),
		width,
		height,
		border,
		static_cast< GLint >( format ),
		static_cast< GLenum >( type ),
		pixels
		);
}

void Gl::Texture::generateMipmap( Target target )
{
	requireBind( target );
	glGenerateMipmap( static_cast< GLenum >( target ) );
}

bool Gl::Texture::isSetBuffer( Target target )
{
	return boundTexture_.isSetBuffer( target );
}

void Gl::Texture::requireBind( Target target )
{
	if ( !isBind( target ) )
		throw std::runtime_error( "The texture was not bound. Bind it and try again." );
}
