/**
* @file   BowlerBlade.cpp
* @author Marco Deuscher
* @date   28.04.2020 (creation)
* @brief  Implementation of bowler blade gadget validation.
*/

#include "GadgetValidator.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetValidator::validateBowlerBlade(const State &s, GadgetAction a, const MatchConfig &config) {
        // check LoS
        auto character = s.getCharacters().findByUUID(a.getCharacterId());
        bool lineOfSightFree = spy::util::GameLogicUtils::bowlerBladeLineOfSight(s, character->getCoordinates().value(),
                                                                                 a.getTarget());
        // check range
        auto distance = Movement::getMoveDistance(character->getCoordinates().value(), a.getTarget());

        // check if there is a person on target field
        bool personOnField = util::GameLogicUtils::isPersonOnField(s, a.getTarget());

        // cat is not allowed as target of the action
        if (s.getCatCoordinates().has_value() && s.getCatCoordinates().value() == a.getTarget()) {
            return false;
        }

        // janitor is not allowed as target of the action
        if (s.getJanitorCoordinates().has_value() && s.getJanitorCoordinates().value() == a.getTarget()) {
            return false;
        }

        return personOnField && lineOfSightFree && distance <= config.getBowlerBladeRange();
    }
}

