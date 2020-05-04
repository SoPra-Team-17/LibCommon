//
// Created by Carolin on 04.05.2020.
//

#include <util/GameLogicUtils.hpp>
#include "GadgetExecutor.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeGrapple(State &s, const GadgetAction &action, const MatchConfig &config) {
        auto const_character = *(s.getCharacters().findByUUID(action.getCharacterId()));
        bool successfullHit = util::GameLogicUtils::probabilityTestWithCharacter(s, const_character,
                                                                                 config.getGrappleHitChance());
        if (successfullHit) {
            auto character = s.getCharacters().getByUUID(action.getCharacterId());
            auto targetField = s.getMap().getField(action.getTarget());
            character->addGadget(targetField.getGadget().value());
            targetField.removeGadget();
        }

        return successfullHit;
    }
}