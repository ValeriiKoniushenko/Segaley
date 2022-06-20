#include "Repeater.h"

#include <stdexcept>

Repeater::Repeater() noexcept :
	freq_( 0. )
{
}

Repeater::Repeater( callbackT callback, double freq ) noexcept :
	freq_( 0. )
{
	setFreq( freq );
	setCallback( callback );
}

void Repeater::setFreq( double freq )
{
	if ( freq <= 0. )
		throw std::runtime_error( "Repeater's frequency can't be less\\equal then\\of 0" );

	freq_ = freq;
}

double Repeater::getFreq() const noexcept
{
	return freq_;
}

void Repeater::setCallback( callbackT callback ) noexcept
{
	callback_ = callback;
}

void Repeater::release() noexcept
{
	callback_ = nullptr;
}

void Repeater::update() noexcept
{
	using namespace std;
	using namespace std::chrono;

	if ( !callback_ )
		return;

	auto now = system_clock::now();
	if ( duration<double>( now - lastTime_ ).count() >= freq_ ) {
		callback_();

		lastTime_ = now;
	}
}
