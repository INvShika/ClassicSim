#ifndef TESTSPELL_H
#define TESTSPELL_H

#include <QDebug>
#include <QSet>
#include <QString>

#include "TestUtils.h"

class Character;
class CombatRoll;
class Engine;
class Equipment;
class EquipmentDb;
class Faction;
class Race;
class SimSettings;
class Target;

static const bool RUN_EVENT = true;

class TestSpell : public TestUtils {
public:
    TestSpell(EquipmentDb *equipment_db, QString spell_under_test);
    ~TestSpell() = default;

    void set_up_general();
    void tear_down_general();

    void given_no_previous_damage_dealt();
    void given_a_guaranteed_white_hit();
    void given_a_guaranteed_white_glancing_blow();
    void given_a_guaranteed_white_crit();
    void given_a_guaranteed_white_miss();
    void given_a_guaranteed_white_dodge();
    void given_a_guaranteed_white_parry();
    void given_a_guaranteed_white_block();
    void given_a_guaranteed_melee_ability_crit();
    void given_a_guaranteed_melee_ability_hit();
    void given_a_guaranteed_melee_ability_miss();
    void given_a_guaranteed_melee_ability_dodge();
    void given_a_guaranteed_melee_ability_parry();
    void given_a_guaranteed_melee_ability_block();
    void given_a_guaranteed_ranged_white_hit();
    void given_a_guaranteed_ranged_white_crit();
    void given_a_guaranteed_ranged_white_miss();
    void given_a_guaranteed_ranged_white_dodge();
    void given_a_guaranteed_ranged_white_block();
    void given_300_weapon_skill_mh();
    void given_305_weapon_skill_mh();
    void given_310_weapon_skill_mh();
    void given_315_weapon_skill_mh();
    void given_300_weapon_skill_oh();
    void given_305_weapon_skill_oh();
    void given_310_weapon_skill_oh();
    void given_315_weapon_skill_oh();
    void given_a_mainhand_weapon_with_100_min_max_dmg();
    void given_a_mainhand_dagger_with_100_min_max_dmg();
    void given_a_mainhand_weapon_with_3_speed();
    void given_a_mainhand_weapon_with_2_speed();
    void given_a_twohand_weapon_with_100_min_max_dmg();
    void given_no_mainhand();
    void given_no_offhand();
    void given_an_offhand_weapon_with_100_min_max_dmg();
    void given_an_offhand_weapon_with_3_speed();
    void given_an_offhand_weapon_with_2_speed();
    void given_an_offhand_axe();
    void given_a_ranged_weapon_with_100_min_max_dmg();
    void given_a_ranged_weapon_with_3_speed();
    void given_a_ranged_weapon_with_2_speed();
    void given_1000_melee_ap();
    void given_1000_ranged_ap();
    void given_target_has_0_armor();
    void given_engine_priority_at(const double priority);
    void given_engine_priority_pushed_forward(const double priority);
    void given_event_is_ignored(const QString& event);
    void given_1h_axe_equipped_in_mainhand(Character* pchar);
    void given_1h_mace_equipped_in_mainhand(Character* pchar);
    void given_1h_sword_equipped_in_mainhand(Character* pchar);
    void given_fist_weapon_equipped_in_mainhand(Character* pchar);
    void given_dagger_equipped_in_mainhand(Character* pchar);

    void given_no_mainhand(Character* pchar);
    void given_no_offhand(Character* pchar);

    void given_1h_axe_equipped_in_offhand(Character* pchar);
    void given_1h_mace_equipped_in_offhand(Character* pchar);
    void given_1h_sword_equipped_in_offhand(Character* pchar);
    void given_fist_weapon_equipped_in_offhand(Character* pchar);
    void given_dagger_equipped_in_offhand(Character* pchar);

    void given_2h_axe_equipped(Character* pchar);
    void given_2h_mace_equipped(Character* pchar);
    void given_2h_sword_equipped(Character* pchar);
    void given_polearm_equipped(Character* pchar);
    void given_staff_equipped(Character* pchar);

    void when_running_queued_events_until(const double priority);

    void then_damage_dealt_is(const int damage);
    void then_damage_dealt_is_in_range(const int min, const int max);
    void then_next_event_is(const QString &name);
    void then_next_event_is(const QString &name, const QString &priority, bool act_event = false);

    void dump_queued_events();

protected:
    EquipmentDb* equipment_db;
    SimSettings* sim_settings;
    Character* pchar;
    Race* race;
    QString spell_under_test;
    QSet<QString> ignored_events;

    void set_melee_special_table_for_hit(const int wpn_skill);
    void set_melee_special_table_for_crit(const int wpn_skill);
    void set_melee_special_table_for_miss(const int wpn_skill);
    void set_melee_special_table_for_dodge(const int wpn_skill);
    void set_melee_special_table_for_parry(const int wpn_skill);
    void set_melee_special_table_for_block(const int wpn_skill);

    void set_melee_auto_table_for_hit(const int wpn_skill);
    void set_melee_auto_table_for_glancing(const int wpn_skill);
    void set_melee_auto_table_for_crit(const int wpn_skill);
    void set_melee_auto_table_for_miss(const int wpn_skill);
    void set_melee_auto_table_for_dodge(const int wpn_skill);
    void set_melee_auto_table_for_parry(const int wpn_skill);
    void set_melee_auto_table_for_block(const int wpn_skill);

    void set_ranged_auto_table_for_hit(const int wpn_skill);
    void set_ranged_auto_table_for_crit(const int wpn_skill);
    void set_ranged_auto_table_for_miss(const int wpn_skill);
    void set_ranged_auto_table_for_dodge(const int wpn_skill);
    void set_ranged_auto_table_for_block(const int wpn_skill);

    void assert_melee_special_table_can_only_hit(const int wpn_skill);
    void assert_melee_special_table_can_only_crit(const int wpn_skill);
    void assert_melee_special_table_can_only_miss(const int wpn_skill);
    void assert_melee_special_table_can_only_dodge(const int wpn_skill);
    void assert_melee_special_table_can_only_parry(const int wpn_skill);
    void assert_melee_special_table_can_only_block(const int wpn_skill);

    void assert_melee_auto_table_can_only_hit(const int wpn_skill);
    void assert_melee_auto_table_can_only_glance(const int wpn_skill);
    void assert_melee_auto_table_can_only_crit(const int wpn_skill);
    void assert_melee_auto_table_can_only_miss(const int wpn_skill);
    void assert_melee_auto_table_can_only_dodge(const int wpn_skill);
    void assert_melee_auto_table_can_only_parry(const int wpn_skill);
    void assert_melee_auto_table_can_only_block(const int wpn_skill);

    void assert_ranged_auto_table_can_only_hit(const int wpn_skill);
    void assert_ranged_auto_table_can_only_crit(const int wpn_skill);
    void assert_ranged_auto_table_can_only_miss(const int wpn_skill);
    void assert_ranged_auto_table_can_only_dodge(const int wpn_skill);
    void assert_ranged_auto_table_can_only_block(const int wpn_skill);

private:
    void create_100_dmg_1h();
    void create_100_dmg_dagger();
    void create_100_dmg_2h();
    void create_100_dmg_ranged();
    void create_3_speed_ranged();
    void create_2_speed_ranged();
    void create_3_speed();
    void create_2_speed();
    void create_axe();
    void create_5_sword_skill_ring();
    void create_10_sword_skill_ring();
    void create_15_sword_skill_ring();
};

#endif // TESTSPELL_H
