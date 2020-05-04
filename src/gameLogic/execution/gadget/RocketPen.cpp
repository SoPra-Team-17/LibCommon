/**
* @file   RocketPen.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of rocket pen gadget execution
*/

#include "GadgetExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeRocketPen(State &s, const GadgetAction &a, const MatchConfig &config) {
        // destroy potential wall on target field
        bool targetHasWall = (s.getMap().getField(a.getTarget()).getFieldState() == scenario::FieldStateEnum::WALL);
        if (targetHasWall) {
            s.getMap().getField(a.getTarget()).setFieldState(scenario::FieldStateEnum::FREE);
        }

        //Neighboring fields that have walls on them
        auto fieldWithWalls = util::GameLogicUtils::getNearFieldsInDist(s, a.getTarget(), 1,
                                                                        [&s](const util::Point &p) {
                                                                            return s.getMap().getField(
                                                                                    p).getFieldState() ==
                                                                                   scenario::FieldStateEnum::WALL;
                                                                        });
        if (fieldWithWalls.second) {
            for (const auto &p : fieldWithWalls.first) {
                s.getMap().getField(p).setFieldState(scenario::FieldStateEnum::FREE);
            }
        }

        // damage on targetfield, if there is a person
        bool targetHasPerson = util::GameLogicUtils::isPersonOnField(s, a.getTarget());
        if (targetHasPerson) {
            bool babysitter = util::GameLogicUtils::checkBabySitter(s, a, config);
            if (!babysitter) {
                auto person = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), a.getTarget());
                auto damage = config.getRocketPenDamage();
                person->subHealthPoints(damage);
            }
        }

        // get characters on neighboring fields
        auto charPoints = util::GameLogicUtils::getNearFieldsInDist(s, a.getTarget(), 1, [&s](const util::Point &p) {
            return util::GameLogicUtils::isPersonOnField(s, p);
        });
        if (charPoints.second) {
            for (const auto &p : charPoints.first) {
                bool babysitter = util::GameLogicUtils::isPersonOnField(s, p);
                if (!babysitter) {
                    auto person = util::GameLogicUtils::getInCharacterSetByCoordinates(s.getCharacters(), p);
                    auto damage = config.getRocketPenDamage();
                    person->subHealthPoints(damage);
                }
            }
        }

        // remove rocket pen from inventory
        auto character = s.getCharacters().getByUUID(a.getCharacterId());
        character->removeGadget(gadget::GadgetEnum::ROCKET_PEN);

        return true;
    }
}