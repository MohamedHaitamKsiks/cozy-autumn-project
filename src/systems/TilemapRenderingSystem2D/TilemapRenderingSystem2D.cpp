#include "TilemapRenderingSystem2D.h"

void TilemapRenderingSystem2D::OnCreate()
{
	// insert code ...
};

void TilemapRenderingSystem2D::OnUpdate(float delta){
	// insert code ...
};

void TilemapRenderingSystem2D::OnRender2D()
{
	if (!World2D::Instance)
		return;

	int tilesetWidth = World2D::Instance->TilesetTexture.GetWidth();
	int tilesetHeight = World2D::Instance->TilesetTexture.GetHeight();

	ForEach([tilesetWidth, tilesetHeight](TileMap2D &tilemap2D, Transform2D &transform2D)
	{
		for (auto& tilemapLayer2D: tilemap2D.Layers)
		{
			// draw shadow
			for (auto &tile2D : tilemapLayer2D.Tiles)
			{
				// check if tile is on screen
				if (tile2D.Position.x + tilemap2D.TileSize < Renderer2D::GetCamera2D().Position.x ||
					tile2D.Position.y + tilemap2D.TileSize < Renderer2D::GetCamera2D().Position.y ||
					tile2D.Position.x > Renderer2D::GetCamera2D().Position.x + Viewport::GetSize().x / Renderer2D::GetCamera2D().Zoom ||
					tile2D.Position.y > Renderer2D::GetCamera2D().Position.y + Viewport::GetSize().y / Renderer2D::GetCamera2D().Zoom)
				{
					continue;
				}

				// draw shadow
				// draw tile
				DrawCommand tileShadowDrawCommand;
				tileShadowDrawCommand.Quad = tile2D.ShadowQuad;
				tileShadowDrawCommand.MaterialID = World2D::Instance->TilesetMaterialID;

				RenderingSystem2D::QueueDrawCommand(tileShadowDrawCommand, DrawLayer::TilemapShadow);
			}

			// normal draw
			for (auto& tile2D: tilemapLayer2D.Tiles)
			{
				// check if tile is on screen
				if (tile2D.Position.x + tilemap2D.TileSize < Renderer2D::GetCamera2D().Position.x ||
					tile2D.Position.y + tilemap2D.TileSize < Renderer2D::GetCamera2D().Position.y ||
					tile2D.Position.x > Renderer2D::GetCamera2D().Position.x + Viewport::GetSize().x / Renderer2D::GetCamera2D().Zoom ||
					tile2D.Position.y > Renderer2D::GetCamera2D().Position.y + Viewport::GetSize().y / Renderer2D::GetCamera2D().Zoom)
				{
					continue;
				}

				// draw tile
				DrawCommand tileDrawCommand;
				tileDrawCommand.Quad = tile2D.Quad;
				tileDrawCommand.MaterialID = World2D::Instance->TilesetMaterialID;

				RenderingSystem2D::QueueDrawCommand(tileDrawCommand, DrawLayer::Tilemap);
			}
		} });
};

void TilemapRenderingSystem2D::OnInputEvent(const InputEvent &event){
	// insert code ...
};
