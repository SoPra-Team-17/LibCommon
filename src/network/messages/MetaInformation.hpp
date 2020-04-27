//
// Created by jonas on 12.04.20.
//

#ifndef LIBCOMMON_METAINFORMATION_HPP
#define LIBCOMMON_METAINFORMATION_HPP

#include <network/MessageContainer.hpp>
#include <map>
#include <optional>
#include <variant>
#include <datatypes/scenario/Scenario.hpp>
#include <datatypes/matchconfig/MatchConfig.hpp>
#include <datatypes/character/CharacterInformation.hpp>
#include <util/VariantSerialization.hpp>
#include "MetaInformationKey.hpp"

namespace spy::network::messages {
    class MetaInformation : public MessageContainer {
        public:
            using Info = std::variant<
                    int,
                    std::vector<std::string>,
                    scenario::Scenario,
                    MatchConfig,
                    std::vector<character::CharacterInformation>,
                    std::vector<util::UUID>,
                    std::vector<gadget::GadgetEnum>>;

            MetaInformation();

            MetaInformation(const util::UUID &playerId,
                            std::map<MetaInformationKey, Info> information);

            friend void to_json(nlohmann::json &j, const MetaInformation &m);

            friend void from_json(const nlohmann::json &j, MetaInformation &m);

            [[nodiscard]] const std::map<MetaInformationKey, Info> &getInformation() const;

            bool operator==(const MetaInformation &rhs) const;

            friend std::ostream &operator<<(std::ostream &os, const MetaInformation &metaInformation);

        private:
            std::map<MetaInformationKey, Info> information;
    };
}

#endif //LIBCOMMON_METAINFORMATION_HPP
