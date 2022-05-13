#pragma once

#include <functional>
#include <chrono>

class Repeater final
{
public:
    using callbackT = std::function<void()>;

public:
    Repeater() noexcept;
    Repeater( callbackT callback, double freq = 1.0 ) noexcept;

    ~Repeater() = default;
    Repeater( const Repeater& ) = delete;
    Repeater( Repeater&& ) = delete;
    Repeater& operator=( const Repeater& ) = delete;
    Repeater& operator=( Repeater&& ) = delete;

    void setFreq( double freq );
    double getFreq() const noexcept;
    void setCallback( callbackT callback ) noexcept;
    void release() noexcept;
    void update() noexcept;

private:
    std::chrono::system_clock::time_point lastTime_;
    double freq_;
    callbackT callback_;
};