/**
* @file   ChickenFeed.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of chicken feed gadget execution
*/

#include "GadgetExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeChickenFeed(State &s, const GadgetAction &a) {
        // if target person is not in enemy faction gadget disappears
        auto sourceChar = s.getCharacters().getByUUID(a.getCharacterId());
        auto targetChar = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());

        // remove gadget
        sourceChar->removeGadget(gadget::GadgetEnum::CHICKEN_FEED);

        if (targetChar->getFaction() == character::FactionEnum::INVALID
            || targetChar->getFaction() == sourceChar->getFaction()) {
            return false;
        }

        // targetCharacter is of enemy faction
        int ipDiff = static_cast<int>(sourceChar->getIntelligencePoints() - targetChar->getIntelligencePoints());
        if (ipDiff < 0 && static_cast<int>(sourceChar->getIntelligencePoints()) < std::abs(ipDiff)) {
            sourceChar->setIntelligencePoints(0);
        }

        sourceChar->setIntelligencePoints(sourceChar->getIntelligencePoints() + ipDiff);
        return true;
    }
}
