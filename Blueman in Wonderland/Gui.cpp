#include "Gui.h"
Gui::Gui() {

	backgroundTT.loadFromFile(backgroundFile);
	backgroundSP.setTexture(backgroundTT);

	this->font.loadFromFile(this->fontFile);

	this->hpMissTT.loadFromFile(this->hpMissFile);
	this->outerBarTT.loadFromFile(this->outerBarFile);
	this->innerHpBarTT.loadFromFile(this->innerHpBarFile);
	this->innerEnergyBarTT.loadFromFile(this->innerEnergyBarFile);
	this->hpIconTT.loadFromFile(this->hpIconFile);
	this->energyIconTT.loadFromFile(this->energyIconFile);
	this->waveBossOuterTT.loadFromFile(this->waveBossOuterFile);
	this->waveBossInnerTT.loadFromFile(this->waveBossInnerFile);
	this->bossIconTT.loadFromFile(this->bossIconFile);

	this->hpMissSP.setTexture(hpMissTT);
	this->outerHpBarSP.setTexture(outerBarTT);
	this->innerHpBarSP.setTexture(innerHpBarTT);
	this->outerEnergyBarSP.setTexture(outerBarTT);
	this->innerEnergyBarSP.setTexture(innerEnergyBarTT);
	this->hpIconSP.setTexture(hpIconTT);
	this->energyIconSP.setTexture(energyIconTT);
	this->waveBossOuterSP.setTexture(waveBossOuterTT);
	this->waveBossInnerSP.setTexture(waveBossInnerTT);
	this->bossIconSP.setTexture(bossIconTT);

	this->bossIconSP.setScale(0.7,0.7);

	this->hpMissTxt.setFont(font);
	this->hpBarTxt.setFont(font);
	this->energyBarTxt.setFont(font);
	this->scoreTxt.setFont(font);

	this->hpMissTxt.setCharacterSize(40);
	this->hpBarTxt.setCharacterSize(40);
	this->energyBarTxt.setCharacterSize(40);
	this->scoreTxt.setCharacterSize(40);

	this->hpMissSP.setOrigin(hpMissSP.getGlobalBounds().width / 2, hpMissSP.getGlobalBounds().height / 2);
	this->outerHpBarSP.setOrigin(outerHpBarSP.getGlobalBounds().width / 2, outerHpBarSP.getGlobalBounds().height / 2);
	this->innerHpBarSP.setOrigin(innerHpBarSP.getGlobalBounds().width / 2, innerHpBarSP.getGlobalBounds().height / 2);
	this->outerEnergyBarSP.setOrigin(outerEnergyBarSP.getGlobalBounds().width / 2, outerEnergyBarSP.getGlobalBounds().height / 2);
	this->innerEnergyBarSP.setOrigin(innerEnergyBarSP.getGlobalBounds().width / 2, innerEnergyBarSP.getGlobalBounds().height / 2);
	this->hpIconSP.setOrigin(hpIconSP.getGlobalBounds().width / 2, hpIconSP.getGlobalBounds().height / 2);
	this->energyIconSP.setOrigin(energyIconSP.getGlobalBounds().width / 2, energyIconSP.getGlobalBounds().height / 2);
	this->waveBossOuterSP.setOrigin(waveBossOuterSP.getGlobalBounds().width / 2, waveBossOuterSP.getGlobalBounds().height / 2);
	this->waveBossInnerSP.setOrigin(waveBossInnerSP.getGlobalBounds().width / 2, waveBossInnerSP.getGlobalBounds().height / 2);

	this->hpMissSP.setPosition(45, 175);
	this->outerHpBarSP.setPosition(300, 45);
	this->innerHpBarSP.setPosition(300, 45);
	this->outerEnergyBarSP.setPosition(300, 110);
	this->innerEnergyBarSP.setPosition(300, 110);
	this->hpIconSP.setPosition(45, 45);
	this->energyIconSP.setPosition(45, 110);
	this->waveBossOuterSP.setPosition(1920-350, 1080-80);
	this->waveBossInnerSP.setPosition(1920 - 350, 1080-80);
	this->bossIconSP.setPosition(1920 - 110, 1080 - 110);

	this->hpMissTxt.setOrigin(hpMissTxt.getGlobalBounds().width / 2, hpMissTxt.getGlobalBounds().height / 2);
	this->hpBarTxt.setOrigin(hpBarTxt.getGlobalBounds().width / 2, hpBarTxt.getGlobalBounds().height / 2);
	this->energyBarTxt.setOrigin(energyBarTxt.getGlobalBounds().width / 2, energyBarTxt.getGlobalBounds().height / 2);
	this->scoreTxt.setOrigin(scoreTxt.getGlobalBounds().width / 2, scoreTxt.getGlobalBounds().height / 2);

	this->hpMissTxt.setPosition(80, 145);
	this->hpBarTxt.setPosition(230, 20);
	this->energyBarTxt.setPosition(230, 80);
	this->scoreTxt.setPosition(1570,30);

	scoreTxt.setFillColor(sf::Color::White);
	scoreTxt.setOutlineColor(sf::Color::Black);
	scoreTxt.setOutlineThickness(10);

	onUpdate();

	lifeDecreaseBF.loadFromFile("Audio/duck.wav");
	tempLifeDecrease.setBuffer(lifeDecreaseBF);
}

