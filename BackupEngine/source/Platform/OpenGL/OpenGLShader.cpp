#include "bcpch.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "BackupEngine/Core/Timer.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace BackupEngine {

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		//Create An Empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		//Send the vertex shader source code to OpenGL
		const GLchar* source = vertexSrc.c_str();
		m_OpenGLSourceCode[GL_VERTEX_SHADER] = source;
		glShaderSource(vertexShader, 1, &source, 0);

		//Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompilied = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompilied);
		if (isCompilied == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			BC_CORE_ERROR("{0}", infoLog.data());
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//Send the fragment shader source code to OpenGL
		source = vertexSrc.c_str();
		m_OpenGLSourceCode[GL_FRAGMENT_SHADER] = source;
		glShaderSource(fragmentShader, 1, &source, 0);

		//Compile the vertex shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompilied);
		if (isCompilied == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);

			glDeleteShader(vertexShader);

			BC_CORE_ERROR("{0}", infoLog.data());
			return;
		}

		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		
		GLuint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			
			BC_CORE_ERROR("{0}", infoLog.data());
			BC_CORE_ASSERT(false, "Shader link failure")
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		m_Name = name;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_FilePath(filepath)
	{
		std::string sourceCode = ReadFile(filepath);
		m_OpenGLSourceCode = PreProcess(sourceCode);

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = m_OpenGLSourceCode[GL_VERTEX_SHADER].c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		//Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompilied = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompilied);
		if (isCompilied == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			BC_CORE_ERROR("{0}", infoLog.data());
		}

		//Create Fragment Shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//Send the fragment shader source code to OpenGL
		source = m_OpenGLSourceCode[GL_FRAGMENT_SHADER].c_str();

		glShaderSource(fragmentShader, 1, &source, 0);

		//Compile the vertex shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompilied);
		if (isCompilied == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);

			glDeleteShader(vertexShader);

			BC_CORE_ERROR("{0}", infoLog.data());
			return;
		}

		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLuint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			BC_CORE_ERROR("{0}", infoLog.data());
			BC_CORE_ASSERT(false, "Shader link failure")
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		//Extract Name From from Filepath
		auto lastslash = filepath.find_last_of("/\\");
		lastslash = lastslash == std::string::npos ? 0 : lastslash + 1;
		auto lastDot = filepath.rfind(".");
		auto count = lastDot == std::string::npos ? filepath.size() - lastslash : lastDot - lastslash;
		m_Name = filepath.substr(lastslash, count);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		UploadUniformFloat2(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if(size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else
			{
				BC_CORE_ERROR("Could not open file '{0}'", filepath);
			}
		}
		else
		{
			BC_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		GLuint shader_type = GL_ZERO;

		std::string line;
		std::stringstream sourceCode;
		sourceCode << source;
		std::stringstream ss[2];
		while (std::getline(sourceCode, line))
		{
			if (line.find(typeToken) != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					shader_type = GL_VERTEX_SHADER;
				else if (line.find("fragment") != std::string::npos)
					shader_type = GL_FRAGMENT_SHADER;
			}
			else
			{
				if (shader_type == GL_VERTEX_SHADER)
					ss[0] << line << "\n";
				else if (shader_type == GL_FRAGMENT_SHADER)
					ss[1] << line << "\n";
			}
		}
		shaderSources[GL_VERTEX_SHADER] = ss[0].str();
		shaderSources[GL_FRAGMENT_SHADER] = ss[1].str();

		return shaderSources;
	}

}