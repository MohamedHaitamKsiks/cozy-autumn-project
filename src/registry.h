#ifndef ASENGINE_ECS_REGISTRY_H
#define ASENGINE_ECS_REGISTRY_H

#include "ASEngine.h"
using namespace ASEngine;

#include "components/EmptyComponent.h"
#include "components/AudioPlayer2D/AudioPlayer2D.h"
#include "components/TileMap2D/TileMap2D.h"
#include "components/Physics2D/PhysicsBody2D.h"
#include "components/Physics2D/CollisionBox2D.h"
#include "components/Transform2D/Transform2D.h"
#include "systems/PhysicsSystem2D/PhysicsSystem2D.h"
#include "systems/PhysicsSystem2D/CollisionSystem2D.h"
#include "systems/RenderingSystem2D/RenderingSystem2D.h"

// register ecs
void ECSRegistry();

#endif