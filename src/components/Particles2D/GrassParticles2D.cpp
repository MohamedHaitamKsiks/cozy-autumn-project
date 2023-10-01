#include "GrassParticles2D.h"

#define DISTANCE_BETWEEN_BLADES 3
#define BLADE_OFFSET 2.0f

template <>
Json Serializer<GrassParticles2D>::Serialize(const GrassParticles2D &value)
{
    return Json({});
}

template <>
void Serializer<GrassParticles2D>::Deserialize(const Json &object, GrassParticles2D &dest)
{
    
}

void GrassParticles2D::OnCreate()
{
    int bladeCount = (int) Width / DISTANCE_BETWEEN_BLADES;
    
    for (int i = 0; i < bladeCount; i++)
    {
        GrassBlade blade;
        blade.Position = vec2
        {
            (float) i * DISTANCE_BETWEEN_BLADES + Random::Range(-1.0f, 1.0f) * DISTANCE_BETWEEN_BLADES * 0.25f,
            3.0f
        };
        blade.Position.x = (blade.Position.x > 4.0f) ? blade.Position.x : 4.0f;
        blade.Position.x = (blade.Position.x < Width) ? blade.Position.x : Width;

        blade.Frame = Random::Int();
        blade.DefaultScale = 0.5f * (Interpolate::Linear(0.5f, 1.0f, blade.Position.x / 6.0f) + Interpolate::Linear(0.5f, 1.0f, (Width - blade.Position.x) / 6.0f));
        blade.DefaultRotation = M_PI * 0.2 * 0.5f * (Interpolate::Linear(1.0f, 0.0f, blade.Position.x / 6.0f) + Interpolate::Linear(-1.0f, 0.0f, (Width - blade.Position.x) / 6.0f));

        GrassBlades.Push(blade);
    }

}
