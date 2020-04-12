//
// Created by jonas on 12.04.20.
//

#ifndef LIBCOMMON_VARIANTSERIALIZATION_HPP
#define LIBCOMMON_VARIANTSERIALIZATION_HPP

#include <nlohmann/json.hpp>

namespace nlohmann {
    template<typename... T>
    struct adl_serializer<std::variant<T...>> {
        static void to_json(json &j, const std::variant<T...> &opt) {
            std::visit([&j](auto const &arg) {
                j = arg;
            }, opt);
        }
    };
}

#endif //LIBCOMMON_VARIANTSERIALIZATION_HPP
