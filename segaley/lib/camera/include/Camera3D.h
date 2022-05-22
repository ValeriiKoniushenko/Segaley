#pragma once

#include "Camera.h"
#include "Keyboard.h"

class Camera3D final : public Camera
{
public:
	struct Rotation final
	{
		float yaw = 0.f;
		float pitch = 0.f;
	};

	struct ControlConfig
	{
		Keyboard::Key up = Keyboard::Key::Space;
		Keyboard::Key down = Keyboard::Key::C;
		Keyboard::Key left = Keyboard::Key::A;
		Keyboard::Key right = Keyboard::Key::D;
		Keyboard::Key forward = Keyboard::Key::W;
		Keyboard::Key backward = Keyboard::Key::S;
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

	void updateControl() noexcept;
	void updateImpulse() noexcept;

	void setControlConfig( const ControlConfig& controlConfig ) noexcept;
	ControlConfig getControlConfig() const noexcept;

	void setSmoothLevel( float k );
	float getSmoothLevel() const noexcept;

	void setSpeed( float speed );
	float getSpeed() const noexcept;

	void setTopSpeed( float speed );
	float getTopSpeed() const noexcept;

private:
	bool checkMaxSpeed( glm::vec3 vec );

private:
	glm::vec3 position_ = glm::vec3( 0.f );
	glm::vec3 impulse_ = glm::vec3( 0.f );
	float smoothK_ = 0.995f;
	float topSpeed_ = 0.1f;
	float speed_ = 0.01f;
	Rotation rotation_;
	ControlConfig controlConfig_;
};
