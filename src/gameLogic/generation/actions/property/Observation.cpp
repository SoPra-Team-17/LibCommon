//
// Created by Carolin on 08.05.2020.
//

#include <gameLogic/validation/ActionValidator.hpp>
#include <datatypes/gameplay/PropertyAction.hpp>
#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateObservation(const State &s, const util::UUID &activeCharacter, const MatchConfig &config) {
        auto character = s.getCharacters().findByUUID(activeCharacter);

        std::vector<std::shared_ptr<BaseOperation>> valid_ops;
        for (const auto &targetChar : s.getCharacters()) {
            if (targetChar.getCoordinates().has_value() &&
                character->getCoordinates().value() != targetChar.getCoordinates().value()) {
                auto action = std::make_shared<PropertyAction>(false, targetChar.getCoordinates().value(),
                                                               activeCharacter,
                                                               character::PropertyEnum::OBSERVATION);
                bool valid = ActionValidator::validate(s, action, config);
                if (valid) {
                    valid_ops.push_back(action);
                }
            }
        }

        return valid_ops;
    }
}