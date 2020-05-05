//
// Created by Carolin on 04.05.2020.
//

#include <util/GameLogicUtils.hpp>
#include "GadgetExecutor.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeGrapple(State &s, const GadgetAction &action, const MatchConfig &config) {
        auto character = s.getCharacters().getByUUID(action.getCharacterId());
        bool successfullHit = util::GameLogicUtils::probabilityTestWithCharacter(*character,
                                                                                 config.getGrappleHitChance());
        if (successfullHit) {
            auto targetField = s.getMap().getField(action.getTarget());
            character->addGadget(targetField.getGadget().value());
            targetField.removeGadget();
        }

        return successfullHit;
    }
}