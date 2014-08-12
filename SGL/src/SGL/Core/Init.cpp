#include <iostream>
#include <SGL/Core/Init.hpp>

namespace Intern {
	void initSDL() {
		if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
			SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
		}
#if SGL_DEBUG
		printf("init SDL\n");
#endif
	}

	void quitSDL(sgl::uint8 count) {
		if (count == 0) {
#if SGL_DEBUG
			printf("quit SDL\n");
#endif
			SDL_Quit();
		}
	}

	void initGL() {
		glCheck(glDisable(GL_DITHER));
		glCheck(glDisable(GL_LIGHTING));
		glCheck(glDisable(GL_DEPTH_TEST));
		glCheck(glDisable(GL_ALPHA_TEST));

		glCheck(glEnable(GL_CULL_FACE));
		glCheck(glEnable(GL_TEXTURE_2D));
		glCheck(glEnable(GL_BLEND));

		glCheck(glCullFace(GL_FRONT));
		glCheck(glShadeModel(GL_FLAT));
		glCheck(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

		glCheck(glEnableClientState(GL_VERTEX_ARRAY));
		glCheck(glEnableClientState(GL_TEXTURE_COORD_ARRAY));
		glCheck(glEnableClientState(GL_COLOR_ARRAY));

		// Hints
		glCheck(glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST));

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		const GLenum err = glewInit();
		if (err != GLEW_OK) {
			std::cerr << "Couldn't initialize GLEW" << std::endl;

			exit(1);
		}
#if SGL_DEBUG
		printf("init GL\n");
#endif
	}
}