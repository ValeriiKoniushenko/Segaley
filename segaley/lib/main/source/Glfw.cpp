#include "Glfw.h"

std::unique_ptr< Glfw > Glfw::pointer;

Glfw& Glfw::instance( int vMajor, int vMinor, int profile, bool forwardCompat )
{
	if ( !pointer )
		pointer = std::unique_ptr< Glfw >( new Glfw( vMajor, vMinor, profile, forwardCompat ) );

	return *pointer.get();
}

Glfw::Glfw( int vMajor, int vMinor, int profile, bool forwardCompat )
{
	glfwInit();
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, vMajor );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, vMinor );
	glfwWindowHint( GLFW_OPENGL_PROFILE, profile );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, forwardCompat );

	#ifdef __APPLE__
	glfwWindowHint( Glfw_OPENGL_FORWARD_COMPAT, forwardCompat );
	#endif
}

Glfw::~Glfw()
{
	glfwTerminate();
}

bool Glfw::isInit() noexcept
{
	return pointer.get();
}
