/**
* @file   Jetpack.cpp
* @author Marco Deuscher
* @date   28.04.2020 (creation)
* @brief  Implementation of jetpack gadget validation.
*/

#include <util/GadgetUtils.hpp>
#include "GadgetValidator.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateJetpack(const State &s, GadgetAction a) {
        // flying to the field the character is currently standing on is useless, but valid
        if (s.getCharacters().findByUUID(a.getCharacterId())->getCoordinates() == a.getTarget()) {
            return true;
        }

        // check if target field type is free
        if (s.getMap().getField(a.getTarget()).getFieldState() != scenario::FieldStateEnum::FREE) {
            return false;
        }

        //check if any character is occupying the field
        return !util::GadgetUtils::isPersonOnField(s, a.getTarget());
    }

}

