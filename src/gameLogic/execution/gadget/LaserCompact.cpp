/**
* @file   LaserCompact.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of laser compact gadget execution
*/

#include "GadgetExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeLaserCompact(State &s, const GadgetAction &a, const MatchConfig &config) {
        auto character = s.getCharacters().getByUUID(a.getCharacterId());
        // check if shot hit
        bool hitSuccessful = util::GameLogicUtils::probabilityTestWithCharacter(*character,
                                                                                 config.getLaserCompactHitChance());

        if (!hitSuccessful) {
            return false;
        }

        // check if person on field
        bool personOnField = util::GameLogicUtils::isPersonOnField(s, a.getTarget());

        if (personOnField) {
            auto targetPerson = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());
            targetPerson->removeGadget(gadget::GadgetEnum::COCKTAIL);
        } else {
            // remove cocktail from field (there is a cocktail on the field, see validate LaserCompact)
            s.getMap().getField(a.getTarget()).removeGadget();
        }

        return true;
    }
}
