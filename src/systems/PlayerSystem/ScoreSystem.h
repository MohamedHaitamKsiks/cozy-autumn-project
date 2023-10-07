#ifndef SYSTEM_SCORESYSTEM_H
#define SYSTEM_SCORESYSTEM_H

#include <sstream>

#include "components/Objects/Leaf.h"
#include "components/EmptyComponent.h"

#include "systems/RenderingSystem2D/RenderingSystem2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class ScoreSystem : public System<EmptyComponent>
{
public:
	ScoreSystem();

	static void IncrementLeafCounter();
	static void IncrementDeathCounter();

private:

	// system's instance
	static ScoreSystem *s_Instance;

	// score data
	int m_LeafCounter = 0;
	int m_DeathCounter = 0;

	// update score
	float m_VisibleTimer = 0.0f;
	float m_Opacity = 0.0f;
	bool m_Visible = false;
	void Show();

	// transition out
	float m_TransitionTimer = 0.25f;
	float m_Transition = 1.0f;

	ResourceID m_FontID;
	ResourceID m_LeafIconID;
	ResourceID m_SkullIconID;

	void DrawScore(ResourceID iconID, const vec2 &offset, int value, const std::string& suffix);

	void OnCreate();
	void OnUpdate(float delta);
	void OnUIRender2D();
	void OnInputEvent(const InputEvent &event);
};

#endif // SYSTEM_SCORESYSTEM_H