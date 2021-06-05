#pragma once
#include "Engine.h"
#include "../../engine/vendor/imgui/imgui.h"
#include "Platforms/OpenGl/OpenGLShader.h"

using namespace Engine;

class Sandbox2D : public Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	
	void OnAttach() override;
	void OnDetach() override;
	
	void OnImGuiRender() override;
	void OnUpdate(Timestep timestep) override;
	void OnEvent(Event& e) override;

private:
	OrthographicCameraController _cameraController;
	ShaderLibrary _shaderLibrary;
	
	Ref<Texture2D> _texture;

	Ref<VertexArray> _vertexArray;
	Ref<VertexBuffer> _squareVertexBuffer;
	Ref<IndexBuffer> _squareIndexBuffer;
		
	Ref<Shader> _shader;

	glm::vec4 _color;

	struct ProfileResult
	{
		const char* Name;
		float Time;		
	};

	std::vector<ProfileResult> _profile_results;
	glm::vec4 _squareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};
