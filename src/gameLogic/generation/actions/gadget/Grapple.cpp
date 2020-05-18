//
// Created by Carolin on 08.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "util/GameLogicUtils.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"


namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateGrapple(const State &s, const util::UUID &activeCharacter,
                                     const spy::MatchConfig &config) {

        std::vector<std::shared_ptr<BaseOperation>> valid_ops;

        auto gadgetFields = util::GameLogicUtils::getAllFieldsWith(s, [&s](const util::Point &p) {
            return s.getMap().getField(p).getGadget().has_value();
        });

        for (const auto &pt : gadgetFields) {
            auto action = std::make_shared<GadgetAction>(false, pt, activeCharacter, gadget::GadgetEnum::GRAPPLE);
            bool valid = ActionValidator::validate(s, action, config);

            if (valid) {
                valid_ops.push_back(action);
            }
        }
        return valid_ops;
    }
}