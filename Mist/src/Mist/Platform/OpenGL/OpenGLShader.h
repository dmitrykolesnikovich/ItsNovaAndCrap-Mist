#pragma once

#include <string>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Mist\Renderer\Shader.h"

namespace Mist {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformUint(const std::string& name, unsigned int value);
		void UploadUniformDouble(const std::string& name, double value);
		
		void UploadUniformVec2f(const std::string& name, const glm::vec2& vector);
		void UploadUniformVec3f(const std::string& name, const glm::vec3& vector);
		void UploadUniformVec4f(const std::string& name, const glm::vec4& vector);
		void UploadUniformVec2i(const std::string& name, const glm::ivec2& vector);
		void UploadUniformVec3i(const std::string& name, const glm::ivec3& vector);
		void UploadUniformVec4i(const std::string& name, const glm::ivec4& vector);
		void UploadUniformVec2u(const std::string& name, const glm::uvec2& vector);
		void UploadUniformVec3u(const std::string& name, const glm::uvec3& vector);
		void UploadUniformVec4u(const std::string& name, const glm::uvec4& vector);
		void UploadUniformVec2d(const std::string& name, const glm::dvec2& vector);
		void UploadUniformVec3d(const std::string& name, const glm::dvec3& vector);
		void UploadUniformVec4d(const std::string& name, const glm::dvec4& vector);

		void UploadUniformMat2(const std::string& name, const glm::mat2& matrix);
		void UploadUniformMat2x3(const std::string& name, const glm::mat2x3& matrix);
		void UploadUniformMat2x4(const std::string& name, const glm::mat2x4& matrix);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat3x2(const std::string& name, const glm::mat3x2& matrix);
		void UploadUniformMat3x4(const std::string& name, const glm::mat3x4& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat4x3(const std::string& name, const glm::mat4x3& matrix);
		void UploadUniformMat4x2(const std::string& name, const glm::mat4x2& matrix);
	private:
		uint32_t m_RendererID;
	};

}