//
// Created by Carolin on 02.04.2020.
//

#ifndef LIBCOMMON_CHARACTERDESCRIPTION_HPP
#define LIBCOMMON_CHARACTERDESCRIPTION_HPP

#include <string>
#include <list>
#include <datatypes/character/Character.hpp>

namespace spy::character {
    enum class GenderEnum {
        MALE,
        FEMALE,
        DIVERSE
    };

    class CharacterDescription {
    public:
        CharacterDescription(std::string &name,
                             std::string &description,
                             GenderEnum gender,
                             std::list<PropertyEnum> &features)
                : name(name), description(description), gender(gender), features(features) {}

        [[nodiscard]] const std::string &getName() const;

        [[nodiscard]] const std::string &getDescription() const;

        [[nodiscard]] GenderEnum getGender() const;

        [[nodiscard]] const std::list<PropertyEnum> &getFeatures() const;

    private:
        const std::string name;
        const std::string description;
        GenderEnum gender;
        const std::list<spy::character::PropertyEnum> features;
    };
}

#endif //LIBCOMMON_CHARACTERDESCRIPTION_HPP
