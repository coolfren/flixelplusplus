#ifndef FLXPOINT_HPP
#define FLXPOINT_HPP

#include "flixel++/Common.hpp"

namespace Flx {
	class Point {
	public:
		/// @brief Used commonly for coordination
		Point();

		/// @brief Used commonly for coordination
		/// @param x X position of the point
		/// @param y Y position of the point
		Point(float x, float y);
		
		~Point();

		/// @brief Adds an value to the point coordinates
		/// @param x X position adddition 
		/// @param y Y position adddition 
		void add(float x, float y);

		/// @brief Sets an value to the point coordinates
		/// @param x X position 
		/// @param y Y position 
		void set(float x, float y);

		/// @brief Subtracts an value to the point coordinates
		/// @param x X position subtraction 
		/// @param y Y position subtraction 
		void subtract(float x, float y);

		/// @brief Point X position
		float x;

		/// @brief Point Y position
		float y;

		int _x,_y;

		/// @brief Point's width 
		int w;
		
		/// @brief Point's height 
		int h;

		/// @brief Point's angle 
		float angle;

		/// @brief Point's scale 
		float scale;
	};
}

#endif