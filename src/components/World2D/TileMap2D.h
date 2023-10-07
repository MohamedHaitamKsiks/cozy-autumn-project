#ifndef COMPONENT_TILEMAP2D_H
#define COMPONENT_TILEMAP2D_H

#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"


using namespace ASEngine;

struct Tile2D
{
	vec2 Source;
	vec2 Position;
	Quad2D Quad;
	Quad2D ShadowQuad;
};

struct TileMapLayer2D 
{
	TDynamicArray<Tile2D> Tiles{};
	DrawLayer Layer = DrawLayer::Tilemap;
};

struct TileMap2D: public TComponent<TileMap2D>
{
	TDynamicArray<TileMapLayer2D> Layers{};
	float TileSize = 0.0f;
	int LevelID = -1;

	void OnCreate();
};

#endif // COMPONENT_TILEMAP2D_H