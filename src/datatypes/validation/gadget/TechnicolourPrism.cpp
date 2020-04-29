/**
 * @file   TechnicolourPrism.cpp
 * @author Marco Deuscher
 * @date   28.04.2020 (creation)
 * @brief  Implemenation of Technicolour prism gadget validation.
 */

#include "datatypes/gameplay/Movement.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateTechnicolourPrism(const State &s, GadgetAction a) {
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        auto distance = gameplay::Movement::getMoveDistance(a.getTarget(), character->getCoordinates().value());
        bool targetIsRouletteTable = (s.getMap().getField(a.getTarget()).getFieldState() ==
                                      scenario::FieldStateEnum::ROULETTE_TABLE);

        return distance == 1 && targetIsRouletteTable;
    }
}
