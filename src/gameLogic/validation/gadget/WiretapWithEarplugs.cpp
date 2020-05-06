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

    bool GadgetValidator::validateWiretapWithEarplugs(const State &state, GadgetAction a) {
        State s = state; //undo const -> otherwise getGadget is not working
        auto character = s.getCharacters().getByUUID(a.getCharacterId());
        auto gadget = std::dynamic_pointer_cast<gadget::WiretapWithEarplugs>(
                character->getGadget(gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS).value());
        if (gadget->getActiveOn().has_value()) {
            //gadget is already in use
            return false;
        }
        return spy::util::GameLogicUtils::personOnNeighbourField(s, a.getTarget(), character->getCoordinates().value());
    }
}
