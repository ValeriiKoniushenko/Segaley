#pragma once
#include "glm/glm.hpp"
#include "Gl.h"

#include <filesystem>

class Image final
{
public:
	enum class Channel
	{
		//Next values were taken from the stb_image.h documentation.
		None = 0,
		Grey = 1,
		GreyA = 2,
		RGB = 3,
		RGBA = 4
	};

public:
	Image( std::filesystem::path path = "" );
	~Image();

	Image( const Image& obj ) = delete;
	Image( Image&& obj ) noexcept;
	Image& operator=( const Image& obj ) = delete;
	Image& operator=( Image&& obj )	noexcept;

	static Gl::Format toGlFormat( Channel ch );

	int	getWidth() const;
	int	getHeight() const;
	glm::ivec2 getSize() const;
	Channel	getChannel() const;
	unsigned char* data();
	const unsigned char* data() const;
	void loadImage( std::filesystem::path path, bool isFlipVertically = true );
	void clear() noexcept;
	bool isEmpty() const noexcept;

private:
	void init_() noexcept;

private:
	unsigned char* data_ = nullptr;
	int width_ = 0;
	int height_ = 0;
	Channel channel_ = Channel::None;
};