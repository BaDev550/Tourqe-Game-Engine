#include "tupch.h"
#include "Shader.h"
#include "glad/glad.h"

TourqeE::Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	const GLchar* source = (const GLchar*)vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(vertexShader);

		TU_ENGINE_ERROR("{0}", infoLog.data());
		TU_ENGINE_ASSERT(false, "vertex Shader Compile Error");
		return;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	source = (const GLchar*)fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);

		TU_ENGINE_ERROR("{0}", infoLog.data());
		TU_ENGINE_ASSERT(false, "fragment Shader Compile Error");
		return;
	}

	m_ProgramID = glCreateProgram();
	glAttachShader(m_ProgramID, vertexShader);
	glAttachShader(m_ProgramID, fragmentShader);

	glLinkProgram(m_ProgramID);

	GLint isLinked = 0;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(m_ProgramID);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		TU_ENGINE_ERROR("{0}", infoLog.data());
		TU_ENGINE_ASSERT(false, "Shader program failed to link");
		return;
	}

	glDetachShader(m_ProgramID, vertexShader);
	glDetachShader(m_ProgramID, fragmentShader);
}

TourqeE::Shader::~Shader()
{
	glDeleteProgram(m_ProgramID);
}

void TourqeE::Shader::Bind() const
{
	glUseProgram(m_ProgramID);
}

void TourqeE::Shader::Unbind() const
{
	glUseProgram(0);
}
