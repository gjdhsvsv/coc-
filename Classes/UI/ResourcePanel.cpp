// File: ResourcePanel.cpp
// Brief: Implements the ResourcePanel component.
#include "UI/ResourcePanel.h"
#include <chrono>
using namespace cocos2d;
bool ResourcePanel::init() {
    _goldLabel = Label::createWithSystemFont("", "Arial", 14);
    _elixirLabel = Label::createWithSystemFont("", "Arial", 14);
    _popLabel = Label::createWithSystemFont("", "Arial", 14);
    _goldLabel->setColor(Color3B::WHITE);
    _elixirLabel->setColor(Color3B::WHITE);
    _popLabel->setColor(Color3B::WHITE);
    _goldBg = LayerColor::create(Color4B(40, 40, 40, 200), 10, 10);
    _elixirBg = LayerColor::create(Color4B(40, 40, 40, 200), 10, 10);
    _popBg = LayerColor::create(Color4B(40, 40, 40, 200), 10, 10);
    _fillGoldBg = LayerColor::create(Color4B(235, 200, 50, 220), 10, 10);
    _fillElixirBg = LayerColor::create(Color4B(170, 70, 200, 220), 10, 10);
    _timeBg = LayerColor::create(Color4B(40, 40, 40, 200), 10, 10);
    addChild(_goldBg);
    addChild(_elixirBg);
    addChild(_popBg);
    addChild(_fillGoldBg);
    addChild(_fillElixirBg);
    addChild(_timeBg);
    addChild(_goldLabel);
    addChild(_elixirLabel);
    addChild(_popLabel);
    _menu = Menu::create();
    _menu->setPosition(Vec2::ZERO);
    addChild(_menu, 2);

    
    
    
    
    _menu->setVisible(true);

    auto goldText = Label::createWithSystemFont("Fill Gold", "Arial", 16);
    goldText->setColor(Color3B::BLACK);
    _fillGoldItem = MenuItemLabel::create(goldText, [](cocos2d::Ref*) {
        ResourceManager::setGold(ResourceManager::getGoldCap());
        });
    auto elixirText = Label::createWithSystemFont("Fill Elixir", "Arial", 16);
    elixirText->setColor(Color3B::BLACK);
    _fillElixirItem = MenuItemLabel::create(elixirText, [](cocos2d::Ref*) {
        ResourceManager::setElixir(ResourceManager::getElixirCap());
        });
    auto timeText = Label::createWithSystemFont("x10000", "Arial", 16);
    timeText->setColor(Color3B::BLACK);
    _timeItem = MenuItemLabel::create(timeText, [this, timeText](cocos2d::Ref*) {
        const long long nowMs = (long long)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        
        if (_lastCheatMs != 0 && nowMs - _lastCheatMs < 400) return;
        _lastCheatMs = nowMs;
_timeActive = !_timeActive;
        if (_timeActive) {
            timeText->setString("Cancel");
            if (onSetTimeScale) onSetTimeScale(10000.f);
        }
        else {
            timeText->setString("x10000");
            if (onSetTimeScale) onSetTimeScale(1.f);
        }
        });
    _menu->addChild(_fillGoldItem);
    _menu->addChild(_fillElixirItem);
    _menu->addChild(_timeItem);
    updateTexts(ResourceManager::get());
    layout();
    ResourceManager::onChanged([this](const Resources& r) {
        updateTexts(r);
        layout();
        });
    return true;
}

void ResourcePanel::onExit()
{
    
    
    
    ResourceManager::onChanged(std::function<void(const Resources&)>());
    cocos2d::Node::onExit();
}
void ResourcePanel::setPanelScale(float s) {
    _scale = std::max(0.5f, std::min(3.0f, s));
    layout();
}
void ResourcePanel::updateTexts(const Resources& r) {
    
    if (!_goldLabel || !_elixirLabel) return;
    int goldCap = ResourceManager::getGoldCap();
    int elixirCap = ResourceManager::getElixirCap();
    _goldRatio = (goldCap > 0) ? std::min(1.0f, std::max(0.0f, (float)r.gold / (float)goldCap)) : 0.0f;
    _elixirRatio = (elixirCap > 0) ? std::min(1.0f, std::max(0.0f, (float)r.elixir / (float)elixirCap)) : 0.0f;

    
    _goldLabel->setString(cocos2d::StringUtils::format("%d/%d", r.gold, goldCap));
    _elixirLabel->setString(cocos2d::StringUtils::format("%d/%d", r.elixir, elixirCap));
    
    
    _popLabel->setString("");
}

void ResourcePanel::layout() {
    auto vs = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    const float margin = 10.0f * _scale;
    const float gapY = 6.0f * _scale;
    const float gapX = 8.0f * _scale;
    const float barW = 170.0f * _scale;
    const float barH = 14.0f * _scale;

    
    float rightX = origin.x + vs.width - margin;
    float topY = origin.y + vs.height - margin;

    auto placeRow = [&](cocos2d::Label* text, cocos2d::LayerColor* bg, cocos2d::LayerColor* fill, float ratio, float yTopRow) {
        
        float rowH = barH + 8.0f * _scale;
        float y = yTopRow - rowH;

        
        bg->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
        bg->setContentSize(cocos2d::Size(barW, barH));
        bg->setPosition(cocos2d::Vec2(rightX - barW, y + (rowH - barH) * 0.5f));

        
        fill->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
        fill->setPosition(bg->getPosition());
        fill->setContentSize(cocos2d::Size(barW * std::min(1.0f, std::max(0.0f, ratio)), barH));

        
        text->setScale(_scale);
        text->setAnchorPoint(cocos2d::Vec2(1.0f, 0.5f));
        text->setPosition(cocos2d::Vec2(bg->getPositionX() - gapX, y + rowH * 0.5f));

        return y;
    };

    float y = topY;
    y = placeRow(_goldLabel, _goldBg, _fillGoldBg, _goldRatio, y);
    y -= gapY;
    y = placeRow(_elixirLabel, _elixirBg, _fillElixirBg, _elixirRatio, y);

    
    if (_menu) {
        float cheatY = y - 14.0f * _scale;
        float leftX = rightX - barW;
        float step = barW / 3.0f;

        if (_fillGoldItem) {
            _fillGoldItem->setScale(_scale);
            _fillGoldItem->setPosition(Vec2(leftX + step * 0.5f, cheatY));
        }
        if (_fillElixirItem) {
            _fillElixirItem->setScale(_scale);
            _fillElixirItem->setPosition(Vec2(leftX + step * 1.5f, cheatY));
        }
        if (_timeItem) {
            _timeItem->setScale(_scale);
            _timeItem->setPosition(Vec2(leftX + step * 2.5f, cheatY));
        }
    }

    
    
    _popBg->setVisible(false);
    _popLabel->setVisible(false);
    _timeBg->setVisible(false);
}
