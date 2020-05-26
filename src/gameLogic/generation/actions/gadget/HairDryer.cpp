/**
 * @file   HairDryer.cpp
 * @author Marco Deuscher (code), Carolin (creation)
 * @date   08.05.2020 (creation)
 * @brief  Implementation of hair dryer gadget action generation
 */


#include "gameLogic/generation/ActionGenerator.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "util/GameLogicUtils.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateHairDryer(const State &s, const util::UUID &activeCharacter,
                                       const spy::MatchConfig &config) {
        auto character = s.getCharacters().findByUUID(activeCharacter);
        std::vector<std::shared_ptr<BaseOperation>> valid_ops;

        valid_ops.push_back(std::make_shared<GadgetAction>(false, character->getCoordinates().value(), activeCharacter,
                                                           gadget::GadgetEnum::HAIRDRYER));

        // neighboring fields with person on them
        auto points = util::GameLogicUtils::getNearFieldsInDist(s, character->getCoordinates().value(), 1,
                                                                [&s](const util::Point &p) {
                                                                    return util::GameLogicUtils::isPersonOnField(s, p);
                                                                });
        if (points.second) {
            for (const auto &pt : points.first) {
                valid_ops.push_back(
                        std::make_shared<GadgetAction>(false, pt, activeCharacter, gadget::GadgetEnum::HAIRDRYER));
            }
        }

        for (const auto &ops : valid_ops) {
            bool valid = ActionValidator::validate(s, ops, config);
            if (!valid) {
                valid_ops.erase(std::remove(valid_ops.begin(), valid_ops.end(), ops), valid_ops.end());
            }
        }

        valid_ops.erase(std::remove_if(valid_ops.begin(), valid_ops.end(),
                                       [&s, &config](std::shared_ptr<BaseOperation> &action) {
                                           return !ActionValidator::validate(s, action, config);
                                       }), valid_ops.end());

        return valid_ops;
    }
}