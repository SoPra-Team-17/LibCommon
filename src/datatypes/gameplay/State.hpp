/**
 * @file   State.hpp
 * @author Jonas
 * @brief  Entire state of the game.
 */

#ifndef LIBCOMMON_STATE_HPP
#define LIBCOMMON_STATE_HPP

#include <set>
#include <nlohmann/json.hpp>
#include "util/Point.hpp"
#include "datatypes/character/Character.hpp"
#include "datatypes/character/CharacterSet.hpp"
#include "datatypes/scenario/FieldMap.hpp"
#include "Movement.hpp"

namespace spy::gameplay {
    class State {
        public:

            State() = default;

            State(unsigned int currentRound, scenario::FieldMap map, std::set<int> mySafeCombinations,
                  character::CharacterSet characters, const std::optional<util::Point> &catCoordinates,
                  const std::optional<util::Point> &janitorCoordinates);

            [[nodiscard]] unsigned int getCurrentRound() const;

            [[nodiscard]] scenario::FieldMap getMap() const;

            [[nodiscard]] const std::set<int> &getMySafeCombinations() const;

            [[nodiscard]] const character::CharacterSet &getCharacters() const;

            [[nodiscard]] const std::optional<util::Point> &getCatCoordinates() const;

            [[nodiscard]] const std::optional<util::Point> &getJanitorCoordinates() const;

            /**
              * @brief Sets the cat coordinates.
              * @details Standard specifies that absence of cat can be indicated by coordinates outside the map, so this resets
              * the catCoordinates optional if the coordinates are outside the map.
              */
            void setCatCoordinates(const std::optional<util::Point> &catCoordinates);

            /**
             * @brief Sets the janitor coordinates.
             * @details Standard specifies that absence of janitor can be indicated by coordinates outside the map, so this resets
             * the janitorCoordinates optional if the coordinates are outside the map.
             */
            void setJanitorCoordinates(const std::optional<util::Point> &janitorCoordinates);

            /**
             * Checks if the given movement operation is valid in the current game state.
             * @param op Operation to check.
             * @return True if the operation is valid, otherwise false.
             */
            [[nodiscard]] bool isMovementValid(const gameplay::Movement &op) const;

            /**
             * Perform the given movement operation.
             * @param op Operation to perform.
             * @return True if the operation was successful, otherwise false.
             */
            [[nodiscard]] bool performMovement(const Movement &op);

            friend void to_json(nlohmann::json &j, const State &s);

            friend void from_json(const nlohmann::json &j, State &s);

            bool operator==(const State &rhs) const;

        private:
            /**
             * Calculates the distance between two points.
             * @param p1 First point.
             * @param p2 Second point.
             * @return Distance between the points.
             * @note The distance is measured using a "king's move metric".
             */
            static unsigned int getMoveDistance(const util::Point &p1, const util::Point &p2);

            unsigned int currentRound = 0;
            scenario::FieldMap map;
            std::set<int> mySafeCombinations;
            character::CharacterSet characters{};
            std::optional<util::Point> catCoordinates;
            std::optional<util::Point> janitorCoordinates;
    };
}
#endif //LIBCOMMON_STATE_HPP
