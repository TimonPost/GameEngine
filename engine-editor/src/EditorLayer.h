#pragma once
#include <memory>
#include <unordered_map>

#include "Engine.h"
#include "../../engine/vendor/imgui/imgui.h"
#include "glm/vec4.hpp"

using namespace Engine;

class EditorLayer : public Layer
{
public:
	EditorLayer();
	virtual ~EditorLayer() = default;
	
	void OnAttach() override;
	void OnDetach() override;
	
	void OnImGuiRender() override;
	void OnUpdate(Timestep timestep) override;
	void OnEvent(Event& e) override;

private:
	OrthographicCameraController _cameraController;
	ShaderLibrary _shaderLibrary;
	
	Ref<Texture2D> _testTexture;
	Ref<Texture2D> _spriteSheet;
	Ref<SubTexture> _textureFromStairs;

	Ref<VertexArray> _vertexArray;
	Ref<VertexBuffer> _squareVertexBuffer;
	Ref<IndexBuffer> _squareIndexBuffer;
		
	Ref<Shader> _shader;

	glm::vec4 _color;
	std::shared_ptr<SubTexture> _barrel;
	std::shared_ptr<SubTexture> _textureThree;
	std::shared_ptr<FrameBuffer> _frameBuffer;

	struct ProfileResult
	{
		const char* Name;
		float Time;		
	};

	std::vector<ProfileResult> _profile_results;
	glm::vec4 _squareColor = {0.2f, 0.3f, 0.8f, 1.0f};

	std::unordered_map<char, Ref<SubTexture>> _textureMap;

	int _mapWidth;
	int _mapHeight;
};
