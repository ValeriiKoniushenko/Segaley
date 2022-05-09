#pragma once

#include <functional>
#include <chrono>

class Repeater final
{
public:
    using callbackT = std::function<void()>;

public:
    Repeater();
    Repeater( callbackT callback, double freq = 1.0 ) noexcept( false );

    ~Repeater() = default;
    Repeater( const Repeater& ) = delete;
    Repeater( Repeater&& ) = delete;
    Repeater& operator=( const Repeater& ) = delete;
    Repeater& operator=( Repeater&& ) = delete;

    void setFreq( double freq ) noexcept( false );
    double getFreq() const;
    void setCallback( callbackT callback );
    void release();
    void update();

private:
    std::chrono::system_clock::time_point lastTime_;
    double freq_;
    callbackT callback_;
};