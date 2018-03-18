
#include "HeroicStrike.h"
#include "Warrior.h"

#include <iostream>

HeroicStrike::HeroicStrike(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Heroic Strike", engine, pchar, roll, 0, 13)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
}

int HeroicStrike::spell_effect(const int) const {
    AttackResult* result = roll->get_melee_ability_result(pchar->get_mh_wpn_skill());

    if (result->is_miss()) {
        add_fail_stats("Miss");
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        add_fail_stats("Dodge");
    }
    if (result->is_parry()) {
        add_fail_stats("Parry");
    }

    int damage_dealt = pchar->get_mh_dmg() + 138;

    // TODO: Apply Flurry
    if (result->is_critical()) {
        // TODO: Remove hardcoding of 2/2 Impale.
        damage_dealt *= 2.2;
        add_success_stats("Critical", damage_dealt);
    }
    else if (result->is_hit())
        add_success_stats("Hit", damage_dealt);

    return resource_cost;
}
