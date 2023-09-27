#ifndef SYSTEM_SPRITEANIMATIONSYSTEM2D_H
#define SYSTEM_SPRITEANIMATIONSYSTEM2D_H

#include "components/AnimatedSprite2D/AnimatedSprite2D.h"
#include "components/Transform2D/Transform2D.h"

#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class SpriteAnimationSystem2D: public System<AnimatedSprite2D, Transform2D>
{
public:
	static void Play(AnimatedSprite2D& animatedSprite2D, ResourceID spriteID);

private:
	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_SPRITEANIMATIONSYSTEM2D_H