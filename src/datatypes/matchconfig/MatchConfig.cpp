/**
 * @file   MatchConfig.cpp
 * @author Dominik Authaler
 * @date   04.04.2020 (creation)
 * @brief  Definition of the match config class.
 */

#include "MatchConfig.hpp"

namespace spy {
    constexpr int INFINITE_LIMIT = -1;

    unsigned int MatchConfig::getMoledieRange() const {
        return moledieRange;
    }

    double MatchConfig::getBowlerBladeHitChance() const {
        return bowlerBladeHitChance;
    }

    unsigned int MatchConfig::getBowlerBladeRange() const {
        return bowlerBladeRange;
    }

    unsigned int MatchConfig::getBowlerBladeDamage() const {
        return bowlerBladeDamage;
    }

    double MatchConfig::getLaserCompactHitChance() const {
        return laserCompactHitChance;
    }

    unsigned int MatchConfig::getRocketPenDamage() const {
        return rocketPenDamage;
    }

    int MatchConfig::getGasGlossDamage() const {
        return gasGlossDamage;
    }

    unsigned int MatchConfig::getMothballPouchRange() const {
        return mothballPouchRange;
    }

    unsigned int MatchConfig::getMothballPouchDamage() const {
        return mothballPouchDamage;
    }

    unsigned int MatchConfig::getFogTinRange() const {
        return fogTinRange;
    }

    unsigned int MatchConfig::getGrappleRange() const {
        return grappleRange;
    }

    double MatchConfig::getGrappleHitChance() const {
        return grappleHitChance;
    }

    double MatchConfig::getWiretapWithEarplugsFailChance() const {
        return wiretapWithEarplugsFailChance;
    }

    double MatchConfig::getMirrorSwapChance() const {
        return mirrorSwapChance;
    }

    double MatchConfig::getCocktailDodgeChance() const {
        return cocktailDodgeChance;
    }

    unsigned int MatchConfig::getCocktailHealthPoints() const {
        return cocktailHealthPoints;
    }

    double MatchConfig::getSpySuccessChance() const {
        return spySuccessChance;
    }

    double MatchConfig::getBabysitterSuccessChance() const {
        return babysitterSuccessChance;
    }

    double MatchConfig::getHoneyTrapSuccessChance() const {
        return honeyTrapSuccessChance;
    }

    double MatchConfig::getObservationSuccessChance() const {
        return observationSuccessChance;
    }

    unsigned int MatchConfig::getChipsToIpFactor() const {
        return chipsToIpFactor;
    }

    unsigned int MatchConfig::getRoundLimit() const {
        return roundLimit;
    }

    std::optional<unsigned int> MatchConfig::getTurnPhaseLimit() const {
        return turnPhaseLimit;
    }

    std::optional<unsigned int> MatchConfig::getPauseLimit() const {
        return pauseLimit;
    }

    std::optional<unsigned int> MatchConfig::getReconnectLimit() const {
        return reconnectLimit;
    }

    unsigned int MatchConfig::getCatIp() const {
        return catIp;
    }

    unsigned int MatchConfig::getStrikeMaximum() const {
        return strikeMaximum;
    }

