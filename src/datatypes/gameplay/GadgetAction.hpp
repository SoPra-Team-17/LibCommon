/**
 * @file   GadgetAction.hpp
 * @author Jonas
 * @brief  GadgetAction operation
 */

#ifndef LIBCOMMON_GADGETACTION_HPP
#define LIBCOMMON_GADGETACTION_HPP

#include "CharacterOperation.hpp"
#include <datatypes/gadgets/GadgetEnum.hpp>

namespace spy::gameplay {
    class GadgetAction : public CharacterOperation {
        public:
            GadgetAction() = default;

            GadgetAction(bool successful, const util::Point &target, const util::UUID &characterId,
                         gadget::GadgetEnum gadget);

            [[nodiscard]] gadget::GadgetEnum getGadget() const;

            friend void to_json(nlohmann::json &j, const GadgetAction &g);

            friend void from_json(const nlohmann::json &j, GadgetAction &g);

        private:
            gadget::GadgetEnum gadget = gadget::GadgetEnum::INVALID;

            bool isEqual(const BaseOperation &rhs) const override;
    };
}

#endif //LIBCOMMON_GADGETACTION_HPP
