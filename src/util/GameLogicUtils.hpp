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
#include "datatypes/matchconfig/MatchConfig.hpp"
#include "datatypes/gameplay/CharacterOperation.hpp"
#include "datatypes/gameplay/GadgetAction.hpp"

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
             * @brief               checks if an other person is on a neighboring field
             * @param s             current state
             * @param target        input target
             * @param charCoord     coordinates of character
             * @return              true of person is on field and field is neighboring
             */
            static bool
            personOnNeighbourField(const spy::gameplay::State &s, const Point &target, const Point &charCoord);

            /**
             * @brief               returns a const_iterator to the character on the specified field,
             *                      if it's a neighboring field
             * @param s             current state
             * @param target        input target
             * @param charCoord     coordinates of character
             * @return              const_iterator to the character if there is a character, otherwise
             *                      a const_iterator to the end of the character set
             */
            static character::CharacterSet::const_iterator
            findPersonOnNeighbourField(const gameplay::State &s, const Point &target, const Point &charCoord);

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
             * Returns a random point on the map for which the predicate returns true
             * @tparam Predicate function-like type mapping spy::util::Point -> bool
             * @param s current game state
             * @param p predicate indicating valid fields, gets called exactly once for each field on the map
             * @return random point for which p returns true, std::nullopt if p returns false for all points
             */
            template<typename Predicate>
            static std::optional<util::Point> getRandomMapPoint(const gameplay::State &s, Predicate p) {
                // List of all fields matching predicate
                auto validFields = getAllFieldsWith(s, p);

                if (validFields.empty()) {
                    // No matching fields found
                    return std::nullopt;
                }

                auto randomField = getRandomItemFromContainer(validFields);
                return *randomField;
            }

            /**
             * Get a random accessible field without a character on it.
             * @param state State to search the field in.
             * @return Coordinates of the found field, otherwise std::nullopt.
             */
            static std::optional<spy::util::Point> getRandomCharacterFreeMapPoint(const spy::gameplay::State &state);

            /**
             * @brief get point of random free neighbouring field with no character on it
             * @param s current state
             * @param p Point where character is at the moment
             * @return point where character can be placed to
             */
            static util::Point getRandomCharacterFreeNearField(const spy::gameplay::State &s, const util::Point &p);

            /**
             * @brief get point of free neighbour field (dist = 1) with no character on it
             * @param s current state
             * @param p Point where character is at the moment
             * @return point where character can move to, if no point is found nullopt is returned
             */
            static std::optional<util::Point>
            getRandomCharacterFreeNeighbourField(const spy::gameplay::State &s, const util::Point &p);

            /**
             * @brief get point of a neighbouring field with a character on it. If there are more fields randomize
             * @param s current state
             * @param p Point where character is at the moment
             * @return point where closest character is standing
             */
            static util::Point getRandomCharacterNearField(const spy::gameplay::State &s, const util::Point &p);

            /**
             * @brief get points of neighbouring fields with a character on it
             * @param s current state
             * @param p Point where character is at the moment
             * @return points where closest characters are standing
             */
            static std::vector<util::Point> getCharacterNearFields(const spy::gameplay::State &s, const util::Point &p);

            /**
             * @brief get point of random neighbouring field which fulfils certain condition
             * @tparam t function
             * @param s current state
             * @param p Point from which to search
             * @param isSearchedField function that defines conditions returned point must fulfil to be accepted
             * @return randomly selected closest point fulfilling conditions
             */
            template<typename T>
            static util::Point
            getRandomNearField(const spy::gameplay::State &s, const util::Point &p, T isSearchedField) {
                int dist = 1;
                while (true) {
                    auto res = getNearFieldsInDist(s, p, dist, isSearchedField);
                    if (!res.second) {
                        throw std::domain_error("No Point fulfilling isSearchedField was found on the whole map");
                    }
                    if (!res.first.empty()) {
                        return *getRandomItemFromContainer(res.first);
                    }
                    dist++;
                }
            }

            /**
             * @brief get points of neighbouring fields which fulfil certain condition (with minimal distance to p)
             * @tparam t function
             * @param s current state
             * @param p Point from which to search
             * @param isSearchedField function that defines conditions returned point must fulfil to be accepted
             * @return closest points fulfilling conditions
             */
            template<typename T>
            static std::vector<util::Point>
            getNearFields(const spy::gameplay::State &s, const util::Point &p, T isSearchedField) {
                int dist = 1;
                while (true) {
                    auto res = getNearFieldsInDist(s, p, dist, isSearchedField);
                    if (!res.second) {
                        throw std::domain_error("No Point fulfilling isSearchedField was found on the whole map");
                    }
                    if (!res.first.empty()) {
                        return res.first;
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
            static util::Point getRandomFreeSeatField(const spy::gameplay::State &s);

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
                        Point p{(int) x, (int) y};
                        if (isSearchedField(p)) {
                            result.push_back(p);
                        }
                    }
                }
                return result;
            }

            /**
             * @brief get random element from a container (e.g. vector)
             * @param v non empty container to select a random element from
             * @return const_iterator pointing to randomly selected element
             */
            template<typename Container>
            static typename Container::const_iterator getRandomItemFromContainer(const Container &v) {
                if (v.empty()) {
                    throw std::invalid_argument("Container is empty, cannot choose any element!");
                }

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

            /**
             * @brief get number of possible babysitters that could be applied
             * @param state current state
             * @return number of babysitters
             */
            static int
            babysitterNumber(const gameplay::State &s, std::shared_ptr<const spy::gameplay::GadgetAction> action);

            /**
             * @brief applies damage to a given character based on his properties and updates stats
             * @param s             Current state
             * @param targetChar    Target Character who receives damage
             * @param damage        unmodified damage value
             */
            static void
            applyDamageToCharacter(spy::gameplay::State &s, character::Character &targetChar, unsigned int damage);

            /**
             * @brief get operation that might change due to possible honey trap property
             * @param s current state
             * @param op GadgetOperation that targets a character
             * @return resulting GadgetOperation after honey trap was checked and applied
             */
            static gameplay::GadgetAction
            getHoneyTrapOperation(const gameplay::State &s, const gameplay::GadgetAction &op,
                                  const MatchConfig &config);

            /**
             * @brief tries to find character that gets ip because of wiretap with earplug gadget
             * @param s current state
             * @param gettingIP character that is getting intelligence points
             * @return character that also gets intelligence points (optional has no value if wiretap with earplug is not applyable)
             */
            static std::optional<std::shared_ptr<character::Character>>
            getWiredCharacter(const gameplay::State &s, const character::Character gettingIP);
    };
}

#endif //LIBCOMMON_GAMELOGICUTILS_HPP
