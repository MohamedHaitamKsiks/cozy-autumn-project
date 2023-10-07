#include "LeafRenderingSystem.h"

void LeafRenderingSystem::OnCreate()
{
};

void LeafRenderingSystem::OnUpdate(float delta)
{
	ForEach([delta](Leaf& leaf, AnimatedSprite2D& animatedSprite2D, ParticleEmitter2D& emitter2D, Transform2D& transform2D)
	{
		if (leaf.Enable)
		{
			leaf.Time += delta;
			transform2D.Rotation = cos(leaf.Time) * M_PI / 8.0f;
		}
		else
		{
			transform2D.Scale = Interpolate::Linear(transform2D.Scale, vec2::ONE() * 0.7f, delta * 25.0f);
			if (abs(transform2D.Scale.x - 0.7f) < 0.001f && animatedSprite2D.Visible)
			{
				animatedSprite2D.Visible = false;

				// add leaf to counter
				ScoreSystem::IncrementLeafCounter();

				// feedback
				CameraSystem2D::Shake(2.0f, 0.2f);
				leaf.CollectPlayer.Play();

				// emit particles
				const int particleNumber = 32;
				for (int i = 0; i < particleNumber; i++)
				{
					Particle2D particle2D;
					particle2D.LifeTime = 0.8f;
					particle2D.Rotation = Random::Float() * 2.0f * M_PI;
					particle2D.Position = transform2D.Position + vec2{Random::Range(-1.0f, 1.0f), Random::Range(-1.0f, 1.0f)} * 3.0f;
					particle2D.SpriteID = leaf.LeafParticlesID;
					particle2D.LinearVelocity = ParticleParam<vec2>(vec2::RIGHT().Rotate(Random::Float() * 2.0f * M_PI) * Random::Range(80.0f, 150.0f), vec2::DOWN() * 200.0f);
					particle2D.AngularVelocity = particle2D.LinearVelocity.Begin.Angle();
					particle2D.Layer = DrawLayer::FrontParticles;
					particle2D.Outline = true;
					particle2D.FrameRate = 15.0f;

					emitter2D.Particles.Push(particle2D);
				}
			}
		}
	});
};

void LeafRenderingSystem::OnRender2D()
{
	ForEach([this](Leaf& leaf, AnimatedSprite2D& animatedSprite2D, ParticleEmitter2D& emitter2D, Transform2D& transform2D)
	{
		if (!leaf.Enable)
			animatedSprite2D.SpriteID = leaf.LeafCollectID;
	});
};

void LeafRenderingSystem::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
