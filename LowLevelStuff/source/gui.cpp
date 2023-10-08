#include "bcpch.h"
#include "gui.h"

void Button::CalculateTextPos()
{
	this->m_text.setPosition(
		this->m_shape.getPosition().x + (this->m_shape.getGlobalBounds().width / 2.f) - this->m_text.getGlobalBounds().width / 2.f,
		this->m_shape.getPosition().y + ((this->m_shape.getGlobalBounds().height / 2) - this->m_text.getGlobalBounds().height)
	);
}

Button::Button(
	float sizeX, float sizeY, float posX, float posY,
	ButtonColor colors,
	std::string text, std::string fontpath, unsigned int fontsize
)
	:m_color(colors)
{
	//Shape
	this->m_shape.setSize(sf::Vector2f(sizeX, sizeY));
	this->m_shape.setPosition(posX, posY);
	this->m_shape.setFillColor(this->m_color.idle);
	this->m_shape.setOutlineColor(colors.outlineColor);
	this->m_shape.setOutlineThickness(3.f);

	//Text
	this->m_font.loadFromFile(fontpath);
	this->m_text.setFont(m_font);
	this->m_text.setString(text);
	this->m_text.setCharacterSize(fontsize);

	CalculateTextPos();

	this->drawables.push_back(&this->m_shape);
	this->drawables.push_back(&this->m_text);
}

Button::~Button()
{

}

void Button::setPosition(float posX, float posY)
{
	this->m_shape.setPosition(posX, posY);
	CalculateTextPos();
}

bool Button::isPressed()
{
	if (this->status == BTN_ACTIVE)
		return true;

	return false;
}

void Button::Update(sf::Vector2i& mousePosWindow)
{
	this->status = BTN_IDLE;

	//Hover
	if (this->m_shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->status = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->status = BTN_ACTIVE;
		}
	}

	switch (this->status)
	{
	case BTN_IDLE:
		this->m_shape.setFillColor(this->m_color.idle);
		break;

	case BTN_HOVER:
		this->m_shape.setFillColor(this->m_color.hover);
		break;

	case BTN_ACTIVE:
		this->m_shape.setFillColor(this->m_color.active);
		break;

	default:
		this->m_shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::Render(sf::RenderWindow& window)
{
	window.draw(this->m_shape);
	window.draw(this->m_text);
}

//TextBox
TextBox::TextBox(float posX, float posY, float boxSizeX, float boxSizeY, uint32_t fontsize, sf::Color textcolor, sf::Color boxcolor, float outlineThicknes, sf::Color outlineColor, bool selected)
{
	this->SetTextAndBoxPosition(posX, posY);
	this->textBox.setFillColor(textcolor);
	this->textBox.setCharacterSize(fontsize);

	isSelected = selected;
	if (selected)
		textBox.setString("_");
	else
		textBox.setString("");

	box.setSize({ boxSizeX, boxSizeY });
	box.setFillColor(boxcolor);
	box.setOutlineThickness(outlineThicknes);
	box.setOutlineColor(outlineColor);
}

void TextBox::SetFont(sf::Font& font)
{
	this->textBox.setFont(font);
}

void TextBox::SetPosition(sf::Vector2f pos)
{
	this->SetTextAndBoxPosition(pos.x, pos.y);
}

void TextBox::SetLimit(bool ToF)
{
	hasLimit = ToF;
}

void TextBox::SetLimit(bool ToF, int limit)
{
	hasLimit = ToF;
	this->limit = limit - 1;
}

void TextBox::SetSelected(bool sel)
{
	isSelected = sel;
	if (!sel)
	{
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length(); i++)
			newT += t[i];
		textBox.setString(newT);
	}
}

std::string TextBox::getText()
{
	return this->text.str();
}

bool TextBox::IsSelected()
{
	return this->isSelected;
}

void TextBox::drawText(sf::RenderTarget& target)
{
	target.draw(box);
	target.draw(textBox);
}

void TextBox::TypedOn(sf::Event input)
{
	if (isSelected)
	{
		int chartyped = input.text.unicode;
		if (chartyped < 130)
		{
			if (hasLimit)
			{
				if (text.str().length() <= limit)
				{
					InputLogic(chartyped);
				}
				else if (text.str().length() > limit && chartyped == DELETE_KEY)
					DeleteLastChar();
			}
			else
			{
				InputLogic(chartyped);
			}
		}
	}
}

void TextBox::BoxClicked(sf::Event input, sf::RenderWindow& window)
{
	if (this->box.getGlobalBounds().contains((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y))
	{
		this->SetSelected(true);
	}
}

const sf::FloatRect TextBox::getGB() const
{
	return this->box.getGlobalBounds();
}

void TextBox::InputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY &&
		charTyped != ENTER_KEY &&
		charTyped != ESCAPE_KEY)
	{
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY)
	{
		if (text.str().length() > 0)
		{
			DeleteLastChar();
		}
	}
	textBox.setString(text.str() + "_");
}

void TextBox::DeleteLastChar()
{
	std::string t = text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; i++)
	{
		newT += t[i];
	}
	text.str("");
	text << newT;

	textBox.setString(text.str());
}

void TextBox::SetTextAndBoxPosition(float boxPosiitonX, float boxpositionY)
{
	this->box.setPosition(boxPosiitonX, boxpositionY);
	this->textBox.setPosition(boxPosiitonX, boxpositionY);
}

void SetTextBox_ButtonPos(TextBox& textbox, Button& button, TBButtonPosion positon)
{
	switch (positon)
	{
	case TB_LEFT:
	{

		break;
	}
	case TB_RIGHT:
	{
		button.setPosition(
			(textbox.getGB().left + textbox.getGB().width) + 2.f,
			textbox.getGB().top + 2
		);

		break;
	}
	default:
		break;
	}
}
