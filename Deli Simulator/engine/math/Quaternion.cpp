
#include "Quaternion.h"

#include "Vector2d.h"
#include "Vector3d.h"
#include "Vector4d.h"
#include "CMatrix.h"
#include "Rotator.h"

using namespace Engine;
using namespace std;

// Constructors

Quaternion::Quaternion() : x(0.0), y(0.0), z(0.0), w(1.0) //Default constructor.
{}
Quaternion::Quaternion(Quaternion const& old) : x(old.x), y(old.y), z(old.z), w(old.w) // Copy class.
{}
Quaternion::Quaternion(ftype const& new_x, ftype const& new_y, ftype const& new_z, ftype const& new_w) : x(new_x), y(new_y), z(new_z), w(new_w) // Inpute conversion consturctor.
{}
Quaternion::Quaternion( const Vector3d& euler_angles ) // Euler angles constructor
{
	SetEulerAngles( euler_angles );
}
Quaternion::Quaternion( const Matrix3x3& rotator ) // 3x3 rotator
{
	*this = rotator.getQuaternion();
}
Quaternion::Quaternion( const Matrix4x4& rotation ) // 4x4 rotation
{
	*this = rotation.getQuaternion();
}

// Operations
/*
Quaternion Quaternion::Invert(Quaternion const& qa) const //Note: This also gives you the conjugate of a quarternion
{
	Quaternion qr;

	qr.w =  qa.w;
    qr.x = -qa.x;
    qr.y = -qa.y;
    qr.z = -qa.z;

	return qr;
}*/
void Quaternion::Invert ( void )
{
	x = -x;
	y = -y;
	z = -z;
}

ftype Quaternion::Magnitude( void ) const // returns a ftype magnitude of the quarternion.
{
	return sqrt( sqr(w) + sqr(x) + sqr(y) + sqr(z) );
}
void Quaternion::Normalize( void ) // Normalizes the quaternion.
{
	ftype magnitude = 1/Magnitude();
	x *= magnitude;
	y *= magnitude;
	z *= magnitude;
	w *= magnitude;
}

Quaternion Quaternion::Multiply(Quaternion const& qa, Quaternion const& qb) // multiplies two quarternions together.
{
	Quaternion qr;

	qr.w = qa.w*qb.w - qa.x*qb.x - qa.y*qb.y - qa.z*qb.z;
	qr.x = qa.w*qb.x + qa.x*qb.w + qa.y*qb.z - qa.z*qb.y;
	qr.y = qa.w*qb.y + qa.y*qb.w + qa.z*qb.x - qa.x*qb.z;
	qr.z = qa.w*qb.z + qa.z*qb.w + qa.x*qb.y - qa.y*qb.x;

	return qr;
}
Quaternion Quaternion::operator* ( Quaternion const& right ) const
{
	//return this->Multiply(*this,right);
	Quaternion qr;

	qr.w = this->w*right.w - this->x*right.x - this->y*right.y - this->z*right.z;
	qr.x = this->w*right.x + this->x*right.w + this->y*right.z - this->z*right.y;
	qr.y = this->w*right.y + this->y*right.w + this->z*right.x - this->x*right.z;
	qr.z = this->w*right.z + this->z*right.w + this->x*right.y - this->y*right.x;

	return qr;
}
Quaternion Quaternion::operator! ( void ) const
{
	Quaternion quat( *this );
	quat.Invert();
	return quat;
	//return this->Invert(*this);
}
const Quaternion Quaternion::operator* ( const float scale ) const
{
	return Quaternion( x*scale, y*scale, z*scale, w*scale );
}

// Dot product
ftype Quaternion::Dot( Quaternion const& qa ) const
{
	return x * qa.x + y * qa.y + z * qa.z + w * qa.w;
}

// Sets the quat to describing a rotation around an axis
void Quaternion::AxisAngle ( const Vector3d& axis, const ftype angle )
{
	Vector3d Axis = axis.normal();
	ftype sourceAngle = (ftype) degtorad(angle) / 2.0f;
    ftype sin_a = sin( sourceAngle );
    x    = Axis.x * sin_a;
    y    = Axis.y * sin_a;
    z    = Axis.z * sin_a;
    w    = cos( sourceAngle );

	Normalize();
}
Quaternion Quaternion::CreateAxisAngle ( const Vector3d& axis, const ftype angle )
{
	Quaternion q;
	q.AxisAngle( axis, angle );
	return q;
}


// Sets the quat to describe a rotation from one vector to another
void Quaternion::RotationTo ( const Vector3d& vfrom, const Vector3d& vto )
{
	// Based on Stan Melax's article in Game Programming Gems
    Quaternion q;

    // Copy, since cannot modify local
    Vector3d v0 = vfrom;
    Vector3d v1 = vto;
    v0.normalize();
    v1.normalize();

    ftype d = v0.dot(v1);
    // If dot == 1, vectors are the same
    if (d >= 1.0f)
    {
        //return Quaternion();
		q = Quaternion();
    }
    else if (d < (1e-6f - 1.0f))
    {
        // Generate an axis
		Vector3d axis = Vector3d::forward.cross(vfrom);
        if (axis.sqrMagnitude() < 0.0001f) // pick another if colinear
			axis = Vector3d::up.cross(vfrom);
        axis.normalize();
		q.AxisAngle( axis, radtodeg(PI) );
    }
    else
    {
        ftype s = sqrt( (1+d)*2 );
		ftype invs = 1 / s;

		Vector3d c = v0.cross(v1);

        q.x = c.x * invs;
        q.y = c.y * invs;
        q.z = c.z * invs;
        q.w = s * 0.5f;
    }

	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;

	Normalize();
}

