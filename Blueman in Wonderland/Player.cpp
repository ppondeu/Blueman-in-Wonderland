#include "Player.h"
Player::Player() {
	for (int i = 1; i <= maxTop; i++) left.push_back(0);
	this->playerIMG.loadFromFile(playerFile);
	this->bodyIMG.loadFromFile(bodyFile);
	this->bulletIMG.loadFromFile(bulletFile);
	this->playerTT.loadFromFile(playerFile);
	this->bodyTT.loadFromFile(bodyFile);
	this->bulletTT.loadFromFile(bulletFile);
	this->playerSP.setTexture(playerTT);
	this->bodySP.setTexture(bodyTT);
	this->bulletSP.setTexture(bulletTT);

	this->playerSP.setScale(this->scale);
	this->bodySP.setScale(this->scale);
	this->bulletSP.setScale(this->scale);

	this->playerSP.setPosition(-35*scale.x, 566.5 - (8+18) * scale.y);
	this->bodySP.setPosition(-35*scale.x, 566.5 - (8+18)*scale.y);

	_setTextureRect();

	deathSoundBF.loadFromFile("Audio/playerDeathSound.wav");
	deathSound.setBuffer(deathSoundBF);

	defaultSoundBF.loadFromFile("Audio/bulletSound.wav");
	extraSoundBF.loadFromFile("Audio/extraSound.wav");
	ultSoundBF.loadFromFile("Audio/ultSound.wav");

	defaultSound.setBuffer(defaultSoundBF);
	defaultSound.setVolume(20);
	extraSound.setBuffer(extraSoundBF);
	extraSound.setVolume(70);
	ultSound.setBuffer(ultSoundBF);
	ultSound.setVolume(80);

}

