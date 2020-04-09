/**
 * @brief C++ wrapper for libuuid
 * @author Jonas Otto
 * @date April 2020
 */

#ifndef LIBCOMMON_UUID_HPP
#define LIBCOMMON_UUID_HPP

#include <uuid/uuid.h>
#include <string>
#include <nlohmann/json.hpp>

namespace spy::util {
    class UUID {
        public:

            /**
             * Creates an empty UUID, for generating a valid UUID see generate().
             */
            UUID() = default;

            /**
             * Parses a UUID from string
             * @param s UUID string of the form 1b4e28ba-2fa1-11d2-883f-b9a761bde3fb
             */
            explicit UUID(const std::string &s);

            /**
            * Constructs a random UUID, see uuid_generate(3)
            * @return Random UUID
            */
            static UUID generate();

            void clear();

            bool isNull();

            /**
             * Converts the UUID into a string of the form 1b4e28ba-2fa1-11d2-883f-0016d3cca427
             */
            [[nodiscard]] std::string to_string() const;

            /**
             * Same as to_string(), but with upper case hex digits
             */
            [[nodiscard]] std::string to_string_upper() const;

            /**
            * Same as to_string(), but with lower case hex digits
            */
            [[nodiscard]] std::string to_string_lower() const;

            bool operator==(const UUID &rhs) const;

            bool operator<(const UUID &rhs) const;

            bool operator>(const UUID &rhs) const;

            bool operator<=(const UUID &rhs) const;

            bool operator>=(const UUID &rhs) const;

            template<typename OStream>
            friend OStream &operator<<(OStream &stream, const UUID &uuid) {
                return stream << uuid.to_string();
            }

            friend void to_json(nlohmann::json &j, const UUID &u);

            friend void from_json(const nlohmann::json &j, UUID &u);

        private:
            uuid_t uuidData{};
    };
}

#endif //LIBCOMMON_UUID_HPP
