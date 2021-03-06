#include "Sprite.h"

#include "Vbo.h"
#include "Vao.h"
#include "Gl.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Window.h"
#include "glm/gtc/matrix_transform.hpp"

void Sprite::draw( ShaderProgram& program, const Camera& camera )
{
	configureShader( program );

	auto projection = camera.getProjectionMatrix();
	auto model = glm::mat4( 1.0f );
	auto view = camera.getViewMatrix();

	view = glm::translate( view, glm::vec3( 0.f, 0.f, -700.f ) );
	model = glm::translate( model, glm::vec3( position_, 0.f ) );
	model = glm::rotate( model, rotation_, glm::vec3( 0.f, 0.f, 1.f ) );
	model = glm::translate( model, glm::vec3( -origin_, 0.f ) );

	if ( texture_ )
		texture_->bind();
    else
        Gl::Texture::reset( Gl::Texture::Target::Texture2d );

	program.use();
	program.uniform( "uProjection", projection );
	program.uniform( "uModel", model );
	program.uniform( "uView", view );
	
	Gl::drawArrays( Gl::DrawMode::Triangles, 0, 6 );
}

void Sprite::setTexture2D( Texture2D& texture ) noexcept
{
	texture_ = &texture;
}

void Sprite::setSize( glm::vec2 size ) noexcept
{
	size_ = size;
}

glm::vec2 Sprite::getSize() const noexcept
{
	return size_;
}

void Sprite::setPosition( glm::vec2 size ) noexcept
{
	position_ = size;
}

void Sprite::move( glm::vec2 size ) noexcept
{
	position_ += size;
}

glm::vec2 Sprite::getPosition() const noexcept
{
	return position_;
}

void Sprite::setOrigin( glm::vec2 origin ) noexcept
{
	origin_ = origin;
}

glm::vec2 Sprite::getOrigin() const noexcept
{
	return origin_;
}

void Sprite::setRotation( float radian ) noexcept
{
	rotation_ = radian;
}

void Sprite::rotate( float radian ) noexcept
{
	rotation_ += radian;
}

float Sprite::getRotation() const noexcept
{
	return rotation_;
}

void Sprite::configureShader( ShaderProgram& program )
{
	static Vbo vbo( Gl::Vbo::Target::Array );
	static Vao vao;
	static bool isInit = false;

	if ( !isInit )
	{
		vbo.generate();
		vbo.bind();
		vbo.bufferData( std::vector< float >{
			0.f,   0.f,   0.0f,    0.f, 0.f,
			0.f,   size_.y, 0.0f,    0.f, 1.f,
			size_.x, size_.y, 0.0f,    1.f, 1.f,
			size_.x, size_.y, 0.0f,    1.f, 1.f,
			size_.x, 0.f,   0.0f,    1.f, 0.f,
			0.f,   0.f,   0.0f,    0.f, 0.f
		}, Gl::Vbo::DrawType::StaticDraw );
		isInit = true;

		vao.generate();
		vao.bind();

		if ( texture_ )
			texture_->bind();
		else
			Gl::Texture::bind( Gl::Texture::Target::Texture2d, 0 );

        program.configure();
	}

	vao.bind();
}