void Player::_setTextureRect() {
	this->playerSP.setTextureRect(sf::IntRect(left[top] * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
	this->bodySP.setTextureRect(sf::IntRect(left[top] * imageSize.x, top * imageSize.y, imageSize.x, imageSize.y));
}

void Player::_move() {
	this->playerSP.move(this->move * deltaTime.asSeconds());
	this->bodySP.move(this->move * deltaTime.asSeconds());
}

void Player::resetFrameExceptIndex(const int top) {
	for (int i = 0; i < this->maxTop; i++) if (i != top) this->left[i] = 0;
}

void Player::setModeSideTop(const int mode, const int side, const int top, const sf::Vector2f move) {
	this->mode = mode;
	this->side = side;
	this->top = top;
	this->move = move;
}

void Player::_setFrame(const int mode) {
	if (mode == this->mode) {
		++this->left[top];
		if (left[top] >= maxLeft[top]) {
			left[top] = 0;
			if (this->mode == ATK) {
				pushBullet(top);

				if (top != ULT_R && top != ULT_L) {
					if (curCombo == ATK_R)
						energyUsed = -3;
					else if (curCombo == EXTRA_ATK_R)
						energyUsed -= 5;
				}
				else {
					energyUsed = -20;
				}


				if (side == RIGHT) setModeSideTop(IDLE, RIGHT, IDLE_R, { 0.0f, 0.0f });
				if (side == LEFT) setModeSideTop(IDLE, LEFT, IDLE_L, { 0.0f, 0.0f });

			}
			else if (this->mode == DEAD) {
				left[top] = maxLeft[top] - 1;
			}
		}

	}

}

void Player::pushBullet(const int top) {
	//bulletSoundS.push_back(bulletSound);
	//bulletSoundS.back().play();
	bulletS.push_back(bulletSP);
	sideBullet.push_back(side);
	if (top == ATK_L || top == ATK_R) {
		bulletSoundS.push_back(defaultSound);
		if (sideBullet.back() == RIGHT) bulletS.back().setPosition(playerSP.getPosition().x + 150, playerSP.getPosition().y - 10);
		else if (sideBullet.back() == LEFT) bulletS.back().setPosition(playerSP.getPosition().x + 100, playerSP.getPosition().y - 10);
	}
	else {
		if (top == EXTRA_ATK_L || top == EXTRA_ATK_R) {
			bulletSoundS.push_back(extraSound);
		}
		else if (top == ULT_L || top == ULT_R) {
			bulletSoundS.push_back(ultSound);
		}
		if (sideBullet.back() == RIGHT) bulletS.back().setPosition(playerSP.getPosition().x + 170, playerSP.getPosition().y - 10);
		else if (sideBullet.back() == LEFT) bulletS.back().setPosition(playerSP.getPosition().x + 80, playerSP.getPosition().y - 10);
	}

	if (side == RIGHT) topBullet.push_back(top - ATK_R);
	if (side == LEFT) topBullet.push_back(top - ATK_R);
	std::vector<int> tmpLeftBullet;
	for (int i = 1; i <= maxBulletTop; i++) tmpLeftBullet.push_back(0);
	leftBullet.push_back(tmpLeftBullet);

	bulletSoundS.back().play();

}

void Player::_popBullet(const int index) {
	
	this->bulletS.erase(bulletS.begin() + index);
	this->sideBullet.erase(sideBullet.begin() + index);
	this->topBullet.erase(topBullet.begin() + index);
	this->leftBullet.erase(leftBullet.begin() + index);
}

void Player::_setTextureRectBullet() {
	for (int i = 0; i < bulletS.size(); i++) {
		this->bulletS[i].setTextureRect(sf::IntRect(leftBullet[i][topBullet[i]] * imageBulletSize.x, topBullet[i] * imageBulletSize.y, imageBulletSize.x, imageBulletSize.y));
	}
}

void Player::_moveBullet() {
	for (int i = 0; i < bulletS.size(); i++) {
		if (this->sideBullet[i] == RIGHT) this->bulletS[i].move(sf::Vector2f{ bulletSpeed * deltaTime.asSeconds(), 0.0f});
		else if (this->sideBullet[i] == LEFT) this->bulletS[i].move(sf::Vector2f{ -bulletSpeed * deltaTime.asSeconds(), 0.0f});
	}
}

void Player::_setBulletFrame() {
	for (int i = 0; i < bulletS.size(); i++) {
		++leftBullet[i][topBullet[i]];
		if (leftBullet[i][topBullet[i]] >= maxBulletFrame[topBullet[i]]) {
			leftBullet[i][topBullet[i]] = 0;
		}
	}
}

bool Player::isBulletOnScreen(sf::Vector2f bulletPos) {
	if (bulletPos.x > 1930) return true;
	if (bulletPos.x < -56) return true;
	return false;
}

void Player::clearBullet() {

	for (auto it = idxErase.begin(); it != idxErase.end(); it++) {
		_popBullet(-1 * *it);
	}
	idxErase.clear();
	for (int i = 0; i < bulletS.size(); i++) {

		if (isBulletOnScreen(bulletS[i].getPosition())) {
			idxErase.insert(-i);
		}
	}
	for (auto it = idxErase.begin(); it != idxErase.end(); it++) {
		_popBullet(-1 * *it);
	}
	idxErase.clear();

	
}
void Player::checkIsPlaySound() {
	if (!bulletSoundS.empty()) {
		if (bulletSoundS.front().getStatus() == 0) bulletSoundS.pop_front();
	}
	
}
bool Player::isPlayerOnScreen() {
	sf::Vector2f playerPos = { playerSP.getPosition().x + 38 * scale.x, playerSP.getPosition().y + 8*scale.y};
	sf::Vector2f playerWidthHeight = { 36 * scale.x , 36 * scale.y};
	if (playerPos.x >= 0 && playerPos.x + playerWidthHeight.x < 1920 && playerPos.y >= 215 && playerPos.y + playerWidthHeight.y < 920) return true;
	return false;
}
void Player::_isKeyPressed() {
	sf::Vector2f playerPos = { playerSP.getPosition().x + 38 * scale.x, playerSP.getPosition().y + 8 * scale.y };
	sf::Vector2f playerWidthHeight = { 36 * scale.x , 36 * scale.y };
	if (isPlayerOnScreen()) {
		if (mode != ATK && !isPlayerDied) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				setModeSideTop(MOVE, RIGHT, MOVE_R, { speed, 0.0f });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				setModeSideTop(MOVE, LEFT, MOVE_L, { -speed, 0.0f });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if (side == RIGHT) setModeSideTop(MOVE, RIGHT, DOWN_R, { 0.0f, verticalSpeed });
				if (side == LEFT) setModeSideTop(MOVE, LEFT, DOWN_L, { 0.0f, verticalSpeed });
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				if (side == RIGHT) setModeSideTop(MOVE, RIGHT, UP_R, { 0.0f, -verticalSpeed });
				if (side == LEFT) setModeSideTop(MOVE, LEFT, UP_L, { 0.0f, -verticalSpeed });
			}
		}
	}
	else {
		if (playerPos.x < 0) {
			playerSP.move(speed * deltaTime.asSeconds(), 0);
			bodySP.move(speed * deltaTime.asSeconds(), 0);
			
		}
		if (playerPos.y < 215) {
			playerSP.move(0, speed * deltaTime.asSeconds());
			bodySP.move(0, speed * deltaTime.asSeconds());
		}
		if (playerPos.y + playerWidthHeight.y > 920) {
			playerSP.move(0, -speed * deltaTime.asSeconds());
			bodySP.move(0, -speed * deltaTime.asSeconds());
		}
		if (playerPos.x + playerWidthHeight.x > 1920) {
			playerSP.move(-speed * deltaTime.asSeconds(), 0);
			bodySP.move(-speed * deltaTime.asSeconds(), 0);
		}
		
	}
	
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		++cntPressedJ;
		if (cntPressedJ == 1) {
			if (curCombo == ATK_R && energyPlayer / 3 > 0) {
				curAtkTime = atkTime;
				if (side == RIGHT) {
					setModeSideTop(ATK, RIGHT, curCombo, { 0.0f, 0.0f });
				}
				if (side == LEFT) {
					setModeSideTop(ATK, LEFT, curCombo + 1, { 0.0f, 0.0f });
				}
			}
			else if (curCombo == EXTRA_ATK_R && energyPlayer / 5 > 0) {
				curAtkTime = extra_atkTime;
				if (side == RIGHT) {
					setModeSideTop(ATK, RIGHT, curCombo, { 0.0f, 0.0f });
				}
				if (side == LEFT) {
					setModeSideTop(ATK, LEFT, curCombo + 1, { 0.0f, 0.0f });
				}
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		++cntPressedK;
		if (cntPressedK == 1) {
			if (energyPlayer / 20 > 0) {
				curAtkTime = ultTime;
				if (side == RIGHT) {
					setModeSideTop(ATK, RIGHT, ultCombo, { 0.0f, 0.0f });
				}
				if (side == LEFT) {
					setModeSideTop(ATK, LEFT, ultCombo + 1, { 0.0f, 0.0f });
				}
			}

		}
	}
}

void Player::onEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyReleased) {
		if (mode != ATK) {
			if (event.key.code == sf::Keyboard::D) {
				setModeSideTop(IDLE, RIGHT, IDLE_R, { 0.0f, 0.0f });
			}
			if (event.key.code == sf::Keyboard::A) {
				setModeSideTop(IDLE, LEFT, IDLE_L, { 0.0f, 0.0f });
			}
			if (event.key.code == sf::Keyboard::S) {
				if (side == RIGHT) setModeSideTop(IDLE, RIGHT, IDLE_R, { 0.0f, 0.0f });
				if (side == LEFT) setModeSideTop(IDLE, LEFT, IDLE_L, { 0.0f, 0.0f });
			}
			if (event.key.code == sf::Keyboard::W) {
				if (side == RIGHT) setModeSideTop(IDLE, RIGHT, IDLE_R, { 0.0f, 0.0f });
				if (side == LEFT) setModeSideTop(IDLE, LEFT, IDLE_L, { 0.0f, 0.0f });
			}
		}


		if (event.key.code == sf::Keyboard::J) {
			cntPressedJ = 0;
		}
		if (event.key.code == sf::Keyboard::K) {
			cntPressedK = 0;
		}
	}
}

