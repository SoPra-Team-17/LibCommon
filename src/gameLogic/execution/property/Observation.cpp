/**
* @file   Observation.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  implementation of observation property execution
*/

#include "PropertyExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    std::shared_ptr<const BaseOperation>
    PropertyExecutor::executeObservation(State &s, const PropertyAction &a, const MatchConfig &config) {
        auto sourceChar = s.getCharacters().findByUUID(a.getCharacterId());
        auto targetChar = util::GameLogicUtils::findInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());

        bool success = util::GameLogicUtils::probabilityTestWithCharacter(*sourceChar,
                                                                          config.getObservationSuccessChance());

        bool targetHasPocketLitter = targetChar->hasGadget(gadget::GadgetEnum::POCKET_LITTER);

        auto retOp = std::make_shared<PropertyAction>(a);

        bool observationSuccess = (success
                                   && sourceChar->getFaction() != targetChar->getFaction()
                                   && targetChar->getFaction() != character::FactionEnum::INVALID);

        retOp->setSuccessful(observationSuccess);

        if (observationSuccess) {
            if (targetHasPocketLitter) {
                retOp->setIsEnemy(false);
            } else {
                retOp->setIsEnemy(targetChar->getFaction() != character::FactionEnum::NEUTRAL);
            }
        }

        return retOp;
    }
}