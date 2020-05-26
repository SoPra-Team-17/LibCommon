//
// Created by Carolin on 07.05.2020.
//

#include <util/GameLogicUtils.hpp>
#include <gameLogic/validation/ActionValidator.hpp>
#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateMovementActions(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getMovePoints() == 0) {
            return {};
        }

        std::vector<std::shared_ptr<BaseOperation>> valid_ops;
        auto points = util::GameLogicUtils::getNearFieldsInDist(s, character->getCoordinates().value(), 1, [](const util::Point &/*p*/) {
            return true;
        });
        for (auto &p: points.first) {
            Movement action {false, p, activeCharacter, character->getCoordinates().value()};
            bool valid = ActionValidator::validateMovement(s, action);
            if (valid) {
                valid_ops.push_back(std::make_shared<Movement>(action));
            }
        }

        return valid_ops;
    }
}
