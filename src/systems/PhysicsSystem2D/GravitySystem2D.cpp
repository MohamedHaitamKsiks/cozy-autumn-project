#include "GravitySystem2D.h"

void GravitySystem2D::OnCreate()
{
	// insert code ...
};

void GravitySystem2D::OnUpdate(float delta)
{
	ForEach([delta](Gravity2D& gravity2D, PhysicsBody2D& physicsBody2D)
	{
		if (physicsBody2D.IsStatic) return;

		physicsBody2D.Velocity.y += gravity2D.Gravity * delta;
	});
};

void GravitySystem2D::OnRender2D()
{
	// insert code ...
};

void GravitySystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
