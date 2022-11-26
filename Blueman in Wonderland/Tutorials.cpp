#include "Tutorials.h"
Tutorials::Tutorials() {
	font.loadFromFile("Font/PixelFont2.ttf");

	tutorials.setFont(font);
	tutorials.setCharacterSize(90);
	tutorials.setString("TUTORIALS");
	tutorials.setOrigin(tutorials.getGlobalBounds().width / 2, tutorials.getGlobalBounds().height / 2);
	tutorials.setPosition(959, 150 - tutorials.getGlobalBounds().height / 2);
	tutorials.setFillColor(sf::Color::Yellow);
	tutorials.setOutlineColor(sf::Color::Red);
	tutorials.setOutlineThickness(-2);
	//tutorials.setStyle(sf::Text::Italic);
	

	wBox.setSize(sf::Vector2f(75, 75));
	wBox.setOrigin(wBox.getGlobalBounds().width / 2, wBox.getGlobalBounds().height / 2);
	wBox.setPosition(500 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 - 25);
	wBox.setFillColor(sf::Color(255, 255, 255, 100));
	wBox.setOutlineColor(sf::Color(0, 0, 0, 150));
	wBox.setOutlineThickness(5);
	

	wTxt.setFont(font);
	wTxt.setCharacterSize(90);
	wTxt.setString("W");
	wTxt.setOrigin(wTxt.getGlobalBounds().width / 2, wTxt.getGlobalBounds().height / 2);
	wTxt.setPosition(500 - 4 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 163 - 25);
	wTxt.setFillColor(sf::Color::Black);
	

	sBox.setSize(sf::Vector2f(75, 75));
	sBox.setOrigin(sBox.getGlobalBounds().width / 2, sBox.getGlobalBounds().height / 2);
	sBox.setPosition(500 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 90 - 25);
	sBox.setFillColor(sf::Color(255, 255, 255, 100));
	sBox.setOutlineColor(sf::Color(0, 0, 0, 150));
	sBox.setOutlineThickness(5);
	

	sTxt.setFont(font);
	sTxt.setCharacterSize(90);
	sTxt.setString("S");
	sTxt.setOrigin(sTxt.getGlobalBounds().width / 2, sTxt.getGlobalBounds().height / 2);
	sTxt.setPosition(500 - 4 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 - 25);
	sTxt.setFillColor(sf::Color::Black);
	


	aBox.setSize(sf::Vector2f(75, 75));
	aBox.setOrigin(aBox.getGlobalBounds().width / 2, aBox.getGlobalBounds().height / 2);
	aBox.setPosition(500 - 90 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 90 - 25);
	aBox.setFillColor(sf::Color(255, 255, 255, 100));
	aBox.setOutlineColor(sf::Color(0, 0, 0, 150));
	aBox.setOutlineThickness(5);
	

	aTxt.setFont(font);
	aTxt.setCharacterSize(90);
	aTxt.setString("A");
	aTxt.setOrigin(aTxt.getGlobalBounds().width / 2, aTxt.getGlobalBounds().height / 2);
	aTxt.setPosition(500 - 4 - 90 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 - 25);
	aTxt.setFillColor(sf::Color::Black);
	

	dBox.setSize(sf::Vector2f(75, 75));
	dBox.setOrigin(dBox.getGlobalBounds().width / 2, dBox.getGlobalBounds().height / 2);
	dBox.setPosition(500 + 90 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 90 - 25);
	dBox.setFillColor(sf::Color(255, 255, 255, 100));
	dBox.setOutlineColor(sf::Color(0, 0, 0, 150));
	dBox.setOutlineThickness(5);
	

	dTxt.setFont(font);
	dTxt.setCharacterSize(90);
	dTxt.setString("D");
	dTxt.setOrigin(dTxt.getGlobalBounds().width / 2, dTxt.getGlobalBounds().height / 2);
	dTxt.setPosition(500 - 4 + 90 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 - 25);
	dTxt.setFillColor(sf::Color::Black);
	

	//description w a s d
	desWASD.setFont(font);
	desWASD.setCharacterSize(40);
	desWASD.setString("Move");
	//desWASD.setOrigin(desWASD.getGlobalBounds().width / 2, desWASD.getGlobalBounds().height / 2);
	desWASD.setPosition(500 - 4 + 360 - 95 - 200 - 50 - 20 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 - 25 - 45);
	desWASD.setFillColor(sf::Color::White);
	desWASD.setOutlineColor(sf::Color::Black);
	desWASD.setOutlineThickness(2);
	
	//

	jBox.setSize(sf::Vector2f(75, 75));
	jBox.setOrigin(jBox.getGlobalBounds().width / 2, jBox.getGlobalBounds().height / 2);
	jBox.setPosition(500 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 90 + 150 - 25);
	jBox.setFillColor(sf::Color(255, 255, 255, 100));
	jBox.setOutlineColor(sf::Color(0, 0, 0, 150));
	jBox.setOutlineThickness(5);
	

	jTxt.setFont(font);
	jTxt.setCharacterSize(90);
	jTxt.setString("J");
	jTxt.setOrigin(jTxt.getGlobalBounds().width / 2, jTxt.getGlobalBounds().height / 2);
	jTxt.setPosition(500 - 4 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 + 150 - 25);
	jTxt.setFillColor(sf::Color::Black);
	

	//description J

	desJ.setFont(font);
	desJ.setCharacterSize(40);
	desJ.setString("Attack");
	//desJ.setOrigin(desJ.getGlobalBounds().width / 2, desJ.getGlobalBounds().height / 2);
	desJ.setPosition(500 - 4 + 360 - 95 - 250 - 20 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 + 150 - 25 - 30 + 40);
	desJ.setFillColor(sf::Color::White);
	desJ.setOutlineColor(sf::Color::Black);
	desJ.setOutlineThickness(2);
	
	//

	kBox.setSize(sf::Vector2f(75, 75));
	kBox.setOrigin(kBox.getGlobalBounds().width / 2, kBox.getGlobalBounds().height / 2);
	kBox.setPosition(500 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 90 + 150 + 90 - 25);
	kBox.setFillColor(sf::Color(255, 255, 255, 100));
	kBox.setOutlineColor(sf::Color(0, 0, 0, 150));
	kBox.setOutlineThickness(5);
	

	kTxt.setFont(font);
	kTxt.setCharacterSize(90);
	kTxt.setString("K");
	kTxt.setOrigin(kTxt.getGlobalBounds().width / 2, kTxt.getGlobalBounds().height / 2);
	kTxt.setPosition(500 - 4 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 + 150 + 90 - 25);
	kTxt.setFillColor(sf::Color::Black);
	

	//description K

	desK.setFont(font);
	desK.setCharacterSize(40);
	desK.setString("Ultimate");
	//desK.setOrigin(desK.getGlobalBounds().width / 2, desK.getGlobalBounds().height / 2);
	desK.setPosition(500 - 4 + 360 - 95 - 250 - 20 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 + 150 + 90 - 25 - 30 + 40);
	desK.setFillColor(sf::Color::White);
	desK.setOutlineColor(sf::Color::Black);
	desK.setOutlineThickness(2);
	
	//


	/*eBox.setSize(sf::Vector2f(75, 75));
	eBox.setOrigin(eBox.getGlobalBounds().width / 2, eBox.getGlobalBounds().height / 2);
	eBox.setPosition(500 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 90 + 150 + 90 + 150 - 25);
	eBox.setFillColor(sf::Color(255, 255, 255, 100));
	eBox.setOutlineColor(sf::Color(0, 0, 0, 150));
	eBox.setOutlineThickness(5);
	

	eTxt.setFont(font);
	eTxt.setCharacterSize(90);
	eTxt.setString("E");
	eTxt.setOrigin(eTxt.getGlobalBounds().width / 2, eTxt.getGlobalBounds().height / 2);
	eTxt.setPosition(500 - 4 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 + 150 + 90 + 150 - 25);
	eTxt.setFillColor(sf::Color::Black);
	

	//description E
	desE.setFont(font);
	desE.setCharacterSize(40);
	desE.setString("Get Item");
	//desE.setOrigin(desE.getGlobalBounds().width / 2, desE.getGlobalBounds().height / 2);
	desE.setPosition(500 - 4 + 360 - 95 - 250 - 20 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 + 150 + 90 + 150 - 25 - 30 + 40);
	desE.setFillColor(sf::Color::White);
	desE.setOutlineColor(sf::Color::Black);
	desE.setOutlineThickness(2);
	
	//*/

	iBox.setSize(sf::Vector2f(75, 75));
	iBox.setOrigin(iBox.getGlobalBounds().width / 2, iBox.getGlobalBounds().height / 2);
	iBox.setPosition(500 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 90 + 150 + 90 + 150 + 90 - 25-90);
	iBox.setFillColor(sf::Color(255, 255, 255, 100));
	iBox.setOutlineColor(sf::Color(0, 0, 0, 150));
	iBox.setOutlineThickness(5);
	

	iTxt.setFont(font);
	iTxt.setCharacterSize(90);
	iTxt.setString("I");
	iTxt.setOrigin(iTxt.getGlobalBounds().width / 2, iTxt.getGlobalBounds().height / 2);
	iTxt.setPosition(500 - 4 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 + 150 + 90 + 150 + 90 - 25-90);
	iTxt.setFillColor(sf::Color::Black);
	

	//description I
	desI.setFont(font);
	desI.setCharacterSize(40);
	desI.setString("Select Item");
	//desI.setOrigin(desI.getGlobalBounds().width / 2, desI.getGlobalBounds().height / 2);
	desI.setPosition(500 - 4 + 360 - 95 - 250 - 20 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 + 150 + 90 + 150 + 90 - 25 - 30 + 40-90);
	desI.setFillColor(sf::Color::White);
	desI.setOutlineColor(sf::Color::Black);
	desI.setOutlineThickness(2);
	
	//

	enterBox.setSize(sf::Vector2f(250, 75));
	enterBox.setOrigin(enterBox.getGlobalBounds().width / 2, enterBox.getGlobalBounds().height / 2);
	enterBox.setPosition(500 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 90 + 150 + 90 + 150 + 90 + 90 - 25-90);
	enterBox.setFillColor(sf::Color(255, 255, 255, 100));
	enterBox.setOutlineColor(sf::Color(0, 0, 0, 150));
	enterBox.setOutlineThickness(5);
	

	enterTxt.setFont(font);
	enterTxt.setCharacterSize(90);
	enterTxt.setString("Enter");
	enterTxt.setOrigin(enterTxt.getGlobalBounds().width / 2, enterTxt.getGlobalBounds().height / 2);
	enterTxt.setPosition(500 - 4 - 200 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 + 150 + 90 + 150 + 90 + 90 - 25-90);
	enterTxt.setFillColor(sf::Color::Black);
	

	//description Enter
	desEnter.setFont(font);
	desEnter.setCharacterSize(40);
	desEnter.setString("Use Item");
	//desEnter.setOrigin(desEnter.getGlobalBounds().width / 2, desEnter.getGlobalBounds().height / 2);
	desEnter.setPosition(500 - 4 + 360 - 95 - 250 - 20 - 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 + 55 + 150 + 90 + 150 + 90 + 90 - 25 - 30 + 40-90);
	desEnter.setFillColor(sf::Color::White);
	desEnter.setOutlineColor(sf::Color::Black);
	desEnter.setOutlineThickness(2);
	
	//

	// item part

	razeTT.loadFromFile("Sprite/Item/razeSpell.png");
	razeSP.setTexture(razeTT);
	razeSP.setPosition(500 + 450 - 200, 150 - tutorials.getGlobalBounds().height / 2 + 200 - 25 + 50-50);
	


	desRazeTxt.setFont(font);
	desRazeTxt.setCharacterSize(40);
	desRazeTxt.setString("Raze spell : Increase bullet Damage of player");
	//desRazeTxt.setOrigin(desRazeTxt.getGlobalBounds().width / 2, desRazeTxt.getGlobalBounds().height / 2);
	desRazeTxt.setPosition(500 - 4 + 360 - 95 + 300 - 200 + 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 - 25 + 50 + 20-50);
	desRazeTxt.setFillColor(sf::Color::White);
	desRazeTxt.setOutlineColor(sf::Color::Black);
	desRazeTxt.setOutlineThickness(2);
	
	//


	slowingTT.loadFromFile("Sprite/Item/slowingSpell.png");
	slowingSP.setTexture(slowingTT);
	slowingSP.setPosition(500 + 450 - 200, 150 - tutorials.getGlobalBounds().height / 2 + 200 - 20 + 150 + 50-50);
	


	desSlowingTxt.setFont(font);
	desSlowingTxt.setCharacterSize(40);
	desSlowingTxt.setString("Slowing spell : Decrease movement speed and\nattack speed of the enemies");
	//desSlowingTxt.setOrigin(desSlowingTxt.getGlobalBounds().width / 2, desSlowingTxt.getGlobalBounds().height / 2);
	desSlowingTxt.setPosition(500 - 4 + 360 - 95 + 300 - 200 + 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 - 20 + 150 + 50-50);
	desSlowingTxt.setFillColor(sf::Color::White);
	desSlowingTxt.setOutlineColor(sf::Color::Black);
	desSlowingTxt.setOutlineThickness(2);
	
	//

	lightningTT.loadFromFile("Sprite/Item/lightningSpell.png");
	lightningSP.setTexture(lightningTT);
	lightningSP.setPosition(500 + 450 - 200, 150 - tutorials.getGlobalBounds().height / 2 + 200 - 20 + 150 + 150 + 50-50);
	


	desLightningTxt.setFont(font);
	desLightningTxt.setCharacterSize(40);
	desLightningTxt.setString("Lightning spell : Electrocute the enemies");
	//desLightningTxt.setOrigin(desLightningTxt.getGlobalBounds().width / 2, desLightningTxt.getGlobalBounds().height / 2);
	desLightningTxt.setPosition(500 - 4 + 360 - 95 + 300 - 200 + 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 - 20 + 150 + 150 + 50 + 20-50);
	desLightningTxt.setFillColor(sf::Color::White);
	desLightningTxt.setOutlineColor(sf::Color::Black);
	desLightningTxt.setOutlineThickness(2);
	
	//


	healingTT.loadFromFile("Sprite/Item/healingSpell.png");
	healingSP.setTexture(healingTT);
	healingSP.setPosition(500 + 450 - 200, 150 - tutorials.getGlobalBounds().height / 2 + 200 - 20 + 150 + 150 + 150 + 50-50);
	



	desHealingTxt.setFont(font);
	desHealingTxt.setCharacterSize(40);
	desHealingTxt.setString("Healing spell : Increase health player");
	//desHealingTxt.setOrigin(desHealingTxt.getGlobalBounds().width / 2, desHealingTxt.getGlobalBounds().height / 2);
	desHealingTxt.setPosition(500 - 4 + 360 - 95 + 300 - 200 + 20, 150 - tutorials.getGlobalBounds().height / 2 + 200 - 20 + 150 + 150 + 150 + 50 + 20-50);
	desHealingTxt.setFillColor(sf::Color::White);
	desHealingTxt.setOutlineColor(sf::Color::Black);
	desHealingTxt.setOutlineThickness(2);
	
	//

	// back button
	backBox.setSize(sf::Vector2f(150, 50));
	backBox.setFillColor(sf::Color(9, 59, 58, 255));
	backBox.setOutlineThickness(5);
	backBox.setOutlineColor(sf::Color(154,164,163,255));
	backBox.setOrigin(backBox.getGlobalBounds().width / 2, backBox.getGlobalBounds().height / 2);
	backBox.setPosition(1919 - backBox.getSize().x, 1079 - backBox.getSize().y);

	backTxt.setFont(font);
	backTxt.setCharacterSize(50);
	backTxt.setString("HOME");
	backTxt.setOrigin(backTxt.getLocalBounds().width / 2, backTxt.getLocalBounds().width / 2);
	backTxt.setPosition(1919 - backBox.getSize().x-4, 1079 - backBox.getSize().y+18);

	buffer.loadFromFile("Audio/onButtonSound.wav");
	sound.setBuffer(buffer);
}

