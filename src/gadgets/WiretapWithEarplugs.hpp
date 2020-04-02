//
// Created by jonas on 02.04.20.
//

#ifndef LIBCOMMON_WIRETAPWITHEARPLUGS_HPP
#define LIBCOMMON_WIRETAPWITHEARPLUGS_HPP

#include <Gadget.hpp>
#include <util/UUID.hpp>
#include <optional>

namespace spy::gadget {
    class WiretapWithEarplugs : public Gadget {
    public:
        WiretapWithEarplugs() : Gadget{GadgetEnum::WIRETAP_WITH_EARPLUGS}, working{true}, activeOn{std::nullopt} {};

        [[nodiscard]] bool isWorking() const {
            return working;
        }

        void setWorking(bool isWorking) {
            WiretapWithEarplugs::working = isWorking;
        }

        [[nodiscard]] const std::optional<spy::util::UUID> &getActiveOn() const {
            return activeOn;
        }

        void setActiveOn(const std::optional<spy::util::UUID> &active) {
            WiretapWithEarplugs::activeOn = active;
        }

    private:
        bool working;
        std::optional<spy::util::UUID> activeOn;
    };
}

#endif //LIBCOMMON_WIRETAPWITHEARPLUGS_HPP
