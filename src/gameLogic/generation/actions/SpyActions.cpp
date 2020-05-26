//
// Created by Carolin on 07.05.2020.
//

#include <util/GameLogicUtils.hpp>
#include <gameLogic/validation/ActionValidator.hpp>
#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateSpyActions(const State &s, const util::UUID &activeCharacter) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        if (character->getActionPoints() == 0 || character->getFaction() == character::FactionEnum::NEUTRAL) {
            return {};
        }

        std::vector<std::shared_ptr<BaseOperation>> valid_ops;
        auto points = util::GameLogicUtils::getNearFieldsInDist(s, character->getCoordinates().value(), 1, [](const util::Point &/*p*/) {
            return true;
        }).first;
        if (character->hasProperty(character::PropertyEnum::FLAPS_AND_SEALS)) {
            auto morePoints = util::GameLogicUtils::getNearFieldsInDist(s, character->getCoordinates().value(), 2, [](const util::Point &/*p*/) {
                return true;
            }).first;
            points.insert(points.end(), morePoints.begin(), morePoints.end());
        }

        for (auto &p: points) {
            SpyAction action {activeCharacter, p};
            bool valid = ActionValidator::validateSpyAction(s, action);
            if (valid) {
                valid_ops.push_back(std::make_shared<SpyAction>(action));
            }
        }

        return valid_ops;
    }
}
