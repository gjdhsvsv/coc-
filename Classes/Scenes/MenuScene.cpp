#include "Scenes/MenuScene.h"

#include "Data/SaveSystem.h"
#include "Managers/SoundManager.h"
#include "Scenes/LoginScene.h"
#include "Scenes/MainScene.h"

#include "ui/CocosGUI.h"

#ifdef _WIN32
#include <windows.h>
#endif

USING_NS_CC;

namespace
{
    static void StyleMainLabel(Label* label)
    {
        if (!label) return;
        // Black text + white outline tends to be readable on both bright and dark backgrounds.
        label->setColor(Color3B::BLACK);
        label->enableOutline(Color4B::WHITE, 2);
        label->enableShadow(Color4B(0, 0, 0, 255), Size(2, -2), 2);
    }
}

Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

bool MenuScene::init()
{
    if (!Scene::init())
        return false;

    CCLOG(">>> ENTER MenuScene");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Background (reuse the same background assets as LoginScene if available)
    auto bg = Sprite::create("background.jpg");
    if (!bg)
        bg = Sprite::create("backgrounds/village_map.jpg");

    if (bg)
    {
        bg->setPosition(origin + visibleSize / 2);
        bg->setScale(
            visibleSize.width / bg->getContentSize().width,
            visibleSize.height / bg->getContentSize().height);
        this->addChild(bg, -1);
    }
    else
    {
        this->addChild(LayerColor::create(Color4B(60, 80, 120, 255)), -1);
    }

    // Title
    auto title = Label::createWithSystemFont("Clash Start", "Arial", 110);
    title->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height - 150));
    StyleMainLabel(title);
    this->addChild(title);

    // Main buttons
    auto createLabel = Label::createWithSystemFont("Create New Save", "Arial", 54);
    StyleMainLabel(createLabel);
    auto createItem = MenuItemLabel::create(createLabel, [this](Ref*) {
        // Pick first empty slot
        int emptySlot = -1;
        auto metas = SaveSystem::listAllSlots();
        for (const auto& m : metas)
        {
            if (!m.exists)
            {
                emptySlot = m.slot;
                break;
            }
        }

        if (emptySlot < 0)
        {
            showToast("No empty save slot (max 20). Delete one first.");
            return;
        }

        // Create default save and enter village
        std::string defName = StringUtils::format("Save %02d", emptySlot + 1);
        SaveData data = SaveSystem::makeDefault(emptySlot, defName);
        SaveSystem::save(data);
        SaveSystem::setCurrentSlot(emptySlot);
        SaveSystem::setBattleTargetSlot(-1);

        Director::getInstance()->replaceScene(
            TransitionFade::create(0.35f, MainScene::createScene()));
    });

    auto loadLabel = Label::createWithSystemFont("Load Existing Save", "Arial", 54);
    StyleMainLabel(loadLabel);
    auto loadItem = MenuItemLabel::create(loadLabel, [](Ref*) {
        Director::getInstance()->replaceScene(
            TransitionFade::create(0.35f, LoginScene::createScene()));
    });

    // Bottom buttons
    auto settingLabel = Label::createWithSystemFont("Settings", "Arial", 50);
    StyleMainLabel(settingLabel);
    auto settingItem = MenuItemLabel::create(settingLabel, [this](Ref*) {
        this->openSettings();
    });

    auto exitLabel = Label::createWithSystemFont("Exit Game", "Arial", 50);
    StyleMainLabel(exitLabel);
    auto exitItem = MenuItemLabel::create(exitLabel, [](Ref*) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        ExitProcess(0);
#else
        Director::getInstance()->end();
#endif
    });

    auto menu = Menu::create(createItem, loadItem, settingItem, exitItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    createItem->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2 + 40));
    loadItem->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2 - 40));
    settingItem->setPosition(origin + Vec2(visibleSize.width / 2 - 140, 90));
    exitItem->setPosition(origin + Vec2(visibleSize.width / 2 + 140, 90));

    // A reusable toast label
    _toast = Label::createWithSystemFont("", "Arial", 28);
    _toast->setOpacity(0);
    StyleMainLabel(_toast);
    _toast->setPosition(origin + Vec2(visibleSize.width / 2, 150));
    this->addChild(_toast, 50);

    return true;
}

