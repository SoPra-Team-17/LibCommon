//
// Created by Carolin on 08.05.2020.
//

#include "gameLogic/generation/ActionGenerator.hpp"
#include "gameLogic/validation/ActionValidator.hpp"
#include "util/GameLogicUtils.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"

namespace spy::gameplay {
    std::vector<std::shared_ptr<BaseOperation>>
    ActionGenerator::generateWiretapWithEarplugs(const State &s, const util::UUID &activeCharacter,
                                                 const spy::MatchConfig &config) {

        std::vector<std::shared_ptr<BaseOperation>> valid_ops;

        auto character = s.getCharacters().findByUUID(activeCharacter);
        auto neighboringFieldsWithPerson = util::GameLogicUtils::getNearFieldsInDist(s,
                                                                                     character->getCoordinates().value(),
                                                                                     1, [&s](const util::Point &p) {
                    return util::GameLogicUtils::isPersonOnField(s, p);
                });

        if (neighboringFieldsWithPerson.second) {
            for (const auto &pt : neighboringFieldsWithPerson.first) {
                GadgetAction action{false, pt, activeCharacter, gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS};
                bool valid = ActionValidator::validateGadgetAction(s, action, config);

                if (valid) {
                    valid_ops.push_back(std::make_shared<GadgetAction>(action));
                }
            }
        }

        return valid_ops;
    }
}