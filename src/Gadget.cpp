//
// Created by jonas on 02.04.20.
//

#include "Gadget.hpp"

void spy::gadget::to_json(nlohmann::json &j, const spy::gadget::Gadget &g) {
    j["GadgetEnum"] = g.type;
    j["usages"] = g.usagesLeft;
}

void spy::gadget::from_json(const nlohmann::json &j, spy::gadget::Gadget &g) {
    j.at("GadgetEnum").get_to(g.type);
    j.at("usages").get_to(g.usagesLeft);
}