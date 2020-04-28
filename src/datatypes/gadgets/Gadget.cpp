//
// Created by jonas on 02.04.20.
//

#include "Gadget.hpp"

namespace spy::gadget {

    Gadget::Gadget(GadgetEnum type, int usagesLeft) : type(type), usagesLeft(usagesLeft) {}

    GadgetEnum Gadget::getType() const {
        return type;
    }

    std::optional<unsigned int> Gadget::getUsagesLeft() const {
        return usagesLeft;
    }

    void Gadget::setUsagesLeft(std::optional<unsigned int> newUsages) {
        Gadget::usagesLeft = newUsages;
    }

    void to_json(nlohmann::json &j, const spy::gadget::Gadget &g) {
        j["GadgetEnum"] = g.type;
        j["usages"] = g.usagesLeft;
    }

    void from_json(const nlohmann::json &j, spy::gadget::Gadget &g) {
        j.at("GadgetEnum").get_to(g.type);
        j.at("usages").get_to(g.usagesLeft);
    }

    bool Gadget::operator==(const Gadget &rhs) const {
        return std::tie(type, usagesLeft) == std::tie(rhs.type, rhs.usagesLeft);
    }
}  // namespace spy::gadget
