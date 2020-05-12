//
// Created by Carolin on 08.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateRocketPen(const State &s, const util::UUID &activeCharacter,
                                       const spy::MatchConfig &config) {
        /**
         * only checks shots directy on another character
         */
        std::vector<std::shared_ptr<BaseOperation>> valid_ops;

        auto character = s.getCharacters().findByUUID(activeCharacter);

        for (const auto &targetChar : s.getCharacters()) {
            if (targetChar.getCoordinates().has_value() &&
                targetChar.getCoordinates().value() != character->getCoordinates().value()) {
                auto action = std::make_shared<GadgetAction>(false, targetChar.getCoordinates().value(),
                                                             activeCharacter, gadget::GadgetEnum::ROCKET_PEN);
                bool valid = ActionValidator::validate(s, action, config);

                auto dist = Movement::getMoveDistance(character->getCoordinates().value(),
                                                      targetChar.getCoordinates().value());

                if (valid && dist > 1) {
                    valid_ops.push_back(action);
                }
            }
        }

        return valid_ops;
    }
}