#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>

class Item
{
private:
	const short RAZE = 0;
	const short SLOWING = 0;
	const short LIGHTNING = 0;
	const short HEALING = 0;

	const std::string itemFile = "Sprite/Item/item.png";
	const std::string itemBarFile = "Sprite/Item/itemShow.png";

	sf::Texture itemTT;

	const short maxItem = 4;

	sf::Vector2f randPos;
	short randItem;


	sf::Time deltaTime = sf::seconds(1.0f / 60.0f);
	const float cooldownTime = 3.0f;
	const float onScreenTime = 5.0f;
	float curCooldown = onScreenTime;
	float cntCooldown = 0.0f;

	sf::Texture itemBarTT;
	sf::Sprite itemBarSP;
	sf::Vector2i imageItemBarSize{ 100, 100 };   // 5 90 5
	std::vector<short> amountItem;

	sf::Text amount;
	sf::Font font;

	std::vector<sf::Sprite> itemBar;
	std::vector<sf::Text> amountItemTxt;

	bool isCollided = false;

	short cntPressedI = 0;
	short cntPressedEnter = 0;

	//crop item bar
	sf::RectangleShape itemBarCrop;
	//

	bool isSelectedItem = false;

	const float selectFadeAwayTime = 3.0f;
	float cntSelectFadeAway = 0.0f;

	short tempItemCrop = 0;
	short tempOfTemp = 0;

	short itemSelected = 666;

	std::pair<const float, float> raze{.0f, 0.0f};
	std::pair<const float, float> slowing{ 5.0f, 0.0f };
	std::pair<const float, float> lightning{ 2.0f, 0.0f };
	std::pair<const float, float> healing{ 2.0f, 0.0f };

	sf::SoundBuffer getItemBF, useItemBF, selectItemBF;
	sf::Sound getItemSound, useItemSound, selectItemSound;

	sf::Sprite playerSP;

private:
	void setFrame();
	void random();

	void setItemBarCropFrame();

	void resetCropInfo();

public:
	sf::Image itemIMG;
	sf::Sprite itemSP;

	short currentItem = 0;
	const sf::Vector2i imageSize{ 100, 100 };

public:
	Item();
	void onUpdate();
	void onEvent(const sf::Event& event);
	void _draw(sf::RenderWindow& window);

	void collision(const bool isCollided);

	short getItemSelected();
	void resetItemSelected();

};