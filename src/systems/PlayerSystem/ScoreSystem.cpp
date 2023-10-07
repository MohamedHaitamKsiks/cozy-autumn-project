#include "ScoreSystem.h"

#define SCORE_SYSTEM_VISIBLE_DURATION 3.0f

ScoreSystem* ScoreSystem::s_Instance = nullptr;

ScoreSystem::ScoreSystem()
{
	
}

void ScoreSystem::IncrementLeafCounter()
{
	s_Instance->m_LeafCounter++;
	s_Instance->Show();
}

void ScoreSystem::IncrementDeathCounter()
{
	s_Instance->m_DeathCounter++;
	s_Instance->Show();
}

void ScoreSystem::Show()
{
	m_VisibleTimer = SCORE_SYSTEM_VISIBLE_DURATION;
	m_Visible = true;
}

void ScoreSystem::DrawScore(ResourceID iconID, const vec2 &offset, int value, const std::string &suffix)
{
	// draw icon
	SpriteDrawInfo iconSpriteInfo;
	iconSpriteInfo.Centered = true;
	iconSpriteInfo.SpriteID = iconID;
	iconSpriteInfo.Layer = DrawLayer::UI;
	iconSpriteInfo.Modulate.a = m_Opacity;

	Transform2D iconSpriteTransform2D;
	iconSpriteTransform2D.Position = vec2{16.0f, 16.0f} + offset;

	RenderingSystem2D::DrawSprite(iconSpriteInfo, iconSpriteTransform2D);

	// draw shadow
	iconSpriteInfo.Layer = DrawLayer::Shadow;
	iconSpriteInfo.Modulate = Color::BLACK();
	iconSpriteInfo.Modulate.a = m_Opacity;
	iconSpriteTransform2D.Position = iconSpriteTransform2D.Position + vec2{-2.0f, 2.0f};
	RenderingSystem2D::DrawSprite(iconSpriteInfo, iconSpriteTransform2D);

	// draw leaf counter
	std::stringstream ss;
	ss << "x" << value << suffix;

	TextDrawInfo textInfo{};
	textInfo.Layer = DrawLayer::UI;
	textInfo.Text = ss.str();
	textInfo.FontID = m_FontID;
	textInfo.Modulate.a = m_Opacity;

	Transform2D textTransform2D{};
	textTransform2D.Position = vec2{32.0f, 22.0f} + offset;
	textTransform2D.Scale = vec2::ONE();

	RenderingSystem2D::DrawText(textInfo, textTransform2D);

	// draw shadow
	textInfo.Layer = DrawLayer::Shadow;
	textInfo.Modulate = Color::BLACK();
	textInfo.Modulate.a = m_Opacity;

	Transform2D shadowTransform2D = textTransform2D;

	shadowTransform2D.Position = textTransform2D.Position + vec2{-2.0f, 2.0f};
	RenderingSystem2D::DrawText(textInfo, shadowTransform2D);

	// draw outline
	shadowTransform2D.Position = textTransform2D.Position + vec2{1.0f, 0.0f} * shadowTransform2D.Scale.x;
	RenderingSystem2D::DrawText(textInfo, shadowTransform2D);

	shadowTransform2D.Position = textTransform2D.Position + vec2{-1.0f, 0.0f} * shadowTransform2D.Scale.x;
	RenderingSystem2D::DrawText(textInfo, shadowTransform2D);

	shadowTransform2D.Position = textTransform2D.Position + vec2{0.0f, 1.0f} * shadowTransform2D.Scale.x;
	RenderingSystem2D::DrawText(textInfo, shadowTransform2D);

	shadowTransform2D.Position = textTransform2D.Position + vec2{0.0f, -1.0f} * shadowTransform2D.Scale.x;
	RenderingSystem2D::DrawText(textInfo, shadowTransform2D);
}

void ScoreSystem::OnCreate()
{
	s_Instance = this;
	m_FontID = ResourceManager<Font>::GetResourceId(UniqueString("fonts/default.font.json"));
	m_LeafIconID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/ui/leaf_icon.sprite.json"));
	m_SkullIconID = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/ui/skull_icon.sprite.json"));
};

void ScoreSystem::OnUpdate(float delta)
{
	// show / hide score
	if (m_Visible)
	{
		m_VisibleTimer -= delta;
		if (m_VisibleTimer < 0.0f)
			m_Visible = false;
		
	}
	m_Opacity = Interpolate::Linear(m_Opacity, (m_Visible)? 1.0f : 0.0f, delta * 6.0f / Application::GetSingleton()->TimeScale);

	// transtition timer
	m_TransitionTimer -= delta;
	if (m_TransitionTimer < 0.0f)
	{
		m_Transition = Interpolate::Linear(m_Transition, 0.0f, delta * 8.0f / Application::GetSingleton()->TimeScale);
	}

};


void ScoreSystem::OnUIRender2D()
{
	vec2 offset = vec2::LEFT() * Interpolate::Linear(32.0f, 0.0f, m_Opacity);

	std::stringstream ss;
	ss << "/" << Leaf::Count;

	DrawScore(m_LeafIconID, vec2::ZERO() + offset, m_LeafCounter, ss.str());
	DrawScore(m_SkullIconID, vec2{0.0f, 30.0f} + offset, m_DeathCounter, "");

	// draw transition rectangle
	RectangleDrawInfo rectInfo;
	rectInfo.Layer = DrawLayer::UI;
	rectInfo.Modulate = Color::BLACK();
	rectInfo.Size = Window::GetSize();

	Transform2D transform2D;
	transform2D.Position = vec2::LEFT() * Interpolate::Linear(Window::GetSize().x, 0.0f, m_Transition);

	RenderingSystem2D::DrawRectangle(rectInfo, transform2D);

};

void ScoreSystem::OnInputEvent(const InputEvent& event)
{
	if (event.GetType() != InputEventType::KEYBOARD)
		return;

	// cast input event to keyboard type
	InputEventKeyboard keyEvent = event.Get<InputEventKeyboard>();

	// get input direction
	if (keyEvent.Code == GLFW_KEY_TAB && keyEvent.Pressed)
		Show();
};
