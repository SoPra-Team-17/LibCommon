/**
 * @file   Exfiltration.hpp
 * @author Jonas
 * @brief  Exfiltration operation
 */

#ifndef LIBCOMMON_EXFILTRATION_HPP
#define LIBCOMMON_EXFILTRATION_HPP

#include "Operation.hpp"

namespace spy::gameplay {
    class Exfiltration : public Operation {
        public:

            Exfiltration() = default;

            Exfiltration(bool successful, const util::Point &target, const util::UUID &characterId,
                         const util::Point &from);

            [[nodiscard]] const util::Point &getFrom() const;

            bool operator==(const Exfiltration &rhs) const;

            bool operator!=(const Exfiltration &rhs) const;

            friend void to_json(nlohmann::json &j, const Exfiltration &e);

            friend void from_json(const nlohmann::json &j, Exfiltration &e);

        private:
            util::Point from{};
    };

}
#endif //LIBCOMMON_EXFILTRATION_HPP
