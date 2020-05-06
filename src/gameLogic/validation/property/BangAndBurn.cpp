/**
* @file   PropertyValidator.cpp
* @author Carolin
* @date   06.05.2020 (creation)
* @brief  Implementation of band and burn property validation
*/

#include "PropertyValidator.hpp"

namespace spy::gameplay {
    bool PropertyValidator::validateBangAndBurn(const State &s, const PropertyAction &a) {
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        return character->hasProperty(character::PropertyEnum::BANG_AND_BURN) &&
               Movement::getMoveDistance(a.getTarget(), character->getCoordinates().value()) == 1 &&
               s.getMap().getField(a.getTarget()).getFieldState() == scenario::FieldStateEnum::ROULETTE_TABLE;
    }
}