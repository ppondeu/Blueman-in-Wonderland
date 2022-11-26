#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<sstream>
#include<queue>
#include<set>
#include<SFML/Audio.hpp>
class Player
{
private:
	const int RIGHT = 0;
	const int LEFT = 1;

	const int IDLE = 0;
	const int MOVE = 1;
	const int ATK = 2;
	const int DEAD = 3;
	int mode = IDLE;

	const int IDLE_R = 0;
	const int IDLE_L = 1;
	const int MOVE_R = 2;
	const int MOVE_L = 3;
	const int UP_R = 4;
	const int UP_L = 5;
	const int DOWN_R = 6;
	const int DOWN_L = 7;
	const int ATK_R = 8;
	const int ATK_L = 9;
	const int EXTRA_ATK_R = 10;
	const int EXTRA_ATK_L = 11;
	const int ULT_R = 12;
	const int ULT_L = 13;
	const int DEAD_R = 14;
	const int DEAD_L = 15;
	int maxTop = 16;
	std::vector<int> maxLeft{ 5,5,3,3,1,1,1,1,3,3,11,11,11,11,5,5 };

	sf::Vector2f move{ 0.0f, 0.0f };
	const float defaultSpeed = 400.0f;
	const float minSpeed = 0.0f;
	float speed = defaultSpeed;
	float verticalSpeed = defaultSpeed - 40;

	const float defaultBulletSpeed = 400;
	float bulletSpeed = defaultBulletSpeed;


	std::set<int> idxErase;

	const float razeTime = 5.0f;
	float cntRaze = 0.0f;

	bool isRaze = false;

	sf::Texture playerTT, bodyTT, bulletTT;

	const std::string  playerFile = "Sprite/Player/whole.png";
	const std::string bodyFile = "Sprite/Player/body.png";
	const std::string bulletFile = "Sprite/Player/weapon.png";

	const float idleTime = 0.18f;
	float cntIdleTime = 0.0f;

	const float bulletTime = 0.08f;
	float cntBulletTime = 0.0f;

	const float bulletSpeedTime = 0.0f;
	float cntBulletSpeedTime = 0.0f;

	const float frameTime = 0.1f;
	float cntFrameTime = 0.0f;

	const float deadTime = 0.2f;
	float cntDeadTime = 0.0f;

	const float atkTime = 0.04f;
	float cntAtkTime = 0.0f;
	const float extra_atkTime = 0.03f;
	const float ultTime = 0.035f;
	float curAtkTime = atkTime;

	int cntPressedJ = 0;
	unsigned cntPressedK = 0;
	int curCombo = ATK_R;
	unsigned ultCombo = ULT_R;

	const int maxBulletTop = 6;
	const std::vector<int> maxBulletFrame{ 3,3,4,4,4,4 };

	const sf::Time deltaTime = sf::seconds(1.0f / 60.0f);

	//temp crop player sprite
	sf::RectangleShape rect;
	//

	short energyUsed = 0;

	short healthRegen = 0;

	std::deque<sf::Sound> bulletSoundS;
	std::queue<short> indexBulletSoundErase;

	sf::SoundBuffer deathSoundBF;
	sf::Sound deathSound;
	
	sf::Sound defaultSound, extraSound, ultSound;
	sf::SoundBuffer defaultSoundBF, extraSoundBF, ultSoundBF;
	
public:
	sf::Vector2f scale{ 3.6f,3.6f };
	int side = RIGHT;
	const sf::Vector2i imageSize{ 114,44 };
	const sf::Vector2i imageBulletSize{ 46,44 };

	sf::Image playerIMG, bodyIMG, bulletIMG;
	sf::Sprite playerSP, bodySP, bulletSP;

	int top = 0;
	std::vector<int> left;

	std::vector<sf::Sprite> bulletS;
	std::vector<int> sideBullet;
	std::vector<int> topBullet;
	std::vector<std::vector<int>> leftBullet;

	bool isPlayerDied = false;

	short maxHealthPlayer = 1000;
	short healthPlayer = maxHealthPlayer;
	short energyPlayer = 100;

	bool isOutofScreen = false;

private:
	void resetFrameExceptIndex(const int top);
	void setModeSideTop(const int mode, const int side, const int top, const sf::Vector2f move);

	void _setTextureRect();
	void _move();
	void _setFrame(const int mode);
	void pushBullet(const int top);

	void _setTextureRectBullet();
	void _moveBullet();
	void _setBulletFrame();
	bool isBulletOnScreen(sf::Vector2f bulletPos);
	void _popBullet(const int index);
	void clearBullet();
	void _isKeyPressed();

	bool isPlayerOnScreen();

	void checkIsPlaySound();
public:

	Player();
	void onEvent(const sf::Event& event);
	void onUpdate();
	void _draw(sf::RenderWindow& window);

	short updateHealthPlayer();
	short updateEnergyPlayer();
	short setHealthPlayer();
	void requestDeltaHealthPlayer(const short deltaHealthPlayer);
	void requestEnergyPlayer(const short energyPlayer);

	void _collision(const std::string condition, const bool isCollided, const int index);

	void itemAffect(const short itemSelected);

};