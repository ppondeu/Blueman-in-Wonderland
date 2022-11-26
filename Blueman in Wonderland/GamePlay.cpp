#include "GamePlay.h"

GamePlay::GamePlay() {
	golaMoska->requestPlayerSide(modelX->side);
	golaMoska->requestPlayerScale(modelX->scale);
}

GamePlay::~GamePlay() {
	delete gui;
	delete item;
	delete modelX;
	delete golaMoska;
	delete skeleton;
	delete eyeSaber;
	delete buffaRed;

	

}
bool GamePlay::PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b, const sf::Image& imgA, const sf::Image& imgB, int topA, int leftA, int topB, int leftB, sf::Vector2i sizeA, sf::Vector2i sizeB) {

	const sf::Transform& TransformA(a.getInverseTransform());
	const sf::Transform& TransformB(b.getInverseTransform());

	sf::FloatRect intersection;
	if (a.getGlobalBounds().intersects(static_cast<sf::FloatRect>(b.getGlobalBounds()), intersection)) {

		sf::Vector2f vecA, vecB;
		sf::Vector2f begin, end;
		begin = { intersection.left, intersection.top };
		end = { begin.x + intersection.width, begin.y + intersection.height };

		for (int i = begin.x; i < end.x; i++) {
			for (int j = begin.y; j < end.y; j++) {
				vecA = TransformA.transformPoint(static_cast<float>(i), static_cast<float>(j));
				vecB = TransformB.transformPoint(static_cast<float>(i), static_cast<float>(j));
				vecA.x += (sizeA.x * leftA);
				vecA.y += (sizeA.y * topA);
				vecB.x += (sizeB.x * leftB);
				vecB.y += (sizeB.y * topB);
				if ((int)imgA.getPixel(vecA.x, vecA.y).a > 0 && (int)imgB.getPixel(vecB.x, vecB.y).a > 0) {
					return true;
				}
			}
		}
	}

	return false;
}

void GamePlay::beforeOnEvent() {
	
	skeleton->updateIsPlayerDied(modelX->isPlayerDied);
	buffaRed->updateIsPlayerDied(modelX->isPlayerDied);
	eyeSaber->updateIsPlayerDied(modelX->isPlayerDied);
	if (skeleton->isEnemyAllDied == true && eyeSaber->isEnemyAllDied == true && buffaRed->isEnemyAllDied == true) {
		golaMoska->requestIsPlayerDied(modelX->isPlayerDied);
		golaMoska->requestPlayerSprite(modelX->playerSP);
	}
	skeleton->requestPlayerSprite(modelX->playerSP);
	buffaRed->requestPlayerSprite(modelX->playerSP);
	eyeSaber->requestPlayerSprite(modelX->playerSP);
}
void GamePlay::onEvent(const sf::Event& event) {
	item->onEvent(event);
	if(gameOverCheck == 0 ) modelX->onEvent(event);
}

