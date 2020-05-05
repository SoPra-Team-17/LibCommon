//
// Created by jonas on 28.04.20.
//

#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validateGambleAction(const State &s, const spy::gameplay::GambleAction& op) {
        // check if target inside map
        if (!s.getMap().isInside(op.getTarget())) {
            return false;
        }

        auto character = s.getCharacters().findByUUID(op.getCharacterId());

        // check if character has enough action points
        if (character->getActionPoints() <= 0) {
            return false;
        }

        auto targetField = s.getMap().getField(op.getTarget());
        if (Movement::getMoveDistance(op.getTarget(), character->getCoordinates().value()) != 1 ||
            targetField.getFieldState() != scenario::FieldStateEnum::ROULETTE_TABLE) {
            // target is no neighbouring roulette table
            return false;
        }
        if (character->getChips() < op.getStake() || op.getStake() > targetField.getChipAmount().value()) {
            // chips amount set is not allowed
            return false;
        }

        return !targetField.isDestroyed().value();
    }
}