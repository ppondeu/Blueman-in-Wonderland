#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<sstream>
#include<set>
#include<vector>
#include<deque>

class Boss
{
private:
	const short MOVE = 0;
	const short ATK = 1;
	const short EXP = 2;
	const short DEAD = 3;

	const short RIGHT = 0;
	const short LEFT = 1;

	const short MOVE_R = 0;
	const short MOVE_L = 1;
	const short ATK_R = 2;
	const short ATK_L = 3;
	const short EXPLOSE = 4;
	const short DEAD_R = 5;
	const short DEAD_L = 6;

	sf::Time deltaTime = sf::seconds(1.0f / 60.0f);

	sf::Vector2f scale{1.7, 1.7};

	const std::string bossFile = "Sprite/Boss/whole.png";
	const std::string bodyFile = "Sprite/Boss/body.png";
	const std::string weaponFile = "Sprite/Boss/weapon.png";

	sf::Texture bossTT, bodyTT, weaponTT;

	short mode = MOVE;
	short side = LEFT;
	const float defaultSpeed = 350;
	const float minSpeed = 300;
	const float maxSpeed = 400;
	float speed = defaultSpeed;
	sf::Vector2f move{ -speed, 0.0f };
	
	const float moveFrameTime = 0.15f;
	float curMoveFrameTime = moveFrameTime;
	float cntMoveFrame = 0.0f;

	const float atkFrameTime = 0.08f;
	float curAtkFrameTime = atkFrameTime;
	float cntAtkFrame = 0.0f;

	const float expFrameTime = 0.1f;
	float curExpFrameTime = expFrameTime;
	float cntExpFrame = 0.0f;


	const float deadFrameTime = 0.2f;
	float cntDead = 0.0f;

	// player sprite
	sf::Sprite playerSP;
	short playerSide;
	sf::Vector2f playerScale;
	//

	bool isAttack = false;
	short cntIsAttack = 0;

	bool isExplose = false;


	short cntHitPlayer = 0;

	short energyRegen = 0;
	short deltaHealthPlayer = 0;

	bool isSlowing = false;
	std::pair<const float, float> slowing{ 5.0f,0.0f };

	short deltaScore = 0;

	sf::SoundBuffer deathSoundBF;
	sf::Sound deathSound;

	bool isPlayedSound = false;

	sf::Font font;
	sf::Text tempDmg;
	std::deque<std::pair<sf::Text, float>> dmg;
	
private:
	void setModeSideTopMove(const short mode, const short side, const short top, const sf::Vector2f move);
	void setTextureRect();
	void setFrame(const short mode);
	void bossMove();
	void chasing();
public:
	sf::Vector2i imageSize{ 172, 180 };
	sf::Image bossIMG, bodyIMG, weaponIMG;
	sf::Sprite bossSP, bodySP, weaponSP;
	const short maxTop = 7;
	const std::vector<short> maxLeft{3,3,10,10,10,5,5};
	short top = 1;
	short left = 0;

	bool isBossDied = false;
	bool isPlayerDied = false;

	// health boss
	short healthBoss = 1000;
	//
public:
	Boss();
	void onUpdate();
	void draw(sf::RenderWindow& window);
	void setHealth(const std::string condition, const short curCombo);
	void collision(const std::string condition, const bool isCollided, const short curCombo);
	void requestPlayerSprite(const sf::Sprite& playerSP);
	void requestPlayerSide(const short playerSide);
	void requestPlayerScale(const sf::Vector2f& playerScale);
	short updateDeltaHealthPlayer();
	short updateEnergyPlayer();
	short updateScore();
	void requestIsPlayerDied(const bool isPlayerDied);
	void itemAffect(const int itemSelected);
};