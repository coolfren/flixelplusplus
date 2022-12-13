#ifndef FLXPOINT_HPP
#define FLXPOINT_HPP

#include "flixel++/Common.hpp";

namespace Flx {
	class Point {
	public:
		Point() {};
		Point(float x, float y) {
			set(x, y);
		}
		~Point() {};
		void add(float x, float y) {
			this->x += x;
			this->y += y;
		}
		void set(float x, float y) {
			this->x = x;
			this->y = y;
		}
		void subtract(float x, float y) {
			this->x -= x;
			this->y -= y;
		}


		float x, y;
		float angle;
		float scale;
	};
}

#endif