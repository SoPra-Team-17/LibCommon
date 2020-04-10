//
// Created by jonas on 10.04.20.
//

#ifndef LIBCOMMON_GADGETACTION_HPP
#define LIBCOMMON_GADGETACTION_HPP

#include "Operation.hpp"
#include <datatypes/gadgets/GadgetEnum.hpp>

namespace spy::gameplay {
    class GadgetAction : Operation {
        public:
            GadgetAction() = default;

            GadgetAction(bool successful, const util::Point &target, const util::UUID &characterId,
                         gadget::GadgetEnum gadget);

            [[nodiscard]] gadget::GadgetEnum getGadget() const;

            bool operator==(const GadgetAction &rhs) const;

            bool operator!=(const GadgetAction &rhs) const;

            friend void to_json(nlohmann::json &j, const GadgetAction &g);

            friend void from_json(const nlohmann::json &j, GadgetAction &g);

        private:
            gadget::GadgetEnum gadget = gadget::GadgetEnum::INVALID;
    };
}

#endif //LIBCOMMON_GADGETACTION_HPP
