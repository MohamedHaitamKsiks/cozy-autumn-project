#include "TilemapRenderingSystem2D.h"

void TilemapRenderingSystem2D::OnCreate()
{
	// insert code ...
};

void TilemapRenderingSystem2D::OnUpdate(float delta)
{
	// insert code ...
};

void TilemapRenderingSystem2D::OnRender2D()
{
	if (!World2D::Instance) return;

	int tilesetWidth = World2D::Instance->TilesetTexture.GetWidth();
	int tilesetHeight = World2D::Instance->TilesetTexture.GetHeight();

	ForEach([tilesetWidth, tilesetHeight](TileMap2D& tilemap2D, Transform2D& transform2D)
	{
		for (auto& tilemapLayer2D: tilemap2D.Layers)
		{
			for (auto& tile2D: tilemapLayer2D.Tiles)
			{

				mat3 tileTransformMatrix = mat3::Translate(transform2D.Position + tile2D.Position);
				vec2 tileSize2D = vec2::ONE() * tilemap2D.TileSize;

				DrawCommand tileDrawCommand;
				tileDrawCommand.Quad = Quad2D(tileSize2D, tileTransformMatrix, Color::WHITE(), tile2D.Source.x / tilemap2D.TileSize, tilesetWidth / tilemap2D.TileSize, tile2D.Source.y / tilemap2D.TileSize, tilesetHeight / tilemap2D.TileSize);
				tileDrawCommand.MaterialID = World2D::Instance->TilesetMaterialID;

				RenderingSystem2D::QueueDrawCommand(tileDrawCommand, DrawLayer::Tilemap);
			}
		}
	});
};

void TilemapRenderingSystem2D::OnInputEvent(const InputEvent& event)
{
	// insert code ...
};
