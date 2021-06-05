#include "EditorLayer.h"

#include "Engine/Debug/Instrumentor.h"
#include "glm/vec4.hpp"

static const int MapWidth = 24;
static const char* _mapTiles =
"WWWWWWWWWWDDWWWWWWWWWWWW"
"WWWWWWWWWDDDDWWWWWWWWWWW"
"WWWWWWWWDDDDDDWWWWWWWWWW"
"WWWWWWDDDDDDDDWDWWWWWWWW"
"WWWWWDDDDDDDDDWWWWWWWWWW"
"WWWWWDDDWWDDDDDDDDWWWWWW"
"WWWWWDDDWWDDDDDDDDWWWWWW"
"WWWWWWDDDDDDDDDDDWWWWWWW"
"WWWWWWDDDDDDDDDDWWWWWWWW"
"WWWWWWWWDDDDDDWWWWWWWWWW"
"WWWWWWWWWDDDDWWWWWWWWWWW"
"WWWWWWWWWWDDWWWWWWWWWWWW"
;

EditorLayer::EditorLayer() : Layer("Sandbox2d"), _cameraController(OrthographicCameraController(SCREEN_WIDTH / SCREEN_HEIGHT, true)), _color(glm::vec4(1, 1, 1, 1))
{
	
}

void EditorLayer::OnAttach()
{
	_testTexture = Texture2D::Create("assets/textures/checkboard.png");
	_spriteSheet = Texture2D::Create("assets/textures/spriteSheet.png");

	_textureMap = {
		{'D', SubTexture::CreateFromCoords(_spriteSheet, { 6, 11 }, { 128, 128 })},
		{'W', SubTexture::CreateFromCoords(_spriteSheet, { 11, 11 }, { 128, 128 })},		
	};
	
	_cameraController.SetZoomLevel(5);

	_mapWidth = MapWidth;
	_mapHeight = strlen(_mapTiles) / _mapWidth;

    FrameBufferSpecification specs;
    specs.width = SCREEN_WIDTH;
    specs.height = SCREEN_HEIGHT;
	
    _frameBuffer = FrameBuffer::Create(specs);
	
}

void EditorLayer::OnDetach()
{
}

void EditorLayer::OnImGuiRender()
{
    static bool dockspace= true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
    // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
    // all active windows docked into it will lose their parent and become undocked.
    // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
    // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspace, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
  
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit")) Application::Instance().Close();
        	
            ImGui::EndMenu();
        }
     
        ImGui::EndMenuBar();
    }

    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(_color));
    
    for (ProfileResult& profileResult : _profile_results)
    {
        char label[50];
        strcpy_s(label, profileResult.Name);
        strcat_s(label, " %.3fms");
        ImGui::Text(label, profileResult.Time);
    }

    auto stats = Renderer2D::GetStats();
    ImGui::Text("Renderer2D Stats: ");
    ImGui::Text("Draw Calls: %d",stats.DrawCalls);
    ImGui::Text("Quad Count: %d", stats.QuadCount);
    ImGui::Text("Vertex Count: %d", stats.GetTotalVertexCount());
    ImGui::Text("Index Count: %d", stats.GetTotalIndexCount());
	
    unsigned int textureId = _frameBuffer->GetColorAttachementRenderID();
    ImGui::Image((void*)textureId, ImVec2{ SCREEN_WIDTH,SCREEN_HEIGHT});
    ImGui::End();
    ImGui::End();
	
	_profile_results.clear();	
}

void EditorLayer::OnUpdate(Timestep timestep)
{
    ENGINE_PROFILE_FUNCTION()

        _frameBuffer->Bind();
	
	{
		ENGINE_PROFILE_SCOPE("Camera Update")
		_cameraController.OnUpdate(timestep);
	}

    Renderer2D::ResetStarts();
	
	{
		ENGINE_PROFILE_SCOPE("Renderer Prep")
		
		RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		RenderCommand::Clear();
	}
		
	{
		ENGINE_PROFILE_SCOPE("Draw")
		Renderer2D::BeginScene(_cameraController.GetCamera());

		for (int y = 0; y < _mapHeight; y++)
		{
			for (int x = 0; x < _mapWidth; x++)
			{
				char tileType = _mapTiles[x + y * _mapWidth];

				Ref<SubTexture> tile;
				if (_textureMap.find(tileType) == _textureMap.end())
				{
					tile = _barrel;
				} else
				{
					tile = _textureMap[tileType];
				}
				
				
				Renderer2D::DrawQuad({ x - _mapWidth / 2, _mapHeight - y - _mapHeight / 2 }, { 1, 1 }, tile);
			}
		}
		
		Renderer2D::EndScene();
        _frameBuffer->Unbind();
	}	
}

void EditorLayer::OnEvent(Event& e)
{
	_cameraController.OnEvent(e);
}
