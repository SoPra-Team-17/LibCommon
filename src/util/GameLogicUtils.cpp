/**
 * @file   GameLogicUtils.cpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  implementation of gadget utils
 */

#include <gameLogic/validation/ActionValidator.hpp>
#include <datatypes/gadgets/WiretapWithEarplugs.hpp>
#include "GameLogicUtils.hpp"
#include "datatypes/gameplay/Movement.hpp"
#include "datatypes/scenario/FieldMap.hpp"


namespace spy::util {
    bool GameLogicUtils::hasCocktail(const spy::gameplay::State &s, const Point &pt) {
        using spy::gadget::GadgetEnum;
        bool targetHasGadget = false;

        // check if field contains gadget
        auto gadget = s.getMap().getField(pt).getGadget();
        if (gadget.has_value()) {
            targetHasGadget = (gadget.value()->getType() == GadgetEnum::COCKTAIL);
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
                                         [](const std::shared_ptr<gadget::Gadget> &g) {
                                             return g->getType() == GadgetEnum::COCKTAIL;
                                         });
            targetHasGadget = (cocktail != person->getGadgets().end());
        }
        return targetHasGadget;
    }

    bool GameLogicUtils::isPersonOnField(const gameplay::State &s, const Point &target) {
        auto person = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                   [target](const character::Character &c) {
                                       return c.getCoordinates() == target;
                                   });
        return !(person == s.getCharacters().end());
    }

    bool
    GameLogicUtils::personOnNeighbourField(const gameplay::State &s, const Point &target, const Point &charCoord) {
        // check distance
        auto distance = gameplay::Movement::getMoveDistance(charCoord, target);
        if (distance != 1) {
            return false;
        }

        // check if person on target field
        return isPersonOnField(s, target);
    }

    character::CharacterSet::const_iterator
    GameLogicUtils::findPersonOnNeighbourField(const gameplay::State &s, const Point &target, const Point &charCoord) {
        // check distance
        auto distance = gameplay::Movement::getMoveDistance(charCoord, target);
        if (distance != 1) {
            return s.getCharacters().end();
        }

        // check if person on target field
        auto character = findInCharacterSetByCoordinates(s.getCharacters(), target);
        return character;
    }

    bool GameLogicUtils::bowlerBladeLineOfSight(const spy::gameplay::State &s, const Point &p1, const Point &p2) {
        return s.getMap().isLineOfSightFree(p1, p2, [&s](util::Point currentPoint) {
            // check if point is conventionally blocked
            if (s.getMap().blocksSight(currentPoint)) {
                return true;
            }
            // check if character blocks point
            bool personOnField = isPersonOnField(s, currentPoint);
            bool catOnField = (s.getCatCoordinates().has_value() && s.getCatCoordinates().value() == currentPoint);
            bool janitorOnField = (s.getJanitorCoordinates().has_value()
                                   && s.getJanitorCoordinates().value() == currentPoint);

            return (personOnField || catOnField || janitorOnField);
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

    std::optional<spy::util::Point> GameLogicUtils::getRandomCharacterFreeMapPoint(const spy::gameplay::State &state) {
        auto point = getRandomMapPoint(state, [&state](const auto &p) {
            if (!state.getMap().isAccessible(p)) {
                return false;
            }
            return !spy::util::GameLogicUtils::isPersonOnField(state, p);
        });

        return point;
    }

    util::Point GameLogicUtils::getRandomCharacterFreeNearField(const gameplay::State &s, const Point &p) {
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
        auto res = getNearFieldsInDist(s, p, 1, [&s](util::Point currentPoint) {
            // check if point is free -> accessible and no character is on point
            return s.getMap().isAccessible(currentPoint) && !isPersonOnField(s, currentPoint);
        });
        if (res.second && !res.first.empty()) {
            result = *getRandomItemFromContainer(res.first);
        }
        return result;
    }

    util::Point GameLogicUtils::getRandomCharacterNearField(const gameplay::State &s, const Point &p) {
        return getRandomNearField(s, p, [&s](util::Point currentPoint) {
            // check if character is on point
            return isPersonOnField(s, currentPoint);
        });
    }

    std::vector<util::Point> GameLogicUtils::getCharacterNearFields(const gameplay::State &s, const Point &p) {
        return getNearFields(s, p, [&s](const util::Point &currentPoint) {
            // check if character is on point
            return isPersonOnField(s, currentPoint);
        });
    }

    bool GameLogicUtils::checkBabySitter(const gameplay::State &s, const gameplay::CharacterOperation &op,
                                         const spy::MatchConfig &config) {
        bool babySitterSuccess = false;

        auto result = getNearFieldsInDist(s, op.getTarget(), 1, [&s](const util::Point &p) {
            return isPersonOnField(s, p);
        });

        auto character = s.getCharacters().findByUUID(op.getCharacterId());

        if (result.second) {
            for (const auto &p : result.first) {
                auto person = GameLogicUtils::findInCharacterSetByCoordinates(s.getCharacters(), p);
                if (person->hasProperty(character::PropertyEnum::BABYSITTER)
                    && (character->getFaction() == person->getFaction())
                    && probabilityTest(config.getBabysitterSuccessChance())) {
                    babySitterSuccess = true;
                    break;
                }
            }
        }

        return babySitterSuccess;
    }

    int GameLogicUtils::babysitterNumber(const gameplay::State &s,
                                           std::shared_ptr<const spy::gameplay::GadgetAction> action) {
        int numBabySitter = 0;

        auto result = getNearFieldsInDist(s, action->getTarget(), 1, [&s](const util::Point &p) {
            return isPersonOnField(s, p);
        });

        auto character = s.getCharacters().findByUUID(action->getCharacterId());

        if (result.second) {
            for (const auto &p : result.first) {
                auto person = GameLogicUtils::findInCharacterSetByCoordinates(s.getCharacters(), p);
                if (person->hasProperty(character::PropertyEnum::BABYSITTER)
                    && (character->getFaction() == person->getFaction())) {
                    numBabySitter += 1;
                }
            }
        }

        return numBabySitter;
    }

    util::Point GameLogicUtils::getRandomFreeSeatField(const gameplay::State &s) {
        auto points = getAllFieldsWith(s, [&s](util::Point currentPoint) {
            // check if field is seat with no character on it
            return s.getMap().getField(currentPoint).getFieldState() == scenario::FieldStateEnum::BAR_SEAT &&
                   !isPersonOnField(s, currentPoint);
        });
        if (!points.empty()) {
            return *getRandomItemFromContainer(points);
        } else {
            throw std::domain_error("No seat field with no character on it was found in the whole map");
        }
    }

    bool GameLogicUtils::probabilityTestWithCharacter(const character::Character &character,
                                                      double chance) {
        using spy::character::PropertyEnum;
        using spy::gadget::GadgetEnum;

        // character with clammy clothes only has half the chance of success
        if (character.hasProperty(PropertyEnum::CLAMMY_CLOTHES) ||
            character.hasProperty(PropertyEnum::CONSTANT_CLAMMY_CLOTHES)) {
            chance /= 2;
        }

        bool result = probabilityTest(chance);
        if (result) {
            return true;
        }

        // if char has tradecraft and not mole die, prob. test is repeated
        if (character.hasProperty(PropertyEnum::TRADECRAFT)
            && !character.hasGadget(GadgetEnum::MOLEDIE)) {
            result = probabilityTest(chance);
        }

        return result;
    }

    void GameLogicUtils::applyDamageToCharacter(spy::gameplay::State &s, character::Character &targetChar,
                                                unsigned int damage) {
        if (targetChar.hasProperty(character::PropertyEnum::TOUGHNESS)) {
            damage /= 2;
        }

        targetChar.subHealthPoints(damage);

        // update stats
        if (targetChar.getFaction() == character::FactionEnum::PLAYER1) {
            s.getFactionStats().damageSuffered.first += damage;
        } else if (targetChar.getFaction() == character::FactionEnum::PLAYER2) {
            s.getFactionStats().damageSuffered.second += damage;
        }
    }

    std::optional<std::shared_ptr<character::Character>>
    GameLogicUtils::getWiredCharacter(const gameplay::State &s, const character::Character gettingIP) {
        std::optional<std::shared_ptr<character::Character>> resultChar;
        auto character = std::find_if(s.getCharacters().begin(), s.getCharacters().end(),
                                      [&gettingIP](const character::Character &c) {
                                          auto gadget_optionalPointer = c.getGadget(
                                                  gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS);
                                          if (!gadget_optionalPointer.has_value()) {
                                              return false;
                                          }
                                          auto gadget = *std::dynamic_pointer_cast<const gadget::WiretapWithEarplugs>(
                                                  gadget_optionalPointer.value());
                                          return gadget.isWorking() && gadget.getActiveOn().has_value() &&
                                                 gadget.getActiveOn().value() == gettingIP.getCharacterId();
                                      });

        if (character != s.getCharacters().end()) {
            //character getting intelligence points is wired
            resultChar = std::make_shared<character::Character>(*character);
        }

        return resultChar;
    }

    gameplay::GadgetAction
    GameLogicUtils::getHoneyTrapOperation(const gameplay::State &s, const gameplay::GadgetAction &op,
                                          const MatchConfig &config) {

        gameplay::GadgetAction a = op; // keep op const to know regular operation/target
        auto sourceChar = s.getCharacters().findByUUID(a.getCharacterId());
        auto targetChar = util::GameLogicUtils::findInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());

        if (targetChar == s.getCharacters().end()
            || !targetChar->hasProperty(character::PropertyEnum::HONEY_TRAP)
            || !util::GameLogicUtils::probabilityTestWithCharacter(*sourceChar, config.getHoneyTrapSuccessChance())) {
            return op;
        }

        std::vector<Point> alternativeTargets;
        for (const auto &character: s.getCharacters()) {
            if (character.getCharacterId() == sourceChar->getCharacterId() ||
                character.getCharacterId() == targetChar->getCharacterId() ||
                !character.getCoordinates().has_value()) {
                // alternative action target is source or target or not in map
                continue;
            }

            auto otherTarget = character.getCoordinates().value();
            if (s.getMap().isInside(otherTarget)) {
                a.setTarget(otherTarget);
                if (gameplay::ActionValidator::validate(s, std::make_shared<gameplay::GadgetAction>(a), config)) {
                    alternativeTargets.push_back(otherTarget);
                }
            }
        }

        if (alternativeTargets.empty()) {
            return op;
        } else {
            a.setTarget(*GameLogicUtils::getRandomItemFromContainer(alternativeTargets));
        }

        return a;
    }
}
