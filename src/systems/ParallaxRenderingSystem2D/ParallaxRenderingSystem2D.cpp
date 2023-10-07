#include "ParallaxRenderingSystem2D.h"

ParallaxRenderingSystem2D::ParallaxRenderingSystem2D()
{
	m_Priority = 299;
}

void ParallaxRenderingSystem2D::OnCreate()
{

};

void ParallaxRenderingSystem2D::OnUpdate(float delta)
{
	// process time
	m_Time += delta;

	// get camera
	const auto& camera = Renderer2D::GetCamera2D();

	ForEach([this, &camera] (ParallaxLayer2D& parallaxLayer2D, Transform2D& transform2D)
	{
		const auto& sprite = ResourceManager<Sprite>::Get(parallaxLayer2D.BackgroundID);
		const vec2 ScreenSize = Viewport::GetSize() / camera.Zoom;

		// offset
		float cloudOffset = (-m_Time * 60.0f) * pow(parallaxLayer2D.ScrollScale, 2.0f);

		// move background
		transform2D.Position.x = cloudOffset + camera.Position.x * (1.0f - parallaxLayer2D.ScrollScale);
		transform2D.Position.y = camera.Position.y * (1.0f - parallaxLayer2D.ScrollScale);

		// keep tilemap in bound
		float precision = 0.001f;
		while (transform2D.Position.x > camera.Position.x + precision)
			transform2D.Position.x -= (float) sprite.GetWidth();
		while (transform2D.Position.x < camera.Position.x - sprite.GetWidth() - precision)
			transform2D.Position.x += (float) sprite.GetWidth();

		while (transform2D.Position.y > camera.Position.y + precision)
			transform2D.Position.y -= (float) sprite.GetHeight();
		while (transform2D.Position.y < camera.Position.y - sprite.GetHeight() - precision)
			transform2D.Position.y += (float) sprite.GetHeight();

	});

};

void ParallaxRenderingSystem2D::OnRender2D()
{
	ForEach([] (ParallaxLayer2D& parallaxLayer2D, Transform2D& transform2D)
	{
		const auto& sprite = ResourceManager<Sprite>::Get(parallaxLayer2D.BackgroundID);

		SpriteDrawInfo info;
		info.Frame = parallaxLayer2D.BackgroundFrame;
		info.Layer = DrawLayer::Background;
		info.SpriteID = parallaxLayer2D.BackgroundID;
		info.Centered = false;

		// draw mirrors
		Transform2D backgroundTransform2D = transform2D;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				backgroundTransform2D.Position.x = transform2D.Position.x + (float) (sprite.GetWidth() * i);
				backgroundTransform2D.Position.y = transform2D.Position.y + (float) (sprite.GetHeight() * j);
				RenderingSystem2D::DrawSprite(info, backgroundTransform2D);
			}
		}

	});
};

void ParallaxRenderingSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
