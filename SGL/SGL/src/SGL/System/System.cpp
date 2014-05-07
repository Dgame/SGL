#include <SGL/System/System.hpp>

namespace sgl {
	/**
	* Returns the available RAM
	*/
	uint32 System::RAM() {
		return SDL_GetSystemRAM();
	}

	/**
	* Returns the total number of logical CPU cores. On CPUs that include technologies such as hyperthreading,
	* the number of logical cores may be more than the number of physical cores.
	*/
	uint16 System::CountGPU() {
		return SDL_GetCPUCount();
	}

	/**
	* Returns the name of the platform
	*/
	System::OS System::Platform() {
		const char* platform = SDL_GetPlatform();

		if (strcmp(platform, "Windows") == 0)
			return OS::Windows;
		if (strcmp(platform, "Mac OS X") == 0)
			return OS::MacOSX;
		if (strcmp(platform, "Linux") == 0)
			return OS::Linux;
		if (strcmp(platform, "iOS") == 0)
			return OS::iOS;
		if (strcmp(platform, "Android") == 0)
			return OS::Android;
		
		return OS::Unknown;
	}
}