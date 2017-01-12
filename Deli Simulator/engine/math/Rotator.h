#ifndef _X_ROTATION_H_
#define _X_ROTATION_H_

#include "Vector2d.h"
#include "Vector3d.h"
#include "Vector4d.h"
#include "types/floattype.h"
#include "Quaternion.h"
#include "CMatrix.h"

namespace Engine
{

	class Rotator : public Matrix3x3
	{
		friend std::ostream& operator<< (std::ostream& out, Rotator const& matx);		//Out stream overload

	public: // Constructors
		Rotator( void );
		Rotator( const Matrix3x3& matx );
		Rotator( ftype const& eulerX, ftype const& eulerY, ftype const& eulerZ );
		Rotator( const Vector3d& euler_angles );
		Rotator( const Quaternion& quat );

	public: // Setters
		// Sets the rotator to describing a rotation around an axis
		void AxisAngle ( const Vector3d& axis, const ftype angle );	
		// Sets the rotator to describing a rotation from vector a to b
		void RotationTo ( const Vector3d& vfrom, const Vector3d& vto );
		// Sets the matrix from an array
		void Set ( ftype * data );

		// Resets matrix to identity
		void SetIdentity ( void );
	
		// Switches the matrix bases
		Rotator& SwitchBasis ( void );

	public: // Inline Setters
		// Set Euler angles
		inline void Euler ( const Vector3d& angles ) {
			setRotation( angles );
		}

	public: // Operators
		// Assignment operator
		Rotator& operator= ( const Matrix3x3& );

	public: // Getters

	public: // Inline Getters
		// Returns Euler angles
		/*inline Vector3d eulerAngles ( void )
		{
			return getEulerAngles
		}*/
	};
}

#endif