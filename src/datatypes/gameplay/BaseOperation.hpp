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

            bool operator==(const BaseOperation &rhs) const;

            bool operator!=(const BaseOperation &rhs) const;

        protected:
            BaseOperation() = default;

            BaseOperation(OperationEnum type, bool successful, const util::Point &target);

            bool isBaseEqual(const BaseOperation &rhs) const;

        private:

            OperationEnum type = OperationEnum::INVALID;
            bool successful = false;
            util::Point target;

            /**
             * This method shall be overridden by deriving classes to perform equality check.
             * The deriving class can assume that the parameter rhs is of the same type as the class.
             * This method shall only be called from BaseOperation::operator==.
             */
            [[nodiscard]] virtual bool isEqual(const BaseOperation &rhs) const = 0;
    };
}


#endif //LIBCOMMON_BASEOPERATION_HPP
