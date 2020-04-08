/**
 * @file   CharacterDescription.cpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Definition of the character description class.
 */
#include "CharacterDescription.hpp"

namespace spy::character {

    CharacterDescription::CharacterDescription(const std::string &name, const std::string &description, GenderEnum gender,
                                               const std::list<PropertyEnum> &features)
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

    const std::list<PropertyEnum> &CharacterDescription::getFeatures() const {
        return features;
    }

    void to_json(nlohmann::json &j, const spy::character::CharacterDescription &cd) {
        j["name"] = cd.name;
        j["description"] = cd.description;
        j["gender"] = cd.gender;
        j["features"] = cd.features;
    }

    void from_json(const nlohmann::json &j, spy::character::CharacterDescription &cd) {
        j.at("name").get_to(cd.name);
        j.at("description").get_to(cd.description);
        j.at("gender").get_to(cd.gender);
        j.at("features").get_to(cd.features);
    }

}   // namespace spy::character
