#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

struct ButtonColor
{
	sf::Color idle;
	sf::Color hover;
	sf::Color active;
	sf::Color outlineColor = sf::Color::Transparent;
};

enum button_status { BTN_IDLE, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:

protected:
	sf::RectangleShape m_shape;
	sf::Font m_font;
	sf::Text m_text;
	ButtonColor m_color;
	button_status status = BTN_IDLE;
	bool m_isHover = false;
	bool m_isActive = false;
	std::vector<sf::Drawable*> drawables;

	void CalculateTextPos();

public:
	Button() { }
	Button(float sizeX, float sizeY, float posX, float posY, ButtonColor colors, std::string text, std::string fontpath, unsigned int fontsize);
	virtual ~Button();

	//Modifiers
	void setPosition(float posX, float posY);

	//accessors
	bool isPressed();
	std::vector<sf::Drawable*>& getDrawables() { return this->drawables; }

	//Functions
	void Update(sf::Vector2i& mouseposWindow);
	void Render(sf::RenderWindow& window);
};

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox
{
public:
	TextBox() { }
	TextBox(float posX, float posY, float boxSizeX, float boxSizeY, uint32_t fontsize, sf::Color textcolor, sf::Color boxColor, float outlineThicknes, sf::Color outlineColor, bool selected);

	void SetFont(sf::Font& font);
	void SetPosition(sf::Vector2f pos);
	void SetLimit(bool ToF);
	void SetLimit(bool ToF, int limit);
	void SetSelected(bool sel);
	std::string getText();
	bool IsSelected();
	void drawText(sf::RenderTarget& target);
	void TypedOn(sf::Event input);
	void BoxClicked(sf::Event input, sf::RenderWindow& window);

	//accessors
	const sf::FloatRect getGB() const;

private:
	sf::RectangleShape box;
	sf::Text textBox;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit = 10;

	void InputLogic(int charTyped);
	void DeleteLastChar();
	void SetTextAndBoxPosition(float boxPosiitonX, float boxpositionY);
};

enum buttonposition { TB_LEFT, TB_RIGHT };
using TBButtonPosion = buttonposition;

void SetTextBox_ButtonPos(TextBox& textbox, Button& button, TBButtonPosion positon);