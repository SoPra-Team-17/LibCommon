/**
 * @file   CharacterInformation.hpp
 * @author Carolin
 * @date   02.04.2020 (creation)
 * @brief  Declaration of the character information class.
 */

#ifndef LIBCOMMON_CHARACTER_INFORMATION_HPP
#define LIBCOMMON_CHARACTER_INFORMATION_HPP

#include <nlohmann/json.hpp>
#include <util/UUID.hpp>
#include <datatypes/character/Character.hpp>
#include <datatypes/character/CharacterDescription.hpp>

namespace spy::character {
    /**
     * @brief Representation of the information of characters being used in the network protocol.
     */
    class CharacterInformation : public CharacterDescription {
        public:
            CharacterInformation() = default;

            CharacterInformation(const util::UUID &characterId, const std::string &name, const std::string &description,
                                 GenderEnum gender,
                                 const std::vector<PropertyEnum> &features);

            CharacterInformation(CharacterDescription description, const util::UUID &characterId);

            [[nodiscard]] const util::UUID &getCharacterId() const;

            friend void to_json(nlohmann::json &j, const CharacterInformation &c);

            friend void from_json(const nlohmann::json &j, CharacterInformation &c);

            bool operator==(const CharacterInformation &rhs) const;

        private:
            spy::util::UUID characterId;
    };

}

#endif //LIBCOMMON_CHARACTER_INFORMATION_HPP
