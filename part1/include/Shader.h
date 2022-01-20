#ifndef SHADER_H
#define SHADER_H

#include <string>

#if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
#else // This works for Mac
#include <SDL.h>
#endif

#include <glad/glad.h>

class Shader {
	// Compile current shader
	unsigned int CompileShader(unsigned int type, const std::string& source);
	// Ensure the shader is actually linked
	bool CheckLinkStatus(GLuint programID);
	// Shader logs
	void PrintProgramLog(GLuint program);
	void PrintShaderLog(GLuint shader);
	// Log error messages
	void Log(const char* system, const char* message);
	// Unique shader ID
	GLuint m_shaderID;

public:
	// Constructor
	Shader();
	// Destructor
	~Shader();
	// Use shader in the pipeline
	void Bind() const;
	// Remove shader from the pipeline
	void Unbind() const;
	// Load shader from filepath
	std::string LoadShader(const std::string& filePath);
	// Create the vertex and fragment shader
	void CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	// Return the shader ID
	GLuint GetID() const;
	// Setup shader uniforms
	void SetUniformMatrix4fv(const GLchar* name, const GLfloat* value);
	void SetUniform3f(const GLchar* name, float f1, float f2, float f3);
	void SetUniform1i(const GLchar* name, int value);
	void SetUniform1f(const GLchar* name, float value);
};

#endif
