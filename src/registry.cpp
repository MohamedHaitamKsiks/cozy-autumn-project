#include "registry.h"

void ECSRegistry()
{
	ComponentManager::RegisterComponent<EmptyComponent>(UniqueString("EmptyComponent"));
	ComponentManager::RegisterComponent<Spawner2D>(UniqueString("Spawner2D"));
	ComponentManager::RegisterComponent<AnimatedSprite2D>(UniqueString("AnimatedSprite2D"));
	ComponentManager::RegisterComponent<AudioPlayer2D>(UniqueString("AudioPlayer2D"));
	ComponentManager::RegisterComponent<World2D>(UniqueString("World2D"));
	ComponentManager::RegisterComponent<TileMap2D>(UniqueString("TileMap2D"));
	ComponentManager::RegisterComponent<Gravity2D>(UniqueString("Gravity2D"));
	ComponentManager::RegisterComponent<PhysicsBody2D>(UniqueString("PhysicsBody2D"));
	ComponentManager::RegisterComponent<CollisionBox2D>(UniqueString("CollisionBox2D"));
	ComponentManager::RegisterComponent<PlayerController>(UniqueString("PlayerController"));
	ComponentManager::RegisterComponent<Transform2D>(UniqueString("Transform2D"));
	SystemManager::RegisterSystem<GravitySystem2D>();
	SystemManager::RegisterSystem<PhysicsSystem2D>();
	SystemManager::RegisterSystem<CollisionSystem2D>();
	SystemManager::RegisterSystem<SpawningSystem2D>();
	SystemManager::RegisterSystem<RenderingSystem2D>();
	SystemManager::RegisterSystem<SpriteAnimationSystem2D>();
	SystemManager::RegisterSystem<PlayerAnimationSystem>();
	SystemManager::RegisterSystem<PlayerControllerSystem>();
	SystemManager::RegisterSystem<TilemapRenderingSystem2D>();
}