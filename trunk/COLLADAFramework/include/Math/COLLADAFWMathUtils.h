/*
Copyright (c) 2008 NetAllied Systems GmbH

This file is part of COLLADAFramework.

Licensed under the MIT Open Source License, 
for details please see LICENSE file or the website
http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADAFW_MATH_UTILS_H__
#define __COLLADAFW_MATH_UTILS_H__

#include "COLLADAFWPrerequisites.h"

#define TOLERANCE 0.0001f

namespace COLLADAFW
{
	namespace Math
	{
		/** A math utility class */
		// A class that holds some static math utility functions
		class Utils
		{

		public:

			static const double PI;
			static const float PI_f;
			/*
			static const double PIff;
			static const double TWOPI;
			static const double HALFPI;
			*/
			static const double DEG_TO_RAD;
			static const double RAD_TO_DEG;

			static const float DEG_TO_RAD_f;
			static const float RAD_TO_DEG_f;

			/** Returns true if @a value1 and @a value2 are equal within @a tolerance*/
			template<class T>
			static bool equals ( const T & value1, const T & value2, const T & tolerance = (T)TOLERANCE )
			{
				return value1 - value2 < tolerance && value1 - value2 > -tolerance;
			}


			/** Returns true if @a value1 and @a value2 are equal within the default tolerance*/
			/*        template<class T>
			static bool equals ( const T & value1, const T & value2 )
			{
			return value1 - value2 < TOLERANCE && value1 - value2 > -TOLERANCE;
			}
			*/

			/** Returns true if @a value1, @a value2 and @a value3 are equal within the tolerance*/
			template<class T>
			static bool equals3 ( const T & value1, const T & value2, const T & value3 )
			{
				return equals ( value1, value2 ) && equals ( value2, value3 ) &&equals ( value3, value1 );
			}


			/** Returns true if @a value is equal to zero within the tolerance*/
			static bool equalsZero ( const float & value )
			{
				return equals ( value, 0.0f );
			}

			/** Returns true if @a value is equal to zero within the tolerance*/
			static bool equalsZero ( const double & value )
			{
				return equals ( value, 0.0 );
			}

			template<class T>
			static double radToDeg ( const T & value )
			{
				return value * RAD_TO_DEG;
			}

			template<class T>
			static double degToRad ( const T & value )
			{
				return value * DEG_TO_RAD;
			}

			template<class T>
			static float radToDegF ( const T & value )
			{
				return value * RAD_TO_DEG_f;
			}

			template<class T>
			static float degToRadF ( const T & value )
			{
				return value * DEG_TO_RAD_f;
			}

			/** Retrieves the sign of a number.
			@param val The number to check.
			@return 1 if positive, -1 if negative. */
			template <class T>
			static T sign ( const T& val )
			{
				return ( val >= T ( 0 ) ) ? T ( 1 ) : T ( -1 );
			}

			/** Clamps the specified object within a range specified by two other objects
			of the same class.
			Clamping refers to setting a value within a given range. If the value is
			lower than the minimum of the range, it is set to the minimum; same for
			the maximum.
			@param val The object to clamp.
			@param mx The highest object of the range.
			@param mn The lowest object of the range.
			@return The clamped value. */
			template <class T, class T2, class T3>
			static T clamp ( T val, T2 mn, T3 mx )
			{
				return ( T ) ( ( val > ( T ) mx ) ? ( T ) mx : ( val < ( T ) mn ) ? ( T ) mn : val );
			}

		};

	}


} // namespace COLLADAFW

#endif // __COLLADAFW_MATH_UTILS_H__
