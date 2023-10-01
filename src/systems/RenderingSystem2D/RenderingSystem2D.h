#ifndef SYSTEM_RENDERINGSYSTEM2D_H
#define SYSTEM_RENDERINGSYSTEM2D_H

#include "components/EmptyComponent.h"
#include "components/Transform2D/Transform2D.h"

#include "ASEngine.h"

using namespace ASEngine;

// layers
enum class DrawLayer
{
	Background,

	Shadow,
	TilemapShadow,
	
	Player,

	// grass layers
	Grass_0,
	Grass_1,
	Grass_2,
	Grass_3,
	Grass_4,

	Tilemap,
	Debug,
	UI,
	// draw layers number
	Count
};

// draw command (Quad & material) will be queued to be drawn 
struct DrawCommand
{
	Quad2D Quad;
	ResourceID MaterialID;
};

// base draw info
struct DrawInfo
{
	Color Modulate = Color::WHITE();
	DrawLayer Layer = DrawLayer::Background;
};

// rectangle draw info
struct RectangleDrawInfo : public DrawInfo
{
	vec2 Size = vec2::ZERO();
};

// sprite draw info
struct SpriteDrawInfo : public DrawInfo
{
	ResourceID SpriteID = CHUNK_NULL;
	float Frame = 0;
	vec2 Offset = vec2::ZERO();
	bool Centered = true;
	bool FlipH = false;
	bool FlipV = false;
};

// text draw info
struct TextDrawInfo : public DrawInfo
{
	std::string Text;
	ResourceID FontID = CHUNK_NULL;
};


class RenderingSystem2D: public System<EmptyComponent>
{
public:
	RenderingSystem2D();

	// draw rectangle
	static void DrawRectangle(const RectangleDrawInfo& rectangleInfo, const Transform2D &transform2D);

	// draw sprite
	static void DrawSprite(const SpriteDrawInfo& spriteInfo, const Transform2D &transform2D);

	// draw text
	static void DrawText(const TextDrawInfo& textInfo, const Transform2D& transform2D);

	// queue draw command
	static inline void QueueDrawCommand(const DrawCommand& drawCommnad, DrawLayer layer)
	{
		s_Instance->IQueueDrawCommand(drawCommnad, layer);
	}

private:
	// system instance
	static RenderingSystem2D* s_Instance;

	// default rectangle material
	static ResourceID s_RectangleDefaultMaterial;

	// draw queue
	TDynamicArray<DrawCommand> m_DrawQueue[(int) DrawLayer::Count];

	// on system first frame
	void OnCreate();

	// init rectangle material
	void InitRectangleDefaultMaterial();

	// queue draw
	void IQueueDrawCommand(const DrawCommand& drawCommand, DrawLayer layer);

	// draw
	void OnRender2D();
};

#endif // SYSTEM_RENDERINGSYSTEM2D_H