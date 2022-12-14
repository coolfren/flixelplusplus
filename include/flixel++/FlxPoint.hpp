#ifndef FLXPOINT_HPP
#define FLXPOINT_HPP

#include "flixel++/Common.hpp";

namespace Flx {
	class Point {
	public:
		Point();
		Point(float x, float y);
		~Point();

		add(float x, float y);
		set(float x, float y);
		subtract(float x, float y);


		float x, y;
		float angle;
		float scale;
	};
}

#endif