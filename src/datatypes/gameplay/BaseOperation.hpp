//
// Created by Carolin on 29.04.2020.
//

#ifndef LIBCOMMON_BASEOPERATION_HPP
#define LIBCOMMON_BASEOPERATION_HPP

#include <util/Point.hpp>
#include <util/UUID.hpp>
#include <iostream>
#include "OperationEnum.hpp"

namespace spy::gameplay {
    class BaseOperation {
        public:
            [[nodiscard]] OperationEnum getType() const;

            [[nodiscard]] bool isSuccessful() const;

            [[nodiscard]] const util::Point &getTarget() const;

            static void common_to_json(nlohmann::json &j, const BaseOperation &op);

            static void common_from_json(const nlohmann::json &j, BaseOperation &op);

            virtual ~BaseOperation() = default;

            virtual bool operator==(const BaseOperation &rhs);

        protected:
            BaseOperation() = default;

            BaseOperation(OperationEnum type, bool successful, const util::Point &target);

            OperationEnum type = OperationEnum::INVALID;
            bool successful = false;
            util::Point target;
    };
}


#endif //LIBCOMMON_BASEOPERATION_HPP
