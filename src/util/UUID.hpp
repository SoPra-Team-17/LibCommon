//
// Created by jonas on 02.04.20.
//

#ifndef LIBCOMMON_UUID_HPP
#define LIBCOMMON_UUID_HPP


#include <uuid/uuid.h>
#include <string>

namespace spy::util {

    class UUID {
        public:
            UUID();

            UUID(const UUID &rhs);

            UUID(const std::string &s);

            void clear();

            [[nodiscard]] std::string toString() const;

            bool operator==(const UUID &rhs) const;

            bool operator<(const UUID &rhs) const;

            bool operator>(const UUID &rhs) const;

            bool operator<=(const UUID &rhs) const;

            bool operator>=(const UUID &rhs) const;

            friend std::ostream &operator<<(std::ostream &stream, const UUID &uuid);

        private:
            uuid_t uuidData;
    };

}

#endif //LIBCOMMON_UUID_HPP
