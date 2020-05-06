//
// Created by Carolin on 06.05.2020.
//

#include <util/GameLogicUtils.hpp>
#include <datatypes/gadgets/WiretapWithEarplugs.hpp>
#include "GadgetExecutor.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeWiretapWithEarplugs(State &s, const GadgetAction &a) {
        auto sourceChar = s.getCharacters().getByUUID(a.getCharacterId());
        auto targetChar = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());
        auto gadget = std::dynamic_pointer_cast<spy::gadget::WiretapWithEarplugs>(sourceChar->getGadget(a.getGadget()).value());
        gadget->setWorking(true);
        gadget->setActiveOn(targetChar->getCharacterId());
        return true;
    }

}