#include "Repeater.h"

Repeater::Repeater() :
	freq_( 0. )
{
}

Repeater::Repeater( callbackT callback, double freq ) noexcept( false ) :
	freq_( 0. )
{
	setFreq( freq );
	setCallback( callback );
}

void Repeater::setFreq( double freq ) noexcept( false )
{
	if ( freq <= 0. )
		throw std::runtime_error( "Repeater's frequency can't be less\\equal then\\of 0" );

	freq_ = freq;
}

double Repeater::getFreq() const
{
	return freq_;
}

void Repeater::setCallback( callbackT callback )
{
	callback_ = callback;
}

void Repeater::release()
{
	callback_ = nullptr;
}

void Repeater::update()
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
