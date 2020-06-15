/**
* @file   PropertyValidator.cpp
* @author Carolin
* @date   06.05.2020 (creation)
* @brief  Implementation of observation property validation
*/

#include "PropertyValidator.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {
    bool PropertyValidator::validateObservation(const State &s, const PropertyAction &a) {
        using spy::gadget::GadgetEnum;
        using spy::util::GameLogicUtils;

        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        auto targetChar = GameLogicUtils::findInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());

        bool hasProperty = character->hasProperty(character::PropertyEnum::OBSERVATION);
        bool freeLoS = s.getMap().isLineOfSightFree(a.getTarget(), character->getCoordinates().value());
        bool validTarget = (targetChar != s.getCharacters().end());


        // if character has mole die observation is deactivated
        bool hasMoleDie = character->hasGadget(GadgetEnum::MOLEDIE);
        if (hasMoleDie) {
            return false;
        }

        return validTarget && hasProperty && freeLoS;
    }
}
