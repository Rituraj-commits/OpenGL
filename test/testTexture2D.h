#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "texture.h"
#include<memory>

namespace test
{
	class TestTexture2D :public Test
	{
	private:
		glm::vec3 m_TranslationA, m_TranslationB;
		std::unique_ptr<VertexArray> m_vao;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<Texture> m_texture;
		glm::mat4 m_proj, m_view;
		std::unique_ptr<VertexBuffer> m_vb;
	public:
		TestTexture2D();
		~TestTexture2D();
		
		void OnUpdate(float deltatime) override;
		void OnRender() override;
		void OnImguiRender() override;

	};
}