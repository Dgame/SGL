#ifndef DRAW_OPTIONS
#define DRAW_OPTIONS

namespace sgl {
	struct Blend;
	//class Shader;

	struct DrawOptions {
		const Blend* blend;
		//const Shader* shader;

		explicit DrawOptions(Blend* bp);
		//explicit DrawOptions(Shader* sp);
		//explicit DrawOptions(Blend* bp, Shader* sp);
	};
}

#endif