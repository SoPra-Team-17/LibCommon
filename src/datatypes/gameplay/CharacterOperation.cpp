//
// Created by jonas on 10.04.20.
//

#include "CharacterOperation.hpp"
#include <utility>
#include <iostream>

namespace spy::gameplay {

    CharacterOperation::CharacterOperation(OperationEnum type, bool successful, const util::Point &target) :
            BaseOperation(type, successful, target) {}

    CharacterOperation::CharacterOperation(OperationEnum type, bool successful, const util::Point &target,
                                           util::UUID characterId) :
            BaseOperation(type, successful, target),
            characterId{characterId} {}

    void CharacterOperation::common_to_json(nlohmann::json &j, const CharacterOperation &op) {
        BaseOperation::common_to_json(j, op);
        j["characterId"] = op.characterId;
    }

    void CharacterOperation::common_from_json(const nlohmann::json &j, CharacterOperation &op) {
        BaseOperation::common_from_json(j, op);
        j.at("characterId").get_to(op.characterId);

    }

    const util::UUID &CharacterOperation::getCharacterId() const {
        return characterId;
    }

    bool CharacterOperation::isCharacterEqual(const CharacterOperation &rhs) const {
        return std::tie(type, successful, target, characterId) ==
               std::tie(rhs.type, rhs.successful, rhs.target, rhs.characterId);
    }
}