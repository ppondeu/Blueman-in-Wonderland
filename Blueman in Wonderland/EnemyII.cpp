#include "EnemyII.h"
EnemyII::EnemyII() {
	this->enemyIMG.loadFromFile(enemyFile);
	this->bodyIMG.loadFromFile(bodyFile);

	this->enemyTT.loadFromFile(enemyFile);
	this->bodyTT.loadFromFile(bodyFile);

	this->enemySP.setTexture(enemyTT);
	this->bodySP.setTexture(bodyTT);

	//bullet
	this->bulletIMG.loadFromFile(bulletFile);
	this->bulletTT.loadFromFile(bulletFile);
	this->bulletSP.setTexture(bulletTT);
	//

	//text font
	font.loadFromFile("Font/PixelFont2.ttf");
	tempDmg.setFont(font);
	tempDmg.setCharacterSize(20);
	tempDmg.setStyle(sf::Text::Bold);
}

void EnemyII::pushEnemy() {
	this->enemyS.push_back(enemySP);
	this->bodyS.push_back(bodySP);

	short tempRandPos = rand() % maxLane;
	this->enemyS.back().setPosition(1920, spawnPos[tempRandPos]);
	this->bodyS.back().setPosition(1920, spawnPos[tempRandPos]);

	std::vector<short> tempLeft;
	for (int i = 0; i < maxTop; i++) tempLeft.push_back(0);
	this->left.push_back(tempLeft);
	this->top.push_back(0);

	this->mode.push_back(MOVE);
	this->side.push_back(LEFT);
	this->move.push_back({ -speed, 0.0f });

	this->cntSpawnBullet.push_back(0.0f);
	this->cntDelayBullet.push_back(0.0f);
	this->isEnemyShot.push_back(false);

	this->healthEnemyS.push_back(80);
}

void EnemyII::popEnemy(const short index) {
	this->enemyS.erase(enemyS.begin() + index);
	this->bodyS.erase(bodyS.begin() + index);

	this->top.erase(top.begin() + index);
	this->left.erase(left.begin() + index);

	this->mode.erase(mode.begin() + index);
	this->side.erase(side.begin() + index);
	this->move.erase(move.begin() + index);

	this->cntSpawnBullet.erase(cntSpawnBullet.begin() + index);

	this->healthEnemyS.erase(healthEnemyS.begin() + index);

}

void EnemyII::setTextureRect() {
	for (int i = 0; i < enemyS.size(); i++) {
		this->enemyS[i].setTextureRect(sf::IntRect(left[i][top[i]] * imageSize.x, top[i] * imageSize.y, imageSize.x, imageSize.y));
		this->bodyS[i].setTextureRect(sf::IntRect(left[i][top[i]] * imageSize.x, top[i] * imageSize.y, imageSize.x, imageSize.y));
	}
}

void EnemyII::moveEnemy() {
	for (int i = 0; i < enemyS.size(); i++) {
		this->enemyS[i].move(move[i] * deltaTime.asSeconds());
		this->bodyS[i].move(move[i] * deltaTime.asSeconds());
	}
}

void EnemyII::setModeSideTopMove(const short mode, const short side, const short top, const sf::Vector2f move, const short index) {
	this->mode[index] = mode;
	this->side[index] = side;
	this->top[index] = top;
	this->move[index] = move;
}

void EnemyII::resetFrameExceptIndex(const short top) {
	for (int i = 0; i < enemyS.size(); i++) {
	}
}


void EnemyII::setFrame(const short mode) {
	for (int i = 0; i < enemyS.size(); i++) {
		if (this->mode[i] == mode) {
			++left[i][top[i]];
			if (left[i][top[i]] >= maxLeft[top[i]]) {
				left[i][top[i]] = 0;

				// set atk to move
				if (this->mode[i] == ATK) {
					setModeSideTopMove(MOVE, LEFT, MOVE_L, { -speed, 0.0f }, i);
				}
				else if (this->mode[i] == DEAD) {
					left[i][top[i]] = maxLeft[top[i]] - 1;
					++cntEnemyDead;
					if (cntEnemyDead == maxEnemy) isEnemyAllDied = true;
					indexEnemyErase.insert(-i);
				}
			}
		}
	}
}

bool EnemyII::isOnLane(const short index) {
	if ((playerSP.getPosition().y + 8 * 3.6 >= enemyS[index].getPosition().y && playerSP.getPosition().y + 8 * 3.6 < enemyS[index].getPosition().y + enemyS[index].getGlobalBounds().height)
		|| (playerSP.getPosition().y + (8 + 36) * 3.6 >= enemyS[index].getPosition().y && playerSP.getPosition().y + (8 + 36) * 3.6 < enemyS[index].getPosition().y + enemyS[index].getGlobalBounds().height)) {
		return true;
	}
	return false;
}

