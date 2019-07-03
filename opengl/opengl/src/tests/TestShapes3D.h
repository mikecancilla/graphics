#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"
#include "primitives/ShapeGenerator.h"

#include <memory>

namespace test {

	class TestShapes3D : public Test
	{
	public:
		TestShapes3D();
		~TestShapes3D();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<Shader> m_shader;

		//glm::mat4 m_proj, m_view;
		//glm::vec3 m_translationA;

        ShapeData m_cube;
        Camera m_camera;
	};
}