//
// Created by Carolin on 08.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "util/GameLogicUtils.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateJetpack(const State &s, const util::UUID &activeCharacter,
                                     const spy::MatchConfig &config) {
        /**
         * CAUTION: N * M many comparisons, where N and M are height and width of map
         */

        std::vector<std::shared_ptr<BaseOperation>> valid_ops;

        auto freeFields = util::GameLogicUtils::getAllFieldsWith(s, [&s](const util::Point &p) {
            return s.getMap().getField(p).getFieldState() == scenario::FieldStateEnum::FREE;
        });

        for (const auto &pt : freeFields) {
            auto action = std::make_shared<GadgetAction>(false, pt, activeCharacter, gadget::GadgetEnum::JETPACK);
            bool valid = ActionValidator::validate(s, action, config);

            if (valid) {
                valid_ops.push_back(action);
            }
        }

        return valid_ops;
    }
}