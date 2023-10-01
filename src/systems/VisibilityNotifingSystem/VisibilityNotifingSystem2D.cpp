#include "VisibilityNotifingSystem2D.h"

VisibilityNotifingSystem2D::VisibilityNotifingSystem2D()
{
	m_Priority = 100;
}

void VisibilityNotifingSystem2D::OnCreate()
{
	// insert code ...
};

void VisibilityNotifingSystem2D::OnUpdate(float delta)
{
	// get camera
	const auto& camera = Renderer2D::GetCamera2D();

	// create camera transoform / collision box to detect if object is on screen
	Transform2D cameraTransform2D;
	cameraTransform2D.Position = camera.Position;

	CollisionBox2D cameraCollisionBox2D;
	cameraCollisionBox2D.Size = Viewport::GetSize() / camera.Zoom;
	cameraCollisionBox2D.CollisionLayers = 1;

	// set visible for every visibility notifier
	ForEach([&cameraCollisionBox2D, &cameraTransform2D] (VisibilityNotifier2D& visibilityNotifier2D, CollisionBox2D& collisionBox2D, Transform2D& transform2D)
	{
		CollisionInfo info;
		CollisionSystem2D::CollisionBetween(cameraCollisionBox2D, cameraTransform2D, collisionBox2D, transform2D, info);

		visibilityNotifier2D.Visible = info.Collision;

	});

};

void VisibilityNotifingSystem2D::OnRender2D()
{
	// insert code ...
};

void VisibilityNotifingSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
