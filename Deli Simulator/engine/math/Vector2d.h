//Implementation Copyright 2012 by John Choi

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "types/floattype.h"
#include <iostream>
#include <cmath>

namespace Engine
{
	class Matrix2x2;

	class Vector2d 
	{
		friend std::ostream& operator<< (std::ostream& out, Vector2d const& current);		//Out stream overload
	
	public:
		Vector2d ();												//Default constructor
		Vector2d (Vector2d const& old);								//Copy constructor
		Vector2d (ftype const& new_x, ftype const& new_y);		//Input conversion constructor

		Vector2d operator+ (Vector2d const& right) const;		//Addition overload
		void operator+= (Vector2d const& right);				//Addition shorthand overload	
		Vector2d operator- (Vector2d const& right) const;		//Subtraction overload
		void operator-= (Vector2d const& right);				//Subtraction shorthand overload
		Vector2d operator* (ftype const& right) const;			//Scalar multiplication overload
		void operator*= (ftype const& right);					//Scalar multiplication shorthand overload
		Vector2d operator/ (ftype const& right) const;			//Scalar division overload   Added: 6/6/13
		void operator/= (ftype const& right);					//Scalar division shorthand overload   Added: 6/6/13
		ftype dot (Vector2d const& right) const;				//Dot product
		ftype cross (Vector2d const& right) const;				// Cross product 10/17/13

		ftype magnitude (void) const;							//Returns the magnitude of the vector
		ftype sqrMagnitude (void) const;						//Returns squared magnitude for fast comparisons 6/6/13

		Vector2d normal ( void ) const;							//Normal of vector Added: 6/6/13
		void normalize ( void );								//Normalize vector Added: 6/6/13

		// Note this doesn't edit the values
		Vector2d lerp (Vector2d const& right, ftype const& t) const;	//Linear interpolation Added: 7/7/13 at 1:12 pm

		ftype& operator[] ( const int );						//Index Accessor Added: 6/4/13
		const ftype& operator[] ( const int ) const;			// 6/4/13

		//Vector2d operator* ( Matrix2x2 const& right ) const;	//Matrix multiplication added: 6/4/13		
		Vector2d rvrMultMatx ( Matrix2x2 const& right ) const;

		bool operator== (Vector2d const& right) const;			//Equal comparison overload
		bool operator!= (Vector2d const& right) const;			//Not equal comparison overload

		ftype x;
		ftype y;

	};
}

#endif