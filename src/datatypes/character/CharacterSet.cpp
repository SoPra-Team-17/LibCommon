/**
 * @file   CharacterSet.cpp
 * @author Dominik Authaler
 * @date   25.04.2020 (creation)
 * @brief  Definition of a specialized set for characters.
 */

#include "CharacterSet.hpp"

namespace spy::character {
    CharacterSet::CharacterSet(std::initializer_list<Character> list) : characters(list) {}

    CharacterSet::iterator CharacterSet::begin() noexcept {
        return characters.begin();
    }

    CharacterSet::const_iterator CharacterSet::begin() const noexcept {
        return characters.begin();
    }

    CharacterSet::iterator CharacterSet::end() noexcept {
        return characters.end();
    }

    CharacterSet::const_iterator CharacterSet::end() const noexcept {
        return characters.end();
    }

    bool CharacterSet::empty() const noexcept {
        return characters.empty();
    }

    size_t CharacterSet::size() const noexcept {
        return characters.size();
    }

    std::pair<CharacterSet::iterator, bool> CharacterSet::emplace(const util::UUID  &characterId,
                                                                   const std::string &name) {
        Character c(characterId, name);
        return insert(c);
    }

    std::pair<CharacterSet::iterator, bool> CharacterSet::insert(Character &&c) {
        for (const auto &character : characters) {
            if (Character::strong_order_compare()(character, c) && Character::strong_order_compare()(c, character)) {
                return std::pair<std::vector<Character>::iterator, bool>(end(), false);
            }
        }
        characters.push_back(std::move(c));
        return std::pair<std::vector<Character>::iterator, bool>(end() - 1, true);
    }

    std::pair<CharacterSet::iterator, bool> CharacterSet::insert(const Character &c) {
        for (const auto &character : characters) {
            if (Character::strong_order_compare()(character, c) && Character::strong_order_compare()(c, character)) {
                return std::pair<CharacterSet::iterator, bool>(end(), false);
            }
        }
        characters.push_back(c);
        return std::pair<CharacterSet::iterator, bool>(end() - 1, true);
    }

    CharacterSet::const_iterator CharacterSet::findByUUID(const util::UUID &uuid) const {
        auto character = std::find_if(characters.begin(), characters.end(), [&uuid](const character::Character &c) {
            return c.getCharacterId() == uuid;
        });

        return character;
    }

    CharacterSet::iterator CharacterSet::getByUUID(const util::UUID &uuid) {
        auto character = findByUUID(uuid);

        return characters.erase(character, character);
    }

    CharacterSet::const_iterator CharacterSet::findByLocation(const util::Point &p) const {
        auto character = std::find_if(characters.begin(), characters.end(), [&p](const character::Character &c) {
            return c.getCoordinates() == p;
        });

        return character;
    }

    CharacterSet::iterator CharacterSet::getByLocation(const util::Point &p) {
        auto character = findByLocation(p);

        return characters.erase(character, character);
    }


    bool CharacterSet::operator==(const CharacterSet &rhs) const {
        return characters == rhs.characters;
    }

    void to_json(nlohmann::json &j, const CharacterSet &c) {
        j = c.characters;
    }

    void from_json(const nlohmann::json &j, CharacterSet &c) {
        j.get_to(c.characters);
    }
}