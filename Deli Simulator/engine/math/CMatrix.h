// The matrix class used for transforms
//------------------------------------
// Please note that the matrix is defined in the same manner that OpenGL uses matrices!
// All matrices are column order. This changes multiplication order. For example, if you 
// want to rotate something, then translate it, the multiplication order is:
//  result = translationMatrix * rotationMatrix;
// Wheras in with a row order matrix, the order would be:
//  result = rotationMatrix * translationMatrix;
// This can cause extreme confusion, since the popular notation is the latter definition.
// If you want to get a row order matrix, there is always the transpose() function
//  transpose(rotationMatrixColumnOrder * translationMatrixColumnOrder) = ( translationMatrixRowOrder*rotationMatrixRowOrder )
// Please note I could be switching around row order and column order. If so, please fix this.
//------------------------------------

#ifndef C_MATRIX_H
#define C_MATRIX_H

// Includes
#include <cmath>
#include <climits>
#include <cstddef>
#include <cfloat>
#include <cassert>

#include "types/standard_types.h"

namespace Engine
{
	class Vector2d;
	class Vector3d;
	class Vector4d;
	class Quaternion;
	class Matrix2x2;
	class Matrix3x3;
	class Matrix4x4;
}

#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Matrix2x2.hpp"
#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"

#endif