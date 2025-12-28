// File: CombatSystem.cpp
// Brief: Implements the CombatSystem component.
#include "Systems/CombatSystem.h"

#include "Patterns/AttackVisitor.h"
#include "GameObjects/Buildings/DefenseBuilding.h"
#include "GameObjects/Buildings/ResourceBuilding.h"
#include "GameObjects/Units/wall_breaker.h"
#include "Managers/SoundManager.h"

#include <algorithm>
#include <cmath>
#include <string>

using namespace cocos2d;

namespace {

/**
 * Computes the best-matching cannon barrel sprite for the current target direction.
 *
 * The project provides 6 directional cannon sprites (N, NE, SE, S, SW, NW). We approximate
 * the direction by the angle from the cannon center to the target, then snap it to the
 * closest 60-degree sector.
 */
std::string GetCannonFacingTexturePath(const Vec2& cannonPos, const Vec2& targetPos)
{
    const float dx = targetPos.x - cannonPos.x;
    const float dy = targetPos.y - cannonPos.y;

    // Avoid unstable facing when both positions are extremely close.
    if (std::abs(dx) < 0.001f && std::abs(dy) < 0.001f)
    {
        return "cannon/cannon_south.png";
    }

    const float rad = std::atan2(dy, dx);
    const float deg = rad * 57.2957795f;  // [-180, 180]

    // Sector centers: N(90), NE(30-60), SE(-30), S(-90), SW(-150), NW(150).
    if (deg >= 60.0f && deg < 120.0f) return "cannon/cannon_north.png";
    if (deg >= 0.0f && deg < 60.0f)   return "cannon/cannon_northeast.png";
    if (deg >= -60.0f && deg < 0.0f)  return "cannon/cannon_southeast.png";
    if (deg >= -120.0f && deg < -60.0f) return "cannon/cannon_south.png";
    if (deg >= -180.0f && deg < -120.0f) return "cannon/cannon_southwest.png";
    // deg in [120, 180]
    return "cannon/cannon_northwest.png";
}

/**
 * Updates the cannon sprite texture to match the target direction.
 *
 * Note: We preserve the node's position and anchor. We may adjust its scale to keep the
 * cannon constrained to a consistent on-screen footprint when different facing textures
 * have different source pixel sizes.
 */
void UpdateCannonFacingSprite(Sprite* cannonSprite, const Vec2& cannonPos, const Vec2& targetPos)
{
    if (!cannonSprite) return;

    // Preserve the current on-screen size of the cannon before swapping textures.
    // The directional cannon textures may have different raw pixel dimensions, and
    // without this, the cannon would visually "grow" or "shrink" when its facing
    // changes.
    const Size oldWorldSize = cannonSprite->getBoundingBox().size;

    const std::string texPath = GetCannonFacingTexturePath(cannonPos, targetPos);
    auto* tex = Director::getInstance()->getTextureCache()->addImage(texPath);
    if (!tex) return;

    cannonSprite->setTexture(tex);
    const Size ts = tex->getContentSize();
    cannonSprite->setTextureRect(Rect(0, 0, ts.width, ts.height));

    // Re-apply a scale so the sprite remains bounded by the same world-space box.
    // We keep aspect ratio to avoid stretching the art.
    if (ts.width > 0.0f && ts.height > 0.0f && oldWorldSize.width > 0.0f && oldWorldSize.height > 0.0f)
    {
        const float sx = oldWorldSize.width / ts.width;
        const float sy = oldWorldSize.height / ts.height;
        const float s = std::min(sx, sy);
        cannonSprite->setScale(std::max(0.0001f, s));
    }
}

}  // namespace

static void playUnitHitSfx(const UnitBase& attacker, const Building& target)
{
    
    if (dynamic_cast<const GoldMine*>(&target) || dynamic_cast<const GoldStorage*>(&target))
    {
        SoundManager::playSfxRandom("coin_steal", 1.0f);
        return;
    }
    if (dynamic_cast<const ElixirCollector*>(&target) || dynamic_cast<const ElixirStorage*>(&target))
    {
        SoundManager::playSfxRandom("elixir_steal", 1.0f);
        return;
    }

    switch (attacker.unitId)
    {
    case 2: 
        SoundManager::playSfxRandom("arrow_hit", 1.0f);
        break;
    case 3: 
        SoundManager::playSfxRandom("giant_attack", 1.0f);
        break;
    case 4: 
        SoundManager::playSfxRandom("wall_breaker_attack", 1.0f);
        break;
    default: 
        SoundManager::playSfxRandom("barbarian_hit_stuff", 1.0f);
        break;
    }
}

