/**
 * @file   Exfiltration.hpp
 * @author Jonas
 * @brief  Exfiltration operation
 */

#ifndef LIBCOMMON_EXFILTRATION_HPP
#define LIBCOMMON_EXFILTRATION_HPP

#include "CharacterOperation.hpp"

namespace spy::gameplay {
    class Exfiltration : public CharacterOperation {
        public:

            Exfiltration() = default;

            Exfiltration(bool successful, const util::Point &target, const util::UUID &characterId,
                         const util::Point &from);

            [[nodiscard]] const util::Point &getFrom() const;

            friend void to_json(nlohmann::json &j, const Exfiltration &e);

            friend void from_json(const nlohmann::json &j, Exfiltration &e);

        private:
            util::Point from{};

            [[nodiscard]] bool isEqual(const BaseOperation &rhs) const override;
    };

}
#endif //LIBCOMMON_EXFILTRATION_HPP
