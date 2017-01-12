

#ifndef _MATH_H_
#define _MATH_H_

#include <cmath>
#include "types/standard_types.h"
#include "types/floattype.h"
#include "math/Vector3d.h"

namespace Engine
{
	// class CMath
	// Math class. Straighten up, you're about to get some learning on!
	// Provides repeatedly used math operations on basic types, such as Linear Interpolation or Cubic Interpolation (Smoothlerp).
	// Provides some not-so-much used math operations that are still used repeatedly, such as generating a non-random sequence of points on a sphere.

	class CMath
	{
	public:
		ftype Smoothlerp ( ftype t );
		ftype Smoothlerp ( ftype t, ftype a, ftype b );

		ftype Lerp ( ftype t, ftype a, ftype b );

		ftype Clamp ( ftype val, ftype lower, ftype upper );
		ftype Wrap ( ftype val, ftype lower, ftype upper );

		// pointsOnSphere ( int NumberOfPoints )
		// Generates a list of equidistant points on a sphere. Usable for explosive ideas.
		// Gives away ownership of the returned array. Remember to delete it.
		Vector3d* pointsOnSphere ( int N );

		template <typename T> int sgn(T val) {
			return (T(0) < val) - (val < T(0));
		}
		template <typename T> T Sqr(T val) {
			return sqr(val);
		}
		template <typename T> T Cub(T val) {
			return cub(val);
		}


		template <typename T> int32_t Round(T r) {
			return (int32_t)((r > 0.0) ? (r + 0.5) : (r - 0.5)); 
		}

	};

	extern CMath Math;
}

#endif