#include "SpringRenderingSystem.h"

void SpringRenderingSystem::OnCreate()
{
	// insert code ...
};

void SpringRenderingSystem::OnUpdate(float delta)
{
	ForEach([](Spring& spring, AnimatedSprite2D& animatedSprite2D)
	{
		if (spring.Collision)
		{
			animatedSprite2D.FrameRate = 12.0f;
			animatedSprite2D.Frame = 0.0f;
			spring.Collision = false;
		}

		const auto& sprite = ResourceManager<Sprite>::Get(animatedSprite2D.SpriteID);
		if (animatedSprite2D.Frame > sprite.GetFrames() - 1.0f)
		{
			animatedSprite2D.Frame = 0.0f;
			animatedSprite2D.FrameRate = 0.0f;
		}
	});
};

void SpringRenderingSystem::OnRender2D()
{
	// insert code ...
};

void SpringRenderingSystem::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
