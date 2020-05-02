//
// Created by jonas on 28.04.20.
//

#include <util/GadgetUtils.hpp>
#include "ActionValidator.hpp"

namespace spy::gameplay {

    bool ActionValidator::validateSpyAction(const State &s, const spy::gameplay::SpyAction& op) {
        auto character = s.getCharacters().findByUUID(op.getCharacterId());
        return spy::util::GadgetUtils::personOnNeighboringField(s, op.getTarget(), character->getCoordinates().value());
    }
}