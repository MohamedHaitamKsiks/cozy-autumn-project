#ifndef COMPONENT_ANIMATEDSPRITE2D_H
#define COMPONENT_ANIMATEDSPRITE2D_H

#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

struct AnimatedSprite2D: public TComponent<AnimatedSprite2D>
{
	UniqueString SpriteName;
	ResourceID SpriteID;

	DrawLayer Layer = DrawLayer::Player;

	float Frame = 0.0f;
	float FrameRate = 12.0f;

	vec2 Offset = vec2::ZERO();
	bool Centered = false;
	
	bool FlipH = false;
	bool FlipV = false;

	Color Modulate = Color::WHITE();

	bool Visible = true;

	void OnCreate();
};

#endif // COMPONENT_ANIMATEDSPRITE2D_H