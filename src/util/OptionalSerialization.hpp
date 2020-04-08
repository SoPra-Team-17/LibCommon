/**
 * @file OptionalSerialization.hpp
 * @author paul
 * @date 25.04.19
 * @brief Adds serialization and deserialization for std::optional<T> if T is serializable
 * @note Stolen from https://github.com/SoPra-Team-10/Messages/blob/2143f21ce627ccf7529751c503e89ee0091b213a/src/Util/OptionalSerialization.hpp
 * @responsibleForResultingUB paul
 */

#ifndef LIBCOMMON_OPTIONALSERIALIZATION_HPP
#define LIBCOMMON_OPTIONALSERIALIZATION_HPP

#include <nlohmann/json.hpp>

// TODO less criminal C++ (thou shalt not hack the std namespace)
//  "The behavior of a C++ program is undefined if it adds declarations or definitions to namespace std or to a
//   namespace within namespace std unless otherwise specified" - 20.5.4.2.1
namespace std {
    template<typename T>
    void to_json(nlohmann::json &j, const std::optional<T> &t) {
        if (t.has_value()) {
            j = t.value();
        } else {
            j = nullptr;
        }
    }

    template<typename T>
    void from_json(const nlohmann::json &j, std::optional<T> &t) {
        if (j.is_null()) {
            t = std::nullopt;
        } else {
            t = j.get<T>();
        }
    }
}

#endif //LIBCOMMON_OPTIONALSERIALIZATION_HPP
