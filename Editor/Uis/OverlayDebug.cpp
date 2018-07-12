#include "OverlayDebug.hpp"

#include <Maths/Visual/DriverConstant.hpp>
#include <Scenes/Scenes.hpp>
#include <Guis/Gui.hpp>
#include "World/World.hpp"

namespace test
{
	OverlayDebug::OverlayDebug(UiObject *parent) :
		UiObject(parent, UiBound(Vector2(0.5f, 0.5f), "Centre", true, true, Vector2(1.0f, 1.0f))),
		m_textFps(CreateStatus("FPS: 0", 0.002f, 0.002f, JUSTIFY_LEFT)),
		m_textUps(CreateStatus("UPS: 0", 0.002f, 0.022f, JUSTIFY_LEFT)),
		m_timerUpdate(new Timer(0.333f))
	{
	}

	OverlayDebug::~OverlayDebug()
	{
		delete m_textFps;
		delete m_textUps;
		delete m_timerUpdate;
	}

	void OverlayDebug::UpdateObject()
	{
		if (m_timerUpdate->IsPassedTime())
		{
			m_timerUpdate->ResetStartTime();

			m_textFps->SetString("FPS: " + std::to_string(static_cast<int>(1.0f / Engine::Get()->GetDeltaRender())));
			m_textUps->SetString("UPS: " + std::to_string(static_cast<int>(1.0f / Engine::Get()->GetDelta())));
		}
	}

	Text *OverlayDebug::CreateStatus(const std::string &content, const float &positionX, const float &positionY, const FontJustify &justify)
	{
		Text *result = new Text(this, UiBound(Vector2(positionX, positionY), "BottomLeft", true), 1.1f, content, FontType::Resource("Fonts/ProximaNova", FAMILY_REGULAR), justify);
		result->SetTextColour(Colour(1.0f, 1.0f, 1.0f));
		result->SetBorderColour(Colour(0.15f, 0.15f, 0.15f));
		result->SetBorderDriver<DriverConstant>(0.04f);
		return result;
	}
}
