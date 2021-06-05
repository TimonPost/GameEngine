#include "epch.h"
#include "OrthographicCameraController.h"

#include "Engine/Core/Input.h"
#include "Engine/Core/Core.h"

namespace  Engine 
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : _aspectRatio(aspectRatio), _rotation(rotation),
		_camera(-aspectRatio * _zoomLevel, aspectRatio* _zoomLevel, -_zoomLevel, _zoomLevel)
	{
	}
	
	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		ENGINE_PROFILE_FUNCTION();
		
		if (Input::IsKeyPressed(Key::Right))
			_cameraPosition.x -= _cameraSpeed * ts;

		else if (Input::IsKeyPressed(Key::Left))
			_cameraPosition.x += _cameraSpeed * ts;

		if (Input::IsKeyPressed(Key::Up))
			_cameraPosition.y -= _cameraSpeed * ts;

		else if (Input::IsKeyPressed(Key::Down))
			_cameraPosition.y += _cameraSpeed * ts;

		if (_rotation) {
			if (Input::IsKeyPressed(Key::A))
				_cameraRotation -= _cameraRotationSpeed * ts;
			else if (Input::IsKeyPressed(Key::D))
				_cameraRotation += _cameraRotationSpeed * ts;
			_camera.SetRotation(_cameraRotation);
		}

		_camera.SetPosition(_cameraPosition);
		_cameraSpeed = _zoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		ENGINE_PROFILE_FUNCTION();
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		ENGINE_PROFILE_FUNCTION();
		
		_zoomLevel -= e.GetYOffset();
		_zoomLevel = std::max(_zoomLevel, 0.25f);
		_camera.SetProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);
		
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{		
		if (e.GetHeight() == 0)
			return false;
		
		_aspectRatio = e.GetWidth() / e.GetHeight();
		return false;
	}

}
