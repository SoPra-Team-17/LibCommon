/**
* @file   BowlerBlade.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of bowler blade gadget execution
*/

#include "GadgetExecutor.hpp"
#include "util/GameLogicUtils.hpp"


namespace spy::gameplay {

    bool GadgetExecutor::executeBowlerBlade(State &s, const GadgetAction &a, const MatchConfig &config) {
        auto character = *(s.getCharacters().getByUUID(a.getCharacterId()));
        bool successfullHit = util::GameLogicUtils::probabilityTestWithCharacter(s, character,
                                                                                 config.getBowlerBladeHitChance());

        // Babysitter successfull
        bool babysitter = util::GameLogicUtils::checkBabySitter(s, a, config);

        auto targetPerson = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());
        // check if target person has magnetic watch
        bool targetHasMagneticWatch = util::GameLogicUtils::characterHasGadget(s, targetPerson->getCharacterId(),
                                                                               gadget::GadgetEnum::MAGNETIC_WATCH);

        if (successfullHit && !targetHasMagneticWatch && !babysitter) {
            auto damage = config.getBowlerBladeDamage();
            targetPerson->subHealthPoints(damage);
        }

        // move hat to random free field of target person
        auto newHatPt = util::GameLogicUtils::getRandomNearField(s, a.getTarget(), [&s](const util::Point &pt) {
            bool fieldHasGadget = s.getMap().getField(pt).getGadget().has_value();
            bool fieldHasPerson = util::GameLogicUtils::isPersonOnField(s, pt);
            bool isFieldFree = s.getMap().getField(pt).getFieldState() == scenario::FieldStateEnum::FREE;
            return !fieldHasGadget && !fieldHasPerson && isFieldFree;
        });

        s.getMap().getField(newHatPt).setGadget(gadget::Gadget(gadget::GadgetEnum::BOWLER_BLADE));

        // remove bowler blade from inventory
        character.removeGadget(gadget::GadgetEnum::BOWLER_BLADE);

        return successfullHit;
    }
}
