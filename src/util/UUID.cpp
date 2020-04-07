//
// Created by jonas on 02.04.20.
//

#include "UUID.hpp"
#include <array>

namespace spy::util {

    void UUID::clear() {
        uuid_clear(uuidData);
    }

    std::string UUID::toString() const {
        char uuidRawString[37];
        uuid_unparse(uuidData, uuidRawString);
        return std::string(uuidRawString);
    }

    UUID::UUID() {
        uuid_generate(uuidData);
    }

    bool UUID::operator==(const UUID &rhs) const {
        return uuid_compare(uuidData, rhs.uuidData) == 0;
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

    UUID::UUID(const UUID &rhs) {
        uuid_copy(uuidData, rhs.uuidData);
    }

    UUID::UUID(const std::string &s) {
        if (uuid_parse(s.c_str(), uuidData) != 0) {
            throw std::invalid_argument("Could not parse \"" + s + "\" as a UUID.");
        }
    }

    std::ostream &operator<<(std::ostream &stream, const UUID &uuid) {
        return stream << uuid.toString();
    }
}