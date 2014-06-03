#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <cstring>
#include <SDL.h>
#include <SGL/Core/Types.hpp>

namespace sgl {
	struct System {
		enum OS : uint8 {
			Unknown = 0,
			Windows = 1,
			MacOSX = 2,
			Linux = 3,
			iOS = 4,
			Android = 5,
		};

		/**
		* Returns the available RAM
		*/
		static uint32 RAM();
		/**
		* Returns the total number of logical CPU cores. On CPUs that include technologies such as hyperthreading,
		* the number of logical cores may be more than the number of physical cores.
		*/
		static uint16 CountGPU();
		/**
		* Returns the name of the platform
		*/
		static OS Platform();
	};
}

#endif