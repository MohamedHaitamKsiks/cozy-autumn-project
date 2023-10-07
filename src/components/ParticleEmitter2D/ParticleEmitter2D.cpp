#include "ParticleEmitter2D.h"

template <>
Json Serializer<ParticleEmitter2D>::Serialize(const ParticleEmitter2D & value)
{
    return Json({});
}

template <>
void Serializer<ParticleEmitter2D>::Deserialize(const Json &object, ParticleEmitter2D &dest)
{
}
