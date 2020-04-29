/**
 * @file   TechnicolourPrism.cpp
 * @author Marco Deuscher
 * @date   28.04.2020 (creation)
 * @brief  Implemenation of Technicolour prism gadget validation.
 */

#include "datatypes/gameplay/Movement.hpp"
#include "util/GadgetUtils.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validateTechnicolourPrism(const State &s, GadgetAction a) {
        using spy::gadget::GadgetEnum;

        if (!s.getMap().isInside(a.getTarget())) {
            return false;
        }

        bool hasPrism = spy::util::GadgetUtils::characterHasGadget(s, a.getCharacterId().value(),
                                                                   GadgetEnum::TECHNICOLOUR_PRISM);

        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        auto distance = gameplay::Movement::getMoveDistance(a.getTarget(), character->getCoordinates().value());
        bool targetIsRouletteTable = (s.getMap().getField(a.getTarget()).getFieldState() ==
                                      scenario::FieldStateEnum::ROULETTE_TABLE);

        return distance == 1 &&
               targetIsRouletteTable &&
               hasPrism;
    }
}
