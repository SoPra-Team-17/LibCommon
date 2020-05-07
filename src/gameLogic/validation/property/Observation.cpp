/**
* @file   PropertyValidator.cpp
* @author Carolin
* @date   06.05.2020 (creation)
* @brief  Implementation of observation property validation
*/

#include "PropertyValidator.hpp"

namespace spy::gameplay {
    bool PropertyValidator::validateObservation(const State &s, const PropertyAction &a) {
        using spy::gadget::GadgetEnum;
        auto character = s.getCharacters().findByUUID(a.getCharacterId());

        // if character has mole die observation is deactivated
        bool hasMoleDie = character->hasGadget(GadgetEnum::MOLEDIE);
        if (hasMoleDie) {
            return false;
        }

        return character->hasProperty(character::PropertyEnum::OBSERVATION) &&
               s.getMap().isLineOfSightFree(a.getTarget(), character->getCoordinates().value());
    }
}
