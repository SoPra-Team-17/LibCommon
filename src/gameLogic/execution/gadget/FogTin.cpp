/**
* @file   FogTin.cpp
* @author Marco Deuscher
* @date   04.05.2020 (creation)
* @brief  Implementation of fog tin gadget execution
*/

#include "GadgetExecutor.hpp"
#include "util/GameLogicUtils.hpp"

namespace spy::gameplay {

    bool GadgetExecutor::executeFogTin(State &s, const GadgetAction &a) {
        s.getMap().getField(a.getTarget()).setFoggy(true);
        // get neighboring fields
        auto points = util::GameLogicUtils::getNearFieldsInDist(s, a.getTarget(), 1, [](const util::Point &/*p*/) {
            return true;
        });

        if (points.second) {
            for (const auto &p : points.first) {
                s.getMap().getField(p).setFoggy(true);
            }
        }
        return true;
    }
}

