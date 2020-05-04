//
// Created by jonas on 02.04.20.
//

#include "WiretapWithEarplugs.hpp"
#include "util/OptionalSerialization.hpp"

namespace spy::gadget {

    bool WiretapWithEarplugs::isWorking() const {
        return working;
    }

    void WiretapWithEarplugs::setWorking(bool isWorking) {
        WiretapWithEarplugs::working = isWorking;
    }

    auto WiretapWithEarplugs::getActiveOn() const -> const std::optional<spy::util::UUID> & {
        return activeOn;
    }

    void WiretapWithEarplugs::setActiveOn(const std::optional<spy::util::UUID> &active) {
        WiretapWithEarplugs::activeOn = active;
    }

    void to_json(nlohmann::json &j, const WiretapWithEarplugs &w) {
        Gadget::common_to_json(j, w);
        j["working"] = w.working;
        j["activeOn"] = w.activeOn;
    }

    void from_json(const nlohmann::json &j, WiretapWithEarplugs &w) {
        Gadget::common_from_json(j,w);
        j.at("working").get_to(w.working);
        j.at("activeOn").get_to(w.activeOn);
    }

}  // namespace spy::gadget
