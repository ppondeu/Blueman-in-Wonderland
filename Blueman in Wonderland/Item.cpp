#include "Item.h"

Item::Item() {
	this->itemIMG.loadFromFile(this->itemFile);
	this->itemTT.loadFromFile(this->itemFile);
	this->itemSP.setTexture(this->itemTT);

	this->itemBarTT.loadFromFile(this->itemBarFile);
	this->itemBarSP.setTexture(this->itemBarTT);

	font.loadFromFile("Font/PixelFont2.ttf");
	amount.setFont(font);
	amount.setCharacterSize(30);
	amount.setFillColor(sf::Color::Magenta);

	for (int i = 0; i < maxItem; i++) {
		this->amountItem.push_back(0);
		amount.setPosition(805 + i * imageItemBarSize.x, 1020);
		this->amountItemTxt.push_back(amount);
		std::stringstream ss;
		ss << amountItem.back();
		this->amountItemTxt.back().setString(ss.str());
		this->amountItemTxt.back().setOrigin(this->amountItemTxt.back().getLocalBounds().width / 2.0f, this->amountItemTxt.back().getLocalBounds().height / 2.0f);
		this->itemBarSP.setPosition(720 + i * imageItemBarSize.x, 950);
		this->itemBar.push_back(itemBarSP);
		this->itemBar.back().setTextureRect(sf::IntRect(i * imageItemBarSize.x, 0, imageItemBarSize.x, imageItemBarSize.y));
	}

	setFrame();
	this->itemBarCrop.setSize(static_cast<sf::Vector2f>(imageItemBarSize));
	this->itemBarCrop.setFillColor(sf::Color::Transparent);
	this->itemBarCrop.setOutlineThickness(-3);
	this->itemBarCrop.setOutlineColor(sf::Color::White);
	setItemBarCropFrame();

	getItemBF.loadFromFile("Audio/getItem.ogg");
	useItemBF.loadFromFile("Audio/useItem.ogg");
	selectItemBF.loadFromFile("Audio/selectItem.wav");

	getItemSound.setBuffer(getItemBF);
	useItemSound.setBuffer(useItemBF);
	selectItemSound.setBuffer(selectItemBF);

}


void Item::random() {
	randPos = sf::Vector2f{ 384.0f + rand() % 768, 210.0f + rand() % (705 - 95) };
	randItem = rand() % maxItem;
	currentItem = randItem;
}

void Item::setFrame() {
	random();
	this->itemSP.setTextureRect(sf::IntRect(currentItem * imageSize.x, 0, imageSize.x, imageSize.y));
	this->itemSP.setPosition(randPos);
}

void Item::setItemBarCropFrame() {
	this->itemBarCrop.setTextureRect(sf::IntRect(tempOfTemp * imageItemBarSize.x, 0, imageItemBarSize.x, imageItemBarSize.y));
	this->itemBarCrop.setPosition(720 + tempOfTemp * imageItemBarSize.x, 950);
}

void Item::resetCropInfo() {
	tempItemCrop = 0;
	tempOfTemp = 0;
	isSelectedItem = false;
	cntSelectFadeAway = 0;
}

void Item::onEvent(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::I) {
			++cntPressedI;
			if (cntPressedI == 1) {
				selectItemSound.play();
				tempOfTemp = tempItemCrop++;
				if (tempOfTemp >= maxItem) tempOfTemp = 0;
				if (tempItemCrop >= maxItem) tempItemCrop = 0;
				isSelectedItem = true;
				cntSelectFadeAway = 0;
			}
		}
		if (isSelectedItem) {
			if (event.key.code == sf::Keyboard::Enter) {
				++cntPressedEnter;
				if (cntPressedEnter == 1) {
					if(amountItem[tempOfTemp] > 0 ) useItemSound.play();
					itemSelected = tempOfTemp;
					resetCropInfo();
				}
			}
		}
	}

	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::I) {
			cntPressedI = 0;
		}

		if (event.key.code == sf::Keyboard::Enter) {
			cntPressedEnter = 0;
		}
	}
}
void Item::onUpdate() {
	cntCooldown += deltaTime.asSeconds();
	if (cntCooldown >= curCooldown) {
		setFrame();
		cntCooldown = 0;
		if (curCooldown == cooldownTime) curCooldown = onScreenTime;
		else if (curCooldown == onScreenTime) curCooldown = cooldownTime;
	}

	if (isSelectedItem) {
		cntSelectFadeAway += deltaTime.asSeconds();
		if (cntSelectFadeAway >= selectFadeAwayTime) {
			resetCropInfo();
		}
		setItemBarCropFrame();
	}
}

void Item::_draw(sf::RenderWindow& window) {

	window.draw(itemSP);
	for (auto& e : itemBar) {
		window.draw(e);
	}
	for (int i = 0; i < amountItemTxt.size(); i++) {
		std::stringstream ss;
		ss << amountItem[i];
		this->amountItemTxt[i].setString(ss.str());
		window.draw(amountItemTxt[i]);
	}
	if (isSelectedItem) window.draw(itemBarCrop);
	
}

void Item::collision(const bool isCollided) {
	this->isCollided = isCollided;
	if (isCollided) {
		getItemSound.play();
		++amountItem[currentItem];
		this->itemSP.setPosition(-500, 0);
		cntCooldown = 0;
		curCooldown = cooldownTime;
	}
}

short Item::getItemSelected() {

	if (itemSelected != 666) {
		if (amountItem[itemSelected] > 0) {
			--amountItem[itemSelected];
			return itemSelected;
		}
	}
	return 666;
}

void Item::resetItemSelected() {
	itemSelected = 666;
}