void EnemyII::checkSide(const short index) {
	if (enemyS[index].getPosition().x > playerSP.getPosition().x) {
		setModeSideTopMove(ATK, LEFT, ATK_L, { 0.0f, 0.0f }, index);
	}
	else if (enemyS[index].getPosition().x < playerSP.getPosition().x) {
		setModeSideTopMove(ATK, RIGHT, ATK_R, { 0.0f, 0.0f }, index);
	}
}

void EnemyII::pushBullet(const short side, const sf::Vector2f enemyPos) {
	this->bulletS.push_back(bulletSP);

	if (side == RIGHT) {
		this->bulletSide.push_back(RIGHT);
		this->bulletTop.push_back(0);
		this->bulletS.back().setPosition(enemyPos.x + 120, enemyPos.y + 20);
	}
	else if (side == LEFT) {
		this->bulletSide.push_back(LEFT);
		this->bulletTop.push_back(1);
		this->bulletS.back().setPosition(enemyPos.x - 70, enemyPos.y + 20);
	}
	this->bulletLeft.push_back(0);
	this->bulletS.back().setTextureRect(sf::IntRect(bulletLeft.back() * bulletImageSize.x, bulletTop.back() * bulletImageSize.y, bulletImageSize.x, bulletImageSize.y));
}

void EnemyII::popBullet(const short index) {
	this->bulletS.erase(bulletS.begin() + index);
	this->bulletSide.erase(bulletSide.begin() + index);
	this->bulletTop.erase(bulletTop.begin() + index);
	this->bulletLeft.erase(bulletLeft.begin() + index);
}

void EnemyII::setBulletFrame() {
	for (int i = 0; i < bulletS.size(); i++) {
		++bulletLeft[i];
		if (bulletLeft[i] >= maxBulletLeft) {
			bulletLeft[i] = 0;
		}
	}
}

void EnemyII::setTextureRectBullet() {
	for (int i = 0; i < bulletS.size(); i++) {
		this->bulletS[i].setTextureRect(sf::IntRect(bulletLeft[i] * bulletImageSize.x, bulletTop[i] * bulletImageSize.y, bulletImageSize.x, bulletImageSize.y));
	}
}

void EnemyII::moveBullet() {
	for (int i = 0; i < bulletS.size(); i++) {
		if (bulletSide[i] == LEFT) this->bulletS[i].move({ -bulletSpeed * deltaTime.asSeconds(), 0.0f });
		else if (bulletSide[i] == RIGHT) this->bulletS[i].move({ bulletSpeed * deltaTime.asSeconds(), 0.0f });
	}
}

bool EnemyII::isEnemyOnScreen(const short index) {
	if (enemyS[index].getPosition().x < -133) {
		isHealthMiss = true;
		return false;
	}
	return true;
}

void EnemyII::clearEnemy() {
	//---------------------clear enemy dead --------------------------------------
	for (auto it = indexEnemyErase.begin(); it != indexEnemyErase.end(); ++it) {
		popEnemy(*it * -1);
	}
	if (!indexEnemyErase.empty()) indexEnemyErase.clear();
	//--------------------clear enemy off screen --------------------------
	for (int i = 0; i < enemyS.size(); ++i) {
		if (!isEnemyOnScreen(i)) {
			++cntEnemyDead;
			if (cntEnemyDead == maxEnemy) isEnemyAllDied = true;
			//std::cout << "EYESABER : EVENT " << cntEnemyDead << std::endl;
			indexEnemyErase.insert(-i);
		}
	}
	for (auto it = indexEnemyErase.begin(); it != indexEnemyErase.end(); ++it) {
		popEnemy(*it * -1);
	}
	if (!indexEnemyErase.empty()) indexEnemyErase.clear();
	//-----------------------------------------------------------------------------
}

bool EnemyII::isBulletOnScreen(const short index) {
	if (bulletS[index].getPosition().x < -80 || bulletS[index].getPosition().x >= 1920) {
		return false;
	}
	return true;
}

void EnemyII::clearBullet() {
	//---------------------clear bullet collide --------------------------------------
	for (auto it = indexBulletErase.begin(); it != indexBulletErase.end(); ++it) {
		popBullet(*it * -1);
	}
	if (!indexBulletErase.empty()) indexBulletErase.clear();
	//--------------------clear bullet off screen --------------------------
	for (int i = 0; i < bulletS.size(); ++i) {
		if (!isBulletOnScreen(i)) indexBulletErase.insert(-i);
	}
	for (auto it = indexBulletErase.begin(); it != indexBulletErase.end(); ++it) {
		popBullet(*it * -1);
	}
	if (!indexBulletErase.empty()) indexBulletErase.clear();
	//-----------------------------------------------------------------------------
}

