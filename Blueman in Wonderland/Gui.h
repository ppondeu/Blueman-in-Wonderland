#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<sstream>
#include<deque>
class Gui
{
private:
	const std::string hpMissFile = "Sprite/Gui/life.png";
	const std::string outerBarFile = "Sprite/Gui/outer.png";
	const std::string innerHpBarFile = "Sprite/Gui/hp.png";
	const std::string innerEnergyBarFile = "Sprite/Gui/energy.png";
	const std::string hpIconFile = "Sprite/Gui/hpIcon.png";
	const std::string energyIconFile = "Sprite/Gui/energyIcon.png";
	const std::string waveBossOuterFile = "Sprite/Gui/waveBossOuter.png";
	const std::string waveBossInnerFile = "Sprite/Gui/waveBossInner.png";
	const std::string bossIconFile = "Sprite/Gui/bossIcon.png";


	sf::Texture hpMissTT, outerBarTT, innerHpBarTT, innerEnergyBarTT, hpIconTT, energyIconTT, waveBossOuterTT, waveBossInnerTT, bossIconTT;
	sf::Sprite hpMissSP, outerHpBarSP, outerEnergyBarSP, innerHpBarSP, innerEnergyBarSP, hpIconSP, energyIconSP, waveBossOuterSP, waveBossInnerSP, bossIconSP;
	
	const std::string fontFile = "Font/PixelFont2.ttf";

	sf::Font font;

	sf::Text hpMissTxt, hpBarTxt, energyBarTxt, scoreTxt;

	short maxHealthPlayer = 1000;
	short healthPlayer = maxHealthPlayer;
	
	int maxEnergyPlayer = 100;
	int energyPlayer = 100;

	std::stringstream ss;

	const float regenTime = 1.0f;
	float cntRegen = 0.0f;
	sf::Time deltaTime = sf::seconds(1.0f / 60.0f);

	const std::string backgroundFile = "Sprite/Background/dungion.png";
	sf::Texture backgroundTT;
	sf::Sprite backgroundSP;

	sf::SoundBuffer lifeDecreaseBF;
	sf::Sound tempLifeDecrease;
	std::deque<sf::Sound> lifeDecrease;

	short amountEnemySpawn = 0;
public:
	int healthMiss = 5;
	unsigned long long score = 0;
private:

public:
	void onUpdate();
	Gui();
	void _draw(sf::RenderWindow& window);

	void requestHealthPlayer(const short deltaHealthPlayer);
	void requestScore(const short deltaScore);
	void requestEnergyPlayer(const short energyPlayer);
	void requestHealthMiss(const int heathMiss);
	void requestAmountEnemySpawn(const short amountEnemySpawn);
	int updateEnergyPlayer();

	unsigned long long getScore();
};