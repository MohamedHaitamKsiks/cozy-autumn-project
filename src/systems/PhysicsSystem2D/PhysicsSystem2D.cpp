#include "PhysicsSystem2D.h"

PhysicsSystem2D::PhysicsSystem2D()
{
	m_Priority = 98;
}

void PhysicsSystem2D::MoveAndCollide(PhysicsBody2D &physicsBody2D, CollisionBox2D &collisionBox2D, Transform2D &transform2D, const vec2 &axis, float delta)
{
	// get velocity
	vec2 velocity = physicsBody2D.Velocity * axis;

	// skip if velocity is zero
	if (velocity.x == 0.0f && velocity.y == 0.0f) return;

	// move physics object 
	transform2D.Position = transform2D.Position + velocity * delta;

	// check for collision with other bodies
	ForEach([delta, &axis, &velocity, &physicsBody2D, &collisionBox2D, &transform2D](PhysicsBody2D& o_PhysicsBody2D, CollisionBox2D& o_CollisionBox2D, Transform2D& o_Transform2D)
	{
		// skip if same object
		if (&physicsBody2D == &o_PhysicsBody2D) return;

		// get collision info
		CollisionInfo collisionInfo;
		CollisionSystem2D::CollisionBetween(collisionBox2D, transform2D, o_CollisionBox2D, o_Transform2D, collisionInfo);

		// skip if no collision
		if (!collisionInfo.Collision) return;

		// move physics body back
		vec2 direction = velocity.Normalized();
		transform2D.Position = transform2D.Position - (collisionInfo.Intersection) * direction;

		// set collision flags
		if (axis.y > 0.0f)
		{
			physicsBody2D.OnGround = direction.y > 0.0f;
			physicsBody2D.OnCeilling = direction.y < 0.0f;
		}
		else
		{
			physicsBody2D.OnWall = direction.x != 0.0f;
		}

	});
}

void PhysicsSystem2D::OnCreate()
{
    // insert code ...
};

void PhysicsSystem2D::OnUpdate(float delta)
{
	if (delta < 0.0000001f) return;

	ForEach([this, delta](PhysicsBody2D& physicsBody2D, CollisionBox2D& collisionBox2D, Transform2D& transform2D)
	{
		if (physicsBody2D.IsStatic) return;

		// reset flags
		physicsBody2D.OnGround = false;
		physicsBody2D.OnCeilling = false;
		physicsBody2D.OnWall = false;

		// move for each axis
		this->MoveAndCollide(physicsBody2D, collisionBox2D, transform2D, vec2::RIGHT(), delta);
		this->MoveAndCollide(physicsBody2D, collisionBox2D, transform2D, vec2::DOWN(), delta);
	});
};

void PhysicsSystem2D::OnRender2D()
{

};

void PhysicsSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};


