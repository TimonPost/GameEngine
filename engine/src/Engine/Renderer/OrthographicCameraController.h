#pragma once
#include "Engine/Core/Timestep.h"
#include "Engine/Event/Application.h"
#include "Engine/Event/Event.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Renderer/OrthographicCamera.h"
#include "Engine/Event/KeyCodes.h"

namespace Engine {
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
					
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		OrthographicCamera& GetCamera() { return _camera;  }
		const OrthographicCamera& GetCamera() const { return _camera; }

		void SetZoomLevel(float zoomLevel) { _zoomLevel = zoomLevel; };
		float GetZoomLevel() const { return _zoomLevel; }
	
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		
	private:
		float _aspectRatio;
		float _zoomLevel = 1.0f;
		bool _rotation = 0.0f;
		glm::vec3 _cameraPosition { 0,0,0 };
		float _cameraSpeed = 3.0f;
		float _cameraRotation = 0.00f;
		float _cameraRotationSpeed = 40.0f;
		
		OrthographicCamera _camera;
	};
}
