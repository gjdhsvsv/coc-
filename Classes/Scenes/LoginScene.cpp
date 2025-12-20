#include "Scenes/LoginScene.h"

#include "Data/SaveSystem.h"
#include "Managers/SoundManager.h"
#include "Scenes/MainScene.h"
#include "Scenes/MenuScene.h"

#include "ui/CocosGUI.h"

USING_NS_CC;

namespace
{
    static void StyleLabelVisible(Label* label)
    {
        if (!label) return;
        label->setColor(Color3B::BLACK);
        label->enableOutline(Color4B::WHITE, 2);
        label->enableShadow(Color4B(0, 0, 0, 255), Size(2, -2), 2);
    }
}

Scene* LoginScene::createScene()
{
    return LoginScene::create();
}

bool LoginScene::init()
{
    if (!Scene::init())
        return false;

    CCLOG(">>> ENTER LoginScene");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Background (reuse the same background assets if available)
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
    auto title = Label::createWithSystemFont("Select Save", "Arial", 90);
    title->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height - 120));
    StyleLabelVisible(title);
    this->addChild(title, 1);

    buildSaveUI();
    refreshSaveList();
    SaveSystem::setBattleTargetSlot(-1);

    // Bottom buttons
    auto backLabel = Label::createWithSystemFont("Back", "Arial", 50);
    StyleLabelVisible(backLabel);
    auto backItem = MenuItemLabel::create(backLabel, [](Ref*) {
        Director::getInstance()->replaceScene(
            TransitionFade::create(0.35f, MenuScene::createScene()));
    });
    backItem->setPosition(origin + Vec2(140, 90));

    auto settingLabel = Label::createWithSystemFont("Settings", "Arial", 50);
    StyleLabelVisible(settingLabel);
    auto settingItem = MenuItemLabel::create(settingLabel, [this](Ref*) {
        this->openSettings();
    });
    settingItem->setPosition(origin + Vec2(visibleSize.width / 2, 90));

    auto menu = Menu::create(backItem, settingItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);

    return true;
}

void LoginScene::buildSaveUI()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // A light mask + panel
    _saveMask = LayerColor::create(Color4B(0, 0, 0, 60));
    this->addChild(_saveMask, 10);

    const float panelW = 820.0f;
    const float panelH = 520.0f;
    auto panel = LayerColor::create(Color4B(255, 255, 255, 235), panelW, panelH);
    panel->setPosition(origin.x + visibleSize.width / 2 - panelW / 2,
        origin.y + visibleSize.height / 2 - panelH / 2);
    _saveMask->addChild(panel);

    auto header = Label::createWithSystemFont("Save Slots", "Arial", 56);
    header->setColor(Color3B::BLACK);
    header->enableOutline(Color4B::WHITE, 2);
    header->setPosition(Vec2(panelW / 2, panelH - 50));
    panel->addChild(header);

    _saveScroll = ui::ScrollView::create();
    _saveScroll->setDirection(ui::ScrollView::Direction::VERTICAL);
    _saveScroll->setBounceEnabled(true);
    _saveScroll->setContentSize(Size(panelW - 40, panelH - 120));
    _saveScroll->setAnchorPoint(Vec2(0.5f, 0.5f));
    _saveScroll->setPosition(Vec2(panelW / 2, panelH / 2 - 30));
    _saveScroll->setScrollBarEnabled(true);
    panel->addChild(_saveScroll);

    // IMPORTANT: Use ScrollView's inner container directly.
    // This avoids invisible/offset bugs caused by putting another Node inside.
    _saveContent = _saveScroll->getInnerContainer();
}

