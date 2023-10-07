#include "CameraSystem2D.h"

CameraSystem2D* CameraSystem2D::s_Instance = nullptr;

CameraSystem2D::CameraSystem2D()
{
	m_Priority = 101;
}

void CameraSystem2D::IShake(float magnitude, float duration)
{
	ForEach([duration, magnitude] (PlayerController& playerController, CameraController2D &cameraController2D, Transform2D &transform2D)
	{
		cameraController2D.ShakeAngle = Random::Float() * 2.0f * M_PI;
		cameraController2D.ShakeDuration = duration;
		cameraController2D.ShakeTime = 0.0f;
		cameraController2D.ShakeMag = magnitude;
	});
}

void CameraSystem2D::ISlowMotion(float duration)
{
	ForEach([duration] (PlayerController& playerController, CameraController2D &cameraController2D, Transform2D &transform2D)
	{
		Application::GetSingleton()->TimeScale = 0.1f;
		cameraController2D.SlowTimer = duration * Application::GetSingleton()->TimeScale;
	});
}

void CameraSystem2D::OnCreate()
{
	s_Instance = this;
	Renderer2D::GetCamera2D().Zoom = 480.0f / 320.0f;
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

		// shake animation
		float shakeMag = Interpolate::Linear(cameraController2D.ShakeMag, 0.0f, cameraController2D.ShakeTime / cameraController2D.ShakeDuration);
		cameraController2D.ShakeOffset = vec2::RIGHT().Rotate(cameraController2D.ShakeAngle) * (shakeMag * sin(2.0f * M_PI * cameraController2D.ShakeFreq * cameraController2D.ShakeTime));
		cameraController2D.ShakeTime += delta;

		// slow duration
		cameraController2D.SlowTimer -= delta;
		if (cameraController2D.SlowTimer < 0.0f)
		{
			Application::GetSingleton()->TimeScale = 1.0f;
		}

		// set camera position
		camera2D.Position = cameraController2D.Position + cameraController2D.TransitionOffset + cameraController2D.ShakeOffset; 

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
