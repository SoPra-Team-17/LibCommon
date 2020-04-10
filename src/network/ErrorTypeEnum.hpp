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
            SESSION_DOES_NOT_EXIST,
            ILLEGAL_MESSAGE,
            TOO_MANY_STRIKES,
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(ErrorTypeEnum, {
        { ErrorTypeEnum::INVALID, nullptr },
        { ErrorTypeEnum::NAME_NOT_AVAILABLE, "NAME_NOT_AVAILABLE" },
        { ErrorTypeEnum::ALREADY_SERVING, "ALREADY_SERVING" },
        { ErrorTypeEnum::SESSION_DOES_NOT_EXIST, "SESSION_DOES_NOT_EXIST" },
        { ErrorTypeEnum::ILLEGAL_MESSAGE, "ILLEGAL_MESSAGE" },
        { ErrorTypeEnum::TOO_MANY_STRIKES, "TOO_MANY_STRIKES" }
    })
}

#endif //LIBCOMMON_ERRORTYPEENUM_HPP
