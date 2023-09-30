#ifndef ASENGINE_ECS_REGISTRY_H
#define ASENGINE_ECS_REGISTRY_H

#include "ASEngine.h"
using namespace ASEngine;

#include "components/EmptyComponent.h"
#include "components/Spawner2D/Spawner2D.h"
#include "components/AnimatedSprite2D/AnimatedSprite2D.h"
#include "components/AudioPlayer2D/AudioPlayer2D.h"
#include "components/World2D/World2D.h"
#include "components/World2D/TileMap2D.h"
#include "components/Physics2D/Gravity2D.h"
#include "components/Physics2D/PhysicsBody2D.h"
#include "components/Physics2D/CollisionBox2D.h"
#include "components/Player/CameraController2D.h"
#include "components/Player/PlayerController.h"
#include "components/Transform2D/Transform2D.h"
#include "systems/PhysicsSystem2D/GravitySystem2D.h"
#include "systems/PhysicsSystem2D/PhysicsSystem2D.h"
#include "systems/PhysicsSystem2D/CollisionSystem2D.h"
#include "systems/SpawningSystem2D/SpawningSystem2D.h"
#include "systems/RenderingSystem2D/RenderingSystem2D.h"
#include "systems/SpriteAnimationSystem2D/SpriteAnimationSystem2D.h"
#include "systems/PlayerSystem/PlayerLevelTransitionSystem.h"
#include "systems/PlayerSystem/PlayerAnimationSystem.h"
#include "systems/PlayerSystem/PlayerControllerSystem.h"
#include "systems/TilemapRenderingSystem2D/TilemapRenderingSystem2D.h"
#include "systems/CameraSystem2D/CameraSystem2D.h"

// register ecs
void ECSRegistry();

#endif