void Player::onUpdate() {
	clearBullet();
	checkIsPlaySound();

	if (!isPlayerDied) {
		_isKeyPressed();
		
		if (mode == IDLE) {
			cntIdleTime += this->deltaTime.asSeconds();
			if (cntIdleTime >= idleTime) {
				if (this->mode == IDLE) _setFrame(IDLE);
				cntIdleTime = 0;
			}
		}
		cntBulletSpeedTime += this->deltaTime.asSeconds();
		if (cntBulletSpeedTime >= bulletSpeedTime) {
			if (!bulletS.empty()) {
				_moveBullet();
			}
			cntBulletSpeedTime = 0;
		}

		cntBulletTime += this->deltaTime.asSeconds();
		if (cntBulletTime >= bulletTime) {
			if (!bulletS.empty()) {
				_setBulletFrame();
			}
			cntBulletTime = 0;
		}
		if (mode == ATK) {
			cntAtkTime += this->deltaTime.asSeconds();
			if (cntAtkTime >= curAtkTime) {
				if (this->mode == ATK) _setFrame(ATK);
				cntAtkTime = 0;
			}
		}
		if (isRaze) {
			cntRaze += this->deltaTime.asSeconds();
			if (cntRaze >= razeTime) {
				curCombo = ATK_R;
				isRaze = false;
				cntRaze = 0.0f;
			}
		}

	}
	else {
		cntDeadTime += this->deltaTime.asSeconds();
		if (cntDeadTime >= deadTime) {
			_setFrame(DEAD);
			cntDeadTime = 0;
		}

	}

	_setTextureRect();
	_move();

	if (!bulletS.empty()) _setTextureRectBullet();

}
void Player::_draw(sf::RenderWindow& window) {
	window.draw(playerSP);
	//window.draw(bodySP);
	//window.draw(bulletSP);
	if (!bulletS.empty()) for (int i = 0; i < bulletS.size(); i++) window.draw(bulletS[i]);

	/*sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(imageSize));
	rect.setOutlineThickness(-1);
	rect.setOutlineColor(sf::Color::Red);
	rect.scale(scale);
	rect.setSize(sf::Vector2f(36 , 36));
	rect.setFillColor(sf::Color::Transparent);
	rect.setPosition(playerSP.getPosition().x + 38 * scale.x, playerSP.getPosition().y + 8 * scale.y);
	window.draw(rect);*/

	/*sf::RectangleShape r;
	r.setSize(sf::Vector2f(imageSize));
	r.setOutlineThickness(-1);
	r.setOutlineColor(sf::Color::Red);
	//r.scale(scale);
	r.setSize(sf::Vector2f(1920,1));
	r.setFillColor(sf::Color::Transparent);
	r.setPosition(playerSP.getPosition().x + 38 * scale.x, playerSP.getPosition().y + 8 * scale.y);
	window.draw(r);

	sf::RectangleShape r2;
	r2.setSize(sf::Vector2f(imageSize));
	r2.setOutlineThickness(-1);
	r2.setOutlineColor(sf::Color::Red);
	//r.scale(scale);
	r2.setSize(sf::Vector2f(1920, 1));
	r2.setFillColor(sf::Color::Transparent);
	r2.setPosition(playerSP.getPosition().x + 38 * scale.x, playerSP.getPosition().y + (8+36) * scale.y);
	window.draw(r2);
*/
}

