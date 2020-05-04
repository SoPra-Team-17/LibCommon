/**
* @file   MirrorOfWilderness.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of mirror of wilderness gadget execution
*/

#include "GadgetExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeMirrorOfWilderness(State &s, const GadgetAction &a, const MatchConfig &config) {
        bool ret = false;
        // check if target person is of own faction
        auto sourceChar = s.getCharacters().getByUUID(a.getCharacterId());
        auto targetChar = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());

        bool sameFaction = (sourceChar->getFaction() == targetChar->getFaction());
        bool success = util::GameLogicUtils::probabilityTestWithCharacter(s, *sourceChar, config.getMirrorSwapChance());

        if (success || sameFaction) {
            ret = true;

            auto sourceCharIP = sourceChar->getIntelligencePoints();
            auto targetCharIP = targetChar->getIntelligencePoints();
            sourceChar->setIntelligencePoints(targetCharIP);
            targetChar->setIntelligencePoints(sourceCharIP);

            if (!sameFaction) {
                sourceChar->removeGadget(gadget::GadgetEnum::MIRROR_OF_WILDERNESS);
            }
        }

        return ret;
    }
}