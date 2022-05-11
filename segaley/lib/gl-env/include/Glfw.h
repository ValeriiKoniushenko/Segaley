#pragma once
#include <glad.h>
#include <GLFW/glfw3.h>
#include <memory>

class Glfw final
{
public:
	static Glfw& instance(
		int vMajor,
		int vMinor,
		int profile = GLFW_OPENGL_CORE_PROFILE,
		bool forwardCompat = true
	);
	
	~Glfw();
	static bool isInit() noexcept;

private:
	Glfw( int vMajor, int vMinor, int profile, bool forwardCompat );

	static std::unique_ptr< Glfw > pointer;
};