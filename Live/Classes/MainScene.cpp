#include "Fruit.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "EventManager.h"
#include "AudioManager.h"
#include "AudioComponent.h"
#include "Direction.h"
#include "ResourceLayer.h"
#include "Mapgen/MapGenerator.h"
#include "Mapgen/GeneratedResources.h"
#include <iostream>
#include <ctime>

USING_NS_CC;

#define TREE_X 5
#define TREE_Y 7
#define MAP_SPR_SHT_PX 64
#define SPRITE_INDEX 6
#define MAP_WIDTH 128
#define MAP_HEIGHT 128

Scene* MainScene::createScene() {
    auto scene = Scene::create();
    auto layer = MainScene::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init() {
#if MULTIPLAYER
    m_network_manager = new NetworkManager(this);
#else
    startGame(time(NULL));
#endif
    return true;
}

void MainScene::startGame( int seed ) {
    m_started = true;
    m_game_layer = Layer::create();


    MapGenerator* mapgen = new MapGenerator( seed );
    GeneratedResources mapResources = mapgen->createMap(MAP_WIDTH, MAP_HEIGHT);
    delete mapgen;

    m_map_manager = new MapManager(mapResources);
    m_game_layer->addChild(m_map_manager->getMap());


    m_player = new Player("Animation/boy_walk_down.plist", SPRITE_INDEX);
    m_player->setPosition(mapResources.m_spawn_point);
    m_map_manager->addPlayer(m_player);

#if MULTIPLAYER
    m_player2 = new Player("Animation/boy_walk_down.plist", SPRITE_INDEX);
    m_player2->setPosition(mapResources.m_spawn_point);
    m_map_manager->addPlayer(m_player2);
#endif
    // Instantiate HUD and add to scene
    m_hud = new HUD(m_player);
    // add HUD to the root layer
    this->addChild(m_hud, 2);
    this->addChild(m_game_layer, 0);

    // Let cocos know we have an update function to be called.
    this->scheduleUpdate();

    // Setup camera to follow the player
    m_camera = Follow::create(m_player->getSprite(), Rect::ZERO);
    m_camera->retain();
    m_game_layer->runAction(m_camera);


    // set up the input/event manager
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(
            EventManager::initializeEventManager(this), this);

    // setup the audio manager
    AudioComponent bg_audio = AudioComponent("Audio/global_bg_day.mp3", 168000);
    AudioManager::getInstance()->changeBackgroundMusic(bg_audio);
}

void MainScene::update(float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
    Node::update(delta);

    EventManager::update(delta);
    m_map_manager->update(delta);
    m_player->updateHunger(delta*HUNGER_DEGEN);
    m_hud->update();
#if MULTIPLAYER
    m_network_manager->update();
#endif
}

Player* MainScene::getPlayer(int id) {
#if MULTIPLAYER
    if(id == 1) return m_player2;
#endif
    return m_player;
}

MapManager* MainScene::getMapManager() {
    return m_map_manager;
}

std::vector<Item*>& MainScene::getMapItems() {
    return m_map_items;
}

HUD* MainScene::getHUD() {
    return m_hud;
}

bool MainScene::isStarted() {
    return m_started;
}

Food* MainScene::getDroppedFood() {
    return m_dropped_food;
}

void MainScene::setDroppedFood(Item* food) {
    m_dropped_food = dynamic_cast<Food*>(food);
}

void MainScene::addMapItem(Item* item, Point pos) {
    m_map_items.push_back(item);
    m_map_manager->getTileMap()->addChild(item->newSprite());
    item->setPosition(pos);
}
