
#ifndef _C_RECT_
#define _C_RECT_

// Includes
#include "types/standard_types.h"
#include "Vector2d.h"

namespace Engine
{
	// Class
	class Rect
	{
	public:
		Rect ( ftype x, ftype y, ftype w, ftype h )
		{
			pos.x = x;
			pos.y = y;
			size.x = w;
			size.y = h;
		}
		Rect ( void )
		{
			pos.x = 0;
			pos.y = 0;
			size.x = 0;
			size.y = 0;
		}

		Vector2d pos;
		Vector2d size;

		FORCE_INLINE bool Contains ( const Vector2d& point ) {
			return ((point.x > pos.x) && (point.y > pos.y) && (point.x < pos.x+size.x) && (point.y < pos.y+size.y));
		}
	};
}

#endif