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

    private:
        bool working;
        std::optional<spy::util::UUID> activeOn;
    };
}

#endif //LIBCOMMON_WIRETAPWITHEARPLUGS_HPP
