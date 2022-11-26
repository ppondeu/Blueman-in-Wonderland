#include "LeaderBoard.h"

LeaderBoard::LeaderBoard() {
	font.loadFromFile("Font/PixelFont2.ttf");
	
	frame.setSize(sf::Vector2f(900, 950));
	frame.setFillColor(sf::Color(8, 92, 224, 255));
	frame.setOutlineColor(sf::Color(248,146,18,255));
	frame.setOutlineThickness(-10);
	
	frame.setOrigin(frame.getGlobalBounds().width / 2, frame.getGlobalBounds().height / 2);
	frame.setPosition(959, 539);

	leaderBoardTxt.setFont(font);
	leaderBoardTxt.setCharacterSize(55);
	leaderBoardTxt.setString("LEADERBOARD");
	//leaderBoardTxt.setStyle(sf::Text::Italic);
	leaderBoardTxt.setOrigin(leaderBoardTxt.getGlobalBounds().width / 2, leaderBoardTxt.getGlobalBounds().height / 2);
	leaderBoardTxt.setPosition(959-10, 539 - 350-30-30);

	leaderBoardFrame.setSize(sf::Vector2f(400, 100));
	leaderBoardFrame.setFillColor(sf::Color(19, 56, 200, 255));
	leaderBoardFrame.setOutlineColor(sf::Color(248, 146, 18, 255));
	leaderBoardFrame.setOutlineThickness(10);
	leaderBoardFrame.setOrigin(leaderBoardFrame.getGlobalBounds().width / 2, leaderBoardFrame.getGlobalBounds().height / 2);
	leaderBoardFrame.setPosition(959, 539-350-30);

	sf::RectangleShape tempPlayerScoreFrame;
	tempPlayerScoreFrame.setSize(sf::Vector2f(800, 80));
	tempPlayerScoreFrame.setFillColor(sf::Color(19, 56, 200, 255));
	tempPlayerScoreFrame.setOutlineColor(sf::Color(248, 146, 18, 255));
	tempPlayerScoreFrame.setOutlineThickness(3);
	tempPlayerScoreFrame.setOrigin(tempPlayerScoreFrame.getGlobalBounds().width / 2, tempPlayerScoreFrame.getGlobalBounds().height);
	for (int i = 0; i < maxPlayer; i++) {
		playerScoreFrame.push_back(tempPlayerScoreFrame);
		playerScoreFrame.back().setPosition(959, 539-180 + i*120);
	}

	sf::Text tempPlayerScoreTxt;
	tempPlayerScoreTxt.setFont(font);
	tempPlayerScoreTxt.setCharacterSize(50);
	//tempPlayerScoreTxt.setString("9999999");
	tempPlayerScoreTxt.setOrigin(tempPlayerScoreTxt.getGlobalBounds().width, 0);

	for (int i = 0; i < maxPlayer; i++) {
		playerScoreTxt.push_back(tempPlayerScoreTxt);
		playerScoreTxt.back().setPosition(959+350, 539 - 150 + i * 120-120+10);
	}

	sf::Text tempPlayerName;
	tempPlayerName.setFont(font);
	tempPlayerName.setCharacterSize(50);
	//tempPlayerName.setString("GUICEDO");

	for (int i = 0; i < maxPlayer; i++) {
		playerNameTxt.push_back(tempPlayerName);
		playerNameTxt.back().setPosition(959 + 350-700-10, 539 - 150 + i * 120 - 120 + 10);
	}


	menuTxt.setFont(font);
	menuTxt.setCharacterSize(50);
	menuTxt.setString("HOME");
	menuTxt.setOrigin(menuTxt.getGlobalBounds().width / 2, menuTxt.getGlobalBounds().height / 2);
	menuTxt.setPosition(959-250, 539+365);

	menuFrame.setSize(sf::Vector2f(150, 50));
	menuFrame.setFillColor(sf::Color(248, 146, 18, 255));
	menuFrame.setOutlineColor(sf::Color(19, 56, 200, 255));
	menuFrame.setOutlineThickness(5);
	menuFrame.setOrigin(menuFrame.getGlobalBounds().width / 2, menuFrame.getGlobalBounds().height / 2);
	menuFrame.setPosition(959 - 250+5, 539 + 365+25);

	playAgainTxt.setFont(font);
	playAgainTxt.setCharacterSize(50);
	playAgainTxt.setString("PLAY\nAGAIN");
	playAgainTxt.setOrigin(playAgainTxt.getGlobalBounds().width / 2, playAgainTxt.getGlobalBounds().height / 2);
	playAgainTxt.setPosition(959 - 250 +500, 539 + 365);

	playAgainFrame.setSize(sf::Vector2f(200, 100));
	playAgainFrame.setFillColor(sf::Color(248, 146, 18, 255));
	playAgainFrame.setOutlineColor(sf::Color(19, 56, 200, 255));
	playAgainFrame.setOutlineThickness(5);
	playAgainFrame.setOrigin(playAgainFrame.getGlobalBounds().width / 2, playAgainFrame.getGlobalBounds().height / 2);
	playAgainFrame.setPosition(959 - 250 + 5 + 500, 539 + 365 + 25);

	buffer.loadFromFile("Audio/onButtonSound.wav");
	sound.setBuffer(buffer);
	
}
void LeaderBoard::isOnButton(const sf::Vector2f& mousePos) {
	if (menuFrame.getGlobalBounds().contains(mousePos)) {
		++cntOnMenu;
		if (cntOnMenu == 1) {
			sound.play();
		}
		menuTxt.setFillColor(sf::Color::Red);
	}
	else {
		cntOnMenu = 0;
		menuTxt.setFillColor(sf::Color::White);
	}

	if (playAgainFrame.getGlobalBounds().contains(mousePos)) {
		++cntOnPlayAgain;
		if (cntOnPlayAgain == 1) {
			sound.play();
		}
		playAgainTxt.setFillColor(sf::Color::Red);
	}
	else {
		cntOnPlayAgain = 0;
		playAgainTxt.setFillColor(sf::Color::White);
	}
}
void LeaderBoard::onUpdate(const sf::Vector2f& mousePos) {
	
	isOnButton(mousePos);
	if (!once) {
		once = true;
		readFile();
	}

}
void LeaderBoard::draw(sf::RenderWindow& window) {
	window.draw(frame);
	window.draw(leaderBoardFrame);
	window.draw(leaderBoardTxt);
	window.draw(menuFrame);
	window.draw(menuTxt);
	if (lastState == 5) {
		window.draw(playAgainFrame);
		window.draw(playAgainTxt);
	}
	for (int i = 0; i < maxPlayer; i++) {
		window.draw(playerScoreFrame[i]);
		
	}

	for (int i = 0; i < maxPlayer; i++) {
		window.draw(playerScoreTxt[i]);
		window.draw(playerNameTxt[i]);
	}

	
}