static const char* HPBAR_NAME = "__hpbar";
static const char* HPFILL_NAME = "__hpfill";
static const char* HPBG_NAME = "__hpbg";

bool CombatSystem::isInRange(const Vec2& a, const Vec2& b, float range)
{
    return a.distance(b) <= range;
}

static void punchScale(Sprite* s, int tag)
{
    if (!s) return;
    s->stopActionByTag(tag);
    float sx = s->getScaleX();
    float sy = s->getScaleY();
    auto a = Sequence::create(
        ScaleTo::create(0.05f, sx * 1.03f, sy * 1.03f),
        ScaleTo::create(0.06f, sx, sy),
        nullptr
    );
    a->setTag(tag);
    s->runAction(a);
}

static void showDamage(Node* parent, const Vec2& pos, int dmg)
{
    if (!parent) return;
    auto lab = Label::createWithSystemFont(StringUtils::format("-%d", dmg), "Arial", 20);
    if (!lab) return;
    lab->setPosition(pos + Vec2(0, 16));
    lab->setOpacity(230);
    parent->addChild(lab, 999);

    auto act = Sequence::create(
        Spawn::create(
            MoveBy::create(0.45f, Vec2(0, 28)),
            FadeOut::create(0.45f),
            nullptr
        ),
        RemoveSelf::create(),
        nullptr
    );
    lab->runAction(act);
}

void CombatSystem::ensureHpBar(Sprite* sprite, int hp, int hpMax, bool isUnit)
{
    if (!sprite) return;
    if (hpMax <= 0) hpMax = 1;
    if (hp < 0) hp = 0;
    if (hp > hpMax) hp = hpMax;

    Node* bar = sprite->getChildByName(HPBAR_NAME);
    LayerColor* bg = nullptr;
    LayerColor* fill = nullptr;

    
    const float w = isUnit ? 40.0f : 48.0f;
    const float h = 5.0f;
    const float pad = 1.0f;

    
    Vec2 ap = sprite->getAnchorPointInPoints();          
    float gapUnder = 7.0f;                               
    float yUnit = ap.y - (h * 0.5f + gapUnder);          
    float yBuilding = sprite->getContentSize().height + 12.0f; 

    if (!bar)
    {
        bar = Node::create();
        bar->setName(HPBAR_NAME);

        
        float sx = std::max(0.001f, sprite->getScaleX());
        float sy = std::max(0.001f, sprite->getScaleY());
        bar->setScaleX(1.0f / sx);
        bar->setScaleY(1.0f / sy);

        
        bar->setPosition(Vec2(std::round(ap.x), std::round(isUnit ? yUnit : yBuilding)));
        sprite->addChild(bar, 999);

        bg = LayerColor::create(Color4B(0, 0, 0, 160), w, h);
        bg->setName(HPBG_NAME);
        bg->setIgnoreAnchorPointForPosition(false);
        bg->setAnchorPoint(Vec2(0.5f, 0.5f));
        bg->setPosition(Vec2(0, 0));
        bar->addChild(bg);

        float fw = std::max(1.0f, w - pad * 2.0f);
        float fh = std::max(1.0f, h - pad * 2.0f);
        fill = LayerColor::create(Color4B(60, 220, 90, 220), fw, fh);
        fill->setName(HPFILL_NAME);
        fill->setIgnoreAnchorPointForPosition(false);
        fill->setAnchorPoint(Vec2(0.0f, 0.5f));
        fill->setPosition(Vec2(-w * 0.5f + pad, 0));
        bar->addChild(fill);
    }
    else
    {
        
        bar->setPosition(Vec2(std::round(ap.x), std::round(isUnit ? yUnit : yBuilding)));

        bg = dynamic_cast<LayerColor*>(bar->getChildByName(HPBG_NAME));
        fill = dynamic_cast<LayerColor*>(bar->getChildByName(HPFILL_NAME));
    }

    if (!fill) return;

    float pct = (float)hp / (float)hpMax;
    pct = std::max(0.0f, std::min(1.0f, pct));
    fill->setScaleX(pct);

    
    if (!isUnit) bar->setVisible(pct < 0.999f);
    else bar->setVisible(true);
}


