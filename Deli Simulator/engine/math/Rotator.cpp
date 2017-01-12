
#include "Rotator.h"

using namespace Engine;
using namespace std;

// Constructors
Rotator::Rotator ( void )
{
	SetIdentity();
}
Rotator::Rotator ( const Matrix3x3& matx )
{
	pData[0] = matx.pData[0];
	pData[1] = matx.pData[1];
	pData[2] = matx.pData[2];
	pData[3] = matx.pData[3];
	pData[4] = matx.pData[4];
	pData[5] = matx.pData[5];
	pData[6] = matx.pData[6];
	pData[7] = matx.pData[7];
	pData[8] = matx.pData[8];
}
Rotator::Rotator( ftype const& eulerX, ftype const& eulerY, ftype const& eulerZ )
{
	setRotation( eulerX, eulerY, eulerZ );
}
Rotator::Rotator( const Vector3d& euler_angles )
{
	setRotation( euler_angles );
}
Rotator::Rotator( const Quaternion& quat )
{
	setRotation( quat );
}

// Sets the matrix to describing a rotation around an axis
void Rotator::AxisAngle ( const Vector3d& axis, const ftype angle )
{
	Quaternion temp;
	temp.AxisAngle( axis, angle );
	setRotation( temp );
}
// Sets the matrix to descrive a rotation from vector a to b
void Rotator::RotationTo ( const Vector3d& vfrom, const Vector3d& vto )
{
	Vector3d axis = vfrom.cross(vto).normal();
	ftype angle = acos( min<ftype>( 1, max<ftype>( -1, vfrom.normal().dot(vto.normal()) ) ) );
	AxisAngle( axis, angle );
}
// Sets the matrix from an array
void Rotator::Set ( ftype * data )
{
	pData[0] = data[0];
	pData[1] = data[1];
	pData[2] = data[2];
	pData[3] = data[3];
	pData[4] = data[4];
	pData[5] = data[5];
	pData[6] = data[6];
	pData[7] = data[7];
	pData[8] = data[8];
}

// Resets matrix to identity
void Rotator::SetIdentity ( void )
{
	pData[0] = 1;
	pData[1] = 0;
	pData[2] = 0;
	pData[3] = 0;
	pData[4] = 1;
	pData[5] = 0;
	pData[6] = 0;
	pData[7] = 0;
	pData[8] = 1;
}

// Switches the matrix bases (right handed-rot to left handed-rot)
Rotator& Rotator::SwitchBasis ( void )
{
	/*ftype arr [] = {-1,0,0, 0,1,0, 0,0,1};
	Matrix3x3 matx ( arr );
	*this *= matx;*/
	pData[0] = -pData[0];
	pData[3] = -pData[3];
	pData[6] = -pData[6];
	return *this;
}

// Assignment operator
Rotator& Rotator::operator= ( const Matrix3x3& right )
{
	pData[0] = right.pData[0];
	pData[1] = right.pData[1];
	pData[2] = right.pData[2];
	pData[3] = right.pData[3];
	pData[4] = right.pData[4];
	pData[5] = right.pData[5];
	pData[6] = right.pData[6];
	pData[7] = right.pData[7];
	pData[8] = right.pData[8];
	return *this;
}

// Out stream overload
ostream& operator<< (ostream& out, Rotator const& matx)
{
	out << matx.pData[0] << "\t" << matx.pData[1] << "\t" << matx.pData[2] << endl;
	out << matx.pData[3] << "\t" << matx.pData[4] << "\t" << matx.pData[5] << endl;
	out << matx.pData[6] << "\t" << matx.pData[7] << "\t" << matx.pData[8] << endl;
	return out;
}