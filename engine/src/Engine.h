 #pragma once

// Used by engine applications

// ---- Core ----
#include "Engine/Core/Application.h"
#include "Engine/Core/Layer.h"
#include "Engine/Core/Log.h"
#include "Engine/Core/Input.h"

#include "Engine/Event/KeyCodes.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/MouseButtonCodes.h"

#include "Engine/ImGui/ImGuiLayer.h"

// ---- Renderer ----
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/RendererAPI.h"

#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Texture.h"
#include "Engine/Renderer/OrthographicCamera.h"
#include "Engine/Renderer/OrthographicCameraController.h"

#include "Engine/Renderer/GraphicsContext.h"

// ---- Buffer ----

#include "Engine/Buffers/VertexBuffer.h"
#include "Engine/Buffers/IndexBuffer.h"
#include "Engine/Buffers/VertexBufferLayout.h"
#include "Engine/Buffers/VertexArray.h"

