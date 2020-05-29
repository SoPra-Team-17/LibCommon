//
// Created by Carolin on 08.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "util/GameLogicUtils.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateCocktail(const State &s, const util::UUID &activeCharacter,
                                      const spy::MatchConfig &config) {

        std::vector<std::shared_ptr<BaseOperation>> valid_ops;

        auto character = s.getCharacters().findByUUID(activeCharacter);

        // drink cocktail
        GadgetAction action {false, character->getCoordinates().value(), activeCharacter,
                                                     gadget::GadgetEnum::COCKTAIL};
        bool valid = ActionValidator::validateGadgetAction(s, action, config);

        if (valid) {
            valid_ops.push_back(std::make_shared<GadgetAction>(action));
        }

        // pour cocktail or get cocktail from bar
        auto neighbouringFields = util::GameLogicUtils::getNearFieldsInDist(s, character->getCoordinates().value(), 1,
                                                                            [](const util::Point &/*p*/) {
                                                                                return true;
                                                                            });

        if (neighbouringFields.second) {
            for (const auto &pt : neighbouringFields.first) {
                action = {false, pt, activeCharacter, gadget::GadgetEnum::COCKTAIL};
                valid = ActionValidator::validateGadgetAction(s, action, config);

                if (valid) {
                    valid_ops.push_back(std::make_shared<GadgetAction>(action));
                }
            }
        }

        return valid_ops;
    }
}