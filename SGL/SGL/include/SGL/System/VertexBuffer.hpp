#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <SGL/Core/Types.hpp>
#include <SGL/Core/OpenGL.hpp>

namespace sgl {
	class VertexBuffer final {
	private:
		uint32 _glBufId = 0;

	public:
		enum class Usage {
			StreamDraw = GL_STREAM_DRAW,
			StreamRead = GL_STREAM_READ,
			StreamCopy = GL_STREAM_COPY,
			StaticDraw = GL_STATIC_DRAW,
			StaticRead = GL_STATIC_READ,
			StaticCopy = GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY
		};

		enum class Access {
			ReadOnly = GL_READ_ONLY,
			WriteOnly = GL_WRITE_ONLY,
			ReadWrite = GL_READ_WRITE
		};

		~VertexBuffer() {
			if (_glBufId != 0)
				glDeleteBuffers(1, &_glBufId);
		}

		void bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, _glBufId);
		}

		void unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void buffer(const void* data, uint32 size, Usage usage) {
			if (_glBufId == 0)
				glGenBuffers(1, &_glBufId);

			this->bind();

			glBufferData(GL_ARRAY_BUFFER, size, data, static_cast<GLenum>(usage));
		}

		const void* map(Access access) const {
			return glMapBuffer(GL_ARRAY_BUFFER, static_cast<GLenum>(access));
		}

		bool unmap() const {
			return glUnmapBuffer(GL_ARRAY_BUFFER) == GL_TRUE;
		}
	};
}

#endif