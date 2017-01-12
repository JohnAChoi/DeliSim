//Implemetation Copyright 2012 by John Choi

#include "Color.h"
#include "math/Math.h"
#include <algorithm>

using namespace Engine;

//Default constructor
Color::Color(): red(0.0), green(0.0), blue(0.0), alpha(1.0)
{}

//Ftype conversion constructor
/*Color::Color (ftype r, ftype g, ftype b, ftype a): red(r), green(g), blue(b), alpha(a)
{}*/

// Char conversion constructor
/*Color::Color (unsigned char r, unsigned char g, unsigned char b): red(ftype(r/255.0)), green(ftype(g/255.0)), blue(ftype(b/255.0)), alpha(ftype(1.0))
{}*/

//Color::Color ( float r, float g, float b, float a ) : red(Real(r)), green(Real(g)), blue(Real(b)), alpha(Real(a))
//{}
Color::Color ( double r, double g, double b, double a ) : red(Real(r)), green(Real(g)), blue(Real(b)), alpha(Real(a))
{}

//Addition operator overload
Color Color::operator+ (Color const& right) const
{
	return Color (red + right.red, green + right.green, blue + right.blue, alpha + right.alpha);
}

//Subtraction operator overload
Color Color::operator- (Color const& right) const
{
	return Color (red - right.red, green - right.green, blue - right.blue, alpha - right.alpha);
}

//Multiplication operator overload
Color Color::operator* (Color const& right) const
{
	return Color (red * right.red, green * right.green, blue * right.blue, alpha * right.alpha);
}
//Multiplication operator overload
Color Color::operator* (ftype const& right) const 
{
	return Color (red * right, green * right, blue * right, alpha * right);
}

//Division operator overload
Color Color::operator/ (Color const& right) const
{
	return Color (red / right.red, green / right.green, blue / right.blue, alpha / right.alpha);
}

//Equal comparison overload
bool Color::operator== (Color const& right) const
{
	if (fabs(right.blue - blue) > FTYPE_PRECISION)
		return false;
	if (fabs(right.green - green) > FTYPE_PRECISION)
		return false;
	if (fabs(right.red - red) > FTYPE_PRECISION)
		return false; 
	if (fabs(right.alpha - alpha) > 2 * FTYPE_PRECISION)
		return false;
	return true;
}

bool Color::operator!= (Color const& right) const
{
	return !((*this) == right);
}

//Randomize the color
void Color::randomize (void)
{
	red = (ftype)(rand() % 256) / 256.0f;
	green = (ftype)(rand() % 256) / 256.0f;
	blue = (ftype)(rand() % 256) / 256.0f;
	alpha = (ftype)(rand() % 256) / 256.0f;
}

//Return the address of the red component to use as an array
const ftype* Color::start_point (void) const
{
	return &red;
}
ftype* Color::start_point_RW (void)
{
	return &red;
}

Color Color::Lerp(Color const c_one, Color const c_two, ftype t)
{
	if(t <= 0)
	{
		return c_one;
	}
	else if(t >= 1)
	{
		return c_two;
	}
	else
	{
		return ((c_two - c_one)*t + c_one);
	}
}

Color Color::Lerp(Color const c_two, ftype t)
{
	if(t <= 0)
	{
		return (*this);
	}
	else if(t >= 1)
	{
		return c_two;
	}
	else
	{
		return ((c_two - (*this))*t + (*this));
	}
}

void Color::GetHSLC ( Color& outHSL ) const
{
	ftype hue, saturation, lightness;

	// compute hue
	//ftype alpha, beta, chroma;
	ftype chroma;
	/*alpha = (red*2 - green - blue) * 0.5f;
	beta  = (ftype)sqrt(3.0f)*0.5f*( green - blue );
	hue = (ftype)radtodeg( atan2( beta, alpha ) );
	if ( hue < 0 ) {
		hue += 360;
	}
	chroma = (ftype)sqrt( sqr(alpha) + sqr(beta) );*/

	// compute lightness
	ftype fmax, fmin;
	fmax = std::max<ftype>( std::max<ftype>( red, green ), blue );
	fmin = std::min<ftype>( std::min<ftype>( red, green ), blue );
	lightness = ( fmax + fmin ) * 0.5f;
	chroma = fmax - fmin;

	// compute hue CORRECLTY.
	if ( chroma < 0.000001f )
		hue = 0;
	else if ( fmax == red )
		hue = (green-blue)/chroma;
	else if ( fmax == green )
		hue = (blue-red)/chroma + 2.0f;
	else if ( fmax = blue )
		hue = (red-green)/chroma + 4.0f;
	else
		throw std::out_of_range("Bad chroma");
	//	cout << "ERRRR" << endl;
	hue *= 60;

	// compute saturation
	if (( chroma > 0 )&&( lightness < 1 ))
		saturation = chroma/(1-fabs(2*lightness-1));
	else
		saturation = 0;

	outHSL.red	 = hue;
	outHSL.green = saturation;
	outHSL.blue	 = lightness;
	outHSL.alpha = chroma;
}

void Color::SetHSL ( const Color& inHSL )
{
	ftype hue = inHSL.red;
	ftype saturation = inHSL.green;
	ftype lightness = inHSL.blue;

	ftype chroma = ( 1.0f - fabs( 2.0f*lightness - 1.0f )) * saturation;
	ftype hue_t = hue / 60.0f;
	ftype cx_t = chroma * ( 1 - fabs( ( (hue_t*0.5f - int(hue_t*0.5f))*2.0f ) - 1.0f ) );
	Color color_t;
	if ( hue_t < 1 )
		color_t = Color( chroma, cx_t, 0 );
	else if ( hue_t < 2 )
		color_t = Color( cx_t, chroma, 0 );
	else if ( hue_t < 3 )
		color_t = Color( 0, chroma, cx_t );
	else if ( hue_t < 4 )
		color_t = Color( 0, cx_t, chroma );
	else if ( hue_t < 5 )
		color_t = Color( cx_t, 0, chroma );
	else if ( hue_t < 6 )
		color_t = Color( chroma, 0, cx_t );
	else
		color_t = Color( 0.0f,0,0 );
	ftype cm_t = lightness - chroma*0.5f;
	red		= color_t.red	+ cm_t;
	green	= color_t.green + cm_t;
	blue	= color_t.blue	+ cm_t;
}