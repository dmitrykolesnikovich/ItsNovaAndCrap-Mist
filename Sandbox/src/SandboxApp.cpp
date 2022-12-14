#include <Mist.h>

#include <imgui.h>
#include "Mist\Platform\OpenGL\OpenGLShader.h"

class ExampleLayer : public Mist::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_CameraRotation(0.0f), m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(Mist::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Mist::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Mist::VertexBuffer::Create(vertices, sizeof(vertices)));
		Mist::BufferLayout layout = {
			{ Mist::ShaderDataType::Vec3f, "a_Position" },
			{ Mist::ShaderDataType::Vec4f, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<Mist::IndexBuffer> indexBuffer;
		indexBuffer.reset(Mist::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Mist::VertexArray::Create());

		float squareVertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Mist::VertexBuffer> squareVB;
		squareVB.reset(Mist::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Mist::BufferLayout squareLayout = {
			{ Mist::ShaderDataType::Vec3f, "a_Position" }
		};
		squareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<Mist::IndexBuffer> squareIB;
		squareIB.reset(Mist::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
				
			out vec4 color;

			in vec4 v_Color;	

			void main()
			{
				color = vec4(v_Color);
			}
		)";

		m_Shader.reset(Mist::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorFragmentSrc = R"(
			#version 330 core
				
			out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Mist::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc));
	}
	
	void OnUpdate(Mist::Timestep ts) override
	{
		if (Mist::Input::IsKeyPressed(MST_KEY_LEFT) || Mist::Input::IsKeyPressed(MST_KEY_A))
			m_CameraPosition.x -= m_CameraSpeed * ts;

		if (Mist::Input::IsKeyPressed(MST_KEY_RIGHT) || Mist::Input::IsKeyPressed(MST_KEY_D))
			m_CameraPosition.x += m_CameraSpeed * ts;

		if (Mist::Input::IsKeyPressed(MST_KEY_DOWN) || Mist::Input::IsKeyPressed(MST_KEY_S))
			m_CameraPosition.y -= m_CameraSpeed * ts;

		if (Mist::Input::IsKeyPressed(MST_KEY_UP) || Mist::Input::IsKeyPressed(MST_KEY_W))
			m_CameraPosition.y += m_CameraSpeed * ts;

		if (Mist::Input::IsMouseButtonPressed(MST_MOUSE_BUTTON_LEFT))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (Mist::Input::IsMouseButtonPressed(MST_MOUSE_BUTTON_RIGHT))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		if (Mist::Input::IsMouseButtonPressed(MST_MOUSE_BUTTON_MIDDLE))
			m_CameraRotation = 0.0f;

		Mist::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Mist::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Mist::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Mist::OpenGLShader>(m_FlatColorShader)->Bind();

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				if (x % 2 == 0)
					std::dynamic_pointer_cast<Mist::OpenGLShader>(m_FlatColorShader)->UploadUniformVec3f("u_Color", m_SquareRedColor);
				else
					std::dynamic_pointer_cast<Mist::OpenGLShader>(m_FlatColorShader)->UploadUniformVec3f("u_Color", m_SquareBlueColor);
				Mist::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		//Mist::Renderer::Submit(m_Shader, m_VertexArray);

		Mist::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Red Color", glm::value_ptr(m_SquareRedColor));
		ImGui::ColorEdit3("Square Blue Color", glm::value_ptr(m_SquareBlueColor));
		ImGui::End();
	}

	void OnEvent(Mist::Event& e) override
	{
		Mist::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Mist::KeyPressedEvent>(MST_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<Mist::MouseButtonPressedEvent>(MST_BIND_EVENT_FN(ExampleLayer::OnMouseButtonPressedEvent));
	}

	bool OnKeyPressedEvent(Mist::KeyPressedEvent& e)
	{
	//	if (e.GetKeyCode() == MST_KEY_LEFT || e.GetKeyCode() == MST_KEY_A)
		//	m_CameraPosition.x -= m_CameraSpeed;

	//	if (e.GetKeyCode() == MST_KEY_RIGHT || e.GetKeyCode() == MST_KEY_D)
		//	m_CameraPosition.x += m_CameraSpeed;

	//	if (e.GetKeyCode() == MST_KEY_DOWN || e.GetKeyCode() == MST_KEY_S)
			//m_CameraPosition.y -= m_CameraSpeed;

	//	if (e.GetKeyCode() == MST_KEY_UP || e.GetKeyCode() == MST_KEY_W)
		//	m_CameraPosition.y += m_CameraSpeed;

		if (e.GetKeyCode() == MST_KEY_SPACE)
			m_CameraPosition = { 0, 0, 0 };

		if (e.GetKeyCode() == MST_KEY_BACKSPACE)
		{
			m_CameraPosition = { 0, 0, 0 };
			m_CameraRotation = 0.0f;
			m_SquarePosition = { 0, 0, 0 };
		}

		if (Mist::Input::IsKeyPressed(MST_KEY_O))
			m_SquarePosition = { 0, 0, 0 };

		return false;
	}

	bool OnMouseButtonPressedEvent(Mist::MouseButtonPressedEvent& e)
	{
	//	if (e.GetMouseButton() == MST_MOUSE_BUTTON_LEFT)
		//	m_CameraRotation -= m_CameraRotationSpeed;

//		if (e.GetMouseButton() == MST_MOUSE_BUTTON_RIGHT)
	//		m_CameraRotation += m_CameraRotationSpeed;

		if (e.GetMouseButton() == MST_MOUSE_BUTTON_MIDDLE)
			m_CameraRotation = 0.0f;

		return false;
	}
private:
	std::shared_ptr<Mist::Shader> m_Shader;
	std::shared_ptr<Mist::VertexArray> m_VertexArray;

	std::shared_ptr<Mist::Shader> m_FlatColorShader;
	std::shared_ptr<Mist::VertexArray> m_SquareVA;

	Mist::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_CameraSpeed = 5.0f;
	float m_CameraRotationSpeed = 180.0f;
	glm::vec3 m_SquarePosition;
	float m_SquareSpeed = 1.0f;
	glm::vec3 m_SquareRedColor = { 0.8f, 0.2f, 0.3f };
	glm::vec3 m_SquareBlueColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Mist::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Mist::Application* Mist::CreateApplication()
{
	return new Sandbox();
}