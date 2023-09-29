#include "RenderingSystem2D.h"

ResourceID RenderingSystem2D::s_RectangleDefaultMaterial = CHUNK_NULL;
RenderingSystem2D* RenderingSystem2D::s_Instance = nullptr;

RenderingSystem2D::RenderingSystem2D()
{
	m_Priority = 10000;
}

void RenderingSystem2D::OnCreate()
{
	s_Instance = this;
	InitRectangleDefaultMaterial();
}

void RenderingSystem2D::InitRectangleDefaultMaterial()
{
	// one pixel white
	uint32_t *whitePixels = new uint32_t[1];
	whitePixels[0] = UINT32_MAX;

	// create image 1x1 white
	Image image{(uint8_t *) whitePixels, 1, 1, ImageFormat::RGBA};

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
	DrawCommand command;
	command.Quad = Quad2D{rectangleInfo.Size, transformMatrix, rectangleInfo.Modulate};
	command.MaterialID = s_RectangleDefaultMaterial;
	QueueDrawCommand(command, rectangleInfo.Layer);
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
	mat3 transformMatrix = mat3::Transform(transform2D.Position, transform2D.Scale * vec2{(spriteInfo.FlipH) ? -1.0f : 1.0f, (spriteInfo.FlipV) ? -1.0f : 1.0f}, transform2D.Rotation) * mat3::Translate(spriteInfo.Offset);
	// center
	if (spriteInfo.Centered)
		transformMatrix = transformMatrix * mat3::Translate(spriteSize * -0.5f);

	// draw quad
	DrawCommand command;
	command.Quad = Quad2D{spriteSize, transformMatrix, spriteInfo.Modulate, (int) spriteInfo.Frame, (int) sprite.GetFrames(), 0, 1};
	command.MaterialID = sprite.GetDefaultMaterial();
	QueueDrawCommand(command, spriteInfo.Layer);
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

			// draw quad
			DrawCommand command;
			command.Quad = Quad2D{
				fontSize,
				characterTransformMatrix,
				textInfo.Modulate,
				fontCharacter.HFrame, FONT_TEXTURE_WIDTH,
				fontCharacter.VFrame, FONT_TEXTURE_HEIGHT};
			command.MaterialID = fontMaterialID;
			QueueDrawCommand(command, textInfo.Layer);

			// move cursor
			cursorPosition.x += (float)fontCharacter.Width + font.GetSeparation();
		}
	}
}

void RenderingSystem2D::IQueueDrawCommand(const DrawCommand &drawCommand, DrawLayer layer)
{
	m_DrawQueue[(int)layer].Push(drawCommand);
}

void RenderingSystem2D::OnRender2D()
{
	for (int layer = 0; layer < (int) DrawLayer::Count; layer++)
	{
		for (const auto &command : m_DrawQueue[(int)layer])
		{
			Renderer2D::DrawQuad(command.Quad, command.MaterialID);
		}
		// clean queue
		m_DrawQueue[(int)layer].Clear();
	}
}