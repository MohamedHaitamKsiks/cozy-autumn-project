#include "AnimatedSprite2D.h"

EXPORT(AnimatedSprite2D, Frame, FrameRate, SpriteName, Offset, Centered)

void AnimatedSprite2D::OnCreate()
{
    SpriteID = ResourceManager<Sprite>::GetResourceId(SpriteName);
}