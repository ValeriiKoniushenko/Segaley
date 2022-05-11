#pragma once
#include "glm/glm.hpp"

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
	Image( std::filesystem::path path = "" )	noexcept( false );

	Image( const Image& obj ) = delete;
	Image( Image&& obj ) noexcept;
	Image& operator=( const Image& obj ) = delete;
	Image& operator=( Image&& obj )	noexcept;

	~Image();

	int	getWidth() const noexcept( false );
	int	getHeight() const noexcept( false );
	glm::ivec2 getSize() const noexcept( false );
	Channel	getChannel() const noexcept( false );
	unsigned char* data() noexcept( false );
	const unsigned char* data() const noexcept( false );
	void loadImage( std::filesystem::path path, bool isFlipVertically = true ) noexcept( false );
	void clear();
	bool isEmpty() const;

private:
	void init_()noexcept;
	unsigned char* data_;
	int width_, height_;
	Channel channel_;
};