void MenuScene::showToast(const std::string& text)
{
    if (!_toast) return;
    _toast->stopAllActions();
    _toast->setString(text);
    _toast->setOpacity(255);
    _toast->runAction(Sequence::create(DelayTime::create(2.0f), FadeOut::create(0.25f), nullptr));
}

void MenuScene::openSettings()
{
    if (_settingsMask) return;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    _settingsMask = LayerColor::create(Color4B(0, 0, 0, 180));
    this->addChild(_settingsMask, 100);

    // Swallow touches
    auto maskListener = EventListenerTouchOneByOne::create();
    maskListener->setSwallowTouches(true);
    maskListener->onTouchBegan = [](Touch*, Event*) { return true; };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(maskListener, _settingsMask);

    // Panel
    const float panelW = 640.0f;
    const float panelH = 420.0f;
    auto panel = LayerColor::create(Color4B(70, 70, 70, 255), panelW, panelH);
    panel->setPosition(origin.x + visibleSize.width / 2 - panelW / 2,
        origin.y + visibleSize.height / 2 - panelH / 2);
    _settingsMask->addChild(panel);

    // Panel swallows touches too
    auto panelListener = EventListenerTouchOneByOne::create();
    panelListener->setSwallowTouches(true);
    panelListener->onTouchBegan = [](Touch*, Event*) { return true; };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(panelListener, panel);

    panel->setScale(0.1f);
    panel->runAction(EaseBackOut::create(ScaleTo::create(0.22f, 1.0f)));

    auto title = Label::createWithSystemFont("Settings", "Arial", 50);
    title->setPosition(Vec2(panelW / 2, panelH - 50));
    panel->addChild(title);

    // Master volume slider
    auto volLabel = Label::createWithSystemFont("Master Volume", "Arial", 32);
    volLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    volLabel->setPosition(Vec2(60, 260));
    panel->addChild(volLabel);

    float curVol = SoundManager::getVolume();

    auto volSlider = ui::Slider::create();
    volSlider->loadBarTexture("ui/sliderTrack.png");
    volSlider->loadSlidBallTextures("ui/sliderThumb.png", "ui/sliderThumb.png", "");
    volSlider->loadProgressBarTexture("ui/sliderProgress.png");
    volSlider->setPosition(Vec2(420, 260));
    volSlider->setPercent((int)(curVol * 100.0f + 0.5f));
    panel->addChild(volSlider);

    // Mute checkbox
    auto mute = ui::CheckBox::create("ui/checkbox_off.png", "ui/checkbox_on.png");
    mute->setPosition(Vec2(110, 160));
    mute->setSelected(curVol <= 0.001f);
    panel->addChild(mute);

    auto muteLabel = Label::createWithSystemFont("Mute", "Arial", 32);
    muteLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
    muteLabel->setPosition(Vec2(150, 160));
    panel->addChild(muteLabel);

    volSlider->addEventListener([=](Ref* sender, ui::Slider::EventType type) {
        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
            auto s = static_cast<ui::Slider*>(sender);
            float v = s->getPercent() / 100.0f;
            SoundManager::setVolume(v);
            mute->setSelected(v <= 0.001f);
        }
    });

    mute->addEventListener([=](Ref*, ui::CheckBox::EventType type) {
        bool isMute = (type == ui::CheckBox::EventType::SELECTED);
        if (isMute)
        {
            SoundManager::setVolume(0.0f);
            volSlider->setPercent(0);
        }
        else
        {
            float v = volSlider->getPercent() / 100.0f;
            SoundManager::setVolume(v);
        }
    });

    // Close button
    auto closeLabel = Label::createWithSystemFont("X", "Arial", 40);
    auto closeItem = MenuItemLabel::create(closeLabel, [=](Ref*) {
        closeSettings();
    });
    closeItem->setPosition(Vec2(panelW - 40, panelH - 40));

    auto closeMenu = Menu::create(closeItem, nullptr);
    closeMenu->setPosition(Vec2::ZERO);
    panel->addChild(closeMenu);
}

void MenuScene::closeSettings()
{
    if (_settingsMask)
    {
        _settingsMask->removeFromParent();
        _settingsMask = nullptr;
    }
}
