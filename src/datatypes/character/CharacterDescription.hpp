/**
 * @file   CharacterDescription.hpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Declaration of the character description class.
 */

#ifndef LIBCOMMON_CHARACTER_DESCRIPTION_HPP
#define LIBCOMMON_CHARACTER_DESCRIPTION_HPP

#include <string>
#include <list>
#include <datatypes/character/Character.hpp>

namespace spy::character {
    enum class GenderEnum {
        MALE,
        FEMALE,
        DIVERSE
    };

    /**
     * @brief Representation of the character information stored in the character configuration file.
     */
    class CharacterDescription {
        public:
            /**
             * Constructor.
             * @param name          Character name.
             * @param description   Textual description of the character.
             * @param gender        Gender of the character.
             * @param features      List of the character's properties.
             */
            CharacterDescription(std::string &name,
                                 std::string &description,
                                 GenderEnum gender,
                                 std::list<PropertyEnum> &features);

            /**
             * Getter for the character name.
             * @return Name of the character.
             */
            [[nodiscard]] const std::string &getName() const;

            /**
             * Getter for the descriptive text of the character.
             * @return Character description text.
             */
            [[nodiscard]] const std::string &getDescription() const;

            /**
             * Getter for the character's gender.
             * @return Gender of the character.
             */
            [[nodiscard]] GenderEnum getGender() const;

            /**
             * Getter for the character's properties.
             * @return List of the character's properties.
             */
            [[nodiscard]] const std::list<PropertyEnum> &getFeatures() const;

        private:
            const std::string name;                                     ///< Character name.
            const std::string description;                              ///< Textual character description.
            GenderEnum gender;                                          ///< Character gender.
            const std::list<spy::character::PropertyEnum> features;     ///< Character properties.
    };
}

#endif //LIBCOMMON_CHARACTER_DESCRIPTION_HPP
