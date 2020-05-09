/**
 * @file   UUID.cpp
 * @author Jonas Otto
 * @date   2. April 2020
 * @brief  C++ wrapper for libuuid.
 */

#include "UUID.hpp"
#include <array>

namespace spy::util {
    UUID::UUID(const std::string &s) {
        if (uuid_parse(s.c_str(), uuidData) != 0) {
            throw std::invalid_argument("Could not parse \"" + s + "\" as a UUID.");
        }
    }

    UUID UUID::generate() {
        UUID u;
        uuid_generate(u.uuidData);
        return u;
    }

    void UUID::clear() {
        uuid_clear(uuidData);
    }

    bool UUID::isNull() const {
        return uuid_is_null(uuidData);
    }

    std::string UUID::to_string() const {
        char uuidRawString[37];
        uuid_unparse(uuidData, uuidRawString);
        return std::string(uuidRawString);
    }

    std::string UUID::to_string_upper() const {
        char uuidRawString[37];
        uuid_unparse_upper(uuidData, uuidRawString);
        return std::string(uuidRawString);
    }

    std::string UUID::to_string_lower() const {
        char uuidRawString[37];
        uuid_unparse_lower(uuidData, uuidRawString);
        return std::string(uuidRawString);
    }

    bool UUID::operator==(const UUID &rhs) const {
        return uuid_compare(uuidData, rhs.uuidData) == 0;
    }

    bool UUID::operator!=(const UUID &rhs) const {
        return !(*this == rhs);
    }

    bool UUID::operator<(const UUID &rhs) const {
        return uuid_compare(uuidData, rhs.uuidData) < 0;
    }

    bool UUID::operator>(const UUID &rhs) const {
        return rhs < *this;
    }

    bool UUID::operator<=(const UUID &rhs) const {
        return !(rhs < *this);
    }

    bool UUID::operator>=(const UUID &rhs) const {
        return !(*this < rhs);
    }

    void to_json(nlohmann::json &j, const UUID &c) {
        j = c.to_string();
    }

    void from_json(const nlohmann::json &j, UUID &c) {
        c = UUID(j.get<std::string>());
    }
}