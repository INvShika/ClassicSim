#include "CharacterSpells.h"

#include "Berserking.h"
#include "BloodFury.h"
#include "Character.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "Engine.h"
#include "MainhandAttack.h"
#include "MainhandMeleeHit.h"
#include "OffhandAttack.h"
#include "OffhandMeleeHit.h"
#include "Race.h"
#include "Target.h"

CharacterSpells::CharacterSpells(Character* pchar) :
    pchar(pchar),
    next_instance_id(SpellStatus::INITIAL_ID)
{
    berserking = new Berserking(pchar);
    blood_fury = new BloodFury(pchar);
    spells = {berserking, blood_fury};
}

CharacterSpells::~CharacterSpells()
{
    for (auto & spell : spells)
        delete spell;

    spells.clear();
    pre_combat_spells.clear();
}

void CharacterSpells::activate_racials() {
    switch (pchar->get_race()->get_race_int()) {
    case Races::Orc:
        blood_fury->enable();
        break;
    case Races::Troll:
        berserking->enable();
        if (pchar->get_target()->get_creature_type() == Target::CreatureType::Beast)
            pchar->get_stats()->increase_total_phys_dmg_mod(5);
        break;
    }
}

void CharacterSpells::deactivate_racials() {
    switch (pchar->get_race()->get_race_int()) {
    case Races::Orc:
        blood_fury->disable();
        break;
    case Races::Troll:
        berserking->disable();
        if (pchar->get_target()->get_creature_type() == Target::CreatureType::Beast)
            pchar->get_stats()->decrease_total_phys_dmg_mod(5);
        break;
    }
}

void CharacterSpells::add_spell(Spell* spell, bool relink) {
    if (spell->get_instance_id() == SpellStatus::INACTIVE) {
        spell->set_instance_id(next_instance_id);
        ++next_instance_id;
    }

    spells.append(spell);

    if (relink)
        pchar->relink_spells();
}

void CharacterSpells::remove_spell(Spell* spell) {
    for (auto & i : spells) {
        if (i->get_instance_id() == spell->get_instance_id()) {
            spells.removeOne(i);
            break;
        }
    }
    pchar->relink_spells();
}

void CharacterSpells::add_pre_combat_spell(Spell* spell) {
    if (spell->get_instance_id() == SpellStatus::INACTIVE) {
        spell->set_instance_id(next_instance_id);
        ++next_instance_id;
    }

    pre_combat_spells.append(spell);
}

void CharacterSpells::remove_pre_combat_spell(Spell* spell) {
    for (auto & i : pre_combat_spells) {
        if (i->get_instance_id() == spell->get_instance_id()) {
            pre_combat_spells.removeOne(i);
            return;
        }
    }
}

void CharacterSpells::run_pre_combat_spells() {
    for (auto & spell : pre_combat_spells)
        spell->perform_pre_combat();
}

Spell* CharacterSpells::get_spell_by_name(const QString& spell_name) const {
    for (auto & spell : spells) {
        if (spell->get_name() == spell_name)
            return spell;
    }

    return nullptr;
}

void CharacterSpells::reset() {
    for (auto & spell : spells)
        spell->reset();
}

void CharacterSpells::start_attack() {
    add_next_mh_attack();

    if (pchar->is_dual_wielding()) {
        add_next_oh_attack();
    }
}

void CharacterSpells::mh_auto_attack(const int iteration) {
    if (!mh_attack->attack_is_valid(iteration))
        return;

    if (!pchar->is_melee_attacking())
        return;

    mh_attack->perform();

    add_next_mh_attack();
}

void CharacterSpells::add_next_mh_attack() {
    auto* new_event = new MainhandMeleeHit(this, get_mh_attack()->get_next_expected_use(), get_mh_attack()->get_next_iteration());
    pchar->get_engine()->add_event(new_event);
}

void CharacterSpells::oh_auto_attack(const int) {
    assert(false);
}

void CharacterSpells::add_next_oh_attack() {
    assert(false);
}

void CharacterSpells::add_next_ranged_attack() {
    assert(false);
}

MainhandAttack* CharacterSpells::get_mh_attack() const {
    return this->mh_attack;
}

OffhandAttack* CharacterSpells::get_oh_attack() const {
    assert(false);
    return nullptr;
}

AutoShoot* CharacterSpells::get_auto_shoot() const {
    return nullptr;
}

Berserking* CharacterSpells::get_berserking() const {
    return this->berserking;
}

BloodFury* CharacterSpells::get_blood_fury() const {
    return this->blood_fury;
}

void CharacterSpells::prepare_set_of_combat_iterations() {
    for (auto & spell : spells)
        spell->prepare_set_of_combat_iterations();
}
