#include "VisibilityNotifier2D.h"

template<>
Json Serializer<VisibilityNotifier2D>::Serialize(const VisibilityNotifier2D& value)
{
    return Json({});
}

template<>
void Serializer<VisibilityNotifier2D>::Deserialize(const Json &object, VisibilityNotifier2D& dest)
{
    dest.Visible = true;
}