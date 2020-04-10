//
// Created by jonas on 10.04.20.
//

#ifndef LIBCOMMON_OPERATIONENUM_HPP
#define LIBCOMMON_OPERATIONENUM_HPP

#include <nlohmann/json.hpp>

namespace spy::gameplay {
    enum class OperationEnum {
            INVALID,
            GADGET_ACTION,
            SPY_ACTION,
            GAMBLE_ACTION,
            PROPERTY_ACTION,
            MOVEMENT,
            CAT_ACTION,
            JANITOR_ACTION,
            EXFILTRATION,
            RETIRE
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(OperationEnum, {
        { OperationEnum::INVALID, nullptr },
        { OperationEnum::GADGET_ACTION, "GADGET_ACTION" },
        { OperationEnum::SPY_ACTION, "SPY_ACTION" },
        { OperationEnum::GAMBLE_ACTION, "GAMBLE_ACTION" },
        { OperationEnum::PROPERTY_ACTION, "PROPERTY_ACTION" },
        { OperationEnum::MOVEMENT, "MOVEMENT" },
        { OperationEnum::CAT_ACTION, "CAT_ACTION" },
        { OperationEnum::JANITOR_ACTION, "JANITOR_ACTION" },
        { OperationEnum::EXFILTRATION, "EXFILTRATION" },
        { OperationEnum::RETIRE, "RETIRE" }
    })
}

#endif //LIBCOMMON_OPERATIONENUM_HPP
