/**
* @file   DiamondCollar.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of diamond collar gadget execution
*/

#include "GadgetExecutor.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeDiamondCollar(State &s, const GadgetAction &a) {
        auto character = s.getCharacters().getByUUID(a.getCharacterId());
        s.getFactionStats().collarToCat = character->getFaction();
        s.setHasCatDiamondCollar(true);

        character->removeGadget(gadget::GadgetEnum::DIAMOND_COLLAR);

        return true;
    }
}
