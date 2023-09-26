#include "RenderingSystem2D.h"

ResourceID RenderingSystem2D::s_RectangleDefaultMaterial = CHUNK_NULL;

void RenderingSystem2D::OnCreate()
{
	InitRectangleDefaultMaterial();
}

void RenderingSystem2D::InitRectangleDefaultMaterial()
{
	// one pixel white
	uint32_t *whitePixels = new uint32_t[1];
	whitePixels[0] = UINT32_MAX;

	// create image 1x1 white
	Image image{(uint8_t *)whitePixels, 1, 1, ImageFormat::RGBA};

	// create texture 1x1 white
	Texture texture = Texture::LoadFromImage(image);

	// get default shader
	ResourceID defaultShaderID = ResourceManager<Shader>::GetResourceId(UniqueString("shaders/default.glsl"));

	// create material
	ResourceID defaultMaterialID = ResourceManager<Material>::Add();

	auto &defaultMaterial = ResourceManager<Material>::Get(defaultMaterialID);
	defaultMaterial.Create(defaultShaderID);
	defaultMaterial.SetShaderParam(UniqueString("u_Texture"), texture);

	// save material ID
	s_RectangleDefaultMaterial = defaultMaterialID;
}

void RenderingSystem2D::DrawRectangle(const RectangleDrawInfo &rectangleInfo, const Transform2D &transform2D)
{
	// get transform matrix
	mat3 transformMatrix = mat3::Transform(transform2D.Position, transform2D.Scale, transform2D.Rotation);

	// draw quad
	Quad2D quad{rectangleInfo.Size, transformMatrix, rectangleInfo.Modulate};
	Renderer2D::DrawQuad(quad, s_RectangleDefaultMaterial);
}

void RenderingSystem2D::DrawSprite(const SpriteDrawInfo &spriteInfo, const Transform2D& transform2D)
{
	// get sprite data
	const auto& sprite = ResourceManager<Sprite>::Get(spriteInfo.SpriteID);
	vec2 spriteSize
	{
		(float) sprite.GetWidth(),
		(float) sprite.GetHeight()
	};

	// get transform matrix
	mat3 transformMatrix = mat3::Transform(transform2D.Position + spriteInfo.Offset, transform2D.Scale, transform2D.Rotation);
	// center
	if (spriteInfo.Centered)
		transformMatrix = transformMatrix * mat3::Translate(spriteSize * -0.5f);

	// draw quad
	Quad2D quad{spriteSize, transformMatrix, spriteInfo.Modulate, (int) spriteInfo.Frame, (int) sprite.GetFrames(), 0, 1};
	Renderer2D::DrawQuad(quad, sprite.GetDefaultMaterial());
}

void RenderingSystem2D::DrawText(const TextDrawInfo &textInfo, const Transform2D &transform2D)
{
	// get font
	const auto &font = ResourceManager<Font>::Get(textInfo.FontID);
	vec2 fontSize
	{
		(float)font.GetSize(),
		(float)font.GetSize()
	};
	ResourceID fontMaterialID = font.GetDefaultMaterialID();

	// transform matrix
	mat3 transformMatrix = mat3::Transform(transform2D.Position, transform2D.Scale, transform2D.Rotation);

	// pointer relative position
	vec2 cursorPosition = vec2::ZERO();

	// draw characters
	for (int i = 0; i < textInfo.Text.length(); i++)
	{
		char c = textInfo.Text[i];

		switch (c)
		{
		// draw space
		case ' ':
			cursorPosition.x += font.GetSpaceSize();
			break;
		// go back to line
		case '\n':
			cursorPosition.x = 0.0f;
			cursorPosition.y += (float)font.GetLineSeparation();
			break;
		// draw normal char
		default:
			const auto &fontCharacter = font.GetFontCharacterOf(c);

			// calculate character position
			vec2 characterPosition
			{
				0.0f,
				(float)fontCharacter.BearingY
			};
			mat3 characterTransformMatrix = transformMatrix * mat3::Translate(cursorPosition + characterPosition);

			// draw quyad
			Quad2D quad{
				fontSize,
				characterTransformMatrix,
				textInfo.Modulate,
				fontCharacter.HFrame, FONT_TEXTURE_WIDTH,
				fontCharacter.VFrame, FONT_TEXTURE_HEIGHT};
			Renderer2D::DrawQuad(quad, fontMaterialID);

			// move cursor
			cursorPosition.x += (float)fontCharacter.Width + font.GetSeparation();
		}
	}
}