/**
 * @file   matchConfigTest.cpp
 * @author Dominik Authaler
 * @date   04.04.2020 (creation)
 * @brief  Unit tests for the MatchConfig class.
 */

#include <gtest/gtest.h>
#include <matchconfig/MatchConfig.hpp>

TEST(MatchConfigDecodingEncoding, MatchConfig) {
    auto input = R"({
            "Moledie_Range" : 1 ,
            "BowlerBlade_Range" : 1 ,
            "BowlerBlade_HitChance" : 0.25 ,
            "BowlerBlade_Damage" : 4 ,
            "LaserCompact_HitChance" : 0.125 ,
            "RocketPen_Damage" : 2 ,
            "GasGloss_Damage" : 6 ,
            "MothballPouch_Range" : 2 ,
            "MothballPouch_Damage" : 1 ,
            "FogTin_Range" : 2 ,
            "Grapple_Range" : 3 ,
            "Grapple_HitChance" : 0.35 ,
            "WiretapWithEarplugs_FailChance" : 0.64 ,
            "Mirror_SwapChance" : 0.35 ,
            "Cocktail_DodgeChance" : 0.25 ,
            "Cocktail_Hp" : 6 ,
            "Spy_SuccessChance" : 0.65 ,
            "Babysitter_SuccessChance" : 0.25 ,
            "HoneyTrap_SuccessChance" : 0.35 ,
            "Observation_SuccessChance" : 0.12 ,
            "ChipsToIpFaktor" : 12 ,
            "RoundLimit" : 15 ,
            "TurnPhaseLimit" : 6 ,
            "CatIp" : 8 ,
            "StrikeMaximum" : 4
    })"_json;

    spy::MatchConfig decodedMatchConfig;
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
    EXPECT_EQ(decodedMatchConfig.getRoundLimit(), 15);
    EXPECT_EQ(decodedMatchConfig.getTurnPhaseLimit(), 6);
    EXPECT_EQ(decodedMatchConfig.getCatIp(), 8);
    EXPECT_EQ(decodedMatchConfig.getStrikeMaximum(), 4);

    std::string jsonString;
    nlohmann::json json;
    EXPECT_NO_THROW(json = decodedMatchConfig);
    EXPECT_EQ(json.dump(), input.dump());
}