bool CombatSystem::tryUnitAttackBuilding(UnitBase& attacker,
    Sprite* attackerSprite,
    Building& target,
    Sprite* targetSprite)
{
    if (!attackerSprite || !targetSprite) return false;
    if (attacker.isDead() || target.hp <= 0) return false;

    if (!attacker.canAttack()) return false;

    Vec2 ap = attackerSprite->getPosition();
    Vec2 tp = targetSprite->getPosition();

    if (!isInRange(ap, tp, attacker.attackRange))
        return false;

    
    playUnitHitSfx(attacker, target);

    int dmg = AttackVisitor::computeDamage(attacker, target);
    target.hp -= dmg;
    if (target.hp < 0) target.hp = 0;

    attacker.startAttackCooldown();

    
    punchScale(targetSprite, 12345);
    ensureHpBar(targetSprite, target.hp, target.hpMax, false);
    showDamage(targetSprite->getParent(), tp, dmg);

    return true;
}

bool CombatSystem::unitHitBuildingNoRange(UnitBase& attacker,
    Sprite* attackerSprite,
    Building& target,
    Sprite* targetSprite)
{
    if (!attackerSprite || !targetSprite) return false;
    if (attacker.isDead() || target.hp <= 0) return false;
    if (!attacker.canAttack()) return false;

    Vec2 tp = targetSprite->getPosition();

    
    playUnitHitSfx(attacker, target);

    int dmg = AttackVisitor::computeDamage(attacker, target);
    target.hp -= dmg;
    if (target.hp < 0) target.hp = 0;

    attacker.startAttackCooldown();

    punchScale(targetSprite, 12345);
    ensureHpBar(targetSprite, target.hp, target.hpMax, false);
    showDamage(targetSprite->getParent(), tp, dmg);
    return true;
}

bool CombatSystem::tryBomberExplode(UnitBase& bomber,
    Sprite* bomberSprite,
    EnemyBuildingRuntime& targetWall,
    std::vector<EnemyBuildingRuntime>& enemyBuildings)
{
    if (!bomberSprite || !targetWall.sprite || !targetWall.building) return false;
    if (bomber.isDead()) return false;
    if (targetWall.building->hp <= 0) return false;
    if (targetWall.id != 10) return false; 

    if (!bomber.canAttack()) return false;

    Vec2 bp = bomberSprite->getPosition();
    Vec2 wp = targetWall.sprite->getPosition();
    if (!isInRange(bp, wp, bomber.attackRange))
        return false;

    
    SoundManager::playSfxRandom("wall_breaker_attack", 1.0f);

    
    const WallBreaker* wb = dynamic_cast<const WallBreaker*>(&bomber);
    int multiplier = wb ? wb->wallDamageMultiplier : 40;
    float radiusTiles = wb ? wb->damageRadiusTiles : 2.0f;
    int wallDmg = std::max(1, bomber.damage * multiplier);

    int tr = targetWall.r;
    int tc = targetWall.c;

    for (auto& e : enemyBuildings)
    {
        if (!e.building || e.building->hp <= 0 || !e.sprite) continue;
        if (e.id != 10) continue;

        float dr = (float)(e.r - tr);
        float dc = (float)(e.c - tc);
        float dist = std::sqrt(dr * dr + dc * dc);
        if (dist > radiusTiles + 0.001f) continue;

        e.building->hp -= wallDmg;
        if (e.building->hp < 0) e.building->hp = 0;

        punchScale(e.sprite, 22345);
        ensureHpBar(e.sprite, e.building->hp, e.building->hpMax, false);
        showDamage(e.sprite->getParent(), e.sprite->getPosition(), wallDmg);
    }

    
    bomber.hp = 0;

    
    showDamage(bomberSprite->getParent(), bp, 999);
    bomber.startAttackCooldown();
    return true;
}

