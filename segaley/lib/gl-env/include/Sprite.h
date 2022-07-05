#pragma once

#include "Gl.h"
#include "glm/glm.hpp"

#include <functional>

class Vao;
class Vbo;
class ShaderProgram;
class Texture2D;
class Camera;

class Sprite final
{
public:
	Sprite() = default;
	~Sprite() = default;
	Sprite( const Sprite& ) = delete;
	Sprite( Sprite&& ) = delete;
	Sprite& operator=( const Sprite& ) = delete;
	Sprite& operator=( Sprite&& ) = delete;

	void draw( ShaderProgram& program, const Camera& camera );
	void setTexture2D( Texture2D& texture ) noexcept;

	void setSize( float size ) noexcept;
	float getSize() const noexcept;

	void setPosition( glm::vec2 size ) noexcept;
	void move( glm::vec2 size ) noexcept;
	glm::vec2 getPosition() const noexcept;

	void setOrigin( glm::vec2 origin ) noexcept;
	glm::vec2 getOrigin() const noexcept;

	void setRotation( float radian ) noexcept;
	void rotate( float radian ) noexcept;
	float getRotation() const noexcept;

private:
	void configureShader( ShaderProgram& program );

private:
	float size_ = 50.f;
	float rotation_ = 0.f;
	glm::vec2 position_ = glm::vec2( 0.f );
	glm::vec2 origin_ = glm::vec2( 0.f );
	Texture2D* texture_ = nullptr;
};
