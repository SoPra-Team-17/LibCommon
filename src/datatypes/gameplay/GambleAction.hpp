/**
 * @file   GambleAction.hpp
 * @author Jonas
 * @brief  GambleAction operation
 */

#ifndef LIBCOMMON_GAMBLEACTION_HPP
#define LIBCOMMON_GAMBLEACTION_HPP

#include "CharacterOperation.hpp"

namespace spy::gameplay {
    class GambleAction : public CharacterOperation {
        public:
            GambleAction() = default;

            GambleAction(bool successful, const util::Point &target, const util::UUID &characterId, unsigned int stake);

            [[nodiscard]] unsigned int getStake() const;

            void setStake(unsigned int stake);

            friend void to_json(nlohmann::json &j, const GambleAction &g);

            friend void from_json(const nlohmann::json &j, GambleAction &g);

            std::shared_ptr<BaseOperation> clone() const override;

        private:
            unsigned int stake = 0;

            [[nodiscard]] bool isEqual(const BaseOperation &rhs) const override;
    };

}
#endif //LIBCOMMON_GAMBLEACTION_HPP
