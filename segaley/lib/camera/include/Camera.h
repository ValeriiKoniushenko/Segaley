#pragma once

#include "glm/glm.hpp"

class Camera
{
public:
	Camera() = default;
	virtual ~Camera() = default;
	Camera( const Camera& ) = default;
	Camera( Camera&& ) = default;
	Camera& operator=( const Camera& ) = default;
	Camera& operator=( Camera&& ) = default;

	virtual glm::mat4 getMatrix() const = 0;
protected:

};
