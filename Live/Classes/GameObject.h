#pragma once

#include "cocos2d.h"

#define SPRITE_DIM 17

class GameObject {
public:
    GameObject(){};
    GameObject(const std::string& spritesheet_file, int grid_pos_x = -1,
            int grid_pos_y = -1);
    virtual ~GameObject();
    virtual void setPosition(float x, float y);
    virtual void setPosition(cocos2d::Vec2);
    virtual void setScale(float xy);
    virtual void setScale(float x, float y);
    virtual void setZOrder(float z);
    virtual cocos2d::Vec2 getPosition() const;
    const float distanceFrom(const GameObject& other);
    virtual cocos2d::Sprite* newSprite();
    virtual cocos2d::Sprite* newSprite(int width, int length);
    virtual cocos2d::Sprite* getSprite();
    virtual std::string getSpriteFile() const;

protected:
    cocos2d::Sprite* m_sprite;
    std::string m_sprite_file;
    int m_grid_pos_x;
    int m_grid_pos_y;
};
