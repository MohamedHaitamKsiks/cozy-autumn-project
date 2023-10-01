#include "GrassParticlesSystem.h"

#define MAX_PRESSION_DISTANCE 16.0f
#define GRASS_ANIMATION_SPEED 12.0f
#define GRASS_WIND_SPEED 2.5f

void GrassParticlesSystem::OnCreate()
{
	m_GrassSpriteID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/particles/grass.sprite.json"));
};

void GrassParticlesSystem::OnUpdate(float delta)
{
    m_Time += delta * GRASS_WIND_SPEED;

	ForEach([this, delta](VisibilityNotifier2D &notifier2D, GrassParticles2D &grassParticles2D, Transform2D &transform2D) 
	{

        if (!notifier2D.Visible) return;

        for (auto &blade : grassParticles2D.GrassBlades)
        {
            float rotationTarget = blade.DefaultRotation + sin((blade.Position.x + transform2D.Position.x) * 0.2f + m_Time) * M_PI * 0.05f + 0.3f;
            
            // apply pression on each blade
            if (grassParticles2D.OnPression)
            {
                float pressionDistance = blade.Position.x - grassParticles2D.PressionPosition;
                // rotate to pression
                if (pressionDistance > 0.0f)
                    rotationTarget += Interpolate::Linear(-1.0f, 0.0f, pressionDistance / MAX_PRESSION_DISTANCE) * M_PI * 0.2f;
                else
                    rotationTarget += Interpolate::Linear(1.0f, 0.0f, -pressionDistance / MAX_PRESSION_DISTANCE) * M_PI * 0.2f;
            }
            
            // animate blade
            blade.Rotation = Interpolate::Linear(blade.Rotation, rotationTarget, delta * GRASS_ANIMATION_SPEED);
        }

    
    });
};

void GrassParticlesSystem::OnRender2D()
{
	// grass sprite
	const auto &grassSprite = ResourceManager<Sprite>::Get(m_GrassSpriteID);

	ForEach([&grassSprite](VisibilityNotifier2D& notifier2D, GrassParticles2D& grassParticles2D, Transform2D& transform2D)
	{
		if (!notifier2D.Visible) return;

		for (const auto& blade: grassParticles2D.GrassBlades)
		{
            // draw blade
			Transform2D bladeTransform2D;
			bladeTransform2D.Position = blade.Position + transform2D.Position;
            bladeTransform2D.Rotation = blade.Rotation;
            bladeTransform2D.Scale = vec2::ONE() * blade.DefaultScale;

            SpriteDrawInfo info;
			info.Frame = 0.0f;
			info.Centered = true;
			info.Offset.y = -grassSprite.GetHeight() / 2.0f;
            info.SpriteID = grassSprite.ID;
            info.Frame = blade.Frame % grassSprite.GetFrames();
            info.Layer = (DrawLayer) ((int) DrawLayer::Grass_0 + blade.Frame % grassSprite.GetFrames());

            RenderingSystem2D::DrawSprite(info, bladeTransform2D);

            // draw outline
            bladeTransform2D.Position = blade.Position + transform2D.Position + vec2{-1.0f, 0.0f};
            info.Modulate = Color::BLACK();
            info.Layer = DrawLayer::Shadow;
            RenderingSystem2D::DrawSprite(info, bladeTransform2D);

            bladeTransform2D.Position = blade.Position + transform2D.Position + vec2{1.0f, 0.0f};
            RenderingSystem2D::DrawSprite(info, bladeTransform2D);

            bladeTransform2D.Position = blade.Position + transform2D.Position + vec2{0.0f, -1.0f};
            RenderingSystem2D::DrawSprite(info, bladeTransform2D);

            bladeTransform2D.Position = blade.Position + transform2D.Position + vec2{0.0f, 1.0f};
            RenderingSystem2D::DrawSprite(info, bladeTransform2D);

            // draw shadow
            bladeTransform2D.Position = blade.Position + transform2D.Position + vec2{-1.0f, 1.0f} * 2.0f;
            RenderingSystem2D::DrawSprite(info, bladeTransform2D);
        }
		
	});
};

void GrassParticlesSystem::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
