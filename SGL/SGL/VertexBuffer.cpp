#include <SGL/System/VertexBuffer.hpp>

namespace sgl {
	VertexBuffer::~VertexBuffer() {
		if (_glBufId != 0)
			glDeleteBuffers(1, &_glBufId);
	}

	void VertexBuffer::buffer(const void* data, uint32 size, Usage usage) {
		if (_glBufId == 0)
			glGenBuffers(1, &_glBufId);

		this->bind();

		glBufferData(GL_ARRAY_BUFFER, size, data, static_cast<GLenum>(usage));
	}
}