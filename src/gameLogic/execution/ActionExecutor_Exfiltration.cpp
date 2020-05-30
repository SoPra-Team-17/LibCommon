/**
 * @file   ActionExecutor_ExFiltration.cpp
 * @author Jonas
 * @date   28.04.2020 (creation)
 * @brief  Implementation of the execution of exfiltration actions.
 */

#include "ActionExecutor.hpp"
#include <util/GameLogicUtils.hpp>

namespace spy::gameplay {
    std::shared_ptr<const BaseOperation> ActionExecutor::executeExfiltration(State &s, const Exfiltration &op) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());

        // search for character at target position
        auto charTarget = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                       [&op](const character::Character &c) {
                                           return c.getCoordinates() == op.getTarget();
                                       });

        if (charTarget != s.getCharacters().end()) {
            // charTarget has to be placed on a random free neighbouring field
            charTarget->setCoordinates(util::GameLogicUtils::getRandomCharacterFreeNearField(s, op.getTarget()));
        }

        // character has to be exfiltrated and drops the diamond collar if he owns it
        auto collar = character->getGadget(gadget::GadgetEnum::DIAMOND_COLLAR);
        if (collar.has_value()) {
            character->removeGadget(gadget::GadgetEnum::DIAMOND_COLLAR);
            s.getMap().getField(character->getCoordinates().value()).setGadget(collar);
        }
        character->setCoordinates(op.getTarget());
        character->setHealthPoints(1);

        auto retOp = std::make_shared<Exfiltration>(op);
        retOp->setSuccessful(true);

        return retOp;
    }
}