#ifndef MELEESPECIALTABLE_H
#define MELEESPECIALTABLE_H

#include "PhysicalAttackResult.h"

class Random;

class MeleeSpecialTable {
public:
    MeleeSpecialTable(Random* _rand,
                      const int wpn_skill,
                      const double miss,
                      const double dodge,
                      const double parry,
                      const double block);

    int get_outcome(const unsigned roll,
                    const double crit_chance,
                    const bool include_dodge = true,
                    const bool include_parry = true,
                    const bool include_block = true,
                    const bool include_miss = true);
    void dump_table(void);
    void update_miss_chance(const double miss);
    void update_dodge_chance(const double dodge);
    void update_parry_chance(const double parry);
    void update_block_chance(const double block);

    int get_wpn_skill();

    void update_ranges();

private:
    Random* random;
    const int wpn_skill;

    double miss;
    double dodge;
    double parry;
    double block;

    unsigned miss_range{};
    unsigned dodge_range{};
    unsigned parry_range{};
    unsigned block_range{};
};

#endif // MELEESPECIALTABLE_H
