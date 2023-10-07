#ifndef COMPONENT_PARTICLEEMITTER2D_H
#define COMPONENT_PARTICLEEMITTER2D_H

#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

template<typename T>
struct ParticleParam
{
	T Begin;
	T End;

	ParticleParam(){};

	ParticleParam(const T& begin, const T& end)
	{
		Begin = begin;
		End = end;
	}

	ParticleParam(const T& value)
	{
		Begin = value;
		End = value;
	}
};

struct Particle2D
{
	float Time = 0.0f;
	float LifeTime = 1.0f;
	
	vec2 Position = vec2::ZERO();
	ParticleParam<float> Scale{1.0f};
	float Rotation = 0.0f;

	float Frame = 0.0f;
	float FrameRate = 0.0f;

	ParticleParam<vec2> LinearVelocity{vec2::ZERO()};
	ParticleParam<float> AngularVelocity{0.0f};

	ParticleParam<Color> Modulate{Color::WHITE()};

	ResourceID SpriteID;

	DrawLayer Layer = DrawLayer::Particles;
	bool Outline = false;

	bool FlipV = false;
	bool FlipH = false;

	float WindForce = 0.0f;

	~Particle2D() = default;

};

// one instance per world
struct ParticleEmitter2D: public TComponent<ParticleEmitter2D>
{
	TPoolAllocator<Particle2D> Particles{256};
};

#endif // COMPONENT_PARTICLEEMITTER2D_H