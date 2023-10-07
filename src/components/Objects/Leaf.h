#ifndef COMPONENT_LEAF_H
#define COMPONENT_LEAF_H

#include "components/AudioPlayer2D/AudioPlayer2D.h"

#include "ASEngine.h"

using namespace ASEngine;

struct Leaf: public TComponent<Leaf>
{
	static int Count;

	float Time = 0.0f;
	bool Enable = true;

	UniqueString LeafCollectName;
	ResourceID LeafCollectID;

	UniqueString LeafParticlesName;
	ResourceID LeafParticlesID;

	AudioPlayer2D CollectPlayer;

	void OnCreate();
};

#endif // COMPONENT_LEAF_H