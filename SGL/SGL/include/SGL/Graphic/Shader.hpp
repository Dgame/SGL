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

		bool hasError(std::string* str = nullptr) const;
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
		ShaderProgram() = default;
		explicit ShaderProgram(const Shader& s1, const Shader& s2, bool link = false);
		virtual ~ShaderProgram();

		uint32 id() const {
			return _glProgId;
		}

		int locationOfUniform(const std::string& name) const {
			return glGetUniformLocation(_glProgId, name.c_str());
		}

		int locationOfAttrib(const std::string& name) const {
			return glGetAttribLocation(_glProgId, name.c_str());
		}

		void use(bool enable = true) const;

		void attach(const Shader& shader) {
			if (_glProgId == 0)
				_glProgId = glCreateProgram();
			glCheck(glAttachShader(_glProgId, shader.id()));
		}

		void detach(const Shader& shader) const {
			glCheck(glDetachShader(_glProgId, shader.id()));
		}

		void link() const {
			glCheck(glLinkProgram(_glProgId));
		}

		bool bind(const std::string& name, float value) const;
		bool bind(const std::string& name, float x, float y) const;
		bool bind(const std::string& name, const Vector2f& vec) const;
		bool bind(const std::string& name, float x, float y, float z) const;
		bool bind(const std::string& name, float r, float g, float b, float a) const;
		bool bind(const std::string& name, const Color& col) const;
		bool bind(const std::string& name, const Texture* tex);

		bool bind(int loc, float value) const;
		bool bind(int loc, float x, float y) const;
		bool bind(int loc, const Vector2f& vec) const;
		bool bind(int loc, float x, float y, float z) const;
		bool bind(int loc, float r, float g, float b, float a) const;
		bool bind(int loc, const Color& col) const;

		void bindAttribute(const std::string& name, uint32 colorNumber) const {
			glCheck(glBindFragDataLocation(_glProgId, colorNumber, name.c_str()));
		}

		bool unbindTexture(const std::string& name);

		bool hasError(std::string* str = nullptr) const;
	};
}

#endif