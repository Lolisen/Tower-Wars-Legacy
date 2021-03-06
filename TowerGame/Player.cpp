#include "Player.h"
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

Player::Player() :coins{100}, income{10} 
{
    DefineEconomyMisc();
    createBase();
    createPortal();
}

void Player::TimerForIncome()
{
    clock.restart();
    coins = coins + income;
}

void Player::UpdateEconomy()
{
    sf::Time time = clock.getElapsedTime();
    if(time.asSeconds() >= 15.0)
	TimerForIncome();
    
    std::stringstream ss;
    ss << fixed << setprecision(0) << income;
    std::string tempIncome = "";
    ss >> tempIncome;
    ss.clear();
    ss << fixed << setprecision(0) << coins;
    std::string tempCoins = "";
    ss >> tempCoins; 
    CoinsValue.setString(tempCoins);
    IncomeValue.setString(tempIncome);
}

void Player::DefineEconomyMisc()
{
    int charsize = 20;

    font.loadFromFile("Arial.ttf");
    coinRectangle.setSize(sf::Vector2f(200, 40));
    coinRectangle.setPosition(750, 930);
    //   coinRectangle.setOrigin(coinRectangle.getSize() / 2.0f);
    coinRectangle.setFillColor(sf::Color::Black);  

    incomeRectangle.setSize(sf::Vector2f(200, 40));
    incomeRectangle.setPosition(1070, 930);
//    incomeRectangle.setOrigin(incomeRectangle.getSize() / 2.0f);
    incomeRectangle.setFillColor(sf::Color::Black);  


    CoinsText.setFont(font);
    CoinsText.setCharacterSize(charsize);
    CoinsText.setFillColor(sf::Color::White);
    CoinsText.setString("Coins:");
    
    CoinsText.setPosition(sf::Vector2f(coinRectangle.getPosition()));
    textRect = CoinsText.getLocalBounds();

    std::string tempCoins = std::to_string(coins);
    CoinsValue.setFont(font);
    CoinsValue.setCharacterSize(charsize);
    CoinsValue.setFillColor(sf::Color::White);
    CoinsValue.setString(tempCoins);
    CoinsValue.setPosition(sf::Vector2f(coinRectangle.getPosition().x + 60.f, coinRectangle.getPosition().y));
    textRect = CoinsValue.getLocalBounds();

    IncomeText.setFont(font);
    IncomeText.setCharacterSize(charsize);
    IncomeText.setFillColor(sf::Color::White);
    IncomeText.setString("Income:");
    IncomeText.setPosition(sf::Vector2f(incomeRectangle.getPosition()));
    textRect = IncomeText.getLocalBounds();

    std::string tempIncome = std::to_string(income);
    IncomeValue.setFont(font);
    IncomeValue.setCharacterSize(charsize);
    IncomeValue.setFillColor(sf::Color::White);
    IncomeValue.setString(tempIncome);
    IncomeValue.setPosition(sf::Vector2f(incomeRectangle.getPosition().x + 75.f, incomeRectangle.getPosition().y));
    textRect = IncomeValue.getLocalBounds();
}


void Player::Update()
{ 
    UpdateEconomy();
}

void Player::BuyWithCoins(float cost, float increaseIncome)
{
    coins = coins - cost;
    income = income + increaseIncome;
}

void Player::createBase()
{
    baseTexture.loadFromFile("images/base.png");
    base.setSize(sf::Vector2f(50, 50));
    base.setOrigin(base.getSize() / 2.0f);
    base.setPosition(sf::Vector2f(60 * 5, 0));
    base.move(30, 30);
    base.setTexture(&baseTexture);

    enemybaseTexture.loadFromFile("images/base2.png");
    enemybase.setSize(sf::Vector2f(50, 50));
    enemybase.setOrigin(enemybase.getSize() / 2.0f);
    enemybase.setPosition(sf::Vector2f(60 * 16, 0));
    enemybase.move(50, 30);
    enemybase.setTexture(&enemybaseTexture);
}

void Player::createPortal()
{
    portalTexture.loadFromFile("images/Portal.png");
    portal.setSize(sf::Vector2f(50, 50));
    portal.setOrigin(portal.getSize()/2.f);
    portal.setPosition(sf::Vector2f(60*3, 0));
    portal.move(30, 30);
    portal.setTexture(&portalTexture);

    enemyportal.setSize(sf::Vector2f(50, 50));
    enemyportal.setOrigin(enemyportal.getSize()/2.f);
    enemyportal.setPosition(sf::Vector2f(60*14, 0));
    enemyportal.move(50, 30);
    enemyportal.setTexture(&portalTexture);

}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(incomeRectangle);
    window.draw(coinRectangle);
    window.draw(IncomeText);
    window.draw(CoinsText);
    window.draw(IncomeValue);
    window.draw(CoinsValue);

    window.draw(portal);
    window.draw(enemyportal);
    if (baseHealthP1 > 0)
	window.draw(base);
    if (baseHealthP2 > 0)
	window.draw(enemybase);
}

int Player::getWinner()
{
    if (GameOver())
    {
	if (baseHealthP1 > 0)
	    return 1;
	else if (baseHealthP2 > 0)
	    return 2;
    }
    else
	return 0;
}

void Player::TakeDamage(int user, int incommingDamage)
{
    if(user == 1)
	baseHealthP1 -= incommingDamage;
    else if (user == 2)
	baseHealthP2 -= incommingDamage;
}
