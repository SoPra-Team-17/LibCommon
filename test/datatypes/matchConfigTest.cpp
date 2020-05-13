/**
 * @file   matchConfigTest.cpp
 * @author Dominik Authaler
 * @date   04.04.2020 (creation)
 * @brief  Unit tests for the MatchConfig class.
 */

#include <gtest/gtest.h>
#include <datatypes/matchconfig/MatchConfig.hpp>

TEST(MatchConfig, MatchConfigDecodingEncoding) {
    auto input = R"({
    "moledieRange": 1,
    "bowlerBladeRange": 1,
    "bowlerBladeHitChance": 0.25,
    "bowlerBladeDamage": 4,
    "laserCompactHitChance": 0.125,
    "rocketPenDamage": 2,
    "gasGlossDamage": 6,
    "mothballPouchRange": 2,
    "mothballPouchDamage": 1,
    "fogTinRange": 2,
    "grappleRange": 3,
    "grappleHitChance": 0.35,
    "wiretapWithEarplugsFailChance": 0.64,
    "mirrorSwapChance": 0.35,
    "cocktailDodgeChance": 0.25,
    "cocktailHp": 6,
    "spySuccessChance": 0.65,
    "babysitterSuccessChance": 0.25,
    "honeyTrapSuccessChance": 0.35,
    "observationSuccessChance": 0.12,
    "chipsToIpFactor": 12,
    "secretToIpFactor": 9 ,
    "minChipsRoulette": 0 ,
    "maxChipsRoulette": 6 ,
    "roundLimit": 15,
    "turnPhaseLimit": 6,
    "catIp": 8,
    "strikeMaximum": 4,
    "pauseLimit": 320,
    "reconnectLimit": 20
})"_json;

    spy::MatchConfig decodedMatchConfig{};
    EXPECT_NO_THROW(decodedMatchConfig = input.get<spy::MatchConfig>());

    EXPECT_EQ(decodedMatchConfig.getMoledieRange(), 1);
    EXPECT_EQ(decodedMatchConfig.getBowlerBladeRange(), 1);
    EXPECT_EQ(decodedMatchConfig.getBowlerBladeHitChance(), 0.25);
    EXPECT_EQ(decodedMatchConfig.getBowlerBladeDamage(), 4);
    EXPECT_EQ(decodedMatchConfig.getLaserCompactHitChance(), 0.125);
    EXPECT_EQ(decodedMatchConfig.getRocketPenDamage(), 2);
    EXPECT_EQ(decodedMatchConfig.getGasGlossDamage(), 6);
    EXPECT_EQ(decodedMatchConfig.getMothballPouchRange(), 2);
    EXPECT_EQ(decodedMatchConfig.getMothballPouchDamage(), 1);
    EXPECT_EQ(decodedMatchConfig.getFogTinRange(), 2);
    EXPECT_EQ(decodedMatchConfig.getGrappleRange(), 3);
    EXPECT_EQ(decodedMatchConfig.getGrappleHitChance(), 0.35);
    EXPECT_EQ(decodedMatchConfig.getWiretapWithEarplugsFailChance(), 0.64);
    EXPECT_EQ(decodedMatchConfig.getMirrorSwapChance(), 0.35);
    EXPECT_EQ(decodedMatchConfig.getCocktailDodgeChance(), 0.25);
    EXPECT_EQ(decodedMatchConfig.getCocktailHealthPoints(), 6);
    EXPECT_EQ(decodedMatchConfig.getSpySuccessChance(), 0.65);
    EXPECT_EQ(decodedMatchConfig.getBabysitterSuccessChance(), 0.25);
    EXPECT_EQ(decodedMatchConfig.getHoneyTrapSuccessChance(), 0.35);
    EXPECT_EQ(decodedMatchConfig.getObservationSuccessChance(), 0.12);
    EXPECT_EQ(decodedMatchConfig.getChipsToIpFactor(), 12);
    EXPECT_EQ(decodedMatchConfig.getSecretToIpFactor(), 9);
    EXPECT_EQ(decodedMatchConfig.getRoundLimit(), 15);
    EXPECT_EQ(decodedMatchConfig.getTurnPhaseLimit(), 6);
    EXPECT_EQ(decodedMatchConfig.getCatIp(), 8);
    EXPECT_EQ(decodedMatchConfig.getStrikeMaximum(), 4);
    EXPECT_EQ(decodedMatchConfig.getPauseLimit(), 320);
    EXPECT_EQ(decodedMatchConfig.getReconnectLimit(), 20);
    EXPECT_EQ(decodedMatchConfig.getMinChipsRoulette(), 0);
    EXPECT_EQ(decodedMatchConfig.getMaxChipsRoulette(), 6);

    nlohmann::json json;
    EXPECT_NO_THROW(json = decodedMatchConfig);
    EXPECT_EQ(json.dump(), input.dump());
}

TEST(MatchConfig, InfiniteLimits) {
    auto input = R"({
    "moledieRange": 1,
    "bowlerBladeRange": 1,
    "bowlerBladeHitChance": 0.25,
    "bowlerBladeDamage": 4,
    "laserCompactHitChance": 0.125,
    "rocketPenDamage": 2,
    "gasGlossDamage": 6,
    "mothballPouchRange": 2,
    "mothballPouchDamage": 1,
    "fogTinRange": 2,
    "grappleRange": 3,
    "grappleHitChance": 0.35,
    "wiretapWithEarplugsFailChance": 0.64,
    "mirrorSwapChance": 0.35,
    "cocktailDodgeChance": 0.25,
    "cocktailHp": 6,
    "spySuccessChance": 0.65,
    "babysitterSuccessChance": 0.25,
    "honeyTrapSuccessChance": 0.35,
    "observationSuccessChance": 0.12,
    "chipsToIpFactor": 12,
    "secretToIpFactor": 9,
    "minChipsRoulette": 0,
    "maxChipsRoulette": 6,
    "roundLimit": 15,
    "turnPhaseLimit": -10,
    "catIp": 8,
    "strikeMaximum": 4,
    "pauseLimit": -5,
    "reconnectLimit": -1
})"_json;

    auto expected = R"({
    "moledieRange": 1,
    "bowlerBladeRange": 1,
    "bowlerBladeHitChance": 0.25,
    "bowlerBladeDamage": 4,
    "laserCompactHitChance": 0.125,
    "rocketPenDamage": 2,
    "gasGlossDamage": 6,
    "mothballPouchRange": 2,
    "mothballPouchDamage": 1,
    "fogTinRange": 2,
    "grappleRange": 3,
    "grappleHitChance": 0.35,
    "wiretapWithEarplugsFailChance": 0.64,
    "mirrorSwapChance": 0.35,
    "cocktailDodgeChance": 0.25,
    "cocktailHp": 6,
    "spySuccessChance": 0.65,
    "babysitterSuccessChance": 0.25,
    "honeyTrapSuccessChance": 0.35,
    "observationSuccessChance": 0.12,
    "chipsToIpFactor": 12,
    "secretToIpFactor": 9,
    "minChipsRoulette": 0,
    "maxChipsRoulette": 6,
    "roundLimit": 15,
    "turnPhaseLimit": -1,
    "catIp": 8,
    "strikeMaximum": 4,
    "pauseLimit": -1,
    "reconnectLimit": -1
})"_json;

    spy::MatchConfig decodedMatchConfig{};
    EXPECT_NO_THROW(decodedMatchConfig = input.get<spy::MatchConfig>());

    EXPECT_NE(decodedMatchConfig.getTurnPhaseLimit(), -10);
    EXPECT_NE(decodedMatchConfig.getPauseLimit(), -5);
    EXPECT_NE(decodedMatchConfig.getReconnectLimit(), -1);
    EXPECT_FALSE(decodedMatchConfig.getTurnPhaseLimit().has_value());
    EXPECT_FALSE(decodedMatchConfig.getPauseLimit().has_value());
    EXPECT_FALSE(decodedMatchConfig.getReconnectLimit().has_value());

    nlohmann::json json;
    EXPECT_NO_THROW(json = decodedMatchConfig);
    EXPECT_EQ(json.dump(), expected.dump());
}


