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
            MatchConfig() = default;

            [[nodiscard]] unsigned int getMoledieRange() const;

            [[nodiscard]] unsigned int getBowlerBladeRange() const;

            [[nodiscard]] double getBowlerBladeHitChance() const;

            [[nodiscard]] int getBowlerBladeDamage() const;

            [[nodiscard]] double getLaserCompactHitChance() const;

            [[nodiscard]] int getRocketPenDamage() const;

            [[nodiscard]] int getGasGlossDamage() const;

            [[nodiscard]] unsigned int getMothballPouchRange() const;

            [[nodiscard]] int getMothballPouchDamage() const;

            [[nodiscard]] unsigned int getFogTinRange() const;

            [[nodiscard]] unsigned int getGrappleRange() const;

            [[nodiscard]] double getGrappleHitChance() const;

            [[nodiscard]] double getWiretapWithEarplugsFailChance() const;

            [[nodiscard]] double getMirrorSwapChance() const;

            [[nodiscard]] double getCocktailDodgeChance() const;

            [[nodiscard]] unsigned int getCocktailHealthPoints() const;

            [[nodiscard]] double getSpySuccessChance() const;

            [[nodiscard]] double getBabysitterSuccessChance() const;

            [[nodiscard]] double getHoneyTrapSuccessChance() const;

            [[nodiscard]] double getObservationSuccessChance() const;

            [[nodiscard]] unsigned int getChipsToIpFactor() const;

            [[nodiscard]] unsigned int getSecretToIpFactor() const;

            [[nodiscard]] unsigned int getRoundLimit() const;

            [[nodiscard]] unsigned int getCatIp() const;

            [[nodiscard]] unsigned int getStrikeMaximum() const;

            [[nodiscard]] std::optional<unsigned int> getTurnPhaseLimit() const;

            [[nodiscard]] std::optional<unsigned int> getPauseLimit() const;

            [[nodiscard]] std::optional<unsigned int> getReconnectLimit() const;

            [[nodiscard]] unsigned int getMinChipsRoulette() const;

            [[nodiscard]] unsigned int getMaxChipsRoulette() const;

            friend void to_json(nlohmann::json &j, const MatchConfig &c);

            friend void from_json(const nlohmann::json &j, MatchConfig &c);

            bool operator==(const MatchConfig &rhs) const;

        private:
            unsigned int moledieRange;

            unsigned int bowlerBladeRange;
            double bowlerBladeHitChance;
            int bowlerBladeDamage;

            double laserCompactHitChance;

            int rocketPenDamage;

            int gasGlossDamage;

            unsigned int mothballPouchRange;
            int mothballPouchDamage;

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
            unsigned int secretToIpFactor;
            unsigned int roundLimit;
            unsigned int catIp;
            unsigned int strikeMaximum;

            unsigned int minChipsRoulette;
            unsigned int maxChipsRoulette;

            std::optional<unsigned int> turnPhaseLimit;
            std::optional<unsigned int> pauseLimit;
            std::optional<unsigned int> reconnectLimit;
    };
}

#endif //LIBCOMMON_MATCH_CONFIG_HPP
