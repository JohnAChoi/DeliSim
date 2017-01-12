
#include "Random.h"
#include "math/Vector2d.h"
#include "math/Vector3d.h"
#include <cmath>

namespace Engine
{
	CRandom Random;
	
	#ifdef random_range
		#undef random_range
	#endif
	#define random_range(a,b) ( ((a) + ((Random.Next()/((ftype)Random.Max()))*((b)-(a)))) )

	ftype CRandom::Range ( ftype min, ftype max )
	{
		return random_range( min,max );
	}

	#undef random_range

	Vector3d CRandom::PointOnUnitSphere ( void )
	{
		ftype angle1 = Range( 0, (ftype) (2*PI) );
		ftype angle2 = Range( (ftype) -PI/2,(ftype) PI/2 );

		ftype fcosz	= cos( angle2 );

		Vector3d result;
		result.z = sin( angle2 );
		result.x = sin( angle1 ) * fcosz;
		result.y = cos( angle1 ) * fcosz;

		return result;
	}

	Vector3d CRandom::PointInUnitSphere ( void )
	{
		return ( PointOnUnitSphere() * Range(0,1) );
	}

	Vector2d CRandom::PointOnUnitCircle ( void )
	{
		ftype angle = Range( 0, (ftype) (2*PI) );
	
		Vector2d result;
		result.x = sin( angle );
		result.y = cos( angle );

		return result;
	}

	bool CRandom::Chance ( ftype test_value )
	{
		return (Range(0,1) < test_value);
	}
}