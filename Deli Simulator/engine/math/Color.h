#ifndef _COLOR_H_
#define _COLOR_H_

#include <iostream>
#include <stdlib.h>
#include "types/floattype.h"
//#include <time.h>

namespace Engine
{
	class Color
	{
	public:
		Color ( void );										//Default constructor
		//Color (ftype r, ftype g, ftype b, ftype a=1.0f);	//Ftype constructor
		//Color (unsigned char r,unsigned char g,unsigned char b);
		//Color ( float r, float g, float b, float a=1.0f );
		Color ( double r, double g, double b, double a=1.0 );

		//Member data
		Real red;
		Real green;
		Real blue;
		Real alpha;
	
		static Color Lerp(Color const c_one, Color const c_two, Real t);
		Color Lerp(Color const c_two, Real t);
		Color operator+ (Color const& right) const;				//Addition overload
		Color operator- (Color const& right) const;				//Subtraction overload
		Color operator* (Color const& right) const;				//Multiplication overload
		Color operator* (ftype const& right) const;				//Multiplication overload
		Color operator/ (Color const& right) const;				//Division overload
		bool operator== (Color const& right) const;				//Equal comparison overload
		bool operator!= (Color const& right) const;				//Not equal comparison overload
		void randomize (void);									//Color randomizer
		const Real* start_point (void) const;							//Return the address of the color red as a pointer
		Real* start_point_RW (void);							//Return the address of the color red as a pointer

		void GetHSLC ( Color& outHSL ) const;				// Returns a Color containing HSL values
		void SetHSL ( const Color& inHSL );					// Sets the Color to a value with the given HSL values (RGB as HSL)
	};
}

#endif