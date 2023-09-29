#ifndef SYSTEM_TILEMAPRENDERINGSYSTEM2D_H
#define SYSTEM_TILEMAPRENDERINGSYSTEM2D_H

#include "components/Transform2D/Transform2D.h"
#include "components/World2D/TileMap2D.h"
#include "components/World2D/World2D.h"

#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class TilemapRenderingSystem2D: public System<TileMap2D, Transform2D>
{

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_TILEMAPRENDERINGSYSTEM2D_H