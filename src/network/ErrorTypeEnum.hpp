//
// Created by jonas on 07.04.20.
//

#ifndef LIBCOMMON_ERRORTYPEENUM_HPP
#define LIBCOMMON_ERRORTYPEENUM_HPP

#include <nlohmann/json.hpp>

namespace spy::network {
    enum class ErrorTypeEnum {
            INVALID,
            NAME_NOT_AVAILABLE,
            ALREADY_SERVING,
            GENERAL
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(ErrorTypeEnum, {
        { ErrorTypeEnum::INVALID, nullptr },
        { ErrorTypeEnum::NAME_NOT_AVAILABLE, "NAME_NOT_AVAILABLE" },
        { ErrorTypeEnum::ALREADY_SERVING, "ALREADY_SERVING" },
        { ErrorTypeEnum::GENERAL, "GENERAL" }
    })
}

#endif //LIBCOMMON_ERRORTYPEENUM_HPP