void EnemyII::onUpdate() {

	clearEnemy();
	clearBullet();

	for (int i = 0; i < dmg.size(); i++) dmg.at(i).first.move(0, -3);
	if (!dmg.empty()) {
		//std::cout << "hello";
		//std::cout << dmg.front().first.getPosition().y;
		if (dmg.front().first.getPosition().y <= dmg.front().second - 150) {
			dmg.pop_front();
		}
	}

	if (isSpawn) {
		pushEnemy();
		isSpawn = false;
	}
	if (isSlowing) {
		slowing.second += deltaTime.asSeconds();
		if (slowing.second >= slowing.first) {
			// reset to default
			isSlowing = false;
			curMoveFrameTime = moveFrameTime;
			curAtkFrameTime = atkFrameTime;
			bulletSpeed = defaultBulletSpeed;
			speed = defaultSpeed;
			slowing.second = 0;
		}
	}
	cntMoveFrame += deltaTime.asSeconds();
	if (cntMoveFrame >= curMoveFrameTime) {
		setFrame(MOVE);
		cntMoveFrame -= curMoveFrameTime;
	}

	cntAtkFrame += deltaTime.asSeconds();
	if (cntAtkFrame >= curAtkFrameTime) {
		setFrame(ATK);
		cntAtkFrame -= curAtkFrameTime;
	}

	if (!bulletS.empty()) {
		cntBulletMove += deltaTime.asSeconds();
		if (cntBulletMove >= bulletMoveTime) {
			setBulletFrame();
			cntBulletMove -= bulletMoveTime;
		}
	}
	cntDeadFrame += deltaTime.asSeconds();
	if (cntDeadFrame >= deadFrameTime) {
		setFrame(DEAD);
		cntDeadFrame -= deadFrameTime;
	}

	if (!isPlayerDied) {
		short check = 0;
		for (int i = 0; i < enemyS.size(); i++) {
			if (mode[i] != DEAD) {
				if (isEnemyShot[i] && isOnLane(i)) {
					checkSide(i);
					//push bullet
					pushBullet(side[i], enemyS[i].getPosition());
					isEnemyShot[i] = false;
				}
				if ((!isOnLane(i) || check == 1) && !isEnemyShot[i]) {
					check = 1;
					cntSpawnBullet[i] = 0;
					cntDelayBullet[i] += deltaTime.asSeconds();
					if (cntDelayBullet[i] >= delayBulletTime) {
						isEnemyShot[i] = true;
						check = 0;
						cntDelayBullet[i] -= delayBulletTime;
					}
				}
				else if (isOnLane(i)) {
					cntSpawnBullet[i] += deltaTime.asSeconds();
					if (cntSpawnBullet[i] >= spawnBulletTime) {
						isEnemyShot[i] = true;
						cntSpawnBullet[i] -= spawnBulletTime;
					}
				}
			}
		}
	}

	setTextureRect();
	moveEnemy();

	setTextureRectBullet();
	moveBullet();
	
}
void EnemyII::draw(sf::RenderWindow& window) {
	for (int i = 0; i < enemyS.size(); i++) {
		window.draw(bodyS[i]);
		window.draw(enemyS[i]);
	}
	for (int i = 0; i < bulletS.size(); i++) {
		window.draw(bulletS[i]);
	}
	for (int i = 0; i < dmg.size(); i++) {
		window.draw(dmg.at(i).first);
	}
	
}

void EnemyII::requestPlayerSprite(const sf::Sprite& playerSP) {
	this->playerSP = playerSP;
}

