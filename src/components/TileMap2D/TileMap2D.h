#ifndef COMPONENT_TILEMAP2D_H
#define COMPONENT_TILEMAP2D_H

#include "ASEngine.h"

using namespace ASEngine;


struct Tile2D
{
	uint32_t TileID = 0;
};

struct TileMapLayer2D
{
	TDynamicArray<Tile2D> Tiles{};
};


struct TileMap2D: public TComponent<TileMap2D>
{
	UniqueString TileMapName;
	TDynamicArray<TileMapLayer2D> Layers{};
};

#endif // COMPONENT_TILEMAP2D_H