/**
 * @file   CharacterInformation.cpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Definition of the character information class.
 */

#include "CharacterInformation.hpp"

namespace spy::character {

    CharacterInformation::CharacterInformation(const util::UUID &characterId,
                                               const std::string &name, const std::string &description,
                                               GenderEnum gender, const std::vector<PropertyEnum> &features)
            : CharacterDescription(name, description, gender, features),
              characterId(characterId) {}

    const util::UUID &CharacterInformation::getCharacterId() const {
        return characterId;
    }

    void to_json(nlohmann::json &j, const spy::character::CharacterInformation &ci) {
        CharacterDescription::common_to_json(j, ci);
        j["characterId"] = ci.characterId;
    }

    void from_json(const nlohmann::json &j, spy::character::CharacterInformation &ci) {
        CharacterDescription::common_from_json(j, ci);
        j.at("characterId").get_to(ci.characterId);
    }

    void from_json(const nlohmann::json &/*j*/, CharacterInformation &/*c*/) {
        // TODO CharacterInformation from_json
    }

    void to_json(nlohmann::json &/*j*/, const CharacterInformation &/*c*/) {
        // TODO CharacterInformation from_json
    }
}   // namespace spy::character
