#include "Boss.h"

Boss::Boss() {
	this->bossIMG.loadFromFile(bossFile);
	this->bodyIMG.loadFromFile(bodyFile);
	this->weaponIMG.loadFromFile(weaponFile);

	this->bossTT.loadFromFile(bossFile);
	this->bodyTT.loadFromFile(bodyFile);
	this->weaponTT.loadFromFile(weaponFile);

	this->bossSP.setTexture(bossTT);
	this->bodySP.setTexture(bodyTT);
	this->weaponSP.setTexture(weaponTT);

	this->bossSP.setScale(scale);
	this->bodySP.setScale(scale);
	this->weaponSP.setScale(scale);

	int randSide = rand() % 2;
	if (randSide == 0) {
		this->bossSP.setPosition(2000, 400);
		this->bodySP.setPosition(2000, 400);
		this->weaponSP.setPosition(2000, 400);
	}
	else if (randSide == 1) {
		this->bossSP.setPosition(-250, 400);
		this->bodySP.setPosition(-250, 400);
		this->weaponSP.setPosition(-250, 400);
	}
	setTextureRect();

	deathSoundBF.loadFromFile("Audio/bossDeathSound.wav");
	deathSound.setBuffer(deathSoundBF);
	
	font.loadFromFile("Font/PixelFont2.ttf");
	tempDmg.setFont(font);
	tempDmg.setCharacterSize(20);
	tempDmg.setStyle(sf::Text::Bold);
}

