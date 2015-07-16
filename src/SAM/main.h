#ifndef Main_H
#define Main_H


class Card;
class CardStack;
class Character;
class Dragon;
class Hero;
class Magic;
class Sword;
class Table;
class Turn;


class Chop;
class Dodge;
class HealthStone;
class Parry;
class Thorn;


class AoeCard;
class AttackCard;
class BuffCard;
class ControlCard;
class DebuffCard;
class DefenseCard;
class DisturbCard;
class PassCard;


class HuXin;
class HuXueDong;


class ArcaneEcho;
class ArcaneInstability;
class Armageddon;
class Avatar;
class Berserker;
class Blade;
class Blind;
class BlurredSpeed;
class CelestialAlignment;
class CheatedDeath;
class ColdBlood;
class Comet;
class CometStorm;
class CounterSpell;
class Crafty;
class DeathWish;
class DeepWounds;
class DieAfterSword;
class Evocation;
class Fireball;
class Garrote;
class IceBarrier;
class IceBlock;
class MassiveSmash;
class MortalStrike;
class Polymorph;
class Reflection;
class Sap;
class ShadowsCloak;
class SliceDice;
class Stealth;
class StormBolt;
class Sweep;
class UnDragonBreath;
class UnMeteor;
class WeaponMaster;



#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <time.h>
#include <typeinfo>
using namespace std;
#include "Enum.h"
#include "Card.h"
#include "CardStack.h"
#include "Character.h"
#include "Dragon.h"
#include "Hero.h"
#include "AI.h"
#include "Magic.h"
#include "Sword.h"
#include "Table.h"
#include "Turn.h"


#include "Magics\ArcaneEcho.cpp"
#include "Magics\ArcaneInstability.cpp"
#include "Magics\Armageddon.cpp"
#include "Magics\Avatar.cpp"
#include "Magics\Berserker.cpp"
#include "Magics\Blade.cpp"
#include "Magics\Blind.cpp"
#include "Magics\BlurredSpeed.cpp"
#include "Magics\CelestialAlignment.cpp"
#include "Magics\CheatedDeath.cpp"
#include "Magics\ColdBlood.cpp"
#include "Magics\Comet.cpp"
#include "Magics\CometStorm.cpp"
#include "Magics\CounterSpell.cpp"
#include "Magics\Crafty.cpp"
#include "Magics\DeathWish.cpp"
#include "Magics\DeepWounds.cpp"
#include "Magics\DieAfterSword.cpp"
#include "Magics\Evocation.cpp"
#include "Magics\Fireball.cpp"
#include "Magics\Garrote.cpp"
#include "Magics\IceBarrier.cpp"
#include "Magics\IceBlock.cpp"
#include "Magics\MassiveSmash.cpp"
#include "Magics\MortalStrike.cpp"
#include "Magics\Polymorph.cpp"
#include "Magics\Reflection.cpp"
#include "Magics\Sap.cpp"
#include "Magics\ShadowsCloak.cpp"
#include "Magics\SliceDice.cpp"
#include "Magics\Stealth.cpp"
#include "Magics\StormBolt.cpp"
#include "Magics\Sweep.cpp"
#include "Magics\UnDragonBreath.cpp"
#include "Magics\UnMeteor.cpp"
#include "Magics\WeaponMaster.cpp"


#include "BaseCard\Chop.cpp"
#include "BaseCard\Dodge.cpp"
#include "BaseCard\HealthStone.cpp"
#include "BaseCard\Parry.cpp"
#include "BaseCard\Thorn.cpp"


#include "MagicCard\AoeCard.cpp"
#include "MagicCard\AttackCard.cpp"
#include "MagicCard\BuffCard.cpp"
#include "MagicCard\ControlCard.cpp"
#include "MagicCard\DebuffCard.cpp"
#include "MagicCard\DefenseCard.cpp"
#include "MagicCard\DisturbCard.cpp"
#include "MagicCard\PassCard.cpp"


#include "Heros\HuXin.cpp"
#include "Heros\HuXueDong.cpp"

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include <time.h>
#include <typeinfo>
using namespace std;



#endif
