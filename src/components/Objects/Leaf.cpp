#include "Leaf.h"

EXPORT(Leaf, LeafCollectName, LeafParticlesName, CollectPlayer)

int Leaf::Count = 0;

void Leaf::OnCreate()
{
    LeafCollectID = ResourceManager<Sprite>::GetResourceId(LeafCollectName);
    LeafParticlesID = ResourceManager<Sprite>::GetResourceId(LeafParticlesName);

    Count++;
}