Quaternion Quaternion::CreateRotationTo ( const Vector3d& vfrom, const Vector3d& vto )
{
	Quaternion temp;
	temp.RotationTo( vfrom, vto );
	return temp;
}

// Sets the quat to describing the given Euler XYZ rotation
void Quaternion::SetEulerAngles ( const Vector3d& euler_angles )
{
	{
		/*(Vector3d vx ( 1, 0, 0 ), vy ( 0, 1, 0 ), vz ( 0, 0, 1 );
		Quaternion qx, qy, qz, qt;
		qx.AxisAngle( vx, euler_angles.x );
		qy.AxisAngle( vy, euler_angles.y );
		qz.AxisAngle( vz, euler_angles.z );
		qt = qz * qy * qx;
		(*this) = qt;*/
	}

	{
		ftype rotx = degtorad(euler_angles.x);
		ftype roty = degtorad(euler_angles.y);
		ftype rotz = degtorad(euler_angles.z);
		Quaternion qx ( sin(rotx/2),0,0,	cos(rotx/2) );
		Quaternion qy ( 0,sin(roty/2),0,	cos(roty/2) );
		Quaternion qz ( 0,0,sin(rotz/2),	cos(rotz/2) );
		//Quaternion qt = qx;
		//qt = qy*qt;
		//qt = qz*qt;
		//Quaternion qt = qx * qy * qz;
		Quaternion qt = qz * qy * qx;
		(*this) = qt;
	}

	{
		// Basically we create 3 Quaternions, one for pitch, one for yaw, one for roll
		// and multiply those together.
		// the calculation below does the same, just shorter
 
		/*float p = (ftype) degtorad( euler_angles.x ) * 0.5f;
		float y = (ftype) degtorad( euler_angles.y ) * 0.5f;
		float r = (ftype) degtorad( euler_angles.z ) * 0.5f;
 
		float sinp = sin(p);
		float siny = sin(y);
		float sinr = sin(r);
		float cosp = cos(p);
		float cosy = cos(y);
		float cosr = cos(r);
 
		this->x = sinr * cosp * cosy - cosr * sinp * siny;
		this->y = cosr * sinp * cosy + sinr * cosp * siny;
		this->z = cosr * cosp * siny - sinr * sinp * cosy;
		this->w = cosr * cosp * cosy + sinr * sinp * siny;
 
		Normalize();*/
	}
}

// Swaps the basis of the quaternion (you should never need to use this)
Quaternion& Quaternion::SwitchBasis ( void )
{
	Rotator temp ( *this );
	temp.SwitchBasis();
	*this = temp.getQuaternion();
	Normalize();
	return *this;
}


// Rotates a vector
Vector3d Quaternion::operator* ( Vector3d const& right ) const
{
	Quaternion qr = *this;
	Quaternion qri= !(*this);
	Quaternion v ( right.x,right.y,right.z,0 ); 
	Quaternion qf = qr*v*qri;
	return Vector3d( qf.x, qf.y, qf.z );
}

// Linear Interpolation (only valid for small differences in angle)
Quaternion Quaternion::Lerp ( Quaternion const& qa, const ftype t )
{
	if (t <= 0)
	{
		return (*this);
	}
	else if(t >= 1)
	{
		return qa;
	}
	else
	{
		return Quaternion(
			( qa.x - this->x )*t + this->x,
			( qa.y - this->y )*t + this->y,
			( qa.z - this->z )*t + this->z,
			( qa.w - this->w )*t + this->w
			);
	}
}

// Spherical Interpolation (works for large angle differences, but is much slower than lerp)
Quaternion Quaternion::Slerp ( Quaternion const& qa, const ftype t )
{
	if (t <= 0)
	{
		return (*this);
	}
	else if(t >= 1)
	{
		return qa;
	}
	else
	{
		Quaternion q3;
		ftype dot = this->Dot( qa );
		
		if (dot < 0)
		{
			dot = -dot;
			q3 = Quaternion( -qa.x, -qa.y, -qa.z, -qa.w );
		}
		else
		{
			q3 = qa;
		}

		float angle = acosf(dot);

		ftype a = sinf(angle*(1-t));
		ftype b = sinf(angle*t);
		ftype c = sinf(angle);
		return Quaternion(
			( x*a + q3.x*b )/c,
			( y*a + q3.y*b )/c,
			( z*a + q3.z*b )/c,
			( w*a + q3.w*b )/c
			);
	}
}

// Gets euler angles from the quaternion
Vector3d Quaternion::GetEulerAngles ( void ) const
{
	return Rotator( *this ).getEulerAngles();
}

// Out stream overload
ostream& operator<< (ostream& out, Quaternion const& quat)
{
	out << "(" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ")";
	return out;
}

//Equal comparison overload
bool Quaternion::operator== (Quaternion const& right) const
{
	if (fabs(right.x - x) > FTYPE_PRECISION)
		return false;
	if (fabs(right.y - y) > FTYPE_PRECISION)
		return false;
	if (fabs(right.z - z) > FTYPE_PRECISION)
		return false;
	if (fabs(right.w - w) > FTYPE_PRECISION)
		return false;
	return true;
}

//Not equal comparison overload
bool Quaternion::operator!= (Quaternion const& right) const
{
	return !((*this) == right);
}