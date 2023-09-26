#include "CollisionSystem2D.h"


void CollisionSystem2D::CalculateRectanglePosition(const CollisionBox2D &collisionBox2D, const Transform2D &src, vec2 &dest)
{
	vec2 offset = collisionBox2D.Offset;
	if (collisionBox2D.IsCentered)
		offset = offset + collisionBox2D.Size * -0.5f;

	dest = src.Position + (offset * src.Scale);
}

void CollisionSystem2D::CollisionBetween(const CollisionBox2D &a_CollisionBox2D, const Transform2D &a_Transform2D, const CollisionBox2D &b_CollisionBox2D, const Transform2D &b_Transform2D, CollisionInfo& collisionInfo)
{
	// check mask intersection
	if ((a_CollisionBox2D.CollisionLayers & b_CollisionBox2D.CollisionLayers) == 0)
	{
		collisionInfo.Collision = false;
		return;
	}
	
	// get rectangle positions
	vec2 a_Position, b_Position;
	CalculateRectanglePosition(a_CollisionBox2D, a_Transform2D, a_Position);
	CalculateRectanglePosition(b_CollisionBox2D, b_Transform2D, b_Position);

	// get rectangle sizes
	vec2 a_Size = a_CollisionBox2D.Size * a_Transform2D.Scale;
	vec2 b_Size = b_CollisionBox2D.Size * b_Transform2D.Scale;

	// offset position to center
	a_Position = a_Position + a_Size * 0.5f;
	b_Position = b_Position + b_Size * 0.5f;

	// get intersection
	vec2 distanceBetweenRectangles
	{
		abs(a_Position.x - b_Position.x),
		abs(a_Position.y - b_Position.y)
	};
	vec2 sumRectanglesSizes = (a_Size + b_Size) * 0.5f;
	collisionInfo.Intersection = sumRectanglesSizes - distanceBetweenRectangles;

	// check collision
	collisionInfo.Collision = collisionInfo.Intersection.x > 0.0f && collisionInfo.Intersection.y > 0.0f;
}

void CollisionSystem2D::OnCreate()
{
    // insert code ...
};

void CollisionSystem2D::OnUpdate(float delta)
{
	// insert code ...
};

void CollisionSystem2D::OnRender2D()
{
	ForEach([this](CollisionBox2D &collisionBox2D, Transform2D &transform2D)
	{
		if (!collisionBox2D.DrawDebug) return;

		RectangleDrawInfo rectangleInfo;
		rectangleInfo.Size = collisionBox2D.Size;
		rectangleInfo.Modulate = Color{0.0f, 1.0f, 0.0f, 0.3f};
		rectangleInfo.Layer = DrawLayer::Debug;

		Transform2D rectangleTransform2D = transform2D;
		CalculateRectanglePosition(collisionBox2D, transform2D, rectangleTransform2D.Position);

		RenderingSystem2D::DrawRectangle(rectangleInfo, rectangleTransform2D); 
	});
};

void CollisionSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
