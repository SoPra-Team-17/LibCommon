/**
 * @file   CharacterSet.hpp
 * @author Dominik Authaler
 * @date   25.04.2020 (creation)
 * @brief  Declaration of a specialized set for characters.
 */

#ifndef LIBCOMMON_CHARACTER_SET_HPP
#define LIBCOMMON_CHARACTER_SET_HPP

#include "character/Character.hpp"

namespace spy::character {
    /**
     * @brief   Realizes a specialized set for characters.
     * @details Characters are sorted solely by their UUID.
     * @note
     */
    class CharacterSet {
        using iterator = std::vector<Character>::iterator;
        using const_iterator = std::vector<Character>::const_iterator;

        public:
            explicit CharacterSet() = default;
            CharacterSet(std::initializer_list<Character> list);

            /**
             * Returns an iterator to the beginning of the set.
             * @note   Because characters are sorted solely by their UUID and this is not editable, it's
             *         possible to use a non-const iterator.
             * @return Non-const iterator to the beginning of the set.
             */
            [[nodiscard]] iterator begin() noexcept;

            [[nodiscard]] const_iterator begin() const noexcept;

            /**
             * Returns an iterator to the end of the set.
             * @note   Because characters are sorted solely by their UUID and this is not editable, it's
             *         possible to use a non-const iterator.
             * @return Non-const iterator to the end of the set.
             */
            [[nodiscard]] iterator end() noexcept;
            [[nodiscard]] const_iterator end() const noexcept;

            [[nodiscard]] bool empty() const noexcept;
            [[nodiscard]] size_t size() const noexcept;

            std::pair<iterator, bool> emplace(const util::UUID &characterId,
                                              const std::string &name);

            [[nodiscard]] const_iterator findByUUID(const util::UUID &uuid) const;
            iterator getByUUID(const util::UUID &uuid);

            [[nodiscard]] const_iterator findByLocation(const util::Point &p) const;
            iterator getByLocation(const util::Point &p);

            std::pair<iterator, bool> insert(Character &&c);
            std::pair<iterator, bool> insert(const Character &c);

            bool operator==(const CharacterSet &rhs) const;

            friend void to_json(nlohmann::json &j, const CharacterSet &c);

            friend void from_json(const nlohmann::json &j, CharacterSet &c);

        private:
            [[nodiscard]] bool isUUIDIncluded(util::UUID uuid) const;

            std::vector<Character> characters;
    };
}


#endif //LIBCOMMON_CHARACTER_SET_HPP
