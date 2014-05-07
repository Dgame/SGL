#include <SGL/Graphic/Smooth.hpp>

namespace sgl {
	bool operator ==(const Smooth& lhs, const Smooth& rhs) {
		return lhs.mode == rhs.mode && lhs.target == rhs.target;
	}

	bool operator !=(const Smooth& lhs, const Smooth& rhs) {
		return !(lhs == rhs);
	}
}