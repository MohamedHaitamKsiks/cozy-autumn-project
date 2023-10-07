#include "KillArea.h"

template <>
Json Serializer<KillArea>::Serialize(const KillArea &value)
{
    return Json({});
}

template <>
void Serializer<KillArea>::Deserialize(const Json &object,KillArea &dest)
{
}