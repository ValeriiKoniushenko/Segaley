#pragma once

template< typename sizeT >
struct Size
{
	sizeT width = 0;
	sizeT height = 0;
};

using FSize = Size< float >;
using DSize = Size< double >;
using ISize = Size< int >;
using SSize = Size< short >;

template< typename positionT >
struct Position2
{
	positionT x = 0;
	positionT y = 0;
};

using FPosition2 = Position2< float >;
using DPosition2 = Position2< double >;
using IPosition2 = Position2< int >;
using SPosition2 = Position2< short >;

template< typename sizeT, typename positionT >
struct Rect
{
	Rect();
	Rect( Position2< positionT > position, Size< sizeT > size );
	~Rect() = default;

	Rect( const Rect& ) = default;
	Rect( Rect&& ) = default;

	Rect& operator=( const Rect& ) = default;
	Rect& operator=( Rect&& ) = default;

	Position2< positionT > position;
	Size< sizeT > size;
};

template< typename sizeT, typename positionT >
inline Rect< sizeT, positionT >::Rect(): 
	size{ static_cast< sizeT >( 0 ), static_cast< sizeT >( 0 ) },
	position{ static_cast< sizeT >( 0 ), static_cast< sizeT >( 0 ) }
{
}

template<typename sizeT, typename positionT>
inline Rect<sizeT, positionT>::Rect( Position2< positionT > position, Size< sizeT > size ) :
	size( size ),
	position( position )
{
}

using IIRect = Rect< int, int >;
using FFRect = Rect< float, float >;
using DDRect = Rect< double, double >;
using FIRect = Rect< float, int >;
using IFRect = Rect< int, float >;
using DIRect = Rect< double, int >;
using IDRect = Rect< int, double >;

