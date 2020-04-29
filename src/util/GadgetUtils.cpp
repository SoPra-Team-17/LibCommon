/**
 * @file   GadgetUtils.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  implementation of gadget utils
 */

#include "GadgetUtils.hpp"
#include "gameplay/Movement.hpp"
#include "scenario/FieldMap.hpp"

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

    bool GadgetUtils::personOnNeighboringField(const gameplay::State &s, const Point &target, const Point &charCoord) {
        // check distance
        auto distance = gameplay::Movement::getMoveDistance(charCoord, target);
        if (distance != 1) {
            return false;
        }

        // check if person on target field
        auto person = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                   [target](const character::Character &c) {
                                       return c.getCoordinates() == target;
                                   });
        return !(person == s.getCharacters().end());
    }

    bool GadgetUtils::bowlerBladeLineOfSight(const spy::gameplay::State &s, const Point &p1, const Point &p2) {

        if (!s.getMap().isInside(p1) || !s.getMap().isInside(p2)) {
            throw std::invalid_argument("At least one point is outside the field map!");
        } else if (p1 == p2) {
            return true;
        }

        int dx = abs(p1.x - p2.x);
        int dy = abs(p1.y - p2.y);

        int incX = (p2.x > p1.x) ? 1 : -1;
        int incY = (p2.y > p1.y) ? 1 : -1;
        int error = dx - dy;
        // scaling is needed to make sure the error term is integral
        dx *= 2;
        dy *= 2;
        auto currentPoint = p1;
        while (currentPoint != p2) {
            // check if character on current point
            auto person = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                       [currentPoint](const character::Character &c) {
                                           return c.getCoordinates() == currentPoint;
                                       });
            bool personOnField = !(person == s.getCharacters().end());

            if (currentPoint != p1 && (s.getMap().blocksSight(currentPoint) || personOnField)) {
                return false;
            }

            if (error > 0) {
                currentPoint.x += incX;
                error -= dy;
            } else if (error < 0) {
                currentPoint.y += incY;
                error += dx;
            } else {
                error -= dy;
                error += dx;
                currentPoint += {incX, incY};
            }
        }

        return true;
    }
}