void LeaderBoard::setLastState(const short lastState) {
	this->lastState = lastState;
}

void LeaderBoard::setData(const std::string name, const unsigned long long score) {
	this->name = name;
	this->score = score;
}

void LeaderBoard::readFile() {
	if (lastState == 0) {
		score = 0;
		name = "";
	}
	std::string tempName = "";
	std::ifstream out("leaderboard.txt");
	int cnt = 0;
	while (std::getline(out, tempName)) {
		++cnt;
		bool isFoundDelim = false;
		std::string nameTxt, scoreTxt;
		int tempScore = 0;
		if (cnt < 6) {
			for (int i = 0; i < tempName.length(); i++) {
				if (tempName[i] == ' ') {
					isFoundDelim = true;
					//i++;
					continue;
				}
				if (isFoundDelim) {
					scoreTxt += tempName[i];;
				}
				else {
					nameTxt += tempName[i];
				}
			}

			int sum = 0;
			for (int i = 0; i < scoreTxt.size() && scoreTxt != ""; i++) {
				int x = scoreTxt[i] - '0';
				sum += x * pow(10, scoreTxt.size() - i - 1);
			}
			tempScore = sum;
			data.push_back(std::make_pair(std::make_pair(nameTxt, scoreTxt), tempScore));
		}
	}
	out.close();
	
	updateLeaderBoard();
	setLeaderBoard();
	writeFile();
}
void LeaderBoard::updateLeaderBoard() {
	int idx = 0;
	int indexInsert = 0;
	bool isInsert = false;
	
	for (auto& e : data) {
		if (score > e.second) {
			indexInsert = idx;
			isInsert = true;
			break;
		}
		++idx;
	}

	if (isInsert) {
		std::stringstream ss;
		ss << score;
		std::string scoreTxt;
		scoreTxt = ss.str();
		data.insert(data.begin() + idx, std::make_pair(std::make_pair(name, scoreTxt), score));

		data.pop_back();
	}
}

void LeaderBoard::setLeaderBoard(){

	for (int i = 0; i < maxPlayer; i++) {
		playerNameTxt[i].setString(data[i].first.first);
		playerScoreTxt[i].setString(data[i].first.second);
		playerScoreTxt[i].setOrigin(playerScoreTxt[i].getGlobalBounds().width, 0);
	}

}
void LeaderBoard::writeFile() {
	std::ofstream out;
	out.open("leaderboard.txt");
	for (auto& e : data) {
		out << e.first.first << " " << e.first.second<<std::endl;
	}
	out.close();
}