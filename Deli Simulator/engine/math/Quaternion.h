#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "Vector3d.h"
#include <cmath>
#include <iostream>

namespace Engine
{
	// Declare class usage
	class Matrix4x4;
	class Matrix3x3;

	class Quaternion
	{
		friend std::ostream& operator<< (std::ostream& out, Quaternion const & quat);		//Out stream overload

	public:
		// Constructors
		Quaternion( ); //Default constructor.
		Quaternion( Quaternion const& old ); // Copy constructor.
		Quaternion( ftype const& new_x, ftype const& new_y, ftype const& new_z, ftype const& new_w ); // Inpute conversion consturctor.
		Quaternion( const Vector3d& euler_angles ); // Euler angles input constructor
		Quaternion( const Matrix3x3& rotator );
		Quaternion( const Matrix4x4& rotation );

		// Operations
		//Quaternion Invert(Quaternion const& qa) const; //Note: This also gives you the conjugate of a quarternion
		//ftype Magnitude(Quaternion const& qa) const; // returns a ftype magnitude of the quarternion.
		//void Normalize(Quaternion const& qa); // Normalizes the quaternion.
		void Invert ( void );
		ftype Magnitude( void ) const;
		void Normalize ( void );
		Quaternion Multiply(Quaternion const& qa, Quaternion const& qb); // multiplies two quarternions together.

		// Dot product
		ftype Dot( Quaternion const& qa ) const;

		// Linear Interpolation (only valid for small differences in angle)
		Quaternion Lerp ( Quaternion const& qa, const ftype t );
		// Spherical Interpolation (works for large angle differences, but is much slower than lerp)
		Quaternion Slerp ( Quaternion const& qa, const ftype t ); 

		// Sets the quat to describing a rotation around an axis
		void AxisAngle ( const Vector3d& axis, const ftype angle );
		static Quaternion CreateAxisAngle ( const Vector3d& axis, const ftype angle );
		// Sets the quat to describe a rotation from one vector to another
		void RotationTo ( const Vector3d& vfrom, const Vector3d& vto );
		static Quaternion CreateRotationTo ( const Vector3d& vfrom, const Vector3d& vto );
		// Sets the quat to describing the given Euler XYZ rotation
		void SetEulerAngles ( const Vector3d& euler_angles );
		static Quaternion CreateFromEuler ( const Vector3d& euler_angles );
		// Sets the quat to describing the given rotation matrix
		//void SetFromRotator ( const Matrix3x3& rotator );
		// Swaps the basis of the quaternion (you should never need to use this)
		Quaternion& SwitchBasis ( void );

		// Rotates a vector
		Vector3d operator* ( Vector3d const& right ) const;	
		// Rotates against another quat
		Quaternion operator* ( Quaternion const& right ) const;
		// Inverts the quaternion
		Quaternion operator! ( void ) const;

		// Scales the quaternion
		const Quaternion operator* ( const float scale ) const;

		// Gets euler angles from the quaternion
		Vector3d GetEulerAngles ( void ) const;

		//Equal comparison overload
		bool operator== (Quaternion const& right) const;

		//Not equal comparison overload
		bool operator!= (Quaternion const& right) const;

		// Returns the private values for direct read
		ftype X ( void ) { return x; };
		ftype Y ( void ) { return y; };
		ftype Z ( void ) { return z; };
		ftype W ( void ) { return w; };

	public:
		ftype x;
		ftype y;
		ftype z;
		ftype w;

	};
}
#endif