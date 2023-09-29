#ifndef COMPONENT_TILEMAP2D_H
#define COMPONENT_TILEMAP2D_H

#include "ASEngine.h"


using namespace ASEngine;

struct Tile2D
{
	vec2 Source;
	vec2 Position;
};

struct TileMapLayer2D 
{
	TDynamicArray<Tile2D> Tiles{};
};

struct TileMap2D: public TComponent<TileMap2D>
{
	TDynamicArray<TileMapLayer2D> Layers{};
	float TileSize = 0.0f;
	int LevelID = -1;

	void OnCreate();
};

#endif // COMPONENT_TILEMAP2D_H