/**
* @file   PoisonPills.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of poison pills gadget execution
*/

#include "GadgetExecutor.hpp"
#include "datatypes/gadgets/Cocktail.hpp"
#include "util/GameLogicUtils.hpp"


namespace spy::gameplay {

    bool GadgetExecutor::executePoisonPills(State &s, const GadgetAction &action, const MatchConfig & config) {
        //Honey Trap property
        bool doHoneyTrap = util::GameLogicUtils::isPersonOnField(s, action.getTarget());
        auto a = doHoneyTrap ? util::GameLogicUtils::getHoneyTrapOperation(s, action, config) : action;
        
        // check if person on field
        bool personOnField = util::GameLogicUtils::isPersonOnField(s, a.getTarget());

        if (personOnField) {
            // person has cocktail (validate)
            auto targetPerson = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());
            auto cocktail = std::dynamic_pointer_cast<gadget::Cocktail>(
                    targetPerson->getGadget(gadget::GadgetEnum::COCKTAIL).value());
            cocktail->setIsPoisoned(true);
        } else {
            // field has cocktail (validate)
            auto cocktail = std::dynamic_pointer_cast<gadget::Cocktail>(
                    s.getMap().getField(a.getTarget()).getGadget().value());
            cocktail->setIsPoisoned(true);
        }

        auto character = s.getCharacters().getByUUID(a.getCharacterId());
        auto poisonPills = character->getGadget(gadget::GadgetEnum::POISON_PILLS);
        poisonPills.value()->setUsagesLeft(poisonPills.value()->getUsagesLeft().value() - 1);

        if (poisonPills.value()->getUsagesLeft().value() == 0) {
            character->removeGadget(gadget::GadgetEnum::POISON_PILLS);
        }

        return true;
    }
}
