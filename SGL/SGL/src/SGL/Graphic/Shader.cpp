#include <typeinfo>
#include <SGL/Graphic/Shader.hpp>
#include <SGL/Graphic/Texture.hpp>

namespace sgl {
	Shader::Shader(Type type) : _type(type) {

	}

	Shader::Shader(Type type, const std::string& filename) : Shader(type) {
		this->loadFromFile(filename);
	}

	Shader::~Shader() {
		if (_glShaderId != 0)
			glDeleteShader(_glShaderId);
	}

	void Shader::loadFromFile(const std::string& filename) {
		std::ifstream is(filename, std::ifstream::binary);

		char* buffer = nullptr;
		int length = 0;

		if (is) {
			// get length of file:
			is.seekg(0, is.end);
			length = is.tellg();

			if (length > 0) {
				is.seekg(0, is.beg); // Back to beginning

				buffer = new char[length];
				// read data as a block:
				is.read(buffer, length);
				is.close();

				if (buffer != nullptr) {
					if (_glShaderId == 0)
						_glShaderId = glCreateShader(static_cast<GLenum>(_type));

					const char* buf = buffer;
					glShaderSource(_glShaderId, 1, &buf, &length);

					delete[] buffer;
					buffer = nullptr;
					buf = nullptr;

					glCompileShader(_glShaderId);
				}
			}
		}
	}

	ShaderTex::ShaderTex(int loc, const Texture* tex) : location(loc), texture(tex) {

	}

	ShaderProgram::ShaderProgram(const Shader& s1, const Shader& s2, bool link) {
		this->attach(s1);
		this->attach(s2);

		if (link)
			this->link();
	}

	ShaderProgram::~ShaderProgram() {
		if (_glProgId != 0)
			glDeleteProgram(_glProgId);
	}

	void ShaderProgram::use(bool enable) const {
		if (enable) {
			glUseProgram(_glProgId);

			auto it = _textures.begin();
			for (std::size_t i = 0; i < _textures.size(); ++i) {
				GLint index = static_cast<GLsizei>(i + 1);
				glUniform1i(it->second.location, index);
				glActiveTexture(GL_TEXTURE0 + index);

				it->second.texture->bind();
				++it;
			}

			glActiveTexture(GL_TEXTURE0);
		} else
			glUseProgram(0);

		//glBindTexture(GL_TEXTURE_2D, 0);
	}

	void ShaderProgram::bind(const std::string& name, float value) const {
		this->use(true);

		const int loc = this->locationOf(name);
		if (loc > 0)
			glUniform1f(loc, value);
	}

	void ShaderProgram::bind(const std::string& name, float x, float y) const {
		this->use(true);

		const int loc = this->locationOf(name);
		if (loc > 0)
			glUniform2f(loc, x, y);
	}

	void ShaderProgram::bind(const std::string& name, const Vector2f& vec) const {
		this->bind(name, vec.x, vec.y);
	}

	void ShaderProgram::bind(const std::string& name, float x, float y, float z) const {
		this->use(true);

		const int loc = this->locationOf(name);
		if (loc > 0)
			glUniform3f(loc, x, y, z);
	}

	void ShaderProgram::bind(const std::string& name, float r, float g, float b, float a) const {
		this->use(true);

		const int loc = this->locationOf(name);
		if (loc > 0)
			glUniform4f(loc, r, g, b, a);
	}

	void ShaderProgram::bind(const std::string& name, const Color& col) const {
		const GLColor glcol = Color::InGLMode(col);
		this->bind(name, glcol.red, glcol.green, glcol.blue, glcol.alpha);
	}

	void ShaderProgram::bind(const std::string& name, const Texture* tex) {
		const int loc = this->locationOf(name);
		if (loc > 0)
			_textures[name] = ShaderTex(loc, tex);
	}

	void ShaderProgram::unbindTexture(const std::string& name) {
		auto it = _textures.find(name);
		if (it != _textures.end() && typeid(it->second).name() == typeid(ShaderTex).name()) {
			_textures.erase(it);
		}
	}
}