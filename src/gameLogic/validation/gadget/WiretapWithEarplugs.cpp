/**
* @file   WiretapWithEarplugs.cpp
* @author Marco Deuscher
* @date   28.04.2020 (creation)
* @brief  Implementation of wiretap with earplugs gadget validation.
*/

#include <datatypes/gadgets/WiretapWithEarplugs.hpp>
#include "GadgetValidator.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateWiretapWithEarplugs(const State &s, GadgetAction a) {
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        auto gadget = std::dynamic_pointer_cast<const gadget::WiretapWithEarplugs>(
                character->getGadget(a.getGadget()).value());

        if (gadget->getActiveOn().has_value()) {
            //gadget is already in use
            return false;
        }

        auto targetUUID = spy::util::GameLogicUtils::getPersonOnNeighbourField(s, a.getTarget(),
                                                                               character->getCoordinates().value());
        if (!targetUUID.has_value()) {
            // no character on target field
            return false;
        } else {
            // wiretap with earplugs can only be used against characters of another faction
            auto targetChar = s.getCharacters().findByUUID(targetUUID.value());
            return (targetChar->getFaction() != character->getFaction());
        }
    }
}
