#include "PhysicsSystem2D.h"

void PhysicsSystem2D::MoveAndCollide(PhysicsBody2D &physicsBody2D, CollisionBox2D &collisionBox2D, Transform2D &transform2D, const vec2 &axis, float delta)
{
	// get velocity
	vec2 velocity = physicsBody2D.Velocity * axis;

	// move physics object 
	transform2D.Position = transform2D.Position + velocity * delta;

	// check for collision with other bodies
	ForEach([delta, &velocity, &physicsBody2D, &collisionBox2D, &transform2D](PhysicsBody2D& o_PhysicsBody2D, CollisionBox2D& o_CollisionBox2D, Transform2D& o_Transform2D)
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

		physicsBody2D.Velocity = physicsBody2D.Velocity - velocity;
	});
}

void PhysicsSystem2D::OnCreate()
{
    // insert code ...
};

void PhysicsSystem2D::OnUpdate(float delta)
{
	ForEach([this, delta](PhysicsBody2D& physicsBody2D, CollisionBox2D& collisionBox2D, Transform2D& transform2D)
	{
		if (physicsBody2D.IsStatic) return;

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


