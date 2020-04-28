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
        if (!s.getMap().isInside(a.getTarget())) {
            return false;
        }

        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        auto gadgets = character->getGadgets();
        auto gadget = std::find_if(gadgets.begin(), gadgets.end(), [](const gadget::Gadget &g) {
            return g.getType() == gadget::GadgetEnum::TECHNICOLOUR_PRISM;
        });

        auto distance = gameplay::Movement::getMoveDistance(a.getTarget(), character->getCoordinates().value());
        bool targetIsRouletteTable = (s.getMap().getField(a.getTarget()).getFieldState() ==
                                      scenario::FieldStateEnum::ROULETTE_TABLE);

        return distance == 1 &&
               targetIsRouletteTable &&
               gadget != gadgets.end();
    }
}
