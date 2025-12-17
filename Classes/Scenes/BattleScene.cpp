#include "Scenes/BattleScene.h"
#include "Scenes/MainScene.h"

USING_NS_CC;

Scene* BattleScene::createScene()
{
    return BattleScene::create();
}

bool BattleScene::init()
{
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Background color (gray for battle)
    auto layer = LayerColor::create(Color4B(50, 50, 50, 255));
    this->addChild(layer);

    auto label = Label::createWithTTF("Battle Scene", "fonts/Marker Felt.ttf", 24);
    if (!label) {
        label = Label::createWithSystemFont("Battle Scene", "Arial", 24);
    }
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));
    this->addChild(label, 1);
    
    // Back button
    auto backLabel = Label::createWithSystemFont("Back to Village", "Arial", 20);
    auto backItem = MenuItemLabel::create(backLabel, [](Ref* sender){
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MainScene::createScene()));
    });
    backItem->setPosition(Vec2(origin.x + 100, origin.y + visibleSize.height - 50));
    
    auto menu = Menu::create(backItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}
