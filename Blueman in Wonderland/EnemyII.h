#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<set>
#include<sstream>
#include<deque>
class EnemyII
{
private:
	const short MOVE = 0;
	const short ATK = 1;
	const short DEAD = 2;

	const short RIGHT = 1;
	const short LEFT = 0;

	const short MOVE_L = 0;
	const short ATK_L = 1;
	const short ATK_R = 2;
	const short DEAD_L = 3;
	const short DEAD_R = 4;

	const std::string enemyFile = "Sprite/EnemyII/whole.png";
	const std::string bodyFile = "Sprite/EnemyII/body.png";

	sf::Texture enemyTT, bodyTT;
	sf::Sprite enemySP, bodySP;

	short cntPressedNum2 = 0;

	const short maxLane = 3;
	const std::vector<float> spawnPos{ 215 + 33.75 + 190 - 144 - 20, 218.5 + 33.75 + 190 + 33.75 + 190 - 144 - 20 , 218.5 + 33.75 + (190 + 33.75) * 2 + 190 - 144 -20 };

	const short maxTop = 5;
	const std::vector<short> maxLeft{ 4, 4, 4, 4, 4 };

	std::vector<sf::Vector2f> move;
	std::vector<short> mode;
	std::vector<short> side;

	const float defaultSpeed = 80;
	const float minSpeed = 30;
	float speed = defaultSpeed;

	sf::Time deltaTime = sf::seconds(1.0f / 60.0f);

	const float moveFrameTime = 0.15f;
	float cntMoveFrame = 0.0f;
	float curMoveFrameTime = moveFrameTime;

	const float spawnBulletTime = 3.0f;
	std::vector<float> cntSpawnBullet;
	std::vector<bool> isEnemyShot;
	const float delayBulletTime = 2.0f;
	std::vector<float> cntDelayBullet;

	const float atkFrameTime = 0.1f;
	float cntAtkFrame = 0.0f;
	float curAtkFrameTime = atkFrameTime;

	const float deadFrameTime = 0.2f;
	float cntDeadFrame = 0.0f;
	// player sprite
	sf::Sprite playerSP;
	//


	// enemy bulllet
	const std::string bulletFile = "Sprite/enemyII/bullet.png";
	sf::Texture bulletTT;
	const short maxBulletTop = 2;
	const short maxBulletLeft = 4;
	const float defaultBulletSpeed = 250;
	const float minBulletSpeed = 80;
	float bulletSpeed = defaultBulletSpeed;
	const float bulletMoveTime = 0.15f;
	float cntBulletMove = 0.0f;

	std::set<short> indexBulletErase;
	//
	std::set<short> indexEnemyErase;

	// text font
	sf::Font font;


	short energyRegen = 0;
	short healthPlayer = 1000;
	short deltaHealthPlayer = 0;

	std::vector<short> healthEnemyS;

	bool isSlowing = false;
	std::pair<const float, float> slowing{ 5.0f, 0.0f };
	bool isEnemyDied = false;

	bool isHealthMiss = false;
	bool isSetEnemyToMoveAfterPlayerDead = false;

	short deltaScore = 0;

	bool isSpawn = false;

	sf::Text tempDmg;
	std::deque<std::pair<sf::Text, float>> dmg;

private:
	void pushEnemy();
	void popEnemy(const short index);
	void setTextureRect();
	void moveEnemy();
	void setModeSideTopMove(const short mode, const short side, const short top, const sf::Vector2f move, const short index);
	void resetFrameExceptIndex(const short top);
	void setFrame(const short mode);
	bool isOnLane(const short index);
	void checkSide(const short index);
	bool isEnemyOnScreen(const short index);
	void clearEnemy();
	//enemy bullet
	void pushBullet(const short side, const sf::Vector2f enemyPos);
	void popBullet(const short index);
	void moveBullet();
	void setTextureRectBullet();
	void setBulletFrame();
	bool isBulletOnScreen(const short index);
	void clearBullet();
	void setHealth(const std::string condition, const short index, const short curCombo);

public:
	const sf::Vector2i imageSize{ 133, 144 };
	sf::Image enemyIMG, bodyIMG;
	std::vector<sf::Sprite> enemyS, bodyS;

	std::vector<short> top;
	std::vector<std::vector<short>> left;

	// enemy bulllet
	sf::Vector2i bulletImageSize{ 80,144 };
	sf::Image bulletIMG;
	sf::Sprite bulletSP;
	std::vector<sf::Sprite> bulletS;
	std::vector<short> bulletSide;
	std::vector<short> bulletTop;
	std::vector<short> bulletLeft;
	//

	bool isPlayerDied = false;

	bool isEnemyAllDied = false;
	int cntEnemyDead = 0;
	const int maxEnemy = 20;
public:
	EnemyII();
	void onUpdate();
	void draw(sf::RenderWindow& window);

	void requestPlayerSprite(const sf::Sprite& playerSP);

	void collision(const std::string condition, const bool isCollided, const short index, const short curCombo);

	void itemAffect(const int itemSelected);
	short updateScore();
	short updateEnergyPlayer();
	void requestHealthPlayer(const short healthPlayer);
	short updateDeltaHealthPlayer();
	short updateHealthMiss();
	void updateIsPlayerDied(const bool isPlayerDIed);

	void requestSpawn(const bool isSpawn);
};