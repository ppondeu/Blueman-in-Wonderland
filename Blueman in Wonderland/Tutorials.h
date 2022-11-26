#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
class Tutorials
{
private:
	sf::Font font;
	sf::Text tutorials, wTxt, sTxt, aTxt, dTxt, jTxt, kTxt, iTxt, eTxt, enterTxt;
	sf::Text desWASD, desJ, desK, desI, desE, desEnter;
	sf::Text desRazeTxt, desSlowingTxt, desLightningTxt, desHealingTxt;
	sf::RectangleShape wBox, sBox, aBox, dBox, jBox, kBox, iBox, eBox, enterBox;
	sf::Texture razeTT, slowingTT, lightningTT, healingTT;
	sf::Sprite razeSP, slowingSP, lightningSP, healingSP;

	sf::Sound sound;
	sf::SoundBuffer buffer;

	short cntOnBack = 0;
public:
	sf::RectangleShape backBox;
	sf::Text backTxt;
private:
public:
	Tutorials();
	void isOnButton(const sf::Vector2f& mousePos);
	void onUpdate(const sf::Vector2f& mousePos);
	void draw(sf::RenderWindow& window);
};