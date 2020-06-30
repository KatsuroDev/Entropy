#pragma once

#include <string>
#include <unordered_map>
#include <GL/glm/glm.hpp>

namespace Entropy {

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Attach() const = 0;
		virtual void Detach() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, unsigned int count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string& GetName() const = 0;

		static Shader* Create(const std::string& filepath);
		static Shader* Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, Shader* shader);
		void Add(Shader* shader);
		Shader* Load(const std::string& filepath);
		Shader* Load(const std::string& name, const std::string& filepath);

		Shader* Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Shader*> m_Shaders;
	};
}