short Player::updateHealthPlayer() {
	short tempHealthRegen = healthRegen;
	healthRegen = 0;
	return tempHealthRegen;
}
short Player::setHealthPlayer() {
	return this->healthPlayer;
}

short Player::updateEnergyPlayer() {
	short tempEnergyUsed = energyUsed;
	energyUsed = 0;
	return tempEnergyUsed;
}
void Player::requestDeltaHealthPlayer(const short deltaHealthPlayer) {
	this->healthPlayer += deltaHealthPlayer;
	if (this->healthPlayer <= 0) {
		deathSound.play();
		this->healthPlayer = 0;
		isPlayerDied = true;
		if (side == RIGHT) setModeSideTop(DEAD, side, DEAD_R, { 0.0f, 0.0f });
		else if (side == LEFT) setModeSideTop(DEAD, side, DEAD_R, { 0.0f, 0.0f });
	}
	else if (this->healthPlayer >= this->maxHealthPlayer) this->healthPlayer = this->maxHealthPlayer;
}

void Player::requestEnergyPlayer(const short energyPlayer) {
	this->energyPlayer = energyPlayer;
}

void Player::_collision(const std::string condition, const bool isCollided, const int index) {
	if (condition == "ENEMY GOT BULLET") {
		if (isCollided) {
			idxErase.insert(-index);
		}
	}
}

void Player::itemAffect(const short itemSelected) {

	if (itemSelected == 0) {
		curCombo = EXTRA_ATK_R;
		isRaze = true;
	}
	else if (itemSelected == 3) {
		this->healthPlayer += 100;
		healthRegen += 100;
		if (this->healthPlayer > this->maxHealthPlayer) this->healthPlayer = this->maxHealthPlayer;
	}

}