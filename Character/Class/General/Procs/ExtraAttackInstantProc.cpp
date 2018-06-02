
#include "ExtraAttackInstantProc.h"
#include "Character.h"
#include "StatisticsResource.h"
#include "ProcInfo.h"
#include "ExtraAttackOnNextSwingBuff.h"

ExtraAttackInstantProc::ExtraAttackInstantProc(Engine* engine, Character* pchar, CombatRoll* roll,
                                               QString proc_name,
                                               QVector<ProcInfo::Source> proc_sources,
                                               const float proc_rate, const int num_attacks) :
    Proc(proc_name, proc_rate, 0, false, QVector<Proc*>(), proc_sources, engine, pchar, roll),
    extra_attack_buff(nullptr),
    num_attacks(num_attacks)
{
    assert(proc_sources.contains(ProcInfo::Source::MainhandSwing) || proc_sources.contains(ProcInfo::Source::OffhandSwing));
}

ExtraAttackInstantProc::~ExtraAttackInstantProc() {
}

void ExtraAttackInstantProc::proc_effect() {
    if (extra_attack_buff != nullptr)
        proc_from_next_swing_effect();
    else
        proc_from_instant_effect();
}

void ExtraAttackInstantProc::set_extra_attack_buff(ExtraAttackOnNextSwingBuff* buff) {
    this->extra_attack_buff = buff;
}

void ExtraAttackInstantProc::proc_from_next_swing_effect() {
    assert(extra_attack_buff != nullptr);
    assert(extra_attack_buff->is_active());


    for (int i = 0; i < extra_attack_buff->get_charges(); ++i) {
        run_extra_attacks();
        extra_attack_buff->use_charge();
    }

    assert(!extra_attack_buff->is_active());
}

void ExtraAttackInstantProc::proc_from_instant_effect() {
    assert(extra_attack_buff == nullptr);

    for (int i = 0; i < num_attacks; ++i)
        run_extra_attacks();
}

void ExtraAttackInstantProc::run_extra_attacks() {
    if (proc_sources.contains(ProcInfo::Source::MainhandSwing) || proc_sources.contains(ProcInfo::Source::MainhandSpell))
        pchar->run_extra_mh_attack();
    if (proc_sources.contains(ProcInfo::Source::OffhandSwing) || proc_sources.contains(ProcInfo::Source::OffhandSpell))
        pchar->run_extra_oh_attack();
}