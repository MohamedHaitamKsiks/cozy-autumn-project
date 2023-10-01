#ifndef COMPONENT_WORLD2D_H
#define COMPONENT_WORLD2D_H

#include <string>
#include <unordered_map>

#include "components/Physics2D/CollisionBox2D.h"
#include "components/Transform2D/Transform2D.h"
#include "components/Particles2D/GrassParticles2D.h"

#include "TileMap2D.h"

#include "systems/SpawningSystem2D/SpawningSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

struct Level2D
{
	vec2 Size = vec2::ZERO();
	vec2 Position = vec2::ZERO();
};

// can be accessed statically 
struct World2D: public TComponent<World2D>
{
	// world instance
	static World2D* Instance;
	
	// world name
	std::string Name;

	// world tileset material
	std::string TilesetName;
	Texture TilesetTexture;
	ResourceID TilesetMaterialID;

	// levels list
	TDynamicArray<Level2D> Levels{2};
	int CurrentLevelID = 0;

	void OnCreate();
	void OnDestroy();

};

#endif // COMPONENT_WORLD2D_H