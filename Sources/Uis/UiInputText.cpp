﻿#include "UiInputText.hpp"

#include "Inputs/Keyboard.hpp"
#include "Maths/Visual/DriverSlide.hpp"
#include "Scenes/Scenes.hpp"

namespace acid
{
	const float UiInputText::CHANGE_TIME = 0.1f;
	const float UiInputText::SCALE_NORMAL = 1.6f;
	const float UiInputText::SCALE_SELECTED = 1.8f;
	const Colour UiInputText::COLOUR_NORMAL = Colour("#000000");

	UiInputText::UiInputText(UiObject *parent, const Vector3 &position, const std::string &prefix, const std::string &value, const TextJustify &justify) :
		UiObject(parent, UiBound(Vector2(0.5f, 0.5f), "Centre", true, true, Vector2(1.0f, 1.0f))),
		m_text(nullptr), //new Text(this, position, SCALE_NORMAL, Vector2(0.5f, 0.5f), prefix + value, FontType::Resource("Fonts/Candara", "Regular"), justify, 0.36f)),
		m_background(nullptr), //new Gui(this, position, Vector3(1.0f, 1.0f, RelativeScreen), Vector2(0.5f, 0.5f), Texture::Resource("Guis/Button.png"))),
		m_prefix(prefix),
		m_value(value),
		m_inputDelay(UiInputDelay()),
		m_lastKey(0),
		m_selected(false),
		m_mouseOver(false),
		m_actionChange(nullptr)
	{
		m_background->SetColourOffset(Colour());
	}

	UiInputText::~UiInputText()
	{
		delete m_text;
		delete m_background;
	}

	void UiInputText::UpdateObject()
	{
		if (m_selected)
		{
			int key = Keyboard::Get()->GetChar();

			// TODO: Fix inputs that are not defined.
			if (key != 0 && Keyboard::Get()->GetKey((Key) toupper(key)))
			{
				m_inputDelay.Update(true);

				if (m_lastKey != key || m_inputDelay.CanInput())
				{
					m_value += static_cast<char>(key);
					m_text->SetString(m_prefix + m_value);

					if (m_actionChange != nullptr)
					{
						m_actionChange();
					}

					m_lastKey = key;
				}
			}
			else if (Keyboard::Get()->GetKey(KEY_BACKSPACE))
			{
				m_inputDelay.Update(true);

				if (m_lastKey != 8 || m_inputDelay.CanInput())
				{
					m_value = m_value.substr(0, m_value.length() - 1);
					m_text->SetString(m_prefix + m_value);

					if (m_actionChange != nullptr)
					{
						m_actionChange();
					}

					m_lastKey = 8;
				}
			}
			else if (Keyboard::Get()->GetKey(KEY_ENTER) && m_lastKey != 13)
			{
				m_inputDelay.Update(true);

				m_selected = false;
				m_text->SetScaleDriver<DriverSlide>(m_text->GetScale(), SCALE_NORMAL, CHANGE_TIME);
			}
			else
			{
				m_inputDelay.Update(false);
				m_lastKey = 0;
			}
		}

		// Click updates.
		if (Uis::Get()->GetSelector().IsSelected(*m_text) && GetAlpha() == 1.0f &&
			Uis::Get()->GetSelector().WasLeftClick())
		{
			m_text->SetScaleDriver<DriverSlide>(m_text->GetScale(), SCALE_SELECTED, CHANGE_TIME);
			m_selected = true;

			Uis::Get()->GetSelector().CancelWasEvent();
		}
		else if (Uis::Get()->GetSelector().WasLeftClick() && m_selected)
		{
			m_text->SetScaleDriver<DriverSlide>(m_text->GetScale(), SCALE_NORMAL, CHANGE_TIME);
			m_selected = false;
		}

		// Mouse over updates.
		if (Uis::Get()->GetSelector().IsSelected(*m_text) && !m_mouseOver && !m_selected)
		{
			m_text->SetScaleDriver<DriverSlide>(m_text->GetScale(), SCALE_SELECTED, CHANGE_TIME);
			m_mouseOver = true;
		}
		else if (!Uis::Get()->GetSelector().IsSelected(*m_text) && m_mouseOver && !m_selected)
		{
			m_text->SetScaleDriver<DriverSlide>(m_text->GetScale(), SCALE_NORMAL, CHANGE_TIME);
			m_mouseOver = false;
		}

		// Update the background colour.
		auto primary = Scenes::Get()->GetScene()->GetUiColour();
		m_background->SetColourOffset(COLOUR_NORMAL.Interpolate(*primary, (m_text->GetScale() - SCALE_NORMAL) / (SCALE_SELECTED - SCALE_NORMAL)));

		// Update background size.
		//*m_background->GetDimensions() = *m_text->GetDimensions();
		//m_background->GetDimensions()->m_y = 0.5f * static_cast<float>(m_text->GetFontType()->GetMetadata()->GetMaxSizeY());
		//*m_background->GetDimensions() = *m_text->GetDimensions() * *m_background->GetDimensions();
		//*m_background->GetDimensions() *= 2.0f * m_text->GetScale();
		//*m_background->GetPosition() = *m_text->GetPosition));
	}

	void UiInputText::SetPrefix(const std::string &prefix)
	{
		m_prefix = prefix;
		m_text->SetString(prefix + m_value);
	}

	void UiInputText::SetValue(const std::string &value)
	{
		m_value = value;
		m_text->SetString(m_prefix + value);
	}
}
