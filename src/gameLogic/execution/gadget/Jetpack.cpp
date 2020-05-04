//
// Created by Carolin on 04.05.2020.
//

#include "GadgetExecutor.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeJetpack(State &s, const GadgetAction &a) {
        auto character = s.getCharacters().getByUUID(a.getCharacterId());
        character->setCoordinates(a.getTarget());
        return true;
    }

}