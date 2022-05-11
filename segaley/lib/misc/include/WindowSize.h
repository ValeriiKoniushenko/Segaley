#pragma once
struct WindowSize
{
    unsigned short width{};
    unsigned short height{};
    bool operator==( const WindowSize& other ) const;
    bool operator!=( const WindowSize& other ) const;
    float getRatio() const;
};