void GamePlay::afterOnEvent() {

	// spawn 

	if (isSpawn[0] == true || isSpawn[1] == true || isSpawn[2] == true) {
		cntDelay += deltaTime.asSeconds();
		if (cntDelay >= delay) {
			int randType = rand() % 3;
			while (isSpawn[randType] == false) {
				randType = rand() % 3;
			}
			++cntPlayer;
			//std::cout << randType << " " << cntPlayer << std::endl;
			if (randType == 0 && isSpawn[0]){
				++a;
				if (a == 25) {
					isSpawn[0] = false;
				}
				skeleton->requestSpawn(true);
				eyeSaber->requestSpawn(false);
				buffaRed->requestSpawn(false);
				
			}
			else if (randType == 1 && isSpawn[1]) {
				++b;
				if (b == 20) isSpawn[1] = false;
				eyeSaber->requestSpawn(true);
				buffaRed->requestSpawn(false);
				skeleton->requestSpawn(false);
			}
			else if (randType == 2 && isSpawn[2]) {
				++c;
				if (c == 15) isSpawn[2] = false;
				buffaRed->requestSpawn(true);
				eyeSaber->requestSpawn(false);
				skeleton->requestSpawn(false);
			}
			//std::cout << a << " " << b << " " << c << std::endl;
			if (cntPlayer == 20) delay = 2.5f;
			else if (cntPlayer == 40) delay = 2.0f;

			cntDelay = 0;
			
		}
		
		
	}

	gui->requestAmountEnemySpawn(cntPlayer);

	//item selected
	short tempItemSelected = item->getItemSelected();
	item->resetItemSelected();

	if (tempItemSelected != 666 && gameOverCheck == 0) {
		if (tempItemSelected == 0 || tempItemSelected == 3) { // item for players
			modelX->itemAffect(tempItemSelected);
		}
		else if (tempItemSelected == 1 || tempItemSelected == 2) { // item for enemies
			skeleton->itemAffect(tempItemSelected);
			gui->requestScore(skeleton->updateScore());

			buffaRed->itemAffect(tempItemSelected);
			gui->requestScore(buffaRed->updateScore());

			eyeSaber->itemAffect(tempItemSelected);
			gui->requestScore(eyeSaber->updateScore());

			if (skeleton->isEnemyAllDied == true && eyeSaber->isEnemyAllDied == true && buffaRed->isEnemyAllDied == true) {
				golaMoska->itemAffect(tempItemSelected);
				gui->requestScore(golaMoska->updateScore());
			}

		}
	}
	//

	if (gameOverCheck == 0) {

		// Item collision
		if (PixelPerfectCollision(modelX->playerSP, item->itemSP, modelX->playerIMG, item->itemIMG,
			modelX->top, modelX->left[modelX->top], 0, item->currentItem, modelX->imageSize, item->imageSize)) {
			item->collision(true);
		}
		else item->collision(false);
		//


		if (skeleton->isEnemyAllDied == true && eyeSaber->isEnemyAllDied == true && buffaRed->isEnemyAllDied == true) {
			if (!modelX->isPlayerDied) {
				if (PixelPerfectCollision(modelX->bodySP, golaMoska->weaponSP, modelX->bodyIMG, golaMoska->weaponIMG, modelX->top, modelX->left[golaMoska->top],
					golaMoska->top, golaMoska->left, modelX->imageSize, golaMoska->imageSize)) {
					// collided
					golaMoska->collision("BOSS HIT PLAYER", true, golaMoska->top);
					modelX->requestDeltaHealthPlayer(golaMoska->updateDeltaHealthPlayer());
				}
				else {
					golaMoska->collision("BOSS HIT PLAYER", false, golaMoska->top);
				}
			}
			for (int i = 0; i < modelX->bulletS.size(); i++) {
				int curVal, lastVal = -666;
				if (golaMoska->healthBoss > 0) {
					if (PixelPerfectCollision(modelX->bulletS[i], golaMoska->bodySP, modelX->bulletIMG, golaMoska->bodyIMG,
						modelX->topBullet[i], modelX->leftBullet[i][modelX->topBullet[i]], golaMoska->top, golaMoska->left,
						modelX->imageBulletSize, golaMoska->imageSize)) {
						golaMoska->collision("BOSS GOT BULLET", true, modelX->topBullet[i]);
						gui->requestScore(static_cast<short>(golaMoska->updateScore()));
						curVal = i;
						if (curVal != lastVal) modelX->_collision("ENEMY GOT BULLET", true, i);
						//break;
						lastVal = curVal;
					}
					else {
						golaMoska->collision("BOSS GOT BULLET", false, NULL);
					}
				}
			}
		}

		//PlayerII V EnemieI
		if (!modelX->isPlayerDied) {
			for (int i = 0; i < skeleton->enemyS.size(); i++) {
				if (skeleton->healthEnemyS[i] > 0) {
					if (PixelPerfectCollision(modelX->playerSP, skeleton->enemyS[i], modelX->playerIMG, skeleton->enemyIMG,
						modelX->top, modelX->left[modelX->top], skeleton->top[i], skeleton->left[i][skeleton->top[i]],
						modelX->imageSize, skeleton->imageSize)) {
						skeleton->_collision("PLAYER V ENEMY", true, i, NULL);
					}
					else {
						skeleton->_collision("PLAYER V ENEMY", false, i, NULL);
					}

					if (PixelPerfectCollision(modelX->bodySP, skeleton->weaponS[i], modelX->bodyIMG, skeleton->weaponIMG,
						modelX->top, modelX->left[modelX->top], skeleton->top[i], skeleton->left[i][skeleton->top[i]],
						modelX->imageSize, skeleton->imageSize)) {
						skeleton->_collision("ENEMY HIT PLAYER", true, i, NULL);

						//update Health Player
						modelX->requestDeltaHealthPlayer(skeleton->updateHealthPlayer());
						gui->requestHealthPlayer(modelX->setHealthPlayer());

						//


					}
					else {
						skeleton->_collision("ENEMY HIT PLAYER", false, i, NULL);
					}
				}
			}
		}

		for (int i = 0; i < modelX->bulletS.size(); i++) {
			int curVal, lastVal = -666;
			for (int j = 0; j < skeleton->enemyS.size(); j++) {
				if (skeleton->healthEnemyS[j] > 0) {
					if (PixelPerfectCollision(modelX->bulletS[i], skeleton->bodyS[j], modelX->bulletIMG, skeleton->bodyIMG,
						modelX->topBullet[i], modelX->leftBullet[i][modelX->topBullet[i]], skeleton->top[j], skeleton->left[j][skeleton->top[j]],
						modelX->imageBulletSize, skeleton->imageSize)) {
						skeleton->_collision("ENEMY GOT BULLET", true, j, modelX->topBullet[i]);
						gui->requestScore(static_cast<short>(skeleton->updateScore()));
						curVal = i;
						if (curVal != lastVal) modelX->_collision("ENEMY GOT BULLET", true, i);
						//break;
						lastVal = curVal;
					}
					else {
						skeleton->_collision("ENEMY GOT BULLET", false, j, NULL);
					}
				}

			}
		}
		//-----------------------------------------------------------------------------------------------------------------
		if (!modelX->isPlayerDied) {
			for (int i = 0; i < buffaRed->enemyS.size(); i++) {
				if (buffaRed->healthEnemyS[i] > 0) {
					if (PixelPerfectCollision(modelX->playerSP, buffaRed->enemyS[i], modelX->playerIMG, buffaRed->enemyIMG,
						modelX->top, modelX->left[modelX->top], buffaRed->top[i], buffaRed->left[i][buffaRed->top[i]],
						modelX->imageSize, buffaRed->imageSize)) {
						buffaRed->_collision("PLAYER V ENEMY", true, i, NULL);
					}
					else {
						buffaRed->_collision("PLAYER V ENEMY", false, i, NULL);
					}

					if (PixelPerfectCollision(modelX->bodySP, buffaRed->weaponS[i], modelX->bodyIMG, buffaRed->weaponIMG,
						modelX->top, modelX->left[modelX->top], buffaRed->top[i], buffaRed->left[i][buffaRed->top[i]],
						modelX->imageSize, buffaRed->imageSize)) {
						buffaRed->_collision("ENEMY HIT PLAYER", true, i, NULL);

						//update health player
						modelX->requestDeltaHealthPlayer(buffaRed->updateHealthPlayer());
						gui->requestHealthPlayer(modelX->setHealthPlayer());

						//


					}
					else {
						buffaRed->_collision("ENEMY HIT PLAYER", false, i, NULL);
					}
				}

			}
		}

		for (int i = 0; i < modelX->bulletS.size(); i++) {
			int curVal, lastVal = -666;
			for (int j = 0; j < buffaRed->enemyS.size(); j++) {

				if (buffaRed->healthEnemyS[j] > 0) {
					if (PixelPerfectCollision(modelX->bulletS[i], buffaRed->bodyS[j], modelX->bulletIMG, buffaRed->bodyIMG,
						modelX->topBullet[i], modelX->leftBullet[i][modelX->topBullet[i]], buffaRed->top[j], buffaRed->left[j][buffaRed->top[j]],
						modelX->imageBulletSize, buffaRed->imageSize)) {
						buffaRed->_collision("ENEMY GOT BULLET", true, j, modelX->topBullet[i]);
						gui->requestScore(static_cast<short>(buffaRed->updateScore()));
						curVal = i;
						if (curVal != lastVal) modelX->_collision("ENEMY GOT BULLET", true, i);
						//break;
						lastVal = curVal;
					}
					else {
						buffaRed->_collision("GOT BULLET", false, j, NULL);
					}
				}

			}
		}

		// playerII v enemyII
		for (int i = 0; i < modelX->bulletS.size(); i++) {
			int curVal, lastVal = -666;
			for (int j = 0; j < eyeSaber->enemyS.size(); j++) {
				if (PixelPerfectCollision(modelX->bulletS[i], eyeSaber->bodyS[j], modelX->bulletIMG, eyeSaber->bodyIMG,
					modelX->topBullet[i], modelX->leftBullet[i][modelX->topBullet[i]], eyeSaber->top[j], eyeSaber->left[j][eyeSaber->top[j]],
					modelX->imageBulletSize, eyeSaber->imageSize)) {
					eyeSaber->collision("ENEMY GOT BULLET", true, j, modelX->topBullet[i]);
					gui->requestScore(static_cast<short>(eyeSaber->updateScore()));
					curVal = i;
					if (curVal != lastVal) modelX->_collision("ENEMY GOT BULLET", true, i);
					//break;
					lastVal = curVal;
				}
			}
		}
		if (!modelX->isPlayerDied) {
			for (int i = 0; i < eyeSaber->bulletS.size(); i++) {
				if (PixelPerfectCollision(modelX->bodySP, eyeSaber->bulletS[i], modelX->bodyIMG, eyeSaber->bulletIMG,
					modelX->top, modelX->left[modelX->top], eyeSaber->bulletTop[i], eyeSaber->bulletLeft[i],
					modelX->imageSize, eyeSaber->bulletImageSize)) {
					// collided
					eyeSaber->collision("PLAYER GOT BULLET", true, i, NULL);

					// update health player
					modelX->requestDeltaHealthPlayer(eyeSaber->updateDeltaHealthPlayer());
					gui->requestHealthPlayer(modelX->setHealthPlayer());
				}
			}
		}


		modelX->requestEnergyPlayer(gui->updateEnergyPlayer());
		gui->requestEnergyPlayer(modelX->updateEnergyPlayer());
		if (skeleton->isEnemyAllDied == true && eyeSaber->isEnemyAllDied == true && buffaRed->isEnemyAllDied == true) gui->requestEnergyPlayer(golaMoska->updateEnergyPlayer());
		gui->requestEnergyPlayer(skeleton->updateEnergyPlayer());
		gui->requestEnergyPlayer(buffaRed->updateEnergyPlayer());
		gui->requestEnergyPlayer(eyeSaber->updateEnergyPlayer());



		gui->requestHealthPlayer(modelX->setHealthPlayer());

		// update health miss
		gui->requestHealthMiss(static_cast<int>(skeleton->updateHealthMiss()));
		gui->requestHealthMiss(static_cast<int>(buffaRed->updateHealthMiss()));
		gui->requestHealthMiss(static_cast<int>(eyeSaber->updateHealthMiss()));

	}


}
void GamePlay::onUpdate() {

	
	if (modelX->isPlayerDied || gui->healthMiss <= 0) {
		++gameOverCheck;
		cntAfterGame += deltaTime.asSeconds();
		if (gameOverCheck >= 2) {
			if (cntAfterGame >= afterGameDelay) {
				isSwitchState = true;
				cntAfterGame = 0;
			}
			if(isSwitchState) isVictory = 0;
		}
		// go to game over state : you died!

	}
	else if (golaMoska->isBossDied) {
		// go to game over state : you win!
		++gameOverCheck;
		cntAfterGame += deltaTime.asSeconds();
		if (gameOverCheck >= 2) {
			if (cntAfterGame >= afterGameDelay) {
				isSwitchState = true;
				cntAfterGame = 0;
			}
			if (isSwitchState) isVictory = 1;
		}
	}

	gui->onUpdate();
	item->onUpdate();
	modelX->onUpdate();
	
	if (skeleton->isEnemyAllDied == true && eyeSaber->isEnemyAllDied == true && buffaRed->isEnemyAllDied == true)  golaMoska->onUpdate();
	skeleton->onUpdate();
	eyeSaber->onUpdate();
	buffaRed->onUpdate();


}
void GamePlay::draw(sf::RenderWindow& window) {
	gui->_draw(window);
	item->_draw(window);
	modelX->_draw(window);
	golaMoska->draw(window);
	skeleton->_draw(window);
	eyeSaber->draw(window);
	buffaRed->_draw(window);

}

bool GamePlay::isStopPlaySound() {
	if (gameOverCheck > 1) return true;
	return false;
}