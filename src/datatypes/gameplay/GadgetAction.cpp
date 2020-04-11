//
// Created by jonas on 10.04.20.
//

#include "GadgetAction.hpp"

namespace spy::gameplay {

    GadgetAction::GadgetAction(bool successful, const util::Point &target, const util::UUID &characterId,
                               gadget::GadgetEnum gadget) :
            Operation(OperationEnum::GADGET_ACTION, successful, target, characterId),
            gadget(gadget) {}

    gadget::GadgetEnum GadgetAction::getGadget() const {
        return gadget;
    }

    void to_json(nlohmann::json &j, const GadgetAction &g) {
        Operation::common_to_json(j, g);
        j["gadget"] = g.gadget;
    }

    void from_json(const nlohmann::json &j, GadgetAction &g) {
        Operation::common_from_json(j, g);
        j.at("gadget").get_to(g.gadget);
    }

    bool GadgetAction::operator==(const GadgetAction &rhs) const {
        return std::tie(static_cast<const spy::gameplay::Operation &>(*this), gadget) ==
               std::tie(static_cast<const spy::gameplay::Operation &>(rhs), rhs.gadget);
    }

    bool GadgetAction::operator!=(const GadgetAction &rhs) const {
        return !(rhs == *this);
    }
}