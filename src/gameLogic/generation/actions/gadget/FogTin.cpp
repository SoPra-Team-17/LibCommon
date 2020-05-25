//
// Created by Carolin on 08.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "util/GameLogicUtils.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateFogTin(const State &s, const util::UUID &activeCharacter,
                                    const spy::MatchConfig &config) {

        std::vector<std::shared_ptr<BaseOperation>> valid_ops;
        std::vector<util::Point> allPoints;

        auto character = s.getCharacters().findByUUID(activeCharacter);
        for (unsigned int range = 2; range < config.getFogTinRange(); range++) {
            auto points = util::GameLogicUtils::getNearFieldsInDist(s, character->getCoordinates().value(), range,
                                                                    [&s](const util::Point &p) {
                                                                        return s.getMap().getField(p).getFieldState() !=
                                                                               scenario::FieldStateEnum::WALL;
                                                                    });
            if (points.second) {
                allPoints.insert(allPoints.end(), points.first.begin(), points.first.end());
            }
        }

        for (const auto &pt : allPoints) {
            auto action = std::make_shared<GadgetAction>(false, pt, activeCharacter, gadget::GadgetEnum::FOG_TIN);
            bool valid = ActionValidator::validate(s, action, config);

            if (valid) {
                valid_ops.push_back(action);
            }
        }

        return valid_ops;
    }
}