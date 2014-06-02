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
			glCheck(glDeleteShader(_glShaderId));
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
					glCheck(glShaderSource(_glShaderId, 1, &buf, &length));

					delete[] buffer;
					buffer = nullptr;
					buf = nullptr;

					glCheck(glCompileShader(_glShaderId));
				}
			}
		}
	}

	bool Shader::hasErrors(std::string* str) const {
		int infologLength = 0;
		int charsWritten = 0;

		glGetShaderiv(_glShaderId, GL_INFO_LOG_LENGTH, &infologLength);

		if (infologLength > 1) {
			std::unique_ptr<char> infoLog = std::unique_ptr<char>(new char[infologLength]);

			glGetShaderInfoLog(_glShaderId, infologLength, &charsWritten, infoLog.get());

			if (str != nullptr)
				str->append(infoLog.get(), charsWritten);

			return true;
		}

		return false;
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
			glCheck(glDeleteProgram(_glProgId));
	}

	void ShaderProgram::execute() const {
		this->use(true);

		auto it = _textures.begin();
		if (it != _textures.end()) {
			for (std::size_t i = 0; i < _textures.size(); ++i) {
				GLint index = static_cast<GLsizei>(i + 1);
				glUniform1i(it->second.location, index);
				glActiveTexture(GL_TEXTURE0 + index);

				it->second.texture->bind();
				++it;
			}

			glCheck(glActiveTexture(GL_TEXTURE0));
		}
	}

	bool ShaderProgram::bind(const std::string& name, float value) const {
		const int loc = this->uniformLocationOf(name);
		
		return this->bind(loc, value);
	}

	bool ShaderProgram::bind(const std::string& name, float x, float y) const {
		const int loc = this->uniformLocationOf(name);
		
		return this->bind(loc, x, y);
	}

	bool ShaderProgram::bind(const std::string& name, const Vector2f& vec) const {
		return this->bind(name, vec.x, vec.y);
	}

	bool ShaderProgram::bind(const std::string& name, float x, float y, float z) const {
		const int loc = this->uniformLocationOf(name);
		
		return this->bind(loc, x, y, z);
	}

	bool ShaderProgram::bind(const std::string& name, float r, float g, float b, float a) const {
		const int loc = this->uniformLocationOf(name);
		
		return this->bind(loc, r, g, b, a);
	}

	bool ShaderProgram::bind(const std::string& name, const Color& col) const {
		const GLColor glcol = Color::InGLMode(col);
		
		return this->bind(name, glcol.red, glcol.green, glcol.blue, glcol.alpha);
	}

	bool ShaderProgram::bind(const std::string& name, const Texture* tex) {
		const int loc = this->uniformLocationOf(name);
		const bool valid = loc >= 0;
		if (valid)
			_textures[name] = ShaderTex(loc, tex);

		this->use(false);

		return valid;
	}

	bool ShaderProgram::unbindTexture(const std::string& name) {
		auto it = _textures.find(name);
		if (it != _textures.end() && typeid(it->second).name() == typeid(ShaderTex).name()) {
			_textures.erase(it);

			return true;
		}

		return false;
	}

	bool ShaderProgram::bind(int loc, float value) const {
		const bool valid = loc >= 0;
		if (valid) {
			this->use(true);
			glCheck(glUniform1f(loc, value));
			this->use(false);
		}

		this->use(false);

		return valid;
	}

	bool ShaderProgram::bind(int loc, float x, float y) const {
		const bool valid = loc >= 0;
		if (valid) {
			this->use(false);
			glCheck(glUniform2f(loc, x, y));
			this->use(false);
		}

		return valid;
	}

	bool ShaderProgram::bind(int loc, const Vector2f& vec) const {
		return this->bind(loc, vec.x, vec.y);
	}

	bool ShaderProgram::bind(int loc, float x, float y, float z) const {
		const bool valid = loc >= 0;
		if (valid) {
			this->use(true);
			glCheck(glUniform3f(loc, x, y, z));
			this->use(false);
		}

		return valid;
	}

	bool ShaderProgram::bind(int loc, float r, float g, float b, float a) const {
		const bool valid = loc >= 0;
		if (valid) {
			this->use(true);
			glCheck(glUniform4f(loc, r, g, b, a));
			this->use(false);
		}

		return valid;
	}

	bool ShaderProgram::bind(int loc, const Color& col) const {
		return this->bind(loc, col.red, col.green, col.blue, col.alpha);
	}

	bool ShaderProgram::hasErrors(std::string* str) const {
		int infologLength = 0;
		int charsWritten = 0;

		glCheck(glGetProgramiv(_glProgId, GL_INFO_LOG_LENGTH, &infologLength));

		if (infologLength > 1) {
			std::unique_ptr<char> infoLog = std::unique_ptr<char>(new char[infologLength]);

			glCheck(glGetProgramInfoLog(_glProgId, infologLength, &charsWritten, infoLog.get()));

			if (str != nullptr)
				str->append(infoLog.get(), charsWritten);

			return true;
		}

		return false;
	}
}