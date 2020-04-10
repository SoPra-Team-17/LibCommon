//
// Created by jonas on 10.04.20.
//

#ifndef LIBCOMMON_OPERATION_HPP
#define LIBCOMMON_OPERATION_HPP

#include <datatypes/gameplay/OperationEnum.hpp>
#include <util/Point.hpp>
#include <util/UUID.hpp>
#include <util/OptionalSerialization.hpp>

namespace spy::gameplay {
    class Operation {
        public:

            Operation() = default;

            Operation(OperationEnum type, bool successful, const util::Point &target);

            Operation(OperationEnum type, bool successful, const util::Point &target, util::UUID characterId);

            [[nodiscard]] OperationEnum getType() const;

            [[nodiscard]] bool isSuccessful() const;

            [[nodiscard]] const util::Point &getTarget() const;

            [[nodiscard]] const std::optional<util::UUID> &getCharacterId() const;

            bool operator==(const Operation &rhs) const;

            bool operator!=(const Operation &rhs) const;

            static void common_to_json(nlohmann::json &j, const Operation &op);

            static void common_from_json(const nlohmann::json &j, Operation &op);

        private:
            OperationEnum type = OperationEnum::INVALID;
            bool successful;
            util::Point target;
            std::optional<util::UUID> characterId;
    };
}

#endif //LIBCOMMON_OPERATION_HPP
