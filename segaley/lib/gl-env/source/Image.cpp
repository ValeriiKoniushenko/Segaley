#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdexcept>

Image::Image( std::filesystem::path path )
{
    init_();
    if( path != "" )
        loadImage( path );
}

Image::~Image()
{
    clear();
}

Image::Image( Image&& obj ) noexcept
{
    init_();
    *this = std::move( obj );
}

Image& Image::operator=( Image&& obj ) noexcept
{
    clear();
    this->data_ = obj.data_;
    this->width_ = obj.width_;
    this->height_ = obj.height_;
    this->channel_ = obj.channel_;
    obj.init_();
    return *this;
}

void Image::init_() noexcept
{
    data_ = nullptr;
    width_ = height_ = 0;
    channel_ = Channel::None;
}

Gl::Format Image::toGlFormat( Channel ch )
{
    switch ( ch )
    {
    case Image::Channel::RGB:
        return Gl::Format::Rgb;
    case Image::Channel::RGBA:
        return Gl::Format::Rgba;
    }

    throw std::runtime_error( "The GL format not found." );
    
    return Gl::Format::Green;
}

int Image::getWidth() const
{
    if( !data_ ) 
        throw std::runtime_error( "Image wasn't loaded. It can't take a width without photo" );

    return width_;
}

int Image::getHeight() const
{
    if( !data_ ) 
        throw std::runtime_error( "Image wasn't loaded. It can't take a height without photo" );

    return height_;
}

glm::ivec2 Image::getSize() const
{
    if( !data_ ) 
        throw std::runtime_error( "Image wasn't loaded. It can't take a height without photo" );

    return glm::ivec2( width_, height_ );
}

Image::Channel Image::getChannel() const
{
    if( !data_ ) 
        throw std::runtime_error( "Image wasn't loaded. It can't take a channels without photo" );

    return channel_;
}

unsigned char* Image::data()
{
    if( !data_ ) 
        throw std::runtime_error( "Image wasn't loaded" );

    return data_;
}

const unsigned char* Image::data() const
{
    if( !data_ ) 
        throw std::runtime_error( "Image wasn't loaded" );

    return data_;
}

void Image::loadImage( std::filesystem::path path, bool isFlipVertically )
{
    clear();
    stbi_set_flip_vertically_on_load( isFlipVertically );
    int channel = 0;
    data_ = stbi_load( path.string().c_str(), &width_, &height_, &channel, 0);
    if( !data_ )
        throw std::runtime_error( "Image wasn't loaded: impossible to find the image by this path" );

    channel_ = static_cast< Channel >( channel );
}

void Image::clear() noexcept
{
    if( data_ )
    {
        stbi_image_free( data_ );
        data_ = nullptr;
    }
    width_ = height_ = 0;
    channel_ = Channel::None;
}

bool Image::isEmpty() const noexcept
{
    return data_ == nullptr;
}
