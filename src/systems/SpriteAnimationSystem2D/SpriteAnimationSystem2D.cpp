#include "SpriteAnimationSystem2D.h"

void SpriteAnimationSystem2D::Play(AnimatedSprite2D &animatedSprite2D, ResourceID spriteID)
{
	if (animatedSprite2D.SpriteID == spriteID) return;

	animatedSprite2D.Frame = 0.0f;
	animatedSprite2D.SpriteID = spriteID;
}

void SpriteAnimationSystem2D::OnCreate()
{
    // insert code ...
};

void SpriteAnimationSystem2D::OnUpdate(float delta)
{
	ForEach([delta](AnimatedSprite2D& animatedSprite2D, Transform2D& transform2D)
	{
		animatedSprite2D.Frame += animatedSprite2D.FrameRate * delta;
	});
};

void SpriteAnimationSystem2D::OnRender2D()
{
	ForEach([](AnimatedSprite2D& animatedSprite2D, Transform2D& transform2D)
	{
		SpriteDrawInfo spriteInfo;
		spriteInfo.Centered = animatedSprite2D.Centered;
		spriteInfo.Frame = animatedSprite2D.Frame;
		spriteInfo.Modulate = Color::BLACK();
		spriteInfo.SpriteID = animatedSprite2D.SpriteID;
		spriteInfo.Layer = animatedSprite2D.Layer;
		spriteInfo.Offset = animatedSprite2D.Offset;
		spriteInfo.FlipH = animatedSprite2D.FlipH;
		spriteInfo.FlipV = animatedSprite2D.FlipV;

		// draw shadow
		Transform2D shadowTransform2D = transform2D;
		shadowTransform2D.Position = shadowTransform2D.Position + vec2{-1.0f, 1.0f} * 2.0f;
		RenderingSystem2D::DrawSprite(spriteInfo, shadowTransform2D);

		// draw sprite
		spriteInfo.Modulate = animatedSprite2D.Modulate;
		RenderingSystem2D::DrawSprite(spriteInfo, transform2D);
	});
};

void SpriteAnimationSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
