#ifndef DRAW_OPTIONS
#define DRAW_OPTIONS

namespace sgl {
	struct Blend;
	class ShaderProgram;

	struct DrawOptions {
		const Blend* blend = nullptr;
		const ShaderProgram* shader = nullptr;

		explicit DrawOptions(const Blend* bp);
		explicit DrawOptions(const ShaderProgram* sp);
		explicit DrawOptions(const Blend* bp, const ShaderProgram* sp);
	};
}

#endif