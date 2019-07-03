#include "TestShapes3D.h"

#include "Renderer.h"

#include "imgui/imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace test {
	TestShapes3D::TestShapes3D()
		//: m_translationA(0.5f, 0.4f, -0.6f)
		//, m_proj(glm::perspective(45.0f, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 20.0f))
		//, m_view(glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0)))
	{
        m_cube = ShapeGenerator::makeCube();
//        m_cube = ShapeGenerator::makePlane();
//        m_cube = ShapeGenerator::makeTriangle();

		// Create and Bind the vertex array
		m_VAO = std::make_unique<VertexArray>();

		// Create and Bind the vertex buffer
		m_vertexBuffer = std::make_unique<VertexBuffer>(m_cube.vertices, m_cube.vertexBufferSize());

		// Define the layout of the vertex buffer memory
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(3);

		m_VAO->AddBuffer(*m_vertexBuffer, layout);

		// Create and Bind the index buffer
		m_indexBuffer = std::make_unique<IndexBuffer>(m_cube.indices, m_cube.numIndices);

		// Create the shader
		m_shader = std::make_unique<Shader>("res/shaders/shader1.shader");

		// Bind the shader
		m_shader->Bind();
	}

	TestShapes3D::~TestShapes3D()
	{
	}

	void TestShapes3D::OnUpdate(float deltaTime)
	{
	}

	void TestShapes3D::OnRender()
	{
	    GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glEnable(GL_CULL_FACE));

        GLCall(glClearColor(0.3f, 0.3f, 0.f, 1.f));
	    GLCall(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
	    GLCall(glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

		Renderer renderer;

	    glm::mat4 viewToProjectionMatrix = glm::perspective(45.0f, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 20.0f);
	    glm::mat4 worldToViewMatrix = m_camera.getWorldToViewMatrix();
	    glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

        glm::mat4 cubeModelToWorldMatrix = glm::translate(glm::vec3(0.f, 0.f, -2.f)) *
            glm::rotate(RAD(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		    glm::rotate(RAD(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	    glm::mat4 modelToProjectionMatrix = worldToProjectionMatrix * cubeModelToWorldMatrix; // MVP

	    glm::vec4 ambientLight(0.02f, 0.02f, 0.1f, 1.0f);
        glm::vec3 lightPositionWorld(0.f, 5.f, 0.f);
	    glm::vec3 eyePositionWorld = m_camera.getPosition();

		m_shader->Bind(); // Bind our shader

		m_shader->SetUniformMat4f("modelToProjectionMatrix", modelToProjectionMatrix);
		m_shader->SetUniformMat4f("modelToWorldMatrix", cubeModelToWorldMatrix);
        m_shader->SetUniform4fv("ambientLight", ambientLight);
        m_shader->SetUniform3fv("eyePositionWorld", eyePositionWorld);
        m_shader->SetUniform3fv("lightPositionWorld", lightPositionWorld);

		renderer.Draw(*m_VAO, *m_indexBuffer, *m_shader);

  	    GLCall(glDisable(GL_DEPTH_TEST));
        GLCall(glDisable(GL_CULL_FACE));
    }

	void TestShapes3D::OnImGuiRender()
	{
		//ImGui::SliderFloat3("Translation A.x", &m_translationA.x, -1.f, 1.f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}