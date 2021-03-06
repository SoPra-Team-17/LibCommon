/**
* @file   RoundUtils.hpp
* @author Dominik Authaler
* @date   04.05.2020 (creation)
* @brief  Implementation of utility methods for round initialization.
*/

#include "RoundUtils.hpp"
#include "datatypes/gadgets/Cocktail.hpp"
#include "datatypes/gadgets/WiretapWithEarplugs.hpp"
#include "util/GameLogicUtils.hpp"


constexpr unsigned int FOG_ROUND_LIMIT = 3;

namespace spy::util {
    void RoundUtils::refillBarTables(spy::gameplay::State &s) {
        s.getMap().forAllFields([](scenario::Field &field) {
            if (field.getFieldState() == spy::scenario::FieldStateEnum::BAR_TABLE
                && !field.getGadget().has_value()) {
                field.setGadget(std::make_shared<spy::gadget::Cocktail>());
            }
        });
    }

    void RoundUtils::updateFog(gameplay::State &s) {
        s.getMap().forAllFields([](scenario::Field &field) {
            if (field.isFoggy()) {
                field.incrementFogCounter();
                if (field.getFogCounter() >= FOG_ROUND_LIMIT) {
                    field.setFoggy(false);
                    field.resetFogCounter();
                }
            }
        });
    }

    void RoundUtils::checkGadgetFailure(gameplay::State &s, const MatchConfig &config) {
        for (auto &c : s.getCharacters()) {
            auto gadget = c.getGadget(gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS);
            if (gadget.has_value()) {
                auto wiretap = std::dynamic_pointer_cast<spy::gadget::WiretapWithEarplugs>(gadget.value());

                if (wiretap->isWorking() &&
                    GameLogicUtils::probabilityTest(config.getWiretapWithEarplugsFailChance())) {
                    wiretap->setWorking(false);
                } else if (!wiretap->isWorking() && wiretap->getActiveOn().has_value()) {
                    // Standard specifies that their must be at least one message with the gadget disabled after fallout
                    c.removeGadget(gadget::GadgetEnum::WIRETAP_WITH_EARPLUGS);
                }
            }
        }
    }

    void RoundUtils::resetUpdatedMarker(gameplay::State &s) {
        s.getMap().forAllFields([](scenario::Field &field) {
            field.setUpdated(false);
        });
    }

    bool RoundUtils::isGameOver(const gameplay::State &s) {
        // check if cat has diamond collar
        bool getHasCollar = s.getHasCatDiamondCollar();

        // check if character remaining on field
        bool charOnField = false;
        for (const auto &character : s.getCharacters()) {
            if (character.getCoordinates().has_value()) {
                charOnField = true;
                break;
            }
        }

        return getHasCollar || !charOnField;
    }

    void RoundUtils::updateGameOver(gameplay::State &s, const spy::MatchConfig &config) {
        // convert chips to IP
        for (auto &character : s.getCharacters()) {
            character.addIntelligencePoints(character.getChips() * config.getChipsToIpFactor());
        }
    }

    VictoryInfo RoundUtils::determineVictory(const gameplay::State &s) {
        using character::FactionEnum;
        using statistics::VictoryEnum;

        FactionEnum winner;

        // check which faction has more ip
        unsigned int ipFaction1 = 0;
        unsigned int ipFaction2 = 0;

        for (const auto &character : s.getCharacters()) {
            if (character.getFaction() == FactionEnum::PLAYER1) {
                ipFaction1 += character.getIntelligencePoints();
            } else if (character.getFaction() == FactionEnum::PLAYER2) {
                ipFaction2 += character.getIntelligencePoints();
            }
        }

        if (ipFaction1 != ipFaction2) {
            winner = (ipFaction1 > ipFaction2) ? FactionEnum::PLAYER1 : FactionEnum::PLAYER2;

            return VictoryInfo(winner, VictoryEnum::VICTORY_BY_IP);
        }

        auto stats = s.getConstFactionStats();

        // which faction brought diamond collar to cat
        if (stats.collarToCat != FactionEnum::INVALID) {
            return VictoryInfo(stats.collarToCat, VictoryEnum::VICTORY_BY_COLLAR);
        }

        // which faction drank more cocktails
        if (stats.cocktails.first != stats.cocktails.second) {
            winner = (stats.cocktails.first > stats.cocktails.second) ? FactionEnum::PLAYER1 : FactionEnum::PLAYER2;
            return VictoryInfo(winner, VictoryEnum::VICTORY_BY_DRINKING);
        }

        // more cocktails pours against the other faction
        if (stats.cocktailsPoured.first != stats.cocktailsPoured.second) {
            winner = (stats.cocktailsPoured.first > stats.cocktailsPoured.second) ? FactionEnum::PLAYER1
                                                                                  : FactionEnum::PLAYER2;
            return VictoryInfo(winner, VictoryEnum::VICTORY_BY_SPILLING);
        }

        // which faction suffered less damage
        if (stats.damageSuffered.first != stats.damageSuffered.second) {
            winner = (stats.damageSuffered.first > stats.damageSuffered.second) ? FactionEnum::PLAYER2
                                                                                : FactionEnum::PLAYER1;
            return VictoryInfo(winner, VictoryEnum::VICTORY_BY_HP);
        }

        // randomly choose winner
        winner = util::GameLogicUtils::probabilityTest(0.5) ? FactionEnum::PLAYER1 : FactionEnum::PLAYER2;
        return VictoryInfo(winner, VictoryEnum::VICTORY_BY_RANDOMNESS);
    }

    void RoundUtils::determinePoints(character::Character &character) {
        // default_mp = 2, default_ap = 1
        unsigned int movement_pts = 2;
        unsigned int action_pts = 1;

        if (character.hasProperty(character::PropertyEnum::NIMBLENESS)) {
            movement_pts = 3;
        }

        if (character.hasProperty(character::PropertyEnum::SLUGGISHNESS)) {
            movement_pts = 1;
        }

        if (character.hasProperty(character::PropertyEnum::SPRYNESS)) {
            action_pts = 2;
        }

        if (character.hasProperty(character::PropertyEnum::PONDEROUSNESS)) {
            if (util::GameLogicUtils::probabilityTest(0.5)) {
                movement_pts--;
            } else {
                action_pts--;
            }
        }

        if (character.hasProperty(character::PropertyEnum::AGILITY)) {
            if (util::GameLogicUtils::probabilityTest(0.5)) {
                movement_pts++;
            } else {
                action_pts++;
            }
        }

        character.setActionPoints(action_pts);
        character.setMovePoints(movement_pts);
    }
}
