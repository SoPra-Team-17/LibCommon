//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"
#include <util/GameLogicUtils.hpp>

namespace spy::gameplay {

    static std::shared_ptr<const BaseOperation>
    handleSpyOnPerson(State &s, const SpyAction &op, const MatchConfig &config,
                      character::CharacterSet::iterator character, character::CharacterSet::const_iterator targetChar) {
        auto retOp = std::make_shared<SpyAction>(op);

        if (targetChar->getFaction() != character::FactionEnum::NEUTRAL) {
            retOp->setSuccessful(false);
            return retOp;
        }

        bool success = util::GameLogicUtils::probabilityTestWithCharacter(*character,
                                                                          config.getSpySuccessChance());
        retOp->setSuccessful(success);
        if (!success) {
            return retOp;
        }

        if (util::GameLogicUtils::probabilityTest(0.5)) {
            // character gets a secret
            unsigned int maxSafeIndex = 1;

            s.getMap().forAllFields([&maxSafeIndex](const scenario::Field &f) {
                if (f.getFieldState() == scenario::FieldStateEnum::SAFE
                    && f.getSafeIndex().value() > maxSafeIndex) {
                    maxSafeIndex = f.getSafeIndex().value();
                }
            });

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<unsigned int> randPos(1, maxSafeIndex);

            auto secret = randPos(gen);

            if (s.getMySafeCombinations().find(secret) != s.getMySafeCombinations().end()) {
                s.addSafeCombination(secret);
                character->addIntelligencePoints(static_cast<int>(config.getSecretToIpFactor()));
            }
        }

        return retOp;
    }

    static std::shared_ptr<const BaseOperation>
    handleSpyOnSafe(State &s, const SpyAction &op, const MatchConfig &config,
                    character::CharacterSet::iterator character) {
        auto retOp = std::make_shared<SpyAction>(op);

        retOp->setSuccessful(true);

        // get index of safe
        auto safeIndex = s.getMap().getField(op.getTarget()).getSafeIndex().value();

        // query safe indexes and the collar location from the current state
        unsigned int maxSafeIndex = 1;
        bool collarOnMap = false;

        s.getMap().forAllFields([&maxSafeIndex, &collarOnMap](const scenario::Field &f) {
            if (f.getFieldState() == scenario::FieldStateEnum::SAFE
                && f.getSafeIndex().value() > maxSafeIndex) {
                maxSafeIndex = f.getSafeIndex().value();
            } else if (f.getGadget().has_value()
                       && f.getGadget().value()->getType() == gadget::GadgetEnum::DIAMOND_COLLAR) {
                collarOnMap = true;
            }
        });

        if (!collarOnMap) {
            for (const auto &c : s.getCharacters()) {
                if (c.hasGadget(gadget::GadgetEnum::DIAMOND_COLLAR)) {
                    collarOnMap = true;
                    break;
                }
            }
        }

        if (safeIndex == maxSafeIndex && !collarOnMap) {
            // first character gets the diamond collar
            character->addGadget(std::make_shared<gadget::Gadget>(gadget::GadgetEnum::DIAMOND_COLLAR));
            character->addIntelligencePoints(static_cast<int>(config.getSecretToIpFactor()));
        } else if (safeIndex < maxSafeIndex) {
            if (s.getMySafeCombinations().find(safeIndex) != s.getMySafeCombinations().end()) {
                // faction gets the key for the next safe
                s.addSafeCombination(safeIndex + 1);
                character->addIntelligencePoints(static_cast<int>(config.getSecretToIpFactor()));
            }
        }

        return retOp;
    }

    std::shared_ptr<const BaseOperation>
    ActionExecutor::executeSpy(State &s, const SpyAction &op, const MatchConfig &config) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());
        character->subActionPoint();

        auto targetChar = util::GameLogicUtils::findInCharacterSetByCoordinates(s.getCharacters(), op.getTarget());

        if (targetChar != s.getCharacters().end()) {
            return handleSpyOnPerson(s, op, config, character, targetChar);
        } else {
            return handleSpyOnSafe(s, op, config, character);
        }
    }
}