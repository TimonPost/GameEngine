#pragma once
#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "RendererAPI.h"
#include "Shader.h"
#include "Engine/Buffers/VertexArray.h"

namespace Engine
{
	class Renderer
	{
	public:

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform= glm::mat4(1.0f));
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		static void Init();
		 
		static void OnWindowResize(unsigned int width, unsigned int height)
		{
			RenderCommand::SetViewPort(0,0, width, height);
		}

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;			
		};

		static SceneData* _sceneData;
	};
}
