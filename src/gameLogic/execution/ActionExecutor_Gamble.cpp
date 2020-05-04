//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {
    bool ActionExecutor::executeGamble(State &s, const GambleAction &op) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());
        character->subActionPoint();
        auto targetField = s.getMap().getField(op.getTarget());

        double winningChance = 18.0/37.0;
        if (character->hasProperty(character::PropertyEnum::LUCKY_DEVIL)) {
            winningChance = 32/37;
        } else if (character->hasProperty(character::PropertyEnum::JINX)) {
            winningChance = 13/37;
        }
        winningChance = targetField.isInverted() ? (1-winningChance) : winningChance;

        bool won = util::GameLogicUtils::probabilityTestWithCharacter(s, *character, winningChance);
        if (won) {
            character->setChips(character->getChips() + op.getStake());
            targetField.setChipAmount(targetField.getChipAmount().value() - op.getStake());
        } else {
            character->setChips(character->getChips() - op.getStake());
            targetField.setChipAmount(targetField.getChipAmount().value() + op.getStake());
        }

        return won;
    }
}
