#include "PearlRenderingSystem.h"

void PearlRenderingSystem::OnCreate()
{
	// insert code ...
};

void PearlRenderingSystem::OnUpdate(float delta)
{
	ForEach([delta] (VisibilityNotifier2D& notifier2D, Pearl& pearl, ParticleEmitter2D& emitter2D, AnimatedSprite2D& animatedSprite2D, Transform2D& transform2D)
	{
		

		const auto& sprite = ResourceManager<Sprite>::Get(animatedSprite2D.SpriteID);
		
		if (pearl.Enabled)
		{
			if (animatedSprite2D.SpriteID == pearl.PearlCreateSpriteID && animatedSprite2D.Frame > sprite.GetFrames() - 1.0f)
			{
				CameraSystem2D::Shake(2.0f, 0.15f);
				animatedSprite2D.SpriteID = pearl.PearlSpriteID;
				animatedSprite2D.FrameRate = 7.0f;
			}
		}
		else
		{
			if (animatedSprite2D.SpriteID == pearl.PearlSpriteID)
			{
				pearl.DestroyPlayer.Play();
				animatedSprite2D.SpriteID = pearl.PearlDestroySpriteID;
				animatedSprite2D.Frame = 0.0f;
				animatedSprite2D.FrameRate = 16.0f;
			}
			else if (animatedSprite2D.SpriteID == pearl.PearlDestroySpriteID && animatedSprite2D.Frame > sprite.GetFrames() - 1.0f)
			{
				CameraSystem2D::Shake(2.0f, 0.15f);
				animatedSprite2D.SpriteID = pearl.PearlDisableSpriteID;

				// add particles
				const int particleNumber = 8;
				for (int i = 0; i < particleNumber; i++)
				{
					Particle2D particle2D{};
					particle2D.Position = transform2D.Position;
					particle2D.Modulate = ParticleParam<Color>(Color::WHITE(), Color{1.0f, 1.0f, 1.0f, 0.0f});
					particle2D.LifeTime = Random::Range(0.8f, 1.3f);
					particle2D.SpriteID = pearl.PearlParticlesSpriteID;
					particle2D.Layer = DrawLayer::FrontParticles;
					particle2D.LinearVelocity = ParticleParam<vec2>(vec2::RIGHT().Rotate(2.0f * M_PI * i / particleNumber) * Random::Range(20.0f, 70.0f), vec2::DOWN() * 50.0f);
					particle2D.Rotation = particle2D.LinearVelocity.Begin.Angle();

					emitter2D.Particles.Push(particle2D);
				}
	 
			}

			// time pearl
			pearl.Timer -= delta;
			if (pearl.Timer < 0.0f)
			{
				pearl.Enabled = true;
				if (notifier2D.Visible)
					pearl.CreatePlayer.Play();
					
				animatedSprite2D.Frame = 0.0f;
				animatedSprite2D.SpriteID = pearl.PearlCreateSpriteID;
			}
		}
	});
};

void PearlRenderingSystem::OnRender2D()
{
	// insert code ...
};

void PearlRenderingSystem::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
