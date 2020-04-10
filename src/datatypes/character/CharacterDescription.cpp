/**
 * @file   CharacterDescription.cpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Definition of the character description class.
 */
#include "CharacterDescription.hpp"

namespace spy::character {

    CharacterDescription::CharacterDescription(const std::string &name, const std::string &description, GenderEnum gender,
                                               const std::vector<PropertyEnum> &features)
            : name(name), description(description), gender(gender), features(features) {}

    const std::string &CharacterDescription::getName() const {
        return name;
    }

    const std::string &CharacterDescription::getDescription() const {
        return description;
    }

    GenderEnum CharacterDescription::getGender() const {
        return gender;
    }

    const std::vector<PropertyEnum> &CharacterDescription::getFeatures() const {
        return features;
    }

    void to_json(nlohmann::json &j, const spy::character::CharacterDescription &cd) {
        CharacterDescription::common_to_json(j, cd);
    }

    void from_json(const nlohmann::json &j, spy::character::CharacterDescription &cd) {
        CharacterDescription::common_from_json(j, cd);
    }

}   // namespace spy::character
