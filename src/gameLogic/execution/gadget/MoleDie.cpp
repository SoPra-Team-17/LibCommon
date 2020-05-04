/**
* @file   MoleDie.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of mole die execution
*/

#include "GadgetExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeMoleDie(State &s, const GadgetAction &a) {
        using spy::gadget::GadgetEnum;

        // character that issues the action and remove mole die from their inventory
        auto character = s.getCharacters().getByUUID(a.getCharacterId());
        character->removeGadget(GadgetEnum::MOLEDIE);

        // check if target field has character
        auto person = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());
        if (person != s.getCharacters().end()) {
            // mole die goes into the person inventory
            person->addGadget(gadget::Gadget(GadgetEnum::MOLEDIE));
            return true;
        }

        // mole die bounces into the inventory of the closest person
        auto closestPoint = util::GameLogicUtils::getRandomCharacterNearField(s, a.getTarget());
        auto closestPerson = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), closestPoint);

        closestPerson->addGadget(gadget::Gadget(GadgetEnum::MOLEDIE));

        return true;
    }

}