//
// Created by Carolin on 02.04.2020.
//

#include "CharacterDescription.hpp"

namespace spy::character {

    const std::string &spy::character::CharacterDescription::getName() const {
        return name;
    }

    const std::string &spy::character::CharacterDescription::getDescription() const {
        return description;
    }

    spy::character::GenderEnum spy::character::CharacterDescription::getGender() const {
        return gender;
    }

    const std::list<spy::character::PropertyEnum> &spy::character::CharacterDescription::getFeatures() const {
        return features;
    }

}   // namespace spy::character
