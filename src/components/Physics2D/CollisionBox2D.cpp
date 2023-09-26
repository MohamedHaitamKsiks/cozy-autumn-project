#include "CollisionBox2D.h"

template<>
Json Serializer<LayerBitMask>::Serialize(const LayerBitMask& value)
{
    return Json({});
}

template<>
void Serializer<LayerBitMask>::Deserialize(const Json& object, LayerBitMask& dest)
{
    assert(object.is_array());

    LayerBitMask layers = 0;
    for (int i = 0; i < object.size(); i++)
    {
        LayerBitMask layer = 1 << (uint32_t) object[i];
        layers = layers | layer;
    }

    dest = layers;
}

EXPORT(CollisionBox2D, Size, Offset, IsCentered, CollisionLayers, DrawDebug)