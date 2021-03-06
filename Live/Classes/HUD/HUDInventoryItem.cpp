#include "HUDInventoryItem.h"
USING_NS_CC;

HUDInventoryItem::HUDInventoryItem(Item** item, double x, double y) : item(item) {
    LayerColor::initWithColor(Color4B(170, 170, 170, 170));
    setPosition(Vec2(x, y));
    setContentSize(Size(INVENTORY_SLOT_SIZE, INVENTORY_SLOT_SIZE));
}

void HUDInventoryItem::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform,
                            bool transformUpdated) {}

void HUDInventoryItem::update() {
    removeAllChildren();
    if (*item == NULL) return;
    Sprite* itemSprite = (*item)->newSprite();
    addChild(itemSprite);
    float base_x = itemSprite->getContentSize().width;
    float base_y = itemSprite->getContentSize().height;

    (*item)->getSprite()->setAnchorPoint(Vec2(0, 0));
    (*item)->setScale(INVENTORY_SLOT_SIZE / base_x, INVENTORY_SLOT_SIZE / base_y);
}

HUDInventoryItem::~HUDInventoryItem() {}