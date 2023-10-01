#include "CameraSystem2D.h"

CameraSystem2D::CameraSystem2D()
{
	m_Priority = 101;
}

void CameraSystem2D::OnCreate()
{
	// insert code ...
};

void CameraSystem2D::OnUpdate(float delta)
{
	// get world 2D
	World2D *world2D = World2D::Instance;
	if (!world2D) return;

	const auto &currentLevel = world2D->Levels[world2D->CurrentLevelID];

	auto &camera2D = Renderer2D::GetCamera2D();

	ForEach([&camera2D, &currentLevel, delta](PlayerController& playerController, CameraController2D &cameraController2D, Transform2D &transform2D)
	{

		// set zoom to fit level
		if (currentLevel.Size.x / currentLevel.Size.y < Viewport::GetSize().x / Viewport::GetSize().y)
			cameraController2D.Zoom = Viewport::GetSize().x / currentLevel.Size.x;
		else
			cameraController2D.Zoom = Viewport::GetSize().y / currentLevel.Size.y;

		// transition zoom
		camera2D.Zoom = Interpolate::Linear(camera2D.Zoom, cameraController2D.Zoom, delta * cameraController2D.TransitionSpeed);

		// get past position
		vec2 pastCameraPosition = cameraController2D.Position;

		// look to player direction
		cameraController2D.LookOffset = Interpolate::Linear(cameraController2D.LookOffset, vec2::RIGHT() * cameraController2D.LookDistance * playerController.LookDirection, delta * cameraController2D.LookSpeed);

		// set position
		cameraController2D.Position = transform2D.Position - Viewport::GetSize() / (2.0f * cameraController2D.Zoom) + cameraController2D.LookOffset;

		// keep camera in world bound
		if (cameraController2D.Position.x < currentLevel.Position.x)
			cameraController2D.Position.x = currentLevel.Position.x;

		if (cameraController2D.Position.y < currentLevel.Position.y)
			cameraController2D.Position.y = currentLevel.Position.y;

		if (cameraController2D.Position.x + Viewport::GetSize().x / cameraController2D.Zoom > currentLevel.Position.x + currentLevel.Size.x)
			cameraController2D.Position.x = currentLevel.Position.x + currentLevel.Size.x - Viewport::GetSize().x / cameraController2D.Zoom;

		if (cameraController2D.Position.y + Viewport::GetSize().y / cameraController2D.Zoom > currentLevel.Position.y + currentLevel.Size.y)
			cameraController2D.Position.y = currentLevel.Position.y + currentLevel.Size.y - Viewport::GetSize().y / cameraController2D.Zoom;

		// transition
		if (cameraController2D.Transition)
		{
			cameraController2D.TransitionOffset = pastCameraPosition - cameraController2D.Position + cameraController2D.TransitionOffset;
			cameraController2D.Transition = false;
		}

		// transition offset to 0
		cameraController2D.TransitionOffset = Interpolate::Linear(cameraController2D.TransitionOffset, vec2::ZERO(), delta * cameraController2D.TransitionSpeed);

		// set camera position
		camera2D.Position = cameraController2D.Position + cameraController2D.TransitionOffset; 
	
	});
};

void CameraSystem2D::OnRender2D()
{
	// insert code ...
};

void CameraSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
