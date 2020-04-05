/**
 * @file   MatchConfig.hpp
 * @author Dominik Authaler
 * @date   04.04.2020 (creation)
 * @brief  Declaration of the match config class.
 */

#ifndef LIBCOMMON_MATCH_CONFIG_HPP
#define LIBCOMMON_MATCH_CONFIG_HPP

#include <nlohmann/json.hpp>

namespace spy {
    /**
     * @brief Represents the match configuration.
     */
    class MatchConfig {
        public:
            MatchConfig();

            /**
             * Getter for the moledie range.
             * @return Range of the moledie gadget.
             */
            [[nodiscard]] unsigned int getMoledieRange() const;

            /**
             * Getter for the bowler blade range.
             * @return Range of the bowler blade gadget.
             */
            [[nodiscard]] unsigned int getBowlerBladeRange() const;

            /**
             * Getter for the bowler blade hit chance.
             * @return Hit chance of the bowler blade gadget.
             */
            [[nodiscard]] double getBowlerBladeHitChance() const;

            /**
             * Getter for the bowler blade damage.
             * @return Damage of the bowler blade gadget.
             */
            [[nodiscard]] unsigned int getBowlerBladeDamage() const;

            /**
             * Getter for the laser compact hit chance.
             * @return Hit chance of the compact laser gadget.
             */
            [[nodiscard]] double getLaserCompactHitChance() const;

            /**
             * Getter for the rocket pen damage.
             * @return Damage of the rocket pen gadget.
             */
            [[nodiscard]] unsigned int getRocketPenDamage() const;

            /**
             * Getter for the gas gloss damage.
             * @return Damage of the gas gloss gadget.
             */
            [[nodiscard]] int getGasGlossDamage() const;

            /**
             * Getter for the mothball pouch range.
             * @return Range of the mothball pouch gadget.
             */
            [[nodiscard]] unsigned int getMothballPouchRange() const;

            /**
             * Getter for the mothball pouch damage.
             * @return Damage of the mothball pouch gadget.
             */
            [[nodiscard]] unsigned int getMothballPouchDamage() const;

            /**
             * Getter for the fog tin range.
             * @return Range of the fog tin gadget.
             */
            [[nodiscard]] unsigned int getFogTinRange() const;

            /**
             * Getter for the grapple range.
             * @return Range of the grapple gadget.
             */
            [[nodiscard]] unsigned int getGrappleRange() const;

            /**
             * Getter for the grapple hit chance.
             * @return Hit chance of the grapple gadget.
             */
            [[nodiscard]] double getGrappleHitChance() const;

            /**
             * Getter for the wiretap with earplugs fail chance.
             * @return Fail chance of the wiretap with earplugs gadget.
             */
            [[nodiscard]] double getWiretapWithEarplugsFailChance() const;

            /**
             * Getter for the mirror swap chance.
             * @return Swap chance of the mirror gadget.
             */
            [[nodiscard]] double getMirrorSwapChance() const;

            /**
             * Getter for the cocktail dodge chance.
             * @return Dodge chance for cocktails.
             */
            [[nodiscard]] double getCocktailDodgeChance() const;

            /**
             * Getter for the cocktail health points.
             * @return Health points of cocktails.
             */
            [[nodiscard]] unsigned int getCocktailHealthPoints() const;

            /**
             * Getter for the spy success chance.
             * @return Success chance of the spy property.
             */
            [[nodiscard]] double getSpySuccessChance() const;

            /**
             * Getter for the babysitter success chance.
             * @return Success chance of the babysitter property.
             */
            [[nodiscard]] double getBabysitterSuccessChance() const;

            /**
             * Getter for the honey trap success chance.
             * @return Success chance of the honey trap property.
             */
            [[nodiscard]] double getHoneyTrapSuccessChance() const;

            /**
             * Getter for the observation success chance.
             * @return Success chance of the observation property.
             */
            [[nodiscard]] double getObservationSuccessChance() const;

            /**
             * Getter for the chips to intelligence points factor.
             * @return Chips to intelligence points factor.
             */
            [[nodiscard]] unsigned int getChipsToIpFactor() const;

            /**
             * Getter for the round limit.
             * @return Round limit.
             */
            [[nodiscard]] unsigned int getRoundLimit() const;

            /**
             * Getter for the turn phase limit.
             * @return Turn phase limit.
             */
            [[nodiscard]] unsigned int getTurnPhaseLimit() const;

            /**
             * Getter for the cat intelligence points.
             * @return Cat intelligence points.
             */
            [[nodiscard]] unsigned int getCatIp() const;

            /**
             * Getter for the Strike maximum.
             * @return Maximum number of strikes.
             */
            [[nodiscard]] unsigned int getStrikeMaximum() const;


            /**
             * Converts from json to a MatchConfig object.
             * @param j Json object (source).
             * @param c Match config object as destination of the conversion.
             */
            friend void from_json(const nlohmann::json &j, MatchConfig &c);

        private:
            unsigned int moledieRange;

            unsigned int bowlerBladeRange;
            double bowlerBladeHitChance;
            unsigned int bowlerBladeDamage;

            double laserCompactHitChance;

            unsigned int rocketPenDamage;

            int gasGlossDamage;

            unsigned int mothballPouchRange;
            unsigned int mothballPouchDamage;

            unsigned int fogTinRange;

            unsigned int grappleRange;
            double grappleHitChance;

            double wiretapWithEarplugsFailChance;

            double mirrorSwapChance;

            double cocktailDodgeChance;
            unsigned int cocktailHealthPoints;

            double spySuccessChance;
            double babysitterSuccessChance;
            double honeyTrapSuccessChance;
            double observationSuccessChance;

            unsigned int chipsToIpFactor;
            unsigned int roundLimit;
            unsigned int turnPhaseLimit;
            unsigned int catIp;
            unsigned int strikeMaximum;
    };
}

#endif //LIBCOMMON_MATCH_CONFIG_HPP
