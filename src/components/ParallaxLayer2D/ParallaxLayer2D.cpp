#include "ParallaxLayer2D.h"

EXPORT(ParallaxLayer2D, ScrollScale, BackgroundName, BackgroundFrame)

void ParallaxLayer2D::OnCreate()
{
    BackgroundID = ResourceManager<Sprite>::GetResourceId(BackgroundName);
}
