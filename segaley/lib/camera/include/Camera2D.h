#pragma once

#include "Camera.h"

class Camera2D final : public Camera
{
public:
	Camera2D() = default;
	~Camera2D() = default;
	Camera2D( const Camera2D& ) = delete;
	Camera2D( Camera2D&& ) = delete;
	Camera2D& operator=( const Camera2D& ) = delete;
	Camera2D& operator=( Camera2D&& ) = delete;
	
	glm::mat4 getMatrix() const override;

	void setPosition( glm::vec2 size ) noexcept;
	void move( glm::vec2 size ) noexcept;
	glm::vec2 getPosition() const noexcept;

	void setRotation( float radian ) noexcept;
	void rotate( float radian ) noexcept;
	float getRotation() const noexcept;

private:
	glm::vec2 position_ = glm::vec2( 0.f );
	float rotation_ = 0.f;
};
