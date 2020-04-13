//
// Created by marco on 10.04.20.
//

#include "RequestItemChoice.hpp"

#include <utility>

namespace spy::network::messages {

    RequestItemChoice::RequestItemChoice() : MessageContainer{MessageTypeEnum::REQUEST_ITEM_CHOICE, {}} {}

    RequestItemChoice::RequestItemChoice(const util::UUID &playerId,
                                         std::vector<util::UUID> offeredCharacterIds,
                                         std::vector<spy::gadget::GadgetEnum> offeredGadgets) :
            MessageContainer{MessageTypeEnum::REQUEST_ITEM_CHOICE, playerId},
            offeredCharacterIds{std::move(offeredCharacterIds)},
            offeredGadgets{std::move(offeredGadgets)} {}

    void to_json(nlohmann::json &j, const RequestItemChoice &r) {
        MessageContainer::common_to_json(j, r);
        j["offeredCharacterIds"] = r.offeredCharacterIds;
        j["offeredGadgets"] = r.offeredGadgets;
    }

    void from_json(const nlohmann::json &j, RequestItemChoice &r) {
        MessageContainer::common_from_json(j, r);
        j.at("offeredCharacterIds").get_to(r.offeredCharacterIds);
        j.at("offeredGadgets").get_to(r.offeredGadgets);
    }

    auto RequestItemChoice::getOfferedCharacterIds() const -> const std::vector<util::UUID> & {
        return offeredCharacterIds;
    }

    auto RequestItemChoice::getOfferedGadgets() const -> const std::vector<spy::gadget::GadgetEnum> & {
        return offeredGadgets;
    }

    bool RequestItemChoice::operator==(const RequestItemChoice &rhs) const {
        return isEqual(rhs) &&
               offeredCharacterIds == rhs.offeredCharacterIds &&
               offeredGadgets == rhs.offeredGadgets;
    }
}

