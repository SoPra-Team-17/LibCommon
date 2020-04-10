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
        j["name"] = ci.name;
        j["description"] = ci.description;
        j["gender"] = ci.gender;
        j["features"] = ci.features;

        j["characterId"] = ci.characterId;
    }

    void from_json(const nlohmann::json &j, spy::character::CharacterInformation &ci) {
        j.at("name").get_to(ci.name);
        j.find("description") != j.end() ? j.at("description").get_to(ci.description) : ci.description = "";
        j.find("gender") != j.end() ? j.at("gender").get_to(ci.gender) : ci.gender = GenderEnum::DIVERSE;
        j.at("features").get_to(ci.features);

        j.at("characterId").get_to(ci.characterId);
    }

}   // namespace spy::character
