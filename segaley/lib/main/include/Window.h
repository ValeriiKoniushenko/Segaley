#pragma once
#include <Windows.h>
#include "GLFW.h"
#include "WindowSize.h"
#include "glm/vec2.hpp"
#include "GLM/glm.hpp"
#include "Color.h"

#include <string>
#include <functional>

enum class KeyAction
{
	Press	= GLFW_PRESS,
	Repeat	= GLFW_REPEAT,
	Release = GLFW_RELEASE
};

enum class MouseKey
{
	Button1,
	Button2,
	Button3,
	Button4,
	Button5,
	Button6,
	Button7,
	Button8,
	Last   = Button8,
	Left   = Button1,
	Right  = Button2,
	Middle = Button3
};

class Window final
{
public:
	using mousePosFuncT = std::function< void( float, float ) >;
	using mouseButtonFuncT = std::function< void( MouseKey, KeyAction, int ) >;
	using mouseScrollFuncT = std::function< void( float, float ) >;

	enum Buffer
	{
		Depth = GL_DEPTH_BUFFER_BIT,
		Stencil = GL_STENCIL_BUFFER_BIT,
		Color = GL_COLOR_BUFFER_BIT
	};

public:
	static Window& instance();

	Window( const Window& ) = delete;
	Window( Window& ) = delete;
	Window& operator=( const Window& ) = delete;
	Window& operator=( Window& ) = delete;
	~Window() noexcept;

	bool isEmpty() const noexcept;
	bool isOpen() const;
	GLFWwindow* data();
	const GLFWwindow* data() const;

	void makeContextCurrent();

	void swapBuffers();

	void pollEvents();

	void close() const noexcept;
	void clearScreen( GLbitfield mask, const RGBA& color ) const noexcept;
	void clearScreen( GLbitfield mask, const RGBAf& color ) const noexcept;

	void setSize( WindowSize size ) noexcept;
	WindowSize getSize() const noexcept;

	void setPosition( glm::ivec2 position ) noexcept;
	glm::ivec2 getPosition() const noexcept;

	void setTitle( std::string title ) noexcept;
	std::string getTitle() const noexcept;

	void setMousePosEventCallback( mousePosFuncT func ) noexcept;
	void resetMousePosEventCallback() noexcept;
	void makeMousePosEvent( glm::vec2 pos ) noexcept;

	void setMouseButtonEventCallback( mouseButtonFuncT func ) noexcept;
	void resetMouseButtonEventCallback() noexcept;
	void makeMouseButtonEvent( MouseKey button, KeyAction action, int mods ) noexcept;

	void setMouseScrollEventCallback( mouseScrollFuncT func ) noexcept;
	void resetMouseScrollEventCallback() noexcept;
	void makeMouseScrollEvent( float xOffset, float yOffset ) noexcept;

	HWND getHwnd() noexcept;

	void initialization();

	void disableCursor() noexcept;
	void enableCursor() noexcept;

	const glm::mat4& getOrthoProjection() const noexcept;

private:
	Window() noexcept;
	void initGl();

	glm::ivec2 position_;
	GLFWwindow* window_;
	WindowSize size_;
	std::string title_;
	mousePosFuncT mousePosEventCallback_;
	mouseButtonFuncT mouseButtonEventCallback_;
	mouseScrollFuncT mouseScrollEventCallback_;

	static Window* oneObject_;
	friend void MousePosCallback( GLFWwindow*, double, double );
	friend void MouseButtonCallback( GLFWwindow*, int, int, int );
	friend void MouseWheelCallback( GLFWwindow*, double, double );
};

void MousePosCallback( GLFWwindow* window, double x, double y );
void MouseButtonCallback( GLFWwindow* window, int button, int action, int mods );
void MouseWheelCallback( GLFWwindow* window, double xoffset, double yoffset );
