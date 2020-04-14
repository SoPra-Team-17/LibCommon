/**
 * @file   CharacterDescription.hpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Declaration of the character description class.
 */

#ifndef LIBCOMMON_CHARACTER_DESCRIPTION_HPP
#define LIBCOMMON_CHARACTER_DESCRIPTION_HPP

#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <datatypes/character/Character.hpp>

namespace spy::character {
    enum class GenderEnum {
        DIVERSE,
        MALE,
        FEMALE
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(GenderEnum, {
        { GenderEnum::DIVERSE, "DIVERSE" },
        { GenderEnum::MALE, "MALE" },
        { GenderEnum::FEMALE, "FEMALE" },
    })

    /**
     * @brief Representation of the character information stored in the character configuration file.
     */
    class CharacterDescription {
        public:
            CharacterDescription() = default;

            CharacterDescription(const std::string &name,
                                 const std::string &description,
                                 GenderEnum gender,
                                 const std::vector<PropertyEnum> &features);

            CharacterDescription(const std::string &name,
                                 const std::string &description,
                                 const std::vector<PropertyEnum> &features);

            [[nodiscard]] const std::string &getName() const;

            [[nodiscard]] const std::string &getDescription() const;

            [[nodiscard]] std::optional<GenderEnum> getGender() const;

            [[nodiscard]] const std::vector<PropertyEnum> &getFeatures() const;

            friend void to_json(nlohmann::json &j, const CharacterDescription &m);

            friend void from_json(const nlohmann::json &j, CharacterDescription &m);

            /**
             * Create json with common CharacterDescription fields
             * @tparam T class type deriving from CharacterDescription
             */
            template<typename T>
            static void common_to_json(nlohmann::json &j, const T &cd) {
                j["name"] = cd.name;
                j["description"] = cd.description;
                j["gender"] = cd.gender;
                j["features"] = cd.features;
            }

            /**
             * Fill common CharacterDescription fields from json, to be used by classes deriving from CharacterDescription.
             * @tparam T class type deriving from CharacterDescription
             */
            template<typename T>
            static void common_from_json(const nlohmann::json &j, T &cd) {
                j.at("name").get_to(cd.name);
                j.find("description") != j.end() ? j.at("description").get_to(cd.description) : cd.description = "";
                j.at("gender").get_to(cd.gender);
                j.at("features").get_to(cd.features);
            }

            bool operator==(const CharacterDescription &rhs) const;

        protected:
            std::string name;
            std::string description;
            std::optional<GenderEnum> gender;
            std::vector<spy::character::PropertyEnum> features;
    };
}

#endif //LIBCOMMON_CHARACTER_DESCRIPTION_HPP
