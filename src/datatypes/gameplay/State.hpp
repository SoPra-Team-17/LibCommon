/**
 * @author Jonas
 * @brief Entire state of the game
 */

#ifndef LIBCOMMON_STATE_HPP
#define LIBCOMMON_STATE_HPP

#include <nlohmann/json.hpp>
#include <util/Point.hpp>
#include <set>
#include <datatypes/character/Character.hpp>
#include <datatypes/scenario/FieldMap.hpp>

namespace spy::gameplay {
    class State {
        public:

            State() = default;

            State(unsigned int currentRound, scenario::FieldMap map, std::set<int> mySafeCombinations,
                  std::set<character::Character> characters, const std::optional<util::Point> &catCoordinates,
                  const std::optional<util::Point> &janitorCoordinates);

            [[nodiscard]] unsigned int getCurrentRound() const;

            [[nodiscard]] scenario::FieldMap getMap() const;

            [[nodiscard]] const std::set<int> &getMySafeCombinations() const;

            [[nodiscard]] const std::set<spy::character::Character> &getCharacters() const;

            [[nodiscard]] const std::optional<util::Point> &getCatCoordinates() const;

            [[nodiscard]] const std::optional<util::Point> &getJanitorCoordinates() const;

            /**
              * Sets the cat coordinates
              * @brief Standard specifies that absence of cat can be indicated by coordinates outside the map, so this resets
              * the catCoordinates optional if the coordinates are outside the map.
              */
            void setCatCoordinates(const std::optional<util::Point> &catCoordinates);

            /**
             * Sets the janitor coordinates
             * @brief Standard specifies that absence of janitor can be indicated by coordinates outside the map, so this resets
             * the janitorCoordinates optional if the coordinates are outside the map.
             */
            void setJanitorCoordinates(const std::optional<util::Point> &janitorCoordinates);

            friend void to_json(nlohmann::json &j, const State &s);

            friend void from_json(const nlohmann::json &j, State &s);

            bool operator==(const State &rhs) const;

        private:
            unsigned int currentRound = 0;
            scenario::FieldMap map;
            std::set<int> mySafeCombinations;
            std::set<character::Character> characters;
            std::optional<util::Point> catCoordinates;
            std::optional<util::Point> janitorCoordinates;
    };
}
#endif //LIBCOMMON_STATE_HPP
