/**
 * @file   PoisonPills.cpp
 * @author Marco Deuscher
 * @date   28.04.2020 (creation)
 * @brief  Implemenation of poison pills gadget validation.
 */

#include "datatypes/gameplay/Movement.hpp"
#include "GadgetValidator.hpp"

namespace spy::gameplay {
    bool GadgetValidator::validatePoisonPills(const State &s, GadgetAction a) {
        using spy::gadget::GadgetEnum;

        // check if target inside map
        if (!s.getMap().isInside(a.getTarget())) {
            return false;
        }

        // check if character has poisonous pills
        auto character = s.getCharacters().findByUUID(a.getCharacterId().value());
        auto gadgets = character->getGadgets();
        auto gadget = std::find_if(gadgets.begin(), gadgets.end(), [](const gadget::Gadget &g) {
            return g.getType() == GadgetEnum::POISON_PILLS;
        });

        // check if target contains cocktail
        bool targetHasCocktail = false;
        auto targetFieldGadget = s.getMap().getField(a.getTarget()).getGadget();
        if (targetFieldGadget.has_value()) {
            targetHasCocktail = (targetFieldGadget->getType() == GadgetEnum::COCKTAIL);
        }
        if(!targetHasCocktail){
            // find person on target coords
            auto person = std::find_if(s.getCharacters().begin(), s.getCharacters().end(), [&a](const character::Character &c){
                return c.getCoordinates() == a.getTarget();
            });
            // check if person has cocktail
            auto cocktail = std::find_if(person->getGadgets().begin(), person->getGadgets().end(), [](const gadget::Gadget &g){
                return g.getType() == GadgetEnum::COCKTAIL;
            });
            targetHasCocktail = (cocktail != person->getGadgets().end());
        }

        // check if target is adjacent field
        auto distance = gameplay::Movement::getMoveDistance(a.getTarget(), character->getCoordinates().value());

        return targetHasCocktail && distance == 1 && gadget != gadgets.end();
    }
}
