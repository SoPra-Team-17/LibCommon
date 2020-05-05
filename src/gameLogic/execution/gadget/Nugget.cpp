/**
* @file   Nugget.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of nugget gadget execution
*/

#include "GadgetExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeNugget(State &s, const GadgetAction &a) {
        // remove nugget from character
        auto character = s.getCharacters().getByUUID(a.getCharacterId());
        character->removeGadget(gadget::GadgetEnum::NUGGET);

        // get person on target field
        auto person = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());

        if (person->getFaction() == character::FactionEnum::INVALID) {
            // npc --> changes faction
            person->setFaction(character->getFaction());
            return true;
        }

        // target person is a player controlled character either your own or an enemy
        person->addGadget(std::make_shared<gadget::Gadget>(gadget::GadgetEnum::NUGGET));
        return false;
    }

}