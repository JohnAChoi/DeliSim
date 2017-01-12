
#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "types/standard_types.h"
#include "types/floattype.h"
/*
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/mersenne_twister.hpp>
*/

#include <limits>
#include <cstdlib>

namespace Engine
{
	class Vector2d;
	class Vector3d;

	#ifdef min
		#undef min
	#endif
	#ifdef max
		#undef max
	#endif 

	class CRandom
	{
	private:
		//typedef boost::random::mt19937 base_generator_type;
		//base_generator_type m_generator;

	public:
		static ftype Range ( ftype min, ftype max );

		static Vector3d PointOnUnitSphere ( void );
		static Vector3d PointInUnitSphere ( void );

		static Vector2d PointOnUnitCircle ( void );

		void Seed ( uint32_t seed ) {
			//m_generator.seed( seed );
			srand(seed);
		};
		uint32_t Next ( void ) {
			//return m_generator();
			return (uint32_t)rand();
		};
		uint32_t Next ( int min, int max ) {
			//boost::random::uniform_int_distribution<> distribution( min, max );
			//return distribution(m_generator);
			return ((uint32_t)rand() % (max-min+1)) + min;
		};
		uint32_t Max ( void ) {
			//return base_generator_type::max();
			return std::numeric_limits<uint32_t>::max();
		};

		bool Chance ( ftype test_value );
	};

	#undef random_range

	extern CRandom Random;
}

#endif