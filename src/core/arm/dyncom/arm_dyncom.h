// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <memory>

#include "common/common_types.h"

#include "core/arm/arm_interface.h"
#include "core/arm/skyeye_common/armdefs.h"

class ARM_DynCom final : virtual public ARM_Interface {
public:
    ARM_DynCom(PrivilegeMode initial_mode);
    ~ARM_DynCom();

    void SetPC(u32 pc) override;
    u32 GetPC() const override;
    u32 GetReg(int index) const override;
    void SetReg(int index, u32 value) override;
    u32 GetCPSR() const override;
    void SetCPSR(u32 cpsr) override;

    u64 GetTicks() const override;
    void AddTicks(u64 ticks) override;

    void ResetContext(Core::ThreadContext& context, u32 stack_top, u32 entry_point, u32 arg);
    void SaveContext(Core::ThreadContext& ctx) override;
    void LoadContext(const Core::ThreadContext& ctx) override;

    void PrepareReschedule() override;
    void ExecuteInstructions(int num_instructions) override;

private:
    std::unique_ptr<ARMul_State> state;
};
