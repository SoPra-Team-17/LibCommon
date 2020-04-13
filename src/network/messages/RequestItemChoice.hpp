//
// Created by marco on 10.04.20.
//

#ifndef LIBCOMMON_REQUESTITEMCHOICE_HPP
#define LIBCOMMON_REQUESTITEMCHOICE_HPP

#include <network/MessageContainer.hpp>
#include <datatypes/gadgets/GadgetEnum.hpp>

namespace spy::network::messages {

    class RequestItemChoice : public MessageContainer {

        public:

            RequestItemChoice();

            explicit RequestItemChoice(const util::UUID &playerId,
                                       std::vector<util::UUID> offeredCharacterIds,
                                       std::vector<spy::gadget::GadgetEnum> offeredGadgets);

            friend void to_json(nlohmann::json &j, const RequestItemChoice &r);

            friend void from_json(const nlohmann::json &j, RequestItemChoice &r);

            [[nodiscard]] auto getOfferedCharacterIds() const -> const std::vector<util::UUID> &;

            [[nodiscard]] auto getOfferedGadgets() const -> const std::vector<spy::gadget::GadgetEnum> &;

        private:
            std::vector<util::UUID> offeredCharacterIds;
            std::vector<spy::gadget::GadgetEnum> offeredGadgets;
    };
}

#endif //LIBCOMMON_REQUESTITEMCHOICE_HPP
