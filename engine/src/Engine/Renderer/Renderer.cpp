#include "epch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Renderer2D.h"
#include "Platforms/OpenGl/OpenGLShader.h"

namespace Engine
{
	Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData();
	
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		_sceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMatrix4fv("u_ViewProjection", _sceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMatrix4fv("u_Transform", transform);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}
}
