#include "Window.h"

#include "GLM/gtx/transform.hpp"
#include "Gl.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <stdexcept>
#include <sstream>

Window* Window::oneObject_ = nullptr;

Window& Window::instance()
{
	static std::unique_ptr< Window > obj;

	if ( !obj )
	{
		obj = std::unique_ptr< Window >( new Window );
		obj->initialization();
	}

	return *obj;
}

Window::Window() noexcept :
	position_( 100, 100 ),
	window_( nullptr ),
	size_{ 1024, 768 },
	title_( "Application" )
{	
}

Window::~Window() noexcept
{
	close();
}

bool Window::isEmpty() const noexcept
{
	return !window_;
}

bool Window::isOpen() const
{
	if( isEmpty() )
		throw std::runtime_error( "Impossible to give not existing data" );

	return !glfwWindowShouldClose( window_ );
}

void Window::makeContextCurrent()
{
	if( isEmpty() )
		throw std::runtime_error( "Impossible to set GLAD context to not existing window" );

	glfwMakeContextCurrent( window_ );
}

void Window::swapBuffers()
{
	if( isEmpty() )
		throw std::runtime_error( "Impossible to give not existing data" );

	glfwSwapBuffers( window_ );
}

void Window::pollEvents()
{
	if( isEmpty() )
		throw std::runtime_error( "Impossible to give not existing data" );

	glfwPollEvents();
}

void Window::close() const noexcept
{
	if ( !oneObject_ )
		return;

	glfwDestroyWindow( window_ );
	oneObject_ = nullptr;
}

void Window::clearScreen( GLbitfield mask, const RGBA& color ) const noexcept
{
	clearScreen( mask, Color::convertToF( color ) );
}

void Window::clearScreen( GLbitfield mask, const RGBAf& color ) const noexcept
{
	glClearColor( color.r, color.g, color.b, color.a );
	glClear( mask );
}

void Window::setSize( WindowSize size ) noexcept
{
	size_ = size;
	glfwSetWindowSize( window_, size_.width, size_.height );
	glViewport( 0, 0, size_.width, size_.height );
}

WindowSize Window::getSize() const noexcept
{
	return size_;
}

void Window::setPosition( glm::ivec2 position ) noexcept
{
	position_ = position;
	glfwSetWindowPos( window_, position_.x, position_.y );
}

glm::ivec2 Window::getPosition() const noexcept
{
	return position_;
}

void Window::setTitle( std::string title ) noexcept
{
	title_ = title;
	glfwSetWindowTitle( window_, title_.c_str() );
}

std::string Window::getTitle() const noexcept
{
	return title_;
}

void Window::setMousePosEventCallback( mousePosFuncT func ) noexcept
{
	mousePosEventCallback_ = func;
}

void Window::resetMousePosEventCallback() noexcept
{
	mousePosEventCallback_ = nullptr;
}

void Window::makeMousePosEvent( glm::vec2 pos ) noexcept
{
	if( mousePosEventCallback_ )
		mousePosEventCallback_( pos.x, pos.y );
}

void Window::setMouseButtonEventCallback( mouseButtonFuncT func ) noexcept
{
	mouseButtonEventCallback_ = func;
}

void Window::resetMouseButtonEventCallback() noexcept
{
	mouseButtonEventCallback_ = nullptr;
}

void Window::makeMouseButtonEvent( MouseKey button, KeyAction action, int mods ) noexcept
{
	if( mouseButtonEventCallback_ )
		mouseButtonEventCallback_( button, action, mods );
}

void Window::setMouseScrollEventCallback( mouseScrollFuncT func ) noexcept
{
	mouseScrollEventCallback_ = func;
}

void Window::resetMouseScrollEventCallback() noexcept
{
	mouseScrollEventCallback_ = nullptr;
}

void Window::makeMouseScrollEvent( float xOffset, float yOffset ) noexcept
{
	if( mouseScrollEventCallback_ )
		mouseScrollEventCallback_( xOffset, yOffset );
}

HWND Window::getHwnd() noexcept
{
	return glfwGetWin32Window( window_ );
}

