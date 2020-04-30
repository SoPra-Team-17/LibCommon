/**
 * @file OperationSerialization.hpp
 * @author Jonas
 * @date 10.04.2020
 * @brief Adds serialization and deserialization for std::optional<T> if T is serializable
 */

#ifndef LIBCOMMON_OPERATIONSERIALIZATION_HPP
#define LIBCOMMON_OPERATIONSERIALIZATION_HPP

#include <nlohmann/json.hpp>
#include <datatypes/gameplay/GadgetAction.hpp>
#include <datatypes/gameplay/SpyAction.hpp>
#include <datatypes/gameplay/GambleAction.hpp>
#include <datatypes/gameplay/PropertyAction.hpp>
#include <datatypes/gameplay/CatAction.hpp>
#include <datatypes/gameplay/JanitorAction.hpp>
#include <datatypes/gameplay/Exfiltration.hpp>
#include <datatypes/gameplay/RetireAction.hpp>
#include <datatypes/gameplay/Movement.hpp>


namespace nlohmann {
    template<>
    struct adl_serializer<std::shared_ptr<spy::gameplay::BaseOperation>> {
        static void to_json(json &j, const std::shared_ptr<spy::gameplay::BaseOperation> &op) {
            using namespace spy::gameplay;
            switch (op->getType()) {
                case OperationEnum::GADGET_ACTION:
                    j = *std::dynamic_pointer_cast<const GadgetAction>(op);
                    break;

                case OperationEnum::SPY_ACTION:
                    j = *std::dynamic_pointer_cast<const SpyAction>(op);
                    break;

                case OperationEnum::GAMBLE_ACTION:
                    j = *std::dynamic_pointer_cast<const GambleAction>(op);
                    break;

                case OperationEnum::PROPERTY_ACTION:
                    j = *std::dynamic_pointer_cast<const PropertyAction>(op);
                    break;

                case OperationEnum::MOVEMENT:
                    j = *std::dynamic_pointer_cast<const Movement>(op);
                    break;

                case OperationEnum::CAT_ACTION:
                    j = *std::dynamic_pointer_cast<const CatAction>(op);
                    break;

                case OperationEnum::JANITOR_ACTION:
                    j = *std::dynamic_pointer_cast<const JanitorAction>(op);
                    break;

                case OperationEnum::EXFILTRATION:
                    j = *std::dynamic_pointer_cast<const Exfiltration>(op);
                    break;

                case OperationEnum::RETIRE:
                    j = *std::dynamic_pointer_cast<const RetireAction>(op);
                    break;

                case OperationEnum::INVALID:
                    throw std::invalid_argument("Operation type not valid");
            }
        }

        static void from_json(const json &j, std::shared_ptr<spy::gameplay::BaseOperation> &opt) {
            using namespace spy::gameplay;

            OperationEnum opType;
            j.at("type").get_to(opType);

            switch (opType) {
                case OperationEnum::GADGET_ACTION:
                    opt = std::make_shared<GadgetAction>();
                    *std::static_pointer_cast<GadgetAction>(opt) = j.get<GadgetAction>();
                    break;
                case OperationEnum::SPY_ACTION:
                    opt = std::make_shared<SpyAction>();
                    *std::static_pointer_cast<SpyAction>(opt) = j.get<SpyAction>();
                    break;
                case OperationEnum::GAMBLE_ACTION:
                    opt = std::make_shared<GambleAction>();
                    *std::static_pointer_cast<GambleAction>(opt) = j.get<GambleAction>();
                    break;
                case OperationEnum::PROPERTY_ACTION:
                    opt = std::make_shared<PropertyAction>();
                    *std::static_pointer_cast<PropertyAction>(opt) = j.get<PropertyAction>();
                    break;
                case OperationEnum::MOVEMENT:
                    opt = std::make_shared<Movement>();
                    *std::static_pointer_cast<Movement>(opt) = j.get<Movement>();
                    break;
                case OperationEnum::CAT_ACTION:
                    opt = std::make_shared<CatAction>();
                    *std::static_pointer_cast<CatAction>(opt) = j.get<CatAction>();
                    break;
                case OperationEnum::JANITOR_ACTION:
                    opt = std::make_shared<JanitorAction>();
                    *std::static_pointer_cast<JanitorAction>(opt) = j.get<JanitorAction>();
                    break;
                case OperationEnum::EXFILTRATION:
                    opt = std::make_shared<Exfiltration>();
                    *std::static_pointer_cast<Exfiltration>(opt) = j.get<Exfiltration>();
                    break;
                case OperationEnum::RETIRE:
                    opt = std::make_shared<RetireAction>();
                    *std::static_pointer_cast<RetireAction>(opt) = j.get<RetireAction>();
                    break;
                case OperationEnum::INVALID:
                    throw std::invalid_argument("Operation type not valid");

            }
        }
    };
}

#endif //LIBCOMMON_OPERATIONSERIALIZATION_HPP
