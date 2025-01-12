#ifndef CLASS_PLAYER_H
#define CLASS_PLAYER_H

#include "Sprite.hpp"
#include "Item.hpp"

class Player : public Sprite
{
  public:
    Player();
    ~Player();
    void update(float dt);
    void move_right();
    void move_left();
    void jump();
    void halt();
    bool isJumping();
    void collisionMap(int type);
    void pickItem(Item *item);
    void releaseItem();
    void setLives(int _lives);
  private:
    int move_velocity;
    float jump_velocity;
    bool jumping;
    Item* backpack;
    int lives;
    int score;
};

#endif
