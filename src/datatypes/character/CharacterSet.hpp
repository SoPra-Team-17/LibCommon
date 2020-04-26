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
     * @note    Because the UUID of a character isn't modifiable, it's perfectly fine to enable the use
     *          of iterators instead of the const_iterators a normal set would return.
     */
    class CharacterSet {
            using iterator = std::vector<Character>::iterator;
            using const_iterator = std::vector<Character>::const_iterator;

        public:
            CharacterSet() = default;

            CharacterSet(std::initializer_list<Character> list);

            /**
             * Returns an iterator to the beginning of the set.
             * @note   Because characters are sorted solely by their UUID and this is not editable, it's
             *         possible to use a non-const iterator.
             * @return Non-const iterator to the beginning of the set.
             */
            [[nodiscard]] iterator begin() noexcept;

            /**
             * Returns an iterator to the beginning of the set.
             * @return Const iterator to the beginning of the set.
             */
            [[nodiscard]] const_iterator begin() const noexcept;

            /**
             * Returns an iterator to the end of the set.
             * @note   Because characters are sorted solely by their UUID and this is not editable, it's
             *         possible to use a non-const iterator.
             * @return Non-const iterator to the end of the set.
             */
            [[nodiscard]] iterator end() noexcept;

            /**
             * Returns an iterator to the end of the set.
             * @return Const iterator to the end of the set.
             */
            [[nodiscard]] const_iterator end() const noexcept;

            /**
             * Test whether the container is empty.
             * @return True if the container size is 0, false otherwise.
             */
            [[nodiscard]] bool empty() const noexcept;

            /**
             * Getter for the number of elements in the container.
             * @return The number of elements in the container.
             */
            [[nodiscard]] size_t size() const noexcept;

            /**
             * Inserts a new in-place constructed character into the set if the uuid isn't already contained.
             * @param  characterId UUID of the character.
             * @param  name        Name of the character.
             * @return Iterator to the end of the set and false if the uuid was already in the set, otherwise
             *         an iterator to the added character and true.
             */
            std::pair<iterator, bool> emplace(const util::UUID &characterId, const std::string &name);

            /**
             * Inserts a new character into the set if the uuid isn't already contained.
             * @param  c Character to insert.
             * @return Iterator to the end of the set and false if the uuid was already in the set, otherwise
             *         an iterator to the added character and true.
             */
            std::pair<iterator, bool> insert(Character &&c);

            /**
             * Inserts a new character into the set if the uuid isn't already contained.
             * @param  c Character to insert.
             * @return Iterator to the end of the set and false if the uuid was already in the set, otherwise
             *         an iterator to the added character and true.
             */
            std::pair<iterator, bool> insert(const Character &c);

            /**
             * Searches the set for a character with the given uuid.
             * @param  uuid UUID to search for.
             * @return Const iterator to the found character if one with the specified uuid exits, otherwise a
             *         const iterator to the end of the set.
             */
            [[nodiscard]] const_iterator findByUUID(const util::UUID &uuid) const;

            /**
             * Searches the set for a character with the given uuid.
             * @param  uuid UUID to search for.
             * @return Iterator to the found character if one with the specified uuid exits, otherwise an
             *         iterator to the end of the set.
             */
            iterator getByUUID(const util::UUID &uuid);

            bool operator==(const CharacterSet &rhs) const;

            friend void to_json(nlohmann::json &j, const CharacterSet &c);

            friend void from_json(const nlohmann::json &j, CharacterSet &c);

        private:
            [[nodiscard]] bool containsUUID(util::UUID uuid) const;

            std::vector<Character> characters;
    };
}


#endif //LIBCOMMON_CHARACTER_SET_HPP