bool CombatSystem::bomberExplodeNoRange(UnitBase& bomber,
    Sprite* bomberSprite,
    EnemyBuildingRuntime& targetWall,
    std::vector<EnemyBuildingRuntime>& enemyBuildings)
{
    if (!bomberSprite || !targetWall.sprite || !targetWall.building) return false;
    if (bomber.isDead()) return false;
    if (targetWall.building->hp <= 0) return false;
    if (targetWall.id != 10) return false;

    if (!bomber.canAttack()) return false;

    
    const WallBreaker* wb = dynamic_cast<const WallBreaker*>(&bomber);
    int multiplier = wb ? wb->wallDamageMultiplier : 40;
    float radiusTiles = wb ? wb->damageRadiusTiles : 2.0f;
    int wallDmg = std::max(1, bomber.damage * multiplier);

    int tr = targetWall.r;
    int tc = targetWall.c;

    for (auto& e : enemyBuildings)
    {
        if (!e.building || e.building->hp <= 0 || !e.sprite) continue;
        if (e.id != 10) continue;

        float dr = (float)(e.r - tr);
        float dc = (float)(e.c - tc);
        float dist = std::sqrt(dr * dr + dc * dc);
        if (dist > radiusTiles + 0.001f) continue;

        e.building->hp -= wallDmg;
        if (e.building->hp < 0) e.building->hp = 0;

        punchScale(e.sprite, 22345);
        ensureHpBar(e.sprite, e.building->hp, e.building->hpMax, false);
        showDamage(e.sprite->getParent(), e.sprite->getPosition(), wallDmg);
    }

    
    bomber.hp = 0;

    Vec2 bp = bomberSprite->getPosition();
    showDamage(bomberSprite->getParent(), bp, 999);
    bomber.startAttackCooldown();
    return true;
}

bool CombatSystem::tryDefenseShoot(float dt,
    Building& defense,
    Sprite* defenseSprite,
    std::vector<BattleUnitRuntime>& units,
    float& cooldown,
    float cellSizePx)
{
    if (!defenseSprite) return false;
    if (defense.hp <= 0) return false;

    float dmgPerHit = 0.0f;
    float atkPerSec = 0.0f;
    int rangeCells = 0;

    if (auto t = dynamic_cast<ArrowTower*>(&defense))
    {
        dmgPerHit = t->damagePerHit;
        atkPerSec = t->attacksPerSecond;
        rangeCells = t->rangeCells;
    }
    else if (auto c = dynamic_cast<Cannon*>(&defense))
    {
        dmgPerHit = c->damagePerHit;
        atkPerSec = c->attacksPerSecond;
        rangeCells = c->rangeCells;
    }
    else
    {
        return false;
    }

    if (atkPerSec <= 0.0001f) return false;

    float atkInterval = 1.0f / atkPerSec;
    float rangePx = std::max(20.0f, (float)rangeCells * std::max(8.0f, cellSizePx));

    cooldown -= dt;
    if (cooldown > 0.0f) return false;

    
    int best = -1;
    float bestDist = 1e30f;
    Vec2 ep = defenseSprite->getPosition();

    for (int i = 0; i < (int)units.size(); ++i)
    {
        auto& u = units[i];
        if (!u.unit || !u.sprite) continue;
        if (u.unit->isDead()) continue;

        float d = u.sprite->getPosition().distance(ep);
        if (d <= rangePx && d < bestDist)
        {
            bestDist = d;
            best = i;
        }
    }
    if (best < 0) return false;

    // Lock the victim now so both facing and damage are applied to the same unit.
    auto& victim = units[best];

    // If this defense is a cannon, rotate its barrel sprite towards the chosen victim.
    // We do this before playing SFX/damage so the feedback feels immediate.
    if (dynamic_cast<Cannon*>(&defense) && victim.sprite)
    {
        UpdateCannonFacingSprite(defenseSprite, ep, victim.sprite->getPosition());
    }

    if (dynamic_cast<ArrowTower*>(&defense)) {
        SoundManager::playSfxRandom("arrow_hit", 1.0f);
    } else if (dynamic_cast<Cannon*>(&defense)) {
        SoundManager::playSfxRandom("cannon_attack", 1.0f);
    }
    int dmg = (int)std::ceil(std::max(1.0f, dmgPerHit));

    victim.unit->takeDamage(dmg);

    
    ensureHpBar(victim.sprite, victim.unit->hp, victim.unit->hpMax, true);
    showDamage(victim.sprite ? victim.sprite->getParent() : nullptr,
        victim.sprite ? victim.sprite->getPosition() : ep, dmg);

    cooldown = atkInterval;
    return true;
}
