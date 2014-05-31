#ifndef SHADER_HPP
#define SHADER_HPP

#include <fstream>
#include <map>
#include <SGL/Core/OpenGL.hpp>
#include <SGL/Core/Types.hpp>
#include <SGL/Core/Output.hpp>
#include <SGL/Graphic/Color.hpp>
#include <SGL/Math/Vector2.hpp>

namespace sgl {
	class Texture;

	class Shader {
	public:
		enum class Type {
			Vertex = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER,
			Geometry = GL_GEOMETRY_SHADER
		};

	private:
		uint32 _glShaderId = 0;
		Type _type;

	public:
		explicit Shader(Type type);
		explicit Shader(Type type, const std::string& filename);

		virtual ~Shader();

		uint32 id() const {
			return _glShaderId;
		}

		Type getType() const {
			return _type;
		}

		void loadFromFile(const std::string& filename);
	};

	struct ShaderTex {
		const Texture* texture;
		int location;

		ShaderTex() = default;
		explicit ShaderTex(int loc, const Texture* tex);
	};

	class ShaderProgram {
	private:
		uint32 _glProgId = 0;

		std::map<std::string, ShaderTex> _textures;

	public:
		virtual ~ShaderProgram();

		uint32 id() const {
			return _glProgId;
		}

		int locationOf(const std::string& name) const {
			return glGetUniformLocation(_glProgId, name.c_str());
		}

		void use(bool enable = true) const;

		void attach(const Shader& shader) {
			if (_glProgId == 0)
				_glProgId = glCreateProgram();
			glAttachShader(_glProgId, shader.id());
		}

		void detach(const Shader& shader) const {
			glDetachShader(_glProgId, shader.id());
		}

		void link() const {
			glLinkProgram(_glProgId);
		}

		void bind(const std::string& name, float value) const;
		void bind(const std::string& name, float x, float y) const;
		void bind(const std::string& name, const Vector2f& vec) const;
		void bind(const std::string& name, float x, float y, float z) const;
		void bind(const std::string& name, float r, float g, float b, float a) const;
		void bind(const std::string& name, const Color& col) const;
		void bind(const std::string& name, const Texture* tex);

		void unbindTexture(const std::string& name);
	};
}

#endif