void LoginScene::refreshSaveList()
{
    if (!_saveScroll || !_saveContent) return;

    // Only show existing saves (create is done in MenuScene).
    std::vector<SaveMeta> existing;
    auto metas = SaveSystem::listAllSlots();
    for (const auto& m : metas)
    {
        if (m.exists) existing.push_back(m);
    }

    auto inner = _saveScroll->getInnerContainer();
    inner->removeAllChildren();

    const float rowH = 70.0f;
    float innerH = std::max(_saveScroll->getContentSize().height, rowH * (float)std::max<size_t>(1, existing.size()));
    _saveScroll->setInnerContainerSize(Size(_saveScroll->getContentSize().width, innerH));

    if (existing.empty())
    {
        auto tip = Label::createWithSystemFont("No saves yet. Go back and create one.", "Arial", 34);
        tip->setColor(Color3B::BLACK);
        tip->enableOutline(Color4B::WHITE, 2);
        tip->setPosition(Vec2(_saveScroll->getContentSize().width / 2, innerH / 2));
        inner->addChild(tip);
        return;
    }

    // Top-down list
    for (size_t i = 0; i < existing.size(); ++i)
    {
        const auto& meta = existing[i];
        float yTop = innerH - rowH * (i + 1);

        auto rowBg = LayerColor::create(Color4B(240, 240, 240, 255), _saveScroll->getContentSize().width, rowH - 8);
        rowBg->setAnchorPoint(Vec2::ZERO);
        rowBg->setPosition(Vec2(0, yTop));
        inner->addChild(rowBg);

        std::string labelText = StringUtils::format("[%02d] %s", meta.slot + 1, meta.name.c_str());
        auto label = Label::createWithSystemFont(labelText, "Arial", 32);
        label->setAnchorPoint(Vec2(0.0f, 0.5f));
        label->setPosition(Vec2(20, rowBg->getContentSize().height / 2));
        label->setColor(Color3B::BLACK);
        label->enableOutline(Color4B::WHITE, 2);
        rowBg->addChild(label);

        auto enterLabel = Label::createWithSystemFont("Enter", "Arial", 28);
        StyleLabelVisible(enterLabel);
        auto enterItem = MenuItemLabel::create(enterLabel, [meta](Ref*) {
            SaveSystem::setCurrentSlot(meta.slot);
            SaveSystem::setBattleTargetSlot(-1);
            Director::getInstance()->replaceScene(
                TransitionFade::create(0.35f, MainScene::createScene()));
        });
        enterItem->setPosition(Vec2(rowBg->getContentSize().width - 200, rowBg->getContentSize().height / 2));

        auto deleteLabel = Label::createWithSystemFont("Delete", "Arial", 26);
        StyleLabelVisible(deleteLabel);
        auto deleteItem = MenuItemLabel::create(deleteLabel, [this, meta](Ref*) {
            if (SaveSystem::exists(meta.slot))
            {
                SaveSystem::remove(meta.slot);
                this->refreshSaveList();
            }
        });
        deleteItem->setPosition(Vec2(rowBg->getContentSize().width - 80, rowBg->getContentSize().height / 2));

        auto rowMenu = Menu::create(enterItem, deleteItem, nullptr);
        rowMenu->setPosition(Vec2::ZERO);
        rowBg->addChild(rowMenu);
    }
}

void LoginScene::openSettings()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // Mask layer (swallow touches)
    auto mask = LayerColor::create(Color4B(0, 0, 0, 180));
    this->addChild(mask, 100);

    auto maskListener = EventListenerTouchOneByOne::create();
    maskListener->setSwallowTouches(true);
    maskListener->onTouchBegan = [](Touch*, Event*) { return true; };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(maskListener, mask);

    // Panel
    const float panelW = 640.0f;
    const float panelH = 420.0f;
    auto panel = LayerColor::create(Color4B(70, 70, 70, 255), panelW, panelH);
    panel->setPosition(origin.x + visibleSize.width / 2 - panelW / 2,
        origin.y + visibleSize.height / 2 - panelH / 2);
    mask->addChild(panel);

    auto panelListener = EventListenerTouchOneByOne::create();
    panelListener->setSwallowTouches(true);
    panelListener->onTouchBegan = [](Touch*, Event*) { return true; };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(panelListener, panel);

    panel->setScale(0.1f);
    panel->runAction(EaseBackOut::create(ScaleTo::create(0.22f, 1.0f)));

    // Title
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
        mask->removeFromParent();
    });
    closeItem->setPosition(Vec2(panelW - 40, panelH - 40));

    auto closeMenu = Menu::create(closeItem, nullptr);
    closeMenu->setPosition(Vec2::ZERO);
    panel->addChild(closeMenu);
}
