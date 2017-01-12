//Implementation Copyright 2012 by John Choi
// Modified and improved 2013 by Joshua Boren

#include "Vector2d.h"
#include "Vector3d.h"
#include "Vector4d.h"
#include "Quaternion.h"

#include "CMatrix.h"

using namespace Engine;
using namespace std;

//Default constructor
Vector2d::Vector2d(): x(0.0), y(0.0)
{}

//Copy constructor
Vector2d::Vector2d (Vector2d const& old): x(old.x), y(old.y)
{}

//Conversion constructor
Vector2d::Vector2d (ftype const& new_x, ftype const& new_y): x(new_x), y(new_y)
{
	/*x = new_x;
	y = new_y;
	z = new_z;*/
}

//Addition overload
Vector2d Vector2d::operator+ (Vector2d const& right) const
{
	return Vector2d (x + right.x, y + right.y);
}

//Addition shorthand overload
void Vector2d::operator+= (Vector2d const& right)
{
	*this = *this + right; 
}

//Subtraction overload
Vector2d Vector2d::operator- (Vector2d const& right) const
{
	return Vector2d (x - right.x, y - right.y);
}

//Subtraction shorthand overload
void Vector2d::operator-= (Vector2d const& right)
{
	*this = *this - right;
}

//Scalar multiplication overload
Vector2d Vector2d::operator* (ftype const& right) const
{
	return Vector2d (x * right, y * right);
}

//Scalar multiplication shorthand overload
void Vector2d::operator*= (ftype const& right)
{
	*this = *this * right;
}

//Scalar multiplication overload
Vector2d Vector2d::operator/ (ftype const& right) const
{
	return Vector2d (x / right, y / right);
}

//Scalar multiplication shorthand overload
void Vector2d::operator/= (ftype const& right)
{
	*this = *this / right;
}

//Dot product				
ftype Vector2d::dot (Vector2d const& right) const
{
	return x * right.x + y * right.y;
}
// Cross product
ftype Vector2d::cross (Vector2d const& right) const
{
	return x*right.y - y*right.x; 
}

ftype& Vector2d::operator[] ( const int a )						//Index Accessor Added: 6/4/13
{
	return *(&x + a);
}
const ftype& Vector2d::operator[] ( const int a ) const			// 6/4/13
{
	return *(&x + a);
}


//Out stream overloard
ostream& operator<< (ostream& out, Vector2d const& current)
{
	out << '(' << current.x << ", " << current.y << ')';

	return out;
}

ftype Vector2d::magnitude (void) const
{
	return sqrt (x*x + y*y);
}

ftype Vector2d::sqrMagnitude (void) const
{
	return (x*x + y*y);
}

Vector2d Vector2d::normal ( void ) const
{
	ftype invMagnitude = magnitude();
/*#ifdef _ENGINE_DEBUG
	if ( fabs(invMagnitude) <= 1.0e-7 ) {
		fnl_assert(0);
	}
#endif*/
	if ( fabs(invMagnitude) <= 1.0e-7 ) {
		return Vector2d(0,0);
	}
	invMagnitude = 1.0f / invMagnitude;
	return (*this)*invMagnitude;
}
void Vector2d::normalize ( void )
{
	//(*this)/(magnitude());
	(*this) = normal();
}

// Note this doesn't edit the values
Vector2d Vector2d::lerp (Vector2d const& right, ftype const& t) const
{
	if (t <= 0) {
		return (*this);
	}
	else if (t >= 1) {
		return right;
	}
	else {
		return ((right - (*this))*t + (*this));
	}
}


//Equal comparison overload
bool Vector2d::operator== (Vector2d const& right) const
{
	if (fabs(right.x - x) > FTYPE_PRECISION)
		return false;
	if (fabs(right.y - y) > FTYPE_PRECISION)
		return false;
	return true;
}

//Not equal comparison overload
bool Vector2d::operator!= (Vector2d const& right) const
{
	return !((*this) == right);
}

//Matrix multiplication
//Vector2d Vector2d::operator* ( Matrix2x2 const& right ) const
Vector2d Vector2d::rvrMultMatx ( Matrix2x2 const& right ) const
{
	return Vector2d(
		right.pData[0]*x+right.pData[1]*y,
		right.pData[2]*x+right.pData[3]*y
		);
}