#include "Camera2D.h"

#include "glm/gtc/matrix_transform.hpp"

glm::mat4 Camera2D::getMatrix() const
{
	auto view = glm::mat4( 1.0f );

	view = glm::translate( view, glm::vec3( -position_, 0.f ) );
	view = glm::rotate( view, -rotation_, glm::vec3( 0.f, 0.f, 1.f ) );

	return view;
}

void Camera2D::setPosition( glm::vec2 size ) noexcept
{
	position_ = size;
}

void Camera2D::move( glm::vec2 size ) noexcept
{
	position_ += size;
}

glm::vec2 Camera2D::getPosition() const noexcept
{
	return position_;
}

void Camera2D::setRotation( float radian ) noexcept
{
	rotation_ = radian;
}

void Camera2D::rotate( float radian ) noexcept
{
	rotation_ += radian;
}

float Camera2D::getRotation() const noexcept
{
	return rotation_;
}