void Tutorials::isOnButton(const sf::Vector2f& mousePos) {
	if (backBox.getGlobalBounds().contains(mousePos)) {
		backTxt.setFillColor(sf::Color::Yellow);
		++cntOnBack;
		if (cntOnBack == 1) {
			sound.play();
		}
			
	}
	else {
		backTxt.setFillColor(sf::Color::White);
		cntOnBack = 0;
	}
}
void Tutorials::onUpdate(const sf::Vector2f& mousePos) {
	isOnButton(mousePos);
}
void Tutorials::draw(sf::RenderWindow& window) {
	window.draw(tutorials);
	window.draw(wBox);
	window.draw(wTxt);
	window.draw(sBox);
	window.draw(sTxt);
	window.draw(aBox);
	window.draw(aTxt);
	window.draw(dBox);
	window.draw(dTxt);
	window.draw(desWASD);
	window.draw(jBox);
	window.draw(jTxt);
	window.draw(desJ);
	window.draw(kBox);
	window.draw(kTxt);
	window.draw(desK);
	//window.draw(eBox);
	//window.draw(eTxt);
	window.draw(desE);
	window.draw(iBox);
	window.draw(iTxt);
	window.draw(desI);
	window.draw(enterBox);
	window.draw(enterTxt);
	window.draw(desEnter);
	window.draw(razeSP);
	window.draw(desRazeTxt);
	window.draw(slowingSP);
	window.draw(desSlowingTxt);
	window.draw(lightningSP);
	window.draw(desLightningTxt);
	window.draw(healingSP);
	window.draw(desHealingTxt);
	
	window.draw(backBox);
	window.draw(backTxt);
}
