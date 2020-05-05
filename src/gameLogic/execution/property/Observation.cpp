/**
* @file   Observation.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  implementation of observation property execution
*/

#include "PropertyExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool PropertyExecutor::executeObservation(State &s, const PropertyAction &a, const MatchConfig &config) {
        auto sourceChar = s.getCharacters().findByUUID(a.getCharacterId());
        auto targetChar = util::GameLogicUtils::findInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());

        bool success = util::GameLogicUtils::probabilityTestWithCharacter(*sourceChar,
                                                                          config.getObservationSuccessChance());

        bool targetHasPocketLitter = targetChar->hasGadget(gadget::GadgetEnum::POCKET_LITTER);

        return success
               && sourceChar->getFaction() != targetChar->getFaction()
               && targetChar->getFaction() != character::FactionEnum::INVALID
               && !targetHasPocketLitter;
    }
}