void Gui::onUpdate() {
	if (!lifeDecrease.empty()) {
		if (lifeDecrease.front().getStatus() == 0) lifeDecrease.pop_front();
	}
	ss << "X" << healthMiss;
	this->hpMissTxt.setString(ss.str());
	ss.str("");
	ss << healthPlayer << "/" << maxHealthPlayer;
	this->hpBarTxt.setString(ss.str());
	ss.str("");
	ss << energyPlayer << "/" << maxEnergyPlayer;
	this->energyBarTxt.setString(ss.str());
	ss.str("");
	ss << "SCORE : " << score;
	this->scoreTxt.setString(ss.str());
	ss.str("");

	cntRegen += deltaTime.asSeconds();

	if (energyPlayer < 0) energyPlayer = 0;
	this->innerEnergyBarSP.setTextureRect(sf::IntRect(0, 0, energyPlayer * 4, 40));
	if (healthPlayer < 0) healthPlayer = 0;
	this->innerHpBarSP.setTextureRect(sf::IntRect(0, 0, healthPlayer / 2.5, 40));
	if (cntRegen >= regenTime) {
		energyPlayer += 2;
		if (energyPlayer > 100) energyPlayer = 100;
		cntRegen -= regenTime;
	}

	this->waveBossInnerSP.setTextureRect(sf::IntRect(0, 0, amountEnemySpawn*500/60, 20));
}
void Gui::_draw(sf::RenderWindow& window) {
	window.draw(backgroundSP);
	window.draw(hpMissSP);
	window.draw(hpMissTxt);
	window.draw(hpIconSP);
	window.draw(energyIconSP);
	window.draw(outerHpBarSP);
	window.draw(innerHpBarSP);
	window.draw(hpBarTxt);
	window.draw(outerEnergyBarSP);
	window.draw(innerEnergyBarSP);
	window.draw(energyBarTxt);
	window.draw(scoreTxt);
	window.draw(waveBossOuterSP);
	window.draw(waveBossInnerSP);
	window.draw(bossIconSP);

}

void Gui::requestEnergyPlayer(const short energyPlayer) {
	this->energyPlayer += energyPlayer;
	if (this->energyPlayer <= 0) this->energyPlayer = 0;
	if (this->energyPlayer > 100) this->energyPlayer = 100;
}

void Gui::requestHealthPlayer(const short healthPlayer) {
	this->healthPlayer = healthPlayer;
	if (this->healthPlayer <= 0) this->healthPlayer = 0;
	if (this->healthPlayer > this->maxHealthPlayer) this->healthPlayer = this->maxHealthPlayer;
}

void Gui::requestScore(const short deltaScore) {
	this->score += deltaScore;
}

void Gui::requestHealthMiss(const int healthMiss) {
	if (healthMiss == 1) {
		lifeDecrease.push_back(tempLifeDecrease);
		lifeDecrease.back().play();
	}
	this->healthMiss -= healthMiss;
	if (this->healthMiss <= 0) {
		this->healthMiss = 0;
		//statement
	}
}

void Gui::requestAmountEnemySpawn(const short amountEnemySpawn) {
	this->amountEnemySpawn = amountEnemySpawn;
}
int Gui::updateEnergyPlayer() {
	return energyPlayer;
}

unsigned long long Gui::getScore() {
	return score;
}