/**
 * @file   Operation.hpp
 * @author Jonas
 * @brief  Generic gameplay operation
 */

#ifndef LIBCOMMON_OPERATION_HPP
#define LIBCOMMON_OPERATION_HPP


#include <datatypes/gameplay/OperationEnum.hpp>
#include <util/Point.hpp>
#include <util/UUID.hpp>
#include <util/OptionalSerialization.hpp>
#include "BaseOperation.hpp"

namespace spy::gameplay {
    class Operation : public BaseOperation {
        public:

            Operation() = default;

            Operation(OperationEnum type, bool successful, const util::Point &target);

            Operation(OperationEnum type, bool successful, const util::Point &target, util::UUID characterId);

            [[nodiscard]] const std::optional<util::UUID> &getCharacterId() const;

            bool operator==(const Operation &rhs) const;

            bool operator!=(const Operation &rhs) const;

            static void common_to_json(nlohmann::json &j, const Operation &op);

            static void common_from_json(const nlohmann::json &j, Operation &op);

            friend void to_json(nlohmann::json &j, const Operation &o);

            friend void from_json(const nlohmann::json &j, Operation &o);

        private:
            std::optional<util::UUID> characterId;
    };
}

#endif //LIBCOMMON_OPERATION_HPP