void EnemyII::setHealth(const std::string condition, const short index, const short curCombo) {
	if (condition == "PLAYER") {
		deltaHealthPlayer -= 20;
	}
	else if (condition == "ENEMY") {
		if (curCombo == 0 || curCombo == 1) {
			healthEnemyS[index] -= 15;
			energyRegen += 2;
			deltaScore += (15 * 1.2);
			dmg.push_back(std::make_pair(tempDmg, enemyS[index].getPosition().y + imageSize.y / 2));
			dmg.back().first.setString("15");
			dmg.back().first.setPosition(enemyS[index].getPosition().x + imageSize.x / 2 - 20, enemyS[index].getPosition().y + imageSize.y / 2);
		}
		else if (curCombo == 2 || curCombo == 3) {
			healthEnemyS[index] -= 30;
			energyRegen += 3;
			deltaScore += (30 * 1.2);
			dmg.push_back(std::make_pair(tempDmg, enemyS[index].getPosition().y + imageSize.y / 2));
			dmg.back().first.setString("30");
			dmg.back().first.setPosition(enemyS[index].getPosition().x + imageSize.x / 2 - 20, enemyS[index].getPosition().y + imageSize.y / 2);
		}
		else if (curCombo == 4 || curCombo == 5) {
			healthEnemyS[index] -= 65;
			deltaScore += (65 * 1.2);
			dmg.push_back(std::make_pair(tempDmg, enemyS[index].getPosition().y + imageSize.y / 2));
			dmg.back().first.setString("65");
			dmg.back().first.setPosition(enemyS[index].getPosition().x + imageSize.x / 2 - 20, enemyS[index].getPosition().y + imageSize.y / 2);
		}

		if (healthEnemyS[index] <= 0) {
			//std::cout << "EYESABER : EVENT " << cntEnemyDead << std::endl;
			healthEnemyS[index] = 0;
			deltaScore += 30;
			isEnemyDied = true;
			if (side[index] == RIGHT) setModeSideTopMove(DEAD, RIGHT, DEAD_R, { 0.0f, 0.0f }, index);
			else if (side[index] == LEFT) setModeSideTopMove(DEAD, LEFT, DEAD_L, { 0.0f, 0.0f }, index);
			energyRegen += 10;
		}
		else isEnemyDied = false;
	}
}
void EnemyII::collision(const std::string condition, const bool isCollided, const short index, const short curCombo){
	if (condition == "ENEMY GOT BULLET") {
		if (isCollided) {
			setHealth("ENEMY", index, curCombo);
		}
	}
	else if (condition == "PLAYER GOT BULLET") {
		if (isCollided) {
			indexBulletErase.insert(-index);
			setHealth("PLAYER", index, curCombo);
		}
	}
}

void EnemyII::itemAffect(const int itemSelected) {
	if (itemSelected == 1) {  // slowing spell
		isSlowing = true;
		curMoveFrameTime = 0.25f;
		curAtkFrameTime = 0.2f;
		bulletSpeed = minBulletSpeed;
		speed = minSpeed;

		for (int i = 0; i < enemyS.size(); i++) {
			if (mode[i] == MOVE) {
				move[i] = { -speed, 0.0f };
			}
		}
	}
	else if (itemSelected == 2) {  // lightning spell
		for (int i = 0; i < healthEnemyS.size(); i++) {
			healthEnemyS[i] -= 20;
			deltaScore += (20 * 1.2);
			if (healthEnemyS[i] <= 0) {
				//std::cout << "EYESABER : EVENT " << cntEnemyDead << std::endl;
				healthEnemyS[i] = 0;
				deltaScore += 30;
				isEnemyDied = true;
				if (side[i] == RIGHT) {
					setModeSideTopMove(DEAD, RIGHT, DEAD_R, { 0.0f, 0.0f }, i);
				}
				else if (side[i] == LEFT) {
					setModeSideTopMove(DEAD, LEFT, DEAD_L, { 0.0f, 0.0f }, i);
				}
			}
			else isEnemyDied = false;
			for (int index = 0; index < enemyS.size(); index++) {
				dmg.push_back(std::make_pair(tempDmg, enemyS[index].getPosition().y + imageSize.y / 2));
				dmg.back().first.setString("20");
				dmg.back().first.setPosition(enemyS[index].getPosition().x + imageSize.x / 2 - 20, enemyS[index].getPosition().y + imageSize.y / 2);
				dmg.back().first.setStyle(sf::Text::Bold);
			}
		}
	}
}

short EnemyII::updateScore() {
	short tempDeltaScore = deltaScore;
	deltaScore = 0;
	return tempDeltaScore;
}

short EnemyII::updateEnergyPlayer() {
	short tempEnergyRegen = energyRegen;
	energyRegen = 0;
	return tempEnergyRegen;
}

void EnemyII::requestHealthPlayer(const short healthPlayer) {
	this->healthPlayer = healthPlayer;
}

short EnemyII::updateDeltaHealthPlayer() {
	short tempDeltaHealthPlayer = deltaHealthPlayer;
	deltaHealthPlayer = 0;
	return tempDeltaHealthPlayer;
}
short EnemyII::updateHealthMiss() {
	short tempHealthMiss = static_cast<short>(isHealthMiss);
	isHealthMiss = false;
	return tempHealthMiss;
}

void EnemyII::updateIsPlayerDied(const bool isPlayerDied) {
	this->isPlayerDied = isPlayerDied;
}

void EnemyII::requestSpawn(const bool isSpawn) {
	this->isSpawn = isSpawn;
}