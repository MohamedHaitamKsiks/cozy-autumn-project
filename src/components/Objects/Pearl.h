#ifndef COMPONENT_PEARL_H
#define COMPONENT_PEARL_H

#define PEARL_TIMER 1.8f

#include "components/AudioPlayer2D/AudioPlayer2D.h"

#include "ASEngine.h"

using namespace ASEngine;

struct Pearl: public TComponent<Pearl>
{
	bool Enabled = true;
	float Timer = 0.0f;

	AudioPlayer2D CreatePlayer;
	AudioPlayer2D DestroyPlayer;

	UniqueString PearlParticlesSpriteName;
	ResourceID PearlParticlesSpriteID;

	UniqueString PearlSpriteName;
	ResourceID PearlSpriteID;

	UniqueString PearlDisableSpriteName;
	ResourceID PearlDisableSpriteID;

	UniqueString PearlDestroySpriteName;
	ResourceID PearlDestroySpriteID;
	
	UniqueString PearlCreateSpriteName;
	ResourceID PearlCreateSpriteID;

	void OnCreate();
};

#endif // COMPONENT_PEARL_H