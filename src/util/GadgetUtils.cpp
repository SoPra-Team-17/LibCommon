/**
 * @file   GadgetUtils.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  implementation of gadget utils
 */

#include "GadgetUtils.hpp"

namespace spy::util {
    bool GadgetUtils::hasCocktail(const spy::gameplay::State &s, const Point &pt) {
        using spy::gadget::GadgetEnum;
        bool targetHasGadget = false;

        // check if field contains gadget
        auto gadget = s.getMap().getField(pt).getGadget();
        if (gadget.has_value()) {
            targetHasGadget = (gadget->getType() == GadgetEnum::COCKTAIL);
        }

        if (!targetHasGadget) {
            // find person on target coords
            auto person = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                       [&pt](const character::Character &c) {
                                           return c.getCoordinates() == pt;
                                       });
            //check if there is an person on field
            if (person == s.getCharacters().end()) {
                return false;
            }

            // check if person has cocktail
            auto cocktail = std::find_if(person->getGadgets().begin(), person->getGadgets().end(),
                                         [](const gadget::Gadget &g) {
                                             return g.getType() == GadgetEnum::COCKTAIL;
                                         });
            targetHasGadget = (cocktail != person->getGadgets().end());
        }
        return targetHasGadget;
    }

    bool GadgetUtils::characterHasGadget(const gameplay::State &s, const UUID &id, spy::gadget::GadgetEnum type) {
        auto character = s.getCharacters().findByUUID(id);
        auto gadgets = character->getGadgets();
        auto gadget = std::find_if(gadgets.begin(), gadgets.end(), [type](const gadget::Gadget &g) {
            return g.getType() == type;
        });

        return gadget != gadgets.end();
    }
}