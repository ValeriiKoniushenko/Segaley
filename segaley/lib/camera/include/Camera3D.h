#pragma once

#include "Camera.h"


class Camera3D final : public Camera
{
public:
	struct Rotation final
	{
		float yaw = 0.f;
		float pitch = 0.f;
	};

public:
	Camera3D() = default;
	~Camera3D() = default;
	Camera3D( const Camera3D& ) = delete;
	Camera3D( Camera3D&& ) = delete;
	Camera3D& operator=( const Camera3D& ) = delete;
	Camera3D& operator=( Camera3D&& ) = delete;

	glm::mat4 getViewMatrix() const override;
	glm::mat4 getProjectionMatrix() const override;

	void setPosition( glm::vec3 size ) noexcept;
	void move( glm::vec3 offset ) noexcept;
	glm::vec3 getPosition() const noexcept;
	void moveForward( float offset );
	void moveBackward( float offset );
	void moveRight( float offset );
	void moveLeft( float offset );
	void moveUp( float offset );
	void moveDown( float offset );

	void setRotation( Rotation radian ) noexcept;
	void setYaw( float radian ) noexcept;
	void setPitch( float radian ) noexcept;
	
	void rotate( Rotation radian ) noexcept;	
	void yaw( float radian ) noexcept;
	void pitch( float radian ) noexcept;

	Rotation getRotation() const noexcept;
	float getYaw() const noexcept;
	float getPitch() const noexcept;

	glm::vec3 getForward() const noexcept;
	glm::vec3 getUp() const noexcept;

	void updateImpulse() noexcept;

private:
	bool checkMaxSpeed( glm::vec3 vec );

private:
	glm::vec3 position_ = glm::vec3( 0.f );
	glm::vec3 impulse_ = glm::vec3( 0.f );
	Rotation rotation_;
};
