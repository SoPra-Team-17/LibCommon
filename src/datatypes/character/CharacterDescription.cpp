//
// Created by Carolin on 02.04.2020.
//

#include "CharacterDescription.hpp"

namespace spy::character {

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

}   // namespace spy::character
