#ifndef SYSTEM_LEAFRENDERINGSYSTEM_H
#define SYSTEM_LEAFRENDERINGSYSTEM_H

#include "components/Objects/Leaf.h"
#include "components/AnimatedSprite2D/AnimatedSprite2D.h"
#include "components/Transform2D/Transform2D.h"
#include "components/ParticleEmitter2D/ParticleEmitter2D.h"

#include "systems/CameraSystem2D/CameraSystem2D.h"
#include "systems/PlayerSystem/ScoreSystem.h"

#include "ASEngine.h"

using namespace ASEngine;

class LeafRenderingSystem : public System<Leaf, AnimatedSprite2D, ParticleEmitter2D, Transform2D>
{

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_LEAFRENDERINGSYSTEM_H