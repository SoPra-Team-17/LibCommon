//
// Created by Carolin on 08.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateMoleDie(const State &s, const util::UUID &activeCharacter,
                                     const spy::MatchConfig &config) {
        auto character = s.getCharacters().findByUUID(activeCharacter);

        std::vector<util::Point> allPoints;
        std::vector<std::shared_ptr<BaseOperation>> valid_ops;

        for (unsigned int range = 1; range <= config.getMoledieRange(); range++) {
            auto points = util::GameLogicUtils::getNearFieldsInDist(s, character->getCoordinates().value(), range,
                                                                    [](const util::Point &/*p*/) {
                                                                        return true;
                                                                    });
            if (points.second) {
                allPoints.insert(allPoints.end(), points.first.begin(), points.first.end());
            }
        }

        for (const auto &pt : allPoints) {
            auto action = std::make_shared<GadgetAction>(false, pt, activeCharacter, gadget::GadgetEnum::MOLEDIE);
            bool valid = ActionValidator::validate(s, action, config);
            if (valid) {
                valid_ops.push_back(action);
            }
        }

        return valid_ops;
    }
}