    void to_json(nlohmann::json &j, const MatchConfig &c) {
        j["moledieRange"] = c.moledieRange;

        j["bowlerBladeRange"] = c.bowlerBladeRange;
        j["bowlerBladeHitChance"] = c.bowlerBladeHitChance;
        j["bowlerBladeDamage"] = c.bowlerBladeDamage;

        j["laserCompactHitChance"] = c.laserCompactHitChance;

        j["rocketPenDamage"] = c.rocketPenDamage;

        j["gasGlossDamage"] = c.gasGlossDamage;

        j["mothballPouchRange"] = c.mothballPouchRange;
        j["mothballPouchDamage"] = c.mothballPouchDamage;

        j["fogTinRange"] = c.fogTinRange;

        j["grappleRange"] = c.grappleRange;
        j["grappleHitChance"] = c.grappleHitChance;

        j["wiretapWithEarplugsFailChance"] = c.wiretapWithEarplugsFailChance;

        j["mirrorSwapChance"] = c.mirrorSwapChance;

        j["cocktailDodgeChance"] = c.cocktailDodgeChance;

        j["cocktailHp"] = c.cocktailHealthPoints;

        j["spySuccessChance"] = c.spySuccessChance;

        j["babysitterSuccessChance"] = c.babysitterSuccessChance;

        j["honeyTrapSuccessChance"] = c.honeyTrapSuccessChance;

        j["observationSuccessChance"] = c.observationSuccessChance;

        j["chipsToIpFactor"] = c.chipsToIpFactor;

        j["roundLimit"] = c.roundLimit;

        if (c.turnPhaseLimit.has_value()) {
            j["turnPhaseLimit"] = c.turnPhaseLimit.value();
        } else {
            j["turnPhaseLimit"] = INFINITE_LIMIT;
        }

        j["catIp"] = c.catIp;

        j["strikeMaximum"] = c.strikeMaximum;

        if (c.pauseLimit.has_value()) {
            j["pauseLimit"] = c.pauseLimit.value();
        } else {
            j["pauseLimit"] = INFINITE_LIMIT;
        }

        if (c.reconnectLimit.has_value()) {
            j["reconnectLimit"] = c.reconnectLimit.value();
        } else {
            j["reconnectLimit"] = INFINITE_LIMIT;
        }
    }

    void from_json(const nlohmann::json &j, MatchConfig &c) {
        int turnPhaseLimit = 0;
        int reconnectLimit = 0;
        int pauseLimit = 0;

        j.at("moledieRange").get_to(c.moledieRange);

        j.at("bowlerBladeRange").get_to(c.bowlerBladeRange);
        j.at("bowlerBladeHitChance").get_to(c.bowlerBladeHitChance);
        j.at("bowlerBladeDamage").get_to(c.bowlerBladeDamage);

        j.at("laserCompactHitChance").get_to(c.laserCompactHitChance);

        j.at("rocketPenDamage").get_to(c.rocketPenDamage);

        j.at("gasGlossDamage").get_to(c.gasGlossDamage);

        j.at("mothballPouchRange").get_to(c.mothballPouchRange);
        j.at("mothballPouchDamage").get_to(c.mothballPouchDamage);

        j.at("fogTinRange").get_to(c.fogTinRange);

        j.at("grappleRange").get_to(c.grappleRange);
        j.at("grappleHitChance").get_to(c.grappleHitChance);

        j.at("wiretapWithEarplugsFailChance").get_to(c.wiretapWithEarplugsFailChance);

        j.at("mirrorSwapChance").get_to(c.mirrorSwapChance);

        j.at("cocktailDodgeChance").get_to(c.cocktailDodgeChance);

        j.at("cocktailHp").get_to(c.cocktailHealthPoints);

        j.at("spySuccessChance").get_to(c.spySuccessChance);

        j.at("babysitterSuccessChance").get_to(c.babysitterSuccessChance);

        j.at("honeyTrapSuccessChance").get_to(c.honeyTrapSuccessChance);

        j.at("observationSuccessChance").get_to(c.observationSuccessChance);

        j.at("chipsToIpFactor").get_to(c.chipsToIpFactor);

        j.at("roundLimit").get_to(c.roundLimit);

        j.at("catIp").get_to(c.catIp);

        j.at("strikeMaximum").get_to(c.strikeMaximum);

        j.at("turnPhaseLimit").get_to(turnPhaseLimit);
        j.at("reconnectLimit").get_to(reconnectLimit);
        j.at("pauseLimit").get_to(pauseLimit);

        c.turnPhaseLimit = (turnPhaseLimit < 0) ? std::optional<unsigned int>() : turnPhaseLimit;
        c.reconnectLimit = (reconnectLimit < 0) ? std::optional<unsigned int>() : reconnectLimit;
        c.pauseLimit = (pauseLimit < 0) ? std::optional<unsigned int>() : pauseLimit;
    }
}
