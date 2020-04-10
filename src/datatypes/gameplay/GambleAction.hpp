/**
 * @file   GambleAction.hpp
 * @author Jonas
 * @brief  GambleAction operation
 */

#ifndef LIBCOMMON_GAMBLEACTION_HPP
#define LIBCOMMON_GAMBLEACTION_HPP

#include "Operation.hpp"

namespace spy::gameplay {
    class GambleAction : public Operation {
        public:
            GambleAction() = default;

            GambleAction(bool successful, const util::Point &target, const util::UUID &characterId, int stake);

            [[nodiscard]] int getStake() const;

            bool operator==(const GambleAction &rhs) const;

            bool operator!=(const GambleAction &rhs) const;

            friend void to_json(nlohmann::json &j, const GambleAction &g);

            friend void from_json(const nlohmann::json &j, GambleAction &g);

        private:
            int stake = 0;
    };

}
#endif //LIBCOMMON_GAMBLEACTION_HPP