GLFWwindow* Window::data()
{
	if( isEmpty() )
		throw std::runtime_error( "Impossible to give not existing data" );

	return window_;
}

const GLFWwindow* Window::data() const
{
	if( isEmpty() )
		throw std::runtime_error( "Impossible to give not existing data" );

	return window_;
}

void Window::initGl()
{
	if( !gladLoadGL() )
		throw std::runtime_error( "Failed to initialize GL" );
}

void Window::initialization()
{
	static bool isInit = false;

	if ( isInit )
		return;


	Glfw::instance( 3, 3 );

	window_ = Gl::createWindow( size_.width, size_.height, title_ );
	
	makeContextCurrent();

	Gl::gladInitialization();
	
	glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
	glDebugMessageCallback( DebugMessageCallback, nullptr );
	
	initGl();
	
	glViewport( 0, 0, size_.width, size_.height );
	
	glfwSetCursorPosCallback( window_, MousePosCallback );
	glfwSetMouseButtonCallback( window_, MouseButtonCallback );
	glfwSetScrollCallback( window_, MouseWheelCallback );


	setPosition( position_ );

	oneObject_ = this;
	isInit = true;
}

void Window::disableCursor() noexcept
{
	glfwSetInputMode( data(), GLFW_CURSOR, GLFW_CURSOR_DISABLED );
}

void Window::enableCursor() noexcept
{
	glfwSetInputMode( data(), GLFW_CURSOR, GLFW_CURSOR_NORMAL );
}

const glm::mat4& Window::getOrthoProjection() const noexcept
{
	static bool isInit = false;
	static auto ortho = glm::mat4( 1.f );
	static auto lastSize = getSize();
	
	if ( lastSize != getSize() || !isInit  )
	{
		auto wndSize = glm::fvec2( static_cast< float >( getSize().width ),
								   static_cast< float >( getSize().height ) );
		ortho = glm::ortho( 0.f, wndSize.x, 0.f, wndSize.y );

		lastSize = getSize();
		isInit = true;
	}

	return ortho;
}

void MousePosCallback( GLFWwindow* window, double x, double y )
{
	Window::oneObject_->makeMousePosEvent( glm::vec2( static_cast< float >( x ), static_cast< float >( y ) ) );
}

void MouseButtonCallback( GLFWwindow* window, int button, int action, int mods )
{
	Window::oneObject_->makeMouseButtonEvent( static_cast< MouseKey >( button ), static_cast< KeyAction >( action ), mods );
}

void MouseWheelCallback( GLFWwindow* window, double xOffset, double yOffset )
{
	Window::oneObject_->makeMouseScrollEvent( static_cast< float >( xOffset ), static_cast< float >( yOffset ) );
}

void DebugMessageCallback( GLenum source, GLenum type, GLuint id,
									  GLenum severity, GLsizei length,
									  const GLchar* msg, const void* data )
{
	const char* _source = nullptr;
	const char* _type = nullptr;
	const char* _severity = nullptr;

	switch ( source )
	{
	case GL_DEBUG_SOURCE_API:
		_source = "API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		_source = "WINDOW SYSTEM";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		_source = "SHADER COMPILER";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		_source = "THIRD PARTY";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		_source = "APPLICATION";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		_source = "UNKNOWN";
		break;
	default:
		_source = "UNKNOWN";
		break;
	}

	switch ( type )
	{
	case GL_DEBUG_TYPE_ERROR:
		_type = "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		_type = "DEPRECATED BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		_type = "UDEFINED BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		_type = "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		_type = "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		_type = "OTHER";
		break;
	case GL_DEBUG_TYPE_MARKER:
		_type = "MARKER";
		break;
	default:
		_type = "UNKNOWN";
		break;
	}

	switch ( severity )
	{
	case GL_DEBUG_SEVERITY_HIGH:
		_severity = "HIGH";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		_severity = "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		_severity = "LOW";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		_severity = "NOTIFICATION";
		break;
	default:
		_severity = "UNKNOWN";
		break;
	}

	std::stringstream ss;
	ss << "[ " << id << " ] [" << _type << "] [ " << _severity << " ] ";
	ss << "a problem was raised from " << _source << ": " << msg;
}