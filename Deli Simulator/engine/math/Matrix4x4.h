
#ifndef _MATRIX_4_4_H_
#define _MATRIX_4_4_H_

namespace Engine
{
	class Matrix4x4
	{
	public:
		FORCE_INLINE Matrix4x4 ( void );
		FORCE_INLINE Matrix4x4 ( const Matrix4x4& );
		FORCE_INLINE Matrix4x4 ( const ftype* );

		// Setters - Translation
		FORCE_INLINE bool setTranslation ( const ftype = 0, const ftype = 0, const ftype = 0 );
		FORCE_INLINE bool setTranslation ( const Vector3d& );

		// Setters - Scaling
		FORCE_INLINE bool setScale ( const ftype = 0, const ftype = 0, const ftype = 0 );
		FORCE_INLINE bool setScale ( const Vector3d& );

		// Setters - Rotation
		FORCE_INLINE bool setRotation ( const ftype = 0, const ftype = 0, const ftype = 0 );
		FORCE_INLINE bool setRotation ( const Vector3d& );
		FORCE_INLINE bool setRotation ( const Quaternion& );
		FORCE_INLINE bool setRotation ( const Matrix3x3& );

		FORCE_INLINE bool setRotationZYX ( const ftype = 0, const ftype = 0, const ftype = 0 );

		// Modders
		FORCE_INLINE void translate ( const Vector3d& );

		// Getters - Translation
		FORCE_INLINE Vector3d	getTranslation ( void ) const;

		// Getters - Rotation
		FORCE_INLINE Vector3d	getEulerAngles ( void ) const;
		FORCE_INLINE Quaternion	getQuaternion ( void ) const;
		FORCE_INLINE Matrix3x3	getRotator ( void ) const;

		// Getters - Scale
		FORCE_INLINE Vector3d	getScaling ( void ) const;

		// Operations
		FORCE_INLINE Matrix4x4 transpose ( void ) const;
		FORCE_INLINE Matrix4x4 inverse ( void ) const;
		FORCE_INLINE ftype det ( void ) const;
	
		FORCE_INLINE Matrix3x3 submatrix ( int, int ) const;

		FORCE_INLINE Matrix4x4 LerpTo( Matrix4x4 const&, ftype const ) const;
		FORCE_INLINE void Lerp ( Matrix4x4 const&, ftype const ); 

		// Multiplication
		FORCE_INLINE Matrix4x4 operator* ( Matrix4x4 const& ) const;
		FORCE_INLINE Matrix4x4 operator*=( Matrix4x4 const& );
		FORCE_INLINE Matrix4x4 operator* ( ftype const ) const;

		FORCE_INLINE Matrix4x4 operator+ ( Matrix4x4 const& ) const;
		FORCE_INLINE Matrix4x4 operator+=( Matrix4x4 const& );

		FORCE_INLINE Vector3d operator* ( Vector3d const& ) const;
		FORCE_INLINE Vector4d operator* ( Vector4d const& ) const;

		// Transpose
		FORCE_INLINE Matrix4x4 operator! ( void ) const;

		// Accessor
		FORCE_INLINE const ftype* operator[] ( int ) const;
		// Editor
		FORCE_INLINE ftype* operator[] ( int );

		//Equal comparison overload
		FORCE_INLINE bool operator== (Matrix4x4 const& right) const;

		//Not equal comparison overload
		FORCE_INLINE bool operator!= (Matrix4x4 const& right) const;

		// Check for valid values
		FORCE_INLINE bool isOk ( void );

	public:
		ftype pData[16];
	};
}

#endif//_MATRIX_4_4_H_