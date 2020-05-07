/**
 * @file   State.cpp
 * @author Marco
 * @date   10.04.2020 (creation)
 * @brief  Entire state of the game.
 */

#include "State.hpp"

#include <utility>


namespace spy::gameplay {
    State::State(unsigned int currentRound, scenario::FieldMap map, std::set<int> mySafeCombinations,
                 character::CharacterSet characters, const std::optional<util::Point> &catCoordinates,
                 const std::optional<util::Point> &janitorCoordinates) :
            currentRound(currentRound),
            map(std::move(map)),
            mySafeCombinations(std::move(mySafeCombinations)),
            characters(std::move(characters)),
            catCoordinates(catCoordinates),
            janitorCoordinates(janitorCoordinates) {}


    unsigned int State::getCurrentRound() const {
        return currentRound;
    }

    scenario::FieldMap &State::getMap() {
        return map;
    }

    const scenario::FieldMap &State::getMap() const {
        return map;
    }

    const std::set<int> &State::getMySafeCombinations() const {
        return mySafeCombinations;
    }

    void State::setCharacters(character::CharacterSet charSet) {
        characters = std::move(charSet);
    }

    const character::CharacterSet &State::getCharacters() const {
        return characters;
    }

    character::CharacterSet &State::getCharacters() {
        return characters;
    }

    const std::optional<util::Point> &State::getCatCoordinates() const {
        return catCoordinates;
    }

    const std::optional<util::Point> &State::getJanitorCoordinates() const {
        return janitorCoordinates;
    }

    void State::setCatCoordinates(const std::optional<util::Point> &newCatCoordinates) {
        if (newCatCoordinates && map.isInside(newCatCoordinates.value())) {
            State::catCoordinates = newCatCoordinates;
        } else {
            catCoordinates.reset();
        }
    }

    void State::setJanitorCoordinates(const std::optional<util::Point> &newJanitorCoordinates) {
        if (newJanitorCoordinates && map.isInside(newJanitorCoordinates.value())) {
            State::janitorCoordinates = newJanitorCoordinates;
        } else {
            janitorCoordinates.reset();
        }
    }

    bool State::operator==(const State &rhs) const {
        return std::tie(currentRound, map, mySafeCombinations, characters, catCoordinates, janitorCoordinates) ==
               std::tie(rhs.currentRound, rhs.map, rhs.mySafeCombinations, rhs.characters, rhs.catCoordinates,
                        rhs.janitorCoordinates);
    }

    void to_json(nlohmann::json &j, const State &s) {
        j["currentRound"] = s.currentRound;
        j["map"] = s.map;
        j["mySafeCombinations"] = s.mySafeCombinations;
        j["characters"] = s.characters;
        j["catCoordinates"] = s.catCoordinates;
        j["janitorCoordinates"] = s.janitorCoordinates;
    }

    void from_json(const nlohmann::json &j, State &s) {
        j.at("currentRound").get_to(s.currentRound);
        j.at("map").get_to(s.map);
        j.at("mySafeCombinations").get_to(s.mySafeCombinations);
        j.at("characters").get_to(s.characters);

        auto catCoordinatesJson = j.find("catCoordinates");
        if (catCoordinatesJson != j.end()) {
            // Use setter instead of get_to to properly handle coordinates outside the map
            s.setCatCoordinates(catCoordinatesJson->get<decltype(s.catCoordinates)>());
        }

        auto janitorCoordinatesJson = j.find("janitorCoordinates");
        if (janitorCoordinatesJson != j.end()) {
            // Use setter instead of get_to to properly handle coordinates outside the map
            s.setJanitorCoordinates(janitorCoordinatesJson->get<decltype(s.janitorCoordinates)>());
        }
    }

    bool State::getHasCatDiamondCollar() const {
        return hasCatDiamondCollar;
    }

    void State::setHasCatDiamondCollar(bool d) {
        hasCatDiamondCollar = d;
    }
}