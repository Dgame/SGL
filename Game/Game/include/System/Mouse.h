#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SDL.h>

/**
 * Represent the Mouse
 */
namespace Mouse {
	/**
	 * Shorthand for SDL_Cursor*
	 */
	using Cursor = SDL_Cursor*;

	/**
	 * Supported mouse buttons
	 */
	enum class Button : short {
		Left = 1, /** */
		Middle = 2, /** */
		Right = 3, /** */
		X1 = 4, /** */
		X2 = 5, /** */
		Other /** */
	};

	/**
	 * Supported mouse states
	 */
	enum class State : short {
		Released, /** */
		Pressed /** */
	};

	/**
	 * Supported mouse motion states
	 */
	enum class MotionStates : short {
		LMask = 0x1, /** */
		MMask = 0x2, /** */
		RMask = 0x4, /** */
		X1Mask = 0x8, /** */
		X2Mask = 0x10 /** */
	};
};

#endif