/**
 * @file   GameLogicUtils.hpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  definition of gadget utils
 */

#ifndef LIBCOMMON_GAMELOGICUTILS_HPP
#define LIBCOMMON_GAMELOGICUTILS_HPP

#include <random>
#include "datatypes/gameplay/State.hpp"

namespace spy::util {
    class GameLogicUtils {
        public:
            GameLogicUtils() = delete;

            /**
             * @brief       checks if a field contains a cocktail, or if the person standing on the field is holding one
             * @param s     current state
             * @param pt    target field which is checked
             * @return      true if there is a cocktail, false if there isn't
             */
            static bool hasCocktail(const spy::gameplay::State &s, const Point &pt);

            /**
             * @brief           checks if a character holds a certain object
             * @param s         current state
             * @param id        character id, who is checked
             * @param type      gadget for which is checked
             * @return          true if character has gadget
             */
            static bool characterHasGadget(const spy::gameplay::State &s, const UUID &id, spy::gadget::GadgetEnum type);

            /**
             * @brief           Checks if a person is at the specified location
             * @param s         current state
             * @param target    coordinate to check for a person
             * @return          true if a person is at the specified location, false otherwise
             */
            static bool isPersonOnField(const gameplay::State &s, const Point &target);

            /**
             * @brief               checks if a other person is on a neighboring field
             * @param s             current state
             * @param target        input target
             * @param charCoord     coordinates of character
             * @return              true of person is on field and field is neighboring
             */
            static bool
            personOnNeighboringField(const spy::gameplay::State &s, const Point &target, const Point &charCoord);

            /**
             * @brief       checks the bowler blade line of sight
             * @note        the implementation from FieldMap is used, with the modification, that characters also block the LoS
             * @param s     current state
             * @param p1    point 1
             * @param p2    point 2
             * @return      true if line of sight is free
             */
            static bool bowlerBladeLineOfSight(const spy::gameplay::State &s, const Point &p1, const Point &p2);

            /**
             * @brief get point of random free neighbouring field with no character on it
             * @param s current state
             * @param p Point where character is at the moment
             * @return point where character can be swapped to if found
             */
            static const util::Point &
            getRandomFreeNeighbouringField(const spy::gameplay::State &s, const util::Point &p);

            /**
             * @brief get point of random neighbouring field which fulfils certain condition
             * @tparam t function
             * @param s current state
             * @param p Point from which to search
             * @param isSearchedField function that defines conditions returned point must fulfil to be accepted
             * @return randomly selected closest point fulfilling conditions
             */
            template<typename T>
            static const util::Point &
            getRandomNeighbouringField(const spy::gameplay::State &s, const util::Point &p, T isSearchedField) {
                std::vector<Point> points;
                for (int i = 0;; i++) {
                    points.clear();
                    getNeighbouringFieldsInDist(points, s, p, i, isSearchedField);
                    if (!points.empty()) {
                        return *getRandomItemFromVector(points);
                    }
                }
            }

            /**
             * @brief get all neighbouring fields with distance dist fulfilling certain conditions
             * @tparam t function
             * @param result contains resutling list of points
             * @param s current state
             * @param p point from which to search
             * @param dist distance that has to be between p and resulting points
             * @param isSearchedField function that defines conditions returned points must fulfil to be accepted
             */
            template<typename T>
            static void
            getNeighbouringFieldsInDist(std::vector<util::Point> &result, const spy::gameplay::State &s,
                                        const util::Point &p, const int dist,
                                        T isSearchedField) {
                std::vector<util::Point> possiblePoints{p + Point{dist, 0}, p + Point{-dist, 0}, p + Point{0, dist},
                                                        p + Point{0, -dist}, p + Point{dist, dist},
                                                        p + Point{-dist, -dist}, p + Point{-dist, dist},
                                                        p + Point{dist, -dist}};
                for (Point &point: possiblePoints) {
                    if (isSearchedField(point)) {
                        result.push_back(point);
                    }
                }
            }

            /**
             * @brief get random element from a vector
             * @tparam T type of vector elements
             * @param v non empty vector to select a random element from
             * @return const_iterator pointing to randomly selected element
             */
            template<typename T>
            static typename std::vector<T>::const_iterator getRandomItemFromVector(const std::vector<T> &v) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<unsigned int> randPos(0, v.size() - 1);
                return v.at(randPos(gen));
            }

            /**
             * @brief test for success
             * @param chance probability given in MatchConfig (double values between 0 and 1)
             * @return true, if test succeeded
             */
            static bool probabilityTest(double chance);
    };
}

#endif //LIBCOMMON_GAMELOGICUTILS_HPP
