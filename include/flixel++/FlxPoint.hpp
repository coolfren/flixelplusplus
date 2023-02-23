#ifndef FLXPOINT_HPP
#define FLXPOINT_HPP

#include "flixel++/Common.hpp"

namespace Flx {
	class Point {
	public:
		Point();
		Point(float x, float y);
		~Point();

		void add(float x, float y);
		void set(float x, float y);
		void subtract(float x, float y);

		float x, y;
		int _x,_y;
		int w,h;
		float angle;
		float scale;
	};
}

#endif