//
// Created by Carolin on 04.05.2020.
//

#include <util/GameLogicUtils.hpp>
#include "GadgetExecutor.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeGasGloss(State &s, const GadgetAction &a, const MatchConfig &config) {
        auto character = s.getCharacters().getByUUID(a.getCharacterId());

        // Babysitter successfull
        bool babysitter = util::GameLogicUtils::checkBabySitter(s, a, config);

        auto targetPerson = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());

        if (!babysitter) {
            auto damage = config.getGasGlossDamage();
            util::GameLogicUtils::applyDamageToCharacter(*targetPerson, damage);
        }

        // remove gas gloss from inventory
        character->removeGadget(gadget::GadgetEnum::GAS_GLOSS);

        return true;
    }

}
