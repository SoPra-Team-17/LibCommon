/**
 * @file   GameLogicUtils.hpp
 * @author Marco Deuscher
 * @date   29.04.2020 (creation)
 * @brief  definition of gadget utils
 */

#ifndef LIBCOMMON_GAMELOGICUTILS_HPP
#define LIBCOMMON_GAMELOGICUTILS_HPP

#include <random>
#include <unordered_set>
#include "datatypes/gameplay/State.hpp"
#include "matchconfig/MatchConfig.hpp"
#include "gameplay/CharacterOperation.hpp"

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
            personOnNeighbourField(const spy::gameplay::State &s, const Point &target, const Point &charCoord);

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
             * @brief Searches the set for a character at the given point. Returns first match.
             * @param cs CharacterSet to search in
             * @param  p Point to search for. Has to be in the map.
             * @return Const iterator to the found character if one at the specified point exits, otherwise a
             *         const iterator to the end of the set.
             */
            static std::vector<character::Character>::const_iterator
            findInCharacterSetByCoordinates(const character::CharacterSet &cs, const util::Point &p);

            /**
             * @brief Searches the set for a character at the given point. Returns first match.
             * @param cs CharacterSet to search in
             * @param  p Point to search for. Has to be in the map.
             * @return Iterator to the found character if one at the specified point exits, otherwise an
             *         iterator to the end of the set.
             */
            static std::vector<character::Character>::iterator
            getInCharacterSetByCoordinates(character::CharacterSet &cs, const util::Point &p);

            /**
             * @brief get point of random free neighbouring field with no character on it
             * @param s current state
             * @param p Point where character is at the moment
             * @return point where character can be placed to
             */
            static const util::Point &
            getRandomCharacterFreeNearField(const spy::gameplay::State &s, const util::Point &p);

            /**
             * @brief get point of free neighbour field (dist = 1) with no character on it
             * @param s current state
             * @param p Point where character is at the moment
             * @return point where character can move to, if no point is found nullopt is returned
             */
            static std::optional<util::Point>
            getRandomCharacterFreeNeighbourField(const spy::gameplay::State &s, const util::Point &p);

            /**
             * @brief get point of of a neighbouring field with a character on it. If there are more fields randomize
             * @param s current state
             * @param p Point where character is at the moment
             * @return point where closest character is standing
             */
            static const util::Point &
            getRandomCharacterNearField(const spy::gameplay::State &s, const util::Point &p);

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
            getRandomNearField(const spy::gameplay::State &s, const util::Point &p, T isSearchedField) {
                int dist = 1;
                while (true) {
                    auto res = getNearFieldsInDist(s, p, dist, isSearchedField);
                    if (!res.second) {
                        throw std::domain_error("No Point fulfilling isSearchedField was found on the whole map");
                    }
                    if (!res.first.empty()) {
                        return *getRandomItemFromVector(res.first);
                    }
                    dist++;
                }
            }

            /**
             * @brief get all neighbouring fields with distance dist fulfilling certain conditions
             * @tparam t function
             * @param s current state
             * @param p point from which to search
             * @param dist distance that has to be between p and resulting points. Has to be != 0
             * @param isSearchedField function that defines conditions returned points must fulfil to be accepted
             * @return pair (std::vector<util::Point>, bool)
             *              vector contains resulting points
             *              bool is true if there was at least one point with dist inside the map
             */
            template<typename T>
            static std::pair<std::vector<util::Point>, bool>
            getNearFieldsInDist(const spy::gameplay::State &s, const util::Point &p, const int dist,
                                T isSearchedField) {
                bool noPointsInMap = true;
                if (dist == 0) {
                    throw std::invalid_argument("dist has to be != 0");
                }

                std::vector<util::Point> possiblePoints;
                for (int i = -dist; i <= dist; i++) {
                    possiblePoints.push_back(p + Point{i, -dist}); // upper line
                    possiblePoints.push_back(p + Point{i, dist}); // bottom line
                    possiblePoints.push_back(p + Point{-dist, i}); // left line
                    possiblePoints.push_back(p + Point{dist, i}); // right line
                }

                std::vector<util::Point> result;
                for (Point &point: possiblePoints) {
                    if (s.getMap().isInside(point)) {
                        noPointsInMap = false;
                        if (isSearchedField(point)) {
                            result.push_back(point);
                        }
                    }
                }

                return std::make_pair(result, !noPointsInMap);
            }

            /**
             * @brief get point of random seat field in map with no character on it
             * @param s current state
             * @return randomly selected point with a free seat on it
             */
            static const util::Point &getRandomFreeSeatField(const spy::gameplay::State &s);

            /**
             * @brief get point of all fields fulfilling certain conditions
             * @tparam t function
             * @param s current state
             * @param isSearchedField function that defines conditions returned points must fulfil to be accepted
             * @return list of points fulfilling conditions
             */
            template<typename T>
            static std::vector<util::Point> getAllFieldsWith(const spy::gameplay::State &s, T isSearchedField) {
                std::vector<util::Point> result;

                auto field = s.getMap().getMap();
                for (unsigned int y = 0; y < field.size(); y++) {
                    for (unsigned int x = 0; x < field.at(y).size(); x++) {
                        Point p {(int)x, (int)y};
                        if (isSearchedField(p)) {
                            result.push_back(p);
                        }
                    }
                }
                return result;
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
                auto result = v.begin();
                std::advance(result, randPos(gen));
                return result;
            }

            /**
             * @brief test for success
             * @param chance probability given in MatchConfig (double values between 0 and 1)
             * @return true, if test succeeded
             */
            static bool probabilityTest(double chance);


            /**
             * @brief tests for success given a character
             * @param state current state
             * @param char character with properties
             * @param chance probability tiven in Matchconfig (double values between 0 and 1)
             * @return true, if test suceeded
             */
            static bool
            probabilityTestWithCharacter(const spy::character::Character &character, double chance);

            /**
             * @brief checks if the babysitter property can be applied
             * @param state current state
             * @return true, if babysitter was applied
             */
            static bool checkBabySitter(const gameplay::State &s, const gameplay::CharacterOperation &op,
                                        const spy::MatchConfig &config);
    };
}

#endif //LIBCOMMON_GAMELOGICUTILS_HPP
