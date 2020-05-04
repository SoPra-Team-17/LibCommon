/**
 * @file   GameLogicUtils.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  implementation of gadget utils
 */

#include "GameLogicUtils.hpp"
#include "gameplay/Movement.hpp"
#include "scenario/FieldMap.hpp"

namespace spy::util {
    bool GameLogicUtils::hasCocktail(const spy::gameplay::State &s, const Point &pt) {
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

    bool GameLogicUtils::characterHasGadget(const gameplay::State &s, const UUID &id, spy::gadget::GadgetEnum type) {
        auto character = s.getCharacters().findByUUID(id);
        auto gadgets = character->getGadgets();
        auto gadget = std::find_if(gadgets.begin(), gadgets.end(), [type](const gadget::Gadget &g) {
            return g.getType() == type;
        });

        return gadget != gadgets.end();
    }

    bool GameLogicUtils::isPersonOnField(const gameplay::State &s, const Point &target) {
        auto person = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                   [target](const character::Character &c) {
                                       return c.getCoordinates() == target;
                                   });
        return !(person == s.getCharacters().end());
    }

    bool
    GameLogicUtils::personOnNeighboringField(const gameplay::State &s, const Point &target, const Point &charCoord) {
        // check distance
        auto distance = gameplay::Movement::getMoveDistance(charCoord, target);
        if (distance != 1) {
            return false;
        }

        // check if person on target field
        return isPersonOnField(s, target);
    }

    bool GameLogicUtils::bowlerBladeLineOfSight(const spy::gameplay::State &s, const Point &p1, const Point &p2) {
        return s.getMap().isLineOfSightFree(p1, p2, [&s](util::Point currentPoint) {
            // check if point is conventionally blocked
            if (s.getMap().blocksSight(currentPoint)) {
                return true;
            }
            // check if character blocks point
            return isPersonOnField(s, currentPoint);
        });
    }

    character::CharacterSet::const_iterator
    GameLogicUtils::findInCharacterSetByCoordinates(const character::CharacterSet &cs, const util::Point &p) {
        auto character = std::find_if(cs.begin(), cs.end(), [&p](const character::Character &c) {
            return c.getCoordinates() == p;
        });

        return character;
    }

    character::CharacterSet::iterator
    GameLogicUtils::getInCharacterSetByCoordinates(character::CharacterSet &cs, const util::Point &p) {
        auto character = std::find_if(cs.begin(), cs.end(), [&p](const character::Character &c) {
            return c.getCoordinates() == p;
        });

        return character;
    }

    const util::Point &
    GameLogicUtils::getRandomCharacterFreeNeighbouringField(const gameplay::State &s, const Point &p) {
        return getRandomNearField(s, p, [&s](util::Point currentPoint) {
            // check if point is free -> accessible and no character is on point
            return s.getMap().isAccessible(currentPoint) && !isPersonOnField(s, currentPoint);
        });
    }

    bool GameLogicUtils::probabilityTest(double chance) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> prob(0.0, std::nextafter(1.0, 0.0));
        // return random number >= change of failure
        return prob(gen) >= (1 - chance);
    }

    std::optional<util::Point>
    GameLogicUtils::getRandomCharacterFreeNeighbourField(const gameplay::State &s, const Point &p) {
        std::optional<Point> result;
        std::vector<Point> points;
        if (getNearFieldsInDist(points, s, p, 1, [&s](util::Point currentPoint) {
            // check if point is free -> accessible and no character is on point
            return s.getMap().isAccessible(currentPoint) && !isPersonOnField(s, currentPoint);
        }) && !points.empty()) {
            result = *getRandomItemFromVector(points);
        }
        return result;
    }

    const util::Point &GameLogicUtils::getRandomCharacterNearField(const gameplay::State &s, const Point &p) {
        return getRandomNearField(s, p, [&s](util::Point currentPoint) {
            // check if character is on point
            return isPersonOnField(s, currentPoint);
        });
    }

    const util::Point &GameLogicUtils::getRandomFreeSeatField(const gameplay::State &s) {
        auto points = getAllFieldsWith(s, [&s](util::Point currentPoint) {
            // check if field is seat with no character on it
            return s.getMap().getField(currentPoint).getFieldState() == scenario::FieldStateEnum::BAR_SEAT &&
                   !isPersonOnField(s, currentPoint);
        });
        if (!points.empty()) {
            return *getRandomItemFromVector(points);
        } else {
            throw std::domain_error("No seat field with no character on it was found in the whole map");
        }
    }
}