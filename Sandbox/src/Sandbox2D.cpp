#include "Sandbox2D.h"

#include "Engine/Debug/Instrumentor.h"


Sandbox2D::Sandbox2D() : Layer("Sandbox2d"), _cameraController(OrthographicCameraController(1280 / 720, true)), _color(glm::vec4(1, 1, 1, 1))
{
	
}

void Sandbox2D::OnAttach()
{
	_texture = Texture2D::Create("assets/textures/checkboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(_color));

	for (ProfileResult& profileResult : _profile_results)
	{
		char label[50];
		strcpy_s(label, profileResult.Name);
		strcat_s(label, " %.3fms");
		ImGui::Text(label, profileResult.Time);
	}

	_profile_results.clear();
	
	ImGui::End();
}

void Sandbox2D::OnUpdate(Timestep timestep)
{
	ENGINE_PROFILE_FUNCTION()

	{
		ENGINE_PROFILE_SCOPE("Camera Update")
		_cameraController.OnUpdate(timestep);
	}

	{
		ENGINE_PROFILE_SCOPE("Renderer Prep")
		
		RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		RenderCommand::Clear();
	}
		
	{
		ENGINE_PROFILE_SCOPE("Draw")
		Renderer2D::BeginScene(_cameraController.GetCamera());
		Renderer2D::DrawQuad({ -1,0 }, { 0.8, 0.8 }, _color);
		Renderer2D::DrawQuad({ 0.5,0.5 }, { 0.5, 0.75 }, { 0.8f, 0.2, 0.3, 1.0 });
		Renderer2D::DrawRotatedQuad({ 0.2,0.5 }, { 0.5, 0.5 }, glm::radians(45.0f),  _texture);
		Renderer2D::EndScene();
	}
	// std::dynamic_pointer_cast<OpenGLShader>(_shader)->Bind();
	// std::dynamic_pointer_cast<OpenGLShader>(_shader)->SetUniform4fv("v_Color", _color);		
}

void Sandbox2D::OnEvent(Event& e)
{
	_cameraController.OnEvent(e);
}
