//
// Created by Carolin on 08.05.2020.
//

#include <gameLogic/validation/ActionValidator.hpp>
#include <util/GameLogicUtils.hpp>
#include "gameLogic/generation/ActionGenerator.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateBangAndBurn(const State &s, const util::UUID &activeCharacter, const MatchConfig &config) {
        auto character = s.getCharacters().findByUUID(activeCharacter);

        std::vector<std::shared_ptr<BaseOperation>> valid_ops;
        auto points = util::GameLogicUtils::getNearFieldsInDist(s, character->getCoordinates().value(), 1,
                                                                [](const util::Point &/*p*/) {
                                                                    return true;
                                                                });

        for (auto &p: points.first) {
            auto action = std::make_shared<PropertyAction>(false, p, activeCharacter,
                                                           character::PropertyEnum::BANG_AND_BURN);
            bool valid = ActionValidator::validate(s, action, config);
            if (valid) {
                valid_ops.push_back(action);
            }
        }

        return valid_ops;
    }
}