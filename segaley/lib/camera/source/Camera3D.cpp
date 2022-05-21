#include "Camera3D.h"

#include "Window.h"

#include "glm/gtc/matrix_transform.hpp"

glm::mat4 Camera3D::getViewMatrix() const
{
	auto view = glm::mat4( 1.0f );

	view = glm::rotate( view, getYaw(), glm::vec3( 1.f, 0.f, 0.f ) );
	view = glm::rotate( view, getPitch(), glm::vec3( 0.f, 1.f, 0.f ) );
	view = glm::translate( view, position_ );

	return view;
}

glm::mat4 Camera3D::getProjectionMatrix() const
{
	auto wndSize = Window::instance().getSize();
	return glm::perspective( glm::radians( 75.0f ), wndSize.getRatio(), 0.1f, 10'000.0f );
}

void Camera3D::setPosition( glm::vec3 size ) noexcept
{
	position_ = size;
}

void Camera3D::move( glm::vec3 offset ) noexcept
{
	if ( !checkMaxSpeed( impulse_ + offset ) )
		impulse_ += offset;
}

void Camera3D::moveForward( float offset )
{
	auto tmp = offset * getForward();
	if ( !checkMaxSpeed( tmp ) )
		move( tmp );
}

void Camera3D::moveBackward( float offset )
{
	auto tmp = offset * -getForward();
	if ( !checkMaxSpeed( tmp ) )
		move( tmp );
}

void Camera3D::moveRight( float offset )
{
	auto tmp = offset * glm::cross( getForward(), getUp() );
	if ( !checkMaxSpeed( tmp ) )
		move( tmp );
}

void Camera3D::moveLeft( float offset )
{
	auto tmp = offset * -glm::cross( getForward(), getUp() );
	if ( !checkMaxSpeed( tmp ) )
		move( tmp );
}

void Camera3D::moveUp( float offset )
{
	auto tmp = offset * -getUp();
	if ( !checkMaxSpeed( tmp ) )
		move( tmp );
}

void Camera3D::moveDown( float offset )
{
	auto tmp = offset * getUp();
	if ( !checkMaxSpeed( tmp ) )
		move( tmp );
}

glm::vec3 Camera3D::getPosition() const noexcept
{
	return position_;
}

void Camera3D::setRotation( Rotation radian ) noexcept
{
	rotation_ = radian;
}

void Camera3D::setYaw( float radian ) noexcept
{
	rotation_.yaw = radian;
}

void Camera3D::setPitch( float radian ) noexcept
{
	rotation_.pitch = radian;
}

void Camera3D::rotate( Rotation radian ) noexcept
{
	rotation_.pitch += radian.pitch;
	rotation_.yaw += radian.yaw;
}

void Camera3D::yaw( float radian ) noexcept
{
	rotation_.yaw += radian;
}

void Camera3D::pitch( float radian ) noexcept
{
	rotation_.pitch += radian;
}

Camera3D::Rotation Camera3D::getRotation() const noexcept
{
	return rotation_;
}

float Camera3D::getYaw() const noexcept
{
	return rotation_.yaw;
}

float Camera3D::getPitch() const noexcept
{
	return rotation_.pitch;
}

glm::vec3 Camera3D::getForward() const noexcept
{
	const auto& r = rotation_;
	return {
		-sin( r.pitch ) * cos( r.yaw ),
		sin( r.yaw ),
		cos( r.pitch ) * cos( r.yaw )
	};
}

glm::vec3 Camera3D::getUp() const noexcept
{
	return {
		0.f,
		1.f,
		0.f
	};
}

void Camera3D::updateImpulse() noexcept
{
	position_ += impulse_;
	impulse_ *= glm::vec3( 0.001 );
}

bool Camera3D::checkMaxSpeed( glm::vec3 vec )
{
	if ( glm::length( impulse_ ) >= 10 )
		return true;

	return false;
}