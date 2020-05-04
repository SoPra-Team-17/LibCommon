/**
* @file   TechnicolorPrism.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of techicolor prism gadget execution
*/

#include "GadgetExecutor.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeTechnicolorPrism(State &s, const GadgetAction &a) {
        using spy::gadget::GadgetEnum;

        // invert roulette table
        s.getMap().getField(a.getTarget()).setInverted(true);

        // remove technicolor prism from inventory
        auto character = s.getCharacters().getByUUID(a.getCharacterId());
        character->removeGadget(GadgetEnum::TECHNICOLOUR_PRISM);

        return true;
    }
}
