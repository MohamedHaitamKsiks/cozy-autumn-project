#ifndef SYSTEM_RENDERINGSYSTEM2D_H
#define SYSTEM_RENDERINGSYSTEM2D_H

#include "components/EmptyComponent.h"
#include "components/Transform2D/Transform2D.h"

#include "ASEngine.h"

using namespace ASEngine;

// base draw info
struct DrawInfo
{
	Color Modulate = Color::WHITE();
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
	// draw rectangle
	static void DrawRectangle(const RectangleDrawInfo& rectangleInfo, const Transform2D &transform2D);

	// draw sprite
	static void DrawSprite(const SpriteDrawInfo& spriteInfo, const Transform2D &transform2D);

	// draw text
	static void DrawText(const TextDrawInfo& textInfo, const Transform2D& transform2D);

private:
	// default rectangle material
	static ResourceID s_RectangleDefaultMaterial;

	// on system first frame
	void OnCreate();

	// init rectangle material
	void InitRectangleDefaultMaterial();
};

#endif // SYSTEM_RENDERINGSYSTEM2D_H