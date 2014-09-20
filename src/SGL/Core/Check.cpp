#include <SGL/Core/Check.hpp>
#include <SGL/Core/GL.hpp>
#include <SGL/Core/SDL.hpp>

void glCheckError(const char* file, unsigned int line) {
    // Get the last error
    const GLenum errorCode = glGetError();

    if (errorCode != GL_NO_ERROR) {
        std::string error = "unknown error";
        std::string description = "no description";

        // Decode the error code
        switch (errorCode) {
            case GL_INVALID_ENUM:
                error = "GL_INVALID_ENUM";
                description = "an unacceptable value has been specified for an enumerated argument";
                break;
            case GL_INVALID_VALUE:
                error = "GL_INVALID_VALUE";
                description = "a numeric argument is out of range";
                break;
            case GL_INVALID_OPERATION:
                error = "GL_INVALID_OPERATION";
                description = "the specified operation is not allowed in the current state";
                break;
            case GL_STACK_OVERFLOW:
                error = "GL_STACK_OVERFLOW";
                description = "this command would cause a stack overflow";
                break;
            case GL_STACK_UNDERFLOW:
                error = "GL_STACK_UNDERFLOW";
                description = "this command would cause a stack underflow";
                break;

            case GL_OUT_OF_MEMORY:
                error = "GL_OUT_OF_MEMORY";
                description = "there is not enough memory left to execute the command";
                break;
        }

        std::cerr << "An internal OpenGL call failed in " << file << " on line " << line << ": " << error << " -> " << description << std::endl;
    }
}

void SDL_CheckError(int ret, const char* file, unsigned int line) {
    if (ret != 0) {
        std::cerr << "An SDL error happens in " << file << " on line " << line << ": " << SDL_GetError() << std::endl;
        SDL_ClearError();
    }
}
