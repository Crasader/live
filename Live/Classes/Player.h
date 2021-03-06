#pragma once

#include "GameObject.h"
#include "cocos2d.h"
#include "Item.h"
#include "Inventory.h"
#include "Direction.h"
#include "EventManager.h"
#include "Animate.h"
#include "Equipment/Equipment.h"

#define MAX_PICKUP_DISTANCE 40

#define START_X     100
#define START_Y     100
#define STATIONARY_INDEX 1  // Refers to where in the sprite frames the stationary
                            // sprite is
#define FRAME_COUNT 3
#define NUM_CHAR    4       // This indicates the number of different characters
                            // in the animation sprite sheet, required for index
                            // jumping
#define DEFAULT_MAX_HUNGER 100
#define DEFAULT_MAX_STAMINA 100

#define PLAYER_SPRITE_HEIGHT 48
#define PLAYER_SPRITE_WIDTH 32
// Half the length of the player square's side
// Needed to form the player hitbox, since the player is defined by a center position
#define PLAYER_HALF_SIZE PLAYER_SPRITE_HEIGHT/2

#define PLAYER_HITBOX_WIDTH 4
#define PLAYER_HITBOX_HEIGHT 12

#define HUNGER_DEGEN -0.1f
#define STAMINA_DEGEN -10
#define STAMINA_REGEN 4

#define PICKUP_RADIUS 20

typedef struct mapping {
    cocos2d::EventKeyboard::KeyCode north, south, west, east, interact;
} Mapping;


class Player : public GameObject, public Live::Animate {
public:
    // Takes in the plist file and the initial sprite frame file index
    Player(const std::string& sprite_frame_file, unsigned int index,
            Mapping mapping = {.north = cocos2d::EventKeyboard::KeyCode::KEY_W,
            .south = cocos2d::EventKeyboard::KeyCode::KEY_S,
            .west = cocos2d::EventKeyboard::KeyCode::KEY_A,
            .east = cocos2d::EventKeyboard::KeyCode::KEY_D});
    void updateHunger(float difference);
    void updateStamina(float difference);
    void moveX(float x);
    void moveY(float y);
    void setPosition(cocos2d::Point point, Direction dir = Direction::DIR_DOWN);
    Direction getOrientation();
    void move(float x, float y);
    float getHunger() const;
    float getStamina() const;
    bool pickup(Item* item);
    Item* drop(int i);
    bool use(int i);
    Inventory* get_inventory();
    virtual cocos2d::Rect getHitbox();
    Arrow* action();
    void releaseAction();
    void equip(Equipment* equip);

protected:
    virtual void animateMove();
    virtual void stopMove();

private:
    float m_hunger;
    float m_max_hunger;
    Inventory* m_inventory;
    float m_stamina;
    float m_max_stamina;
    // TODO Not being used yet, last resort use for local multiplayer
    Mapping m_mapping;
    Equipment* m_equip;
    bool m_action_lock;
};
