//
// This file is part of the Terathon Common Library, by Eric Lengyel.
// Copyright 1999-2025, Terathon Software LLC
//
// This software is distributed under the MIT License.
// Separate proprietary licenses are available from Terathon Software.
//


#ifndef TSHalf_h
#define TSHalf_h


#include "TSPlatform.h"


#define TERATHON_HALF 1


namespace Terathon
{
	class Half
	{
		private:

			uint16		value;

			Half(uint16 v)
			{
				value = v;
			}

			TERATHON_API float GetFloat(void) const;
			TERATHON_API void SetFloat(float v) volatile;

		public:

			inline Half() = default;

			Half(const Half& h)
			{
				value = h.value;
			}

			Half(float v)
			{
				SetFloat(v);
			}

			Half(double v)
			{
				SetFloat(float(v));
			}

			operator float(void) const
			{
				return (GetFloat());
			}

			inline Half& operator =(const Half& h)
			{
				value = h.value;
				return (*this);
			}

			Half& operator =(float v)
			{
				SetFloat(v);
				return (*this);
			}

			void operator =(float v) volatile
			{
				SetFloat(v);
			}

			Half& operator =(double v)
			{
				SetFloat(float(v));
				return (*this);
			}

			void operator =(double v) volatile
			{
				SetFloat(float(v));
			}

			friend Half operator -(const Half& h);
	};


	inline Half operator -(const Half& h)
	{
		return (Half(uint16(h.value ^ 0x8000)));
	}


	inline const Half& ashalf(const int16& i)
	{
		return (reinterpret_cast<const Half&>(i));
	}

	inline const Half& ashalf(const uint16& i)
	{
		return (reinterpret_cast<const Half&>(i));
	}
}


#endif
