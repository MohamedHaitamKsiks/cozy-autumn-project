#include "WorldLeafParticlesSystem.h"

void WorldLeafParticlesSystem::OnCreate()
{
	m_LeafParticlesID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/particles/leaf_particles.sprite.json"));
};

void WorldLeafParticlesSystem::OnUpdate(float delta)
{
	ForEach([delta, this](ParticleEmitter2D &emitter2D, World2D &world2D)
	{
		m_Time += delta;

		if(m_Time > 0.5f)
		{
			const auto& camera2D = Renderer2D::GetCamera2D();

			Particle2D particle2D;
			particle2D.LifeTime = 50.0f;
			particle2D.Rotation = Random::Float() * 2.0f * M_PI;
			particle2D.Position = camera2D.Position + vec2::RIGHT() * (Viewport::GetSize().x / camera2D.Zoom + 32.0f) + vec2::DOWN() * Random::Range(-180.0f, 180.0f);
			particle2D.SpriteID = m_LeafParticlesID;
			particle2D.LinearVelocity = vec2::LEFT() * Random::Range(50.0f, 50.0f) + vec2::DOWN() * 20.0f;
			particle2D.AngularVelocity = 0.01f;

			int layerType = Random::Int() % 2;
			if (layerType)
			{
				particle2D.Layer = DrawLayer::FrontParticles;
			}
			else
			{
				particle2D.Layer = DrawLayer::BackParticles;
				particle2D.Modulate = Color{1.0f, 1.0f, 1.0f, 0.5f};
			}

			particle2D.Outline = true;
			particle2D.Frame = Random::Range(1.0f, 3.0f);
			particle2D.FrameRate = 0.0f;
			particle2D.WindForce = 30.0f;

			emitter2D.Particles.Push(particle2D); 

			m_Time = 0.0f;
		}
			
	});
};

void WorldLeafParticlesSystem::OnRender2D()
{
	// insert code ...
};

void WorldLeafParticlesSystem::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
