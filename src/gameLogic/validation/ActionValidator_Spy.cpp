//
// Created by jonas on 28.04.20.
//

#include <util/GameLogicUtils.hpp>
#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validateSpyAction(const State &s, const spy::gameplay::SpyAction& op) {
        auto character = s.getCharacters().findByUUID(op.getCharacterId());
        return spy::util::GameLogicUtils::personOnNeighbourField(s, op.getTarget(), character->getCoordinates().value());
    }
}