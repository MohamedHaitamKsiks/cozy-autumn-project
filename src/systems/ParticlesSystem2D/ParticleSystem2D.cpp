#include "ParticleSystem2D.h"

void ParticleSystem2D::OnCreate()
{
	// insert code ...
};

void ParticleSystem2D::OnUpdate(float delta)
{
	ForEach([delta](ParticleEmitter2D& emitter2D)
	{
		int particleCount = 0;
		for (ChunkID i = 0; i < emitter2D.Particles.GetCapacity(); i++)
		{
			// skip free particles
			if (emitter2D.Particles.IsFree(i)) continue;
			
			auto& particle2D = emitter2D.Particles.Get(i);

			particle2D.Time += delta;

			if (particle2D.Time > particle2D.LifeTime)
			{
				//Debug::Log(i);
				emitter2D.Particles.Free(i);
				continue;
			}

			// proocess frame animation
			auto& sprite = ResourceManager<Sprite>::Get(particle2D.SpriteID);
			particle2D.Frame += particle2D.FrameRate * delta;
			if (particle2D.Frame > sprite.GetFrames() - 1) particle2D.Frame = sprite.GetFrames() - 1;

			// process velocity
			vec2 linearVelocity = Interpolate::Linear(particle2D.LinearVelocity.Begin, particle2D.LinearVelocity.End, particle2D.Time / particle2D.LifeTime) + vec2::RIGHT() * particle2D.WindForce * sin(particle2D.Time);
			particle2D.Position = particle2D.Position + linearVelocity * delta;

			// process angular velocity
			float angularVelocity = Interpolate::Linear(particle2D.AngularVelocity.Begin, particle2D.AngularVelocity.End, particle2D.Time / particle2D.LifeTime) + particle2D.WindForce * sin(particle2D.Time) / 100.0f;
			particle2D.Rotation = particle2D.Rotation + angularVelocity * delta;
			
			particleCount++;
		}
	});
};

void ParticleSystem2D::OnRender2D()
{
	ForEach([](ParticleEmitter2D &emitter2D)
	{
		int particleCount = 0;
		for (ChunkID i = 0; i < emitter2D.Particles.GetCapacity(); i++)
		{
			// skip free particles
			if (emitter2D.Particles.IsFree(i)) continue;

			auto& particle2D = emitter2D.Particles.Get(i);

			// process modualte
			Color modulate = Interpolate::Linear(particle2D.Modulate.Begin, particle2D.Modulate.End, particle2D.Time / particle2D.LifeTime);

			// draw sprite
			SpriteDrawInfo info;
			info.Centered = true;
			info.Frame = particle2D.Frame;
			info.Modulate = modulate;
			info.SpriteID = particle2D.SpriteID;
			info.FlipH = particle2D.FlipH;
			info.FlipV = particle2D.FlipV;
			info.Layer = particle2D.Layer;

			Transform2D transform2D;
			transform2D.Position = particle2D.Position;
			transform2D.Rotation = particle2D.Rotation;
			transform2D.Scale = vec2::ONE() * Interpolate::Linear(particle2D.Scale.Begin, particle2D.Scale.End, particle2D.Time / particle2D.LifeTime);
		
			RenderingSystem2D::DrawSprite(info, transform2D);

			if (particle2D.Outline)
			{
				info.Modulate = Color::BLACK();
				info.Layer = DrawLayer::Shadow;
				Transform2D shadowTransform2D = transform2D;

				shadowTransform2D.Position = transform2D.Position + vec2{1.0f, 0.0f};
				RenderingSystem2D::DrawSprite(info, shadowTransform2D);

				shadowTransform2D.Position = transform2D.Position + vec2{-1.0f, 0.0f};
				RenderingSystem2D::DrawSprite(info, shadowTransform2D);

				shadowTransform2D.Position = transform2D.Position + vec2{0.0f, 1.0f};
				RenderingSystem2D::DrawSprite(info, shadowTransform2D);

				shadowTransform2D.Position = transform2D.Position + vec2{0.0f, -1.0f};
				RenderingSystem2D::DrawSprite(info, shadowTransform2D);
			}

			particleCount++;
		} 
	});
};

void ParticleSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
