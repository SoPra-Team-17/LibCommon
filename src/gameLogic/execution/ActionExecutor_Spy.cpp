//
// Created by jonas on 28.04.20.
//
#include "ActionExecutor.hpp"
#include <util/GameLogicUtils.hpp>

namespace spy::gameplay {
    std::shared_ptr<const BaseOperation>
    ActionExecutor::executeSpy(State &s, const SpyAction &op, const MatchConfig &config) {
        auto character = s.getCharacters().getByUUID(op.getCharacterId());
        character->subActionPoint();

        auto retOp = std::make_shared<SpyAction>(op);

        auto targetChar = util::GameLogicUtils::findPersonOnNeighbourField(s, op.getTarget(),
                                                                           character->getCoordinates().value());
        if (targetChar != s.getCharacters().end()) {
            // spy on person
            if (targetChar->getFaction() == character::FactionEnum::NEUTRAL) {
                // spy on NPC
                bool success = util::GameLogicUtils::probabilityTestWithCharacter(*character,
                                                                                  config.getSpySuccessChance());
                retOp->setSuccessful(success);

                if (success) {
                    if (util::GameLogicUtils::probabilityTest(0.5)) {
                        // character gets a secret
                        unsigned int maxSafeIndex = 1;

                        s.getMap().forAllFields([&maxSafeIndex](const scenario::Field &f) {
                            if (f.getFieldState() == scenario::FieldStateEnum::SAFE
                                && f.getSafeIndex().has_value()
                                && f.getSafeIndex().value() > maxSafeIndex) {
                                maxSafeIndex = f.getSafeIndex().value();
                            }
                        });

                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<unsigned int> randPos(1, maxSafeIndex);

                        auto secret = randPos(gen);

                        s.addSafeCombination(secret);
                    }
                }
            } else {
                // spy on character of the other faction --> always fails
                retOp->setSuccessful(false);
            }

        } else {
            // spy on safe
            retOp->setSuccessful(true);

            // get index of safe
            auto safeIndex = s.getMap().getField(op.getTarget()).getSafeIndex();

            unsigned int maxSafeIndex = 1;
            bool collarOnMap = false;

            s.getMap().forAllFields([&maxSafeIndex, &collarOnMap](const scenario::Field &f) {
                if (f.getFieldState() == scenario::FieldStateEnum::SAFE
                    && f.getSafeIndex().has_value()
                    && f.getSafeIndex().value() > maxSafeIndex) {
                    maxSafeIndex = f.getSafeIndex().value();
                } else if (f.getGadget().has_value()
                           && f.getGadget().value()->getType() == gadget::GadgetEnum::DIAMOND_COLLAR) {
                    collarOnMap = true;
                }
            });

            if (safeIndex == maxSafeIndex && !collarOnMap) {
                // first character gets the diamond collar
                character->addGadget(std::make_shared<gadget::Gadget>(gadget::GadgetEnum::DIAMOND_COLLAR));
            }
        }

        // check if the character gets intelligence points
        if (retOp->isSuccessful()) {
            character->addIntelligencePoints(static_cast<int>(config.getSecretToIpFactor()));
        }

        return retOp;
    }
}