#ifndef FLXPOINT_HPP
#define FLXPOINT_HPP

#include "flixel++/Common.hpp";

namespace Flx {
	class Point {
	public:
		Point();
		Point(float x, float y);
		~Point();


		float x, y;
		float angle;
		float scale;
	};
}

#endif