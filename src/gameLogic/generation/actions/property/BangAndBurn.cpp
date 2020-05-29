//
// Created by Carolin on 08.05.2020.
//

#include <gameLogic/validation/ActionValidator.hpp>
#include <util/GameLogicUtils.hpp>
#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateBangAndBurn(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);

        std::vector<std::shared_ptr<BaseOperation>> valid_ops;
        auto points = util::GameLogicUtils::getNearFieldsInDist(s, character->getCoordinates().value(), 1,
                                                                [](const util::Point &/*p*/) {
                                                                    return true;
                                                                });

        for (const auto &p: points.first) {
            PropertyAction action {false, p, activeCharacter,
                                                           character::PropertyEnum::BANG_AND_BURN};
            bool valid = ActionValidator::validatePropertyAction(s, action);
            if (valid) {
                valid_ops.push_back(std::make_shared<PropertyAction>(action));
            }
        }

        return valid_ops;
    }
}
