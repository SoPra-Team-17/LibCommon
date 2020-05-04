//
// Created by jonas on 28.04.20.
//

#include <gameLogic/validation/gadget/GadgetValidator.hpp>
#include <util/GameLogicUtils.hpp>
#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validateGadgetAction(const State &s, GadgetAction op, const MatchConfig &config) {
        using spy::gadget::GadgetEnum;

        // check if target inside map
        if (!s.getMap().isInside(op.getTarget())) {
            return false;
        }

        // check if selected character exits and stands within the game field
        auto character = s.getCharacters().findByUUID(op.getCharacterId());
        if (character == s.getCharacters().end()
            || !character->getCoordinates().has_value()
            || !s.getMap().isInside(character->getCoordinates().value())) {
            return false;
        }

        // check if character has enough action points
        if (character->getActionPoints() <= 0) {
            return false;
        }

        // check if character has gadget
        bool hasGadget = spy::util::GameLogicUtils::characterHasGadget(s, op.getCharacterId(),
                                                                       op.getGadget());
        // picking up a cocktail is the only action that can be performed without having the gadget
        if (op.getGadget() != GadgetEnum::COCKTAIL && !hasGadget) {
            return false;
        }

        return GadgetValidator::validate(s, op, config);
    }
}