#ifndef TOWER_H
#define TOWER_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Soldier.h"
#include "math.h"
#include "Bullet.h"
#include <vector>

class Tower : public Entity 
{
public: 
    Tower(int type, sf::Vector2i pos, int user);
    Tower(int type);
    void Update(float deltaTime);
    void Draw(sf::RenderWindow & window) override;
    bool gotTarget();
    void getTarget(Soldier & soldier);
    sf::Vector2i getPos() {return pos;};
    float getCost() {return cost;};
    std::vector<Bullet> bulletList;

private:
    void Create(int type);
    bool inRange();
    float cost {0};
    float damagePoints {0}; 
    float attackSpeed {0};
    float reloadTime {0};
    float range {0}; 
    sf::Texture texture;
    int user = 0;
    float offset;
    float time = 0;
    Soldier * soldierP;
    sf::Vector2i pos;
    bool firstTarget = true;
    float dir = 0;
    float angle = 0;
    int bulletType = 1;
};
#endif
