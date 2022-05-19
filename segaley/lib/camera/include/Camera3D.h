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

	glm::mat4 getMatrix() const override;

	void setPosition( glm::vec3 size ) noexcept;
	void move( glm::vec3 size ) noexcept;
	glm::vec3 getPosition() const noexcept;

	void setRotation( Rotation radian ) noexcept;
	void setYaw( float radian ) noexcept;
	void setPitch( float radian ) noexcept;
	
	void rotate( Rotation radian ) noexcept;	
	void yaw( float radian ) noexcept;
	void pitch( float radian ) noexcept;

	Rotation getRotation() const noexcept;
	float getYaw() const noexcept;
	float getPitch() const noexcept;

private:
	glm::vec3 position_ = glm::vec3( 0.f );
	Rotation rotation_;
};