void Boss::setModeSideTopMove(const short mode, const short side, const short top, const sf::Vector2f move) {
	this->mode = mode;
	this->side = side;
	this->top = top;
	this->move = move;
}
void Boss::setTextureRect() {
	this->bossSP.setTextureRect(sf::IntRect(left * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
	this->bodySP.setTextureRect(sf::IntRect(left * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
	this->weaponSP.setTextureRect(sf::IntRect(left * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
}

void Boss::bossMove() {
	this->bodySP.move(move * deltaTime.asSeconds());
	this->bossSP.move(move * deltaTime.asSeconds());
	this->weaponSP.move(move * deltaTime.asSeconds());
}

void Boss::setFrame(const short mode) {
	if (this->mode == mode) {
		++left;
		if (left >= maxLeft[top]) {
			left = 0;
			if (this->mode == ATK) {
				setModeSideTopMove(EXP, side, EXPLOSE, { 0.0f, 0.0f });
				cntIsAttack = 0;
				cntHitPlayer = 0;
			}
			else if (this->mode == EXP) {
				if (!isPlayerDied) {
					if (side == RIGHT) setModeSideTopMove(MOVE, side, MOVE_R, { speed, move.y });
					else if (side == LEFT) setModeSideTopMove(MOVE, side, MOVE_L, { -speed, move.y });
				}
				
			}
			else if (this->mode == DEAD) {
				left = maxLeft[top] - 1;
				setModeSideTopMove(MOVE, side, top, { 0.0f, 0.0f });
				isBossDied = true;
			}
		}
	}
	
}

void Boss::chasing() {
	if (side == LEFT) {
		if (bossSP.getPosition().x + 35 * scale.x > playerSP.getPosition().x + (38 + 36) * playerScale.x) {
			setModeSideTopMove(mode, LEFT, MOVE_L, move);
		}
		else if (bossSP.getPosition().x + (35 + 73) * scale.x < playerSP.getPosition().x + 38 * playerScale.x) {
			setModeSideTopMove(mode, RIGHT, MOVE_R, move);
		}
	}
	else if (side == RIGHT) {
		if (bossSP.getPosition().x + 65 * scale.x > playerSP.getPosition().x + (38 + 36) * playerScale.x) {
			setModeSideTopMove(mode, LEFT, MOVE_L, move);
		}
		if (bossSP.getPosition().x + (65 + 73) * scale.x < playerSP.getPosition().x + (38 + 36) * playerScale.x) {
			setModeSideTopMove(mode, RIGHT, MOVE_R, move);
		}
	}

	if (side == LEFT) {
		setModeSideTopMove(mode, side, top, {-speed, move.y});
		if (bossSP.getPosition().x + 35 * scale.x < playerSP.getPosition().x + (38+36)*playerScale.x + 10) {
			setModeSideTopMove(mode, side, top, { 0, move.y });
		}

	}
	else if (side == RIGHT) {
		setModeSideTopMove(mode, side, top, { speed, move.y });
		if (bossSP.getPosition().x + (65 + 73) * scale.x > playerSP.getPosition().x + (38) * playerScale.x - 10) {
			setModeSideTopMove(mode, side, top, { 0, move.y });
		}
	}

	if (side == LEFT) {
		if (playerSP.getPosition().x + (38 + 36) * playerScale.x > bossSP.getPosition().x + (35) * scale.x &&
			playerSP.getPosition().x + (38 + 36) * playerScale.x < bossSP.getPosition().x + (65 + 73) * scale.x) {
			setModeSideTopMove(mode, side, top, { speed, move.y });
		}
	}
	else if (side == RIGHT) {
		if (playerSP.getPosition().x + 38 * playerScale.x > bossSP.getPosition().x + 35 * scale.x &&
			playerSP.getPosition().x + 38 * playerScale.x < bossSP.getPosition().x + (65 + 73) * scale.x) {
			setModeSideTopMove(mode, side, top, { -speed, move.y });
		}
	}

	if (bossSP.getPosition().y  + 64 * scale.y < playerSP.getPosition().y + 8 * playerScale.y -20) {
		setModeSideTopMove(mode, side, top, { move.x, speed });
	}
	else if (bossSP.getPosition().y + 64 * scale.y > playerSP.getPosition().y + 8 * playerScale.y + 20) {
		setModeSideTopMove(mode, side, top, { move.x, -speed });
	}
	else {
		setModeSideTopMove(mode, side, top, { move.x, 0.0f});
	}
	if (move.x == 0 && move.y == 0) {
		++cntIsAttack;
		if (cntIsAttack) {
			isAttack = true;
			if (side == RIGHT) setModeSideTopMove(ATK, side, ATK_R, { 0.0f, 0.0f });
			else if (side == LEFT) setModeSideTopMove(ATK, side, ATK_L, { 0.0f, 0.0f });
		}
	}

}

void Boss::onUpdate() {
	if (isPlayerDied) {
		if (mode == ATK || mode == EXP) {
			if (side == RIGHT) setModeSideTopMove(MOVE, side, MOVE_R, { 0.0f, 0.0f });
			else if (side == LEFT) setModeSideTopMove(MOVE, side, MOVE_L, { 0.0f, 0.0f });
		}
	}

	for (int i = 0; i < dmg.size(); i++) {
		dmg.at(i).first.move(0, -3);
	}
	if (!dmg.empty()) {
		//std::cout << "hello";
		//std::cout << dmg.front().first.getPosition().y;
		if (dmg.front().first.getPosition().y <= dmg.front().second - 150) {
			dmg.pop_front();
		}
	}


	if (isSlowing) {
		slowing.second += deltaTime.asSeconds();
		if (slowing.second >= slowing.first) {
			isSlowing = false;
			curMoveFrameTime = moveFrameTime;
			curAtkFrameTime = atkFrameTime;
			curExpFrameTime = expFrameTime;
			
			if (!isPlayerDied) {
				if (healthBoss <= 500) speed = maxSpeed;
				else speed = defaultSpeed;
				if (side == RIGHT) move.x = speed;
				else if (side == LEFT) move.x = -speed;
			}
			else {
				if (side == RIGHT) setModeSideTopMove(MOVE, side, MOVE_R, { 0.0f, 0.0f });
				else if (side == LEFT) setModeSideTopMove(MOVE, side, MOVE_L, { 0.0f, 0.0f });
			}
			slowing.second = 0;
		}
	}
	if (mode != EXP && mode != ATK && !isPlayerDied && !isBossDied) chasing();

	if (mode == MOVE) {
		cntMoveFrame += deltaTime.asSeconds();
		if (cntMoveFrame >= curMoveFrameTime) {
			setFrame(MOVE);
			cntMoveFrame -= curMoveFrameTime;
		}
	}
	else if (mode == ATK &&!isBossDied && !isPlayerDied ) {
		cntAtkFrame += deltaTime.asSeconds();
		if (cntAtkFrame >= curAtkFrameTime) {
			setFrame(ATK);
			cntAtkFrame -= curAtkFrameTime;
		}
	}
	else if (mode == EXP && !isBossDied && !isPlayerDied) {
		cntExpFrame += deltaTime.asSeconds();
		if (cntExpFrame >= curExpFrameTime) {
			setFrame(EXP);
			cntExpFrame -= curExpFrameTime;
			move = { 0.0f, 0.0f };
		}
	}
	else if (mode == DEAD) {
		cntDead += deltaTime.asSeconds();
		if (cntDead >= deadFrameTime) {
			setFrame(DEAD);
			cntDead -= deadFrameTime;
		}
	}
	setTextureRect();
	bossMove();
	
}

void Boss::draw(sf::RenderWindow& window) {
	sf::Texture outsideHealthBossTT, insideHealthBossTT;
	sf::Sprite outsideHealthBossSP, insideHealthBossSP;

	outsideHealthBossTT.loadFromFile("Sprite/Boss/outsideHealthBoss.png");
	insideHealthBossTT.loadFromFile("Sprite/Boss/insideHealthBoss.png");
	outsideHealthBossSP.setTexture(outsideHealthBossTT);
	insideHealthBossSP.setTexture(insideHealthBossTT);

	outsideHealthBossSP.setOrigin(outsideHealthBossSP.getGlobalBounds().width / 2, outsideHealthBossSP.getGlobalBounds().height / 2);
	if (side == LEFT) outsideHealthBossSP.setPosition(bossSP.getPosition().x + 70 * scale.x, bossSP.getPosition().y + 50 * scale.y);
	else if (side == RIGHT) outsideHealthBossSP.setPosition(bossSP.getPosition().x + 95 * scale.x, bossSP.getPosition().y + 50 * scale.y);
	insideHealthBossSP.setOrigin(insideHealthBossSP.getGlobalBounds().width / 2, insideHealthBossSP.getGlobalBounds().height / 2);
	if (side == LEFT) insideHealthBossSP.setPosition(bossSP.getPosition().x + 70 * scale.x, bossSP.getPosition().y + 50 * scale.y + 0.1);
	else if (side == RIGHT) insideHealthBossSP.setPosition(bossSP.getPosition().x + 95 * scale.x, bossSP.getPosition().y + 50 * scale.y + 0.1);
	
	if (healthBoss <= 500) speed = maxSpeed;
	if (healthBoss > 0) insideHealthBossSP.setTextureRect(sf::IntRect(0, 0, healthBoss / 10, 7));
	else {
		insideHealthBossSP.setTextureRect(sf::IntRect(0, 0, 0, 7));
		healthBoss == 0;
		isBossDied = true;
		if (side == RIGHT) setModeSideTopMove(DEAD, side, DEAD_R, { 0.0f, 0.0f });
		else if (side == LEFT) setModeSideTopMove(DEAD, side, DEAD_L, { 0.0f, 0.0f });
	}

	window.draw(bossSP);
	window.draw(bodySP);
	window.draw(weaponSP);

	// bossBox size(73,87)
	//		x : 35 
	//      y : 62
	/*sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(imageSize));
	rect.setOutlineThickness(-1);
	rect.setOutlineColor(sf::Color::Blue);
	rect.scale(scale);
	if (side == LEFT) rect.setPosition(bossSP.getPosition().x + (35 * scale.x), bossSP.getPosition().y + 62 * scale.y);
	else if (side == RIGHT) rect.setPosition(bossSP.getPosition().x + (65 * scale.x), bossSP.getPosition().y + 62 * scale.y);

	rect.setSize(sf::Vector2f(73, 87));
	rect.setFillColor(sf::Color::Transparent);
	window.draw(rect);*/
	
	if (!isBossDied) {
		window.draw(outsideHealthBossSP);
		window.draw(insideHealthBossSP);
	}
	
	for (int i = 0; i < dmg.size(); i++) window.draw(dmg.at(i).first);
}

void Boss::setHealth(const std::string condition, const short curCombo) {
	if (condition == "PLAYER") {
		if (curCombo == 2 || curCombo == 3) deltaHealthPlayer -= 90;
		else if (curCombo == 4) deltaHealthPlayer -= 1;
	}
	if (condition == "BOSS") {
		if (curCombo == 0 || curCombo == 1) {
			healthBoss -= 15;
			energyRegen += 3;
			deltaScore += (15 * 2);
			dmg.push_back(std::make_pair(tempDmg, bossSP.getPosition().y + imageSize.y / 2 * scale.y));
			dmg.back().first.setString("15");
			dmg.back().first.setPosition(bossSP.getPosition().x + imageSize.x / 2 * scale.x - 20, bossSP.getPosition().y + imageSize.y / 2 * scale.y);
		}
		else if (curCombo == 2 || curCombo == 3) {
			healthBoss -= 30;
			energyRegen += 5;
			deltaScore += (30 * 2);
			dmg.push_back(std::make_pair(tempDmg, bossSP.getPosition().y + imageSize.y / 2 * scale.y));
			dmg.back().first.setString("30");
			dmg.back().first.setPosition(bossSP.getPosition().x + imageSize.x / 2 * scale.x - 20, bossSP.getPosition().y + imageSize.y / 2 * scale.y);
		}
		else if (curCombo == 4 || curCombo == 5) {
			healthBoss -= 65;
			deltaScore += (65 * 2);
			dmg.push_back(std::make_pair(tempDmg, bossSP.getPosition().y + imageSize.y / 2 * scale.y));
			dmg.back().first.setString("65");
			dmg.back().first.setPosition(bossSP.getPosition().x + imageSize.x / 2 * scale.x - 20, bossSP.getPosition().y + imageSize.y / 2 * scale.y);
		}

		if (healthBoss <= 0) {
			if (!isPlayedSound) {
				deathSound.play();
				isPlayedSound = true;
			}
			deltaScore += 100;
			healthBoss = 0;
			isBossDied = true;
			if (side == RIGHT) setModeSideTopMove(DEAD, RIGHT, DEAD_R, { 0.0f, 0.0f });
			else if (side == LEFT) setModeSideTopMove(DEAD, LEFT, DEAD_L, { 0.0f, 0.0f });
			energyRegen += 10;
		}
		else isBossDied = false;
	}
}

void Boss::collision(const std::string condition, const bool isCollided, const short curCombo) {
	if (condition == "BOSS HIT PLAYER") {
		if (isCollided) {
			++cntHitPlayer;
			if (curCombo == 2 || curCombo == 3) {
				if (cntHitPlayer == 1) {
					setHealth("PLAYER", curCombo);
				}
			}
			else if (curCombo == 4) setHealth("PLAYER", curCombo);
		}
		else {
			cntHitPlayer = 0;
		}
	}
	else if (condition == "BOSS GOT BULLET") {
		if (isCollided) {
			setHealth("BOSS", curCombo);
		}
	}

}

void Boss::requestPlayerSprite(const sf::Sprite& playerSP) {
	this->playerSP = playerSP;
}

void Boss::requestPlayerSide(const short playerSide) {
	this->playerSide = playerSide;
}

void Boss::requestPlayerScale(const sf::Vector2f& playerScale) {
	this->playerScale = playerScale;
}

short Boss::updateDeltaHealthPlayer() {
	short tempDeltaHealthPlayer = deltaHealthPlayer;
	deltaHealthPlayer = 0;
	return tempDeltaHealthPlayer;
}

short Boss::updateEnergyPlayer() {
	short tempEnergyRegen = energyRegen;
	energyRegen = 0;
	return tempEnergyRegen;
}

short Boss::updateScore() {
	short tempDeltaScore = deltaScore;
	deltaScore = 0;
	return tempDeltaScore;
}

void Boss::requestIsPlayerDied(const bool isPlayerDied) {
	this->isPlayerDied = isPlayerDied;
}

void Boss::itemAffect(const int itemSelected) {
	if (itemSelected == 1) {  // slowing spell
		isSlowing = true;
		curMoveFrameTime = 0.25f;
		curAtkFrameTime = 0.2f;
		curExpFrameTime = 0.2f;
		if (healthBoss <= 500) speed = defaultSpeed;
		else speed = minSpeed;
		if (side == RIGHT) move.x = speed;
		else if (side == LEFT) move.x = -speed;
	}
	else if (itemSelected == 2) {  // lightning spell
	
			healthBoss -= 20;
			deltaScore += (20 * 2);
			if (healthBoss <= 0) {
				if (!isPlayedSound) {
					deathSound.play();
					isPlayedSound = true;
				}
				healthBoss = 0;
				deltaScore += 100;
				isBossDied = true;
				if (side == RIGHT) setModeSideTopMove(DEAD, RIGHT, DEAD_R, { 0.0f, 0.0f });
				else if (side  == LEFT) setModeSideTopMove(DEAD, LEFT, DEAD_L, { 0.0f, 0.0f });
			}
			else isBossDied = false;
			dmg.push_back(std::make_pair(tempDmg, bossSP.getPosition().y + imageSize.y / 2 * scale.y));
			dmg.back().first.setString("20");
			dmg.back().first.setPosition(bossSP.getPosition().x + imageSize.x / 2 * scale.x - 20, bossSP.getPosition().y + imageSize.y / 2 * scale.y);
	}
}