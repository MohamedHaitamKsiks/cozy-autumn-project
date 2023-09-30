#ifndef SYSTEM_CAMERASYSTEM2D_H
#define SYSTEM_CAMERASYSTEM2D_H

#include "components/World2D/World2D.h"
#include "components/Player/PlayerController.h"
#include "components/Player/CameraController2D.h"
#include "components/Transform2D/Transform2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class CameraSystem2D: public System<PlayerController, CameraController2D, Transform2D>
{
public:
	CameraSystem2D();

private:
	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_CAMERASYSTEM2D_H