//
// Created by jonas on 29.04.20.
//

#include "OperationJson.hpp"
#include "GadgetAction.hpp"
#include "SpyAction.hpp"
#include "GambleAction.hpp"
#include "PropertyAction.hpp"
#include "JanitorAction.hpp"
#include "CatAction.hpp"
#include "Movement.hpp"
#include "Exfiltration.hpp"
#include "RetireAction.hpp"

namespace spy::gameplay {
    std::shared_ptr<BaseOperation> OperationJson::fromJson(const nlohmann::json &j) {
        OperationEnum opType;
        j.at("type").get_to(opType);

        switch (opType) {
            case OperationEnum::GADGET_ACTION: {
                auto a = std::make_shared<GadgetAction>();
                j.get_to(*a);
                return a;
            }
            case OperationEnum::SPY_ACTION: {
                auto a = std::make_shared<SpyAction>();
                j.get_to(*a);
                return a;
            }
            case OperationEnum::GAMBLE_ACTION: {
                auto a = std::make_shared<GambleAction>();
                j.get_to(*a);
                return a;
            }
            case OperationEnum::PROPERTY_ACTION: {
                auto a = std::make_shared<PropertyAction>();
                j.get_to(*a);
                return a;
            }
            case OperationEnum::MOVEMENT: {
                auto a = std::make_shared<Movement>();
                j.get_to(*a);
                return a;
            }
            case OperationEnum::CAT_ACTION: {
                auto a = std::make_shared<CatAction>();
                j.get_to(*a);
                return a;
            }
            case OperationEnum::JANITOR_ACTION: {
                auto a = std::make_shared<JanitorAction>();
                j.get_to(*a);
                return a;
            }
            case OperationEnum::EXFILTRATION: {
                auto a = std::make_shared<Exfiltration>();
                j.get_to(*a);
                return a;
            }
            case OperationEnum::RETIRE: {
                auto a = std::make_shared<RetireAction>();
                j.get_to(*a);
                return a;
            }
            case OperationEnum::INVALID:
                throw std::invalid_argument("Operation type not valid");

        }
        return nullptr;
    }

    nlohmann::json OperationJson::toJson(std::shared_ptr<const BaseOperation> op) {
        nlohmann::json j;
        switch (op->getType()) {
            case OperationEnum::GADGET_ACTION: {
                j = *std::dynamic_pointer_cast<const GadgetAction>(op);
                break;
            }
            case OperationEnum::SPY_ACTION: {
                j = *std::dynamic_pointer_cast<const SpyAction>(op);
                break;
            }
            case OperationEnum::GAMBLE_ACTION: {
                j = *std::dynamic_pointer_cast<const GambleAction>(op);
                break;
            }
            case OperationEnum::PROPERTY_ACTION: {
                j = *std::dynamic_pointer_cast<const PropertyAction>(op);
                break;
            }
            case OperationEnum::MOVEMENT: {
                auto mp = std::dynamic_pointer_cast<const Movement>(op);
                auto m = *mp;
                j = m;
                break;
            }
            case OperationEnum::CAT_ACTION: {
                j = *std::dynamic_pointer_cast<const CatAction>(op);
                break;
            }
            case OperationEnum::JANITOR_ACTION: {
                j = *std::dynamic_pointer_cast<const JanitorAction>(op);
                break;
            }
            case OperationEnum::EXFILTRATION: {
                j = *std::dynamic_pointer_cast<const Exfiltration>(op);
                break;
            }
            case OperationEnum::RETIRE: {
                j = *std::dynamic_pointer_cast<const RetireAction>(op);
                break;
            }
            case OperationEnum::INVALID:
                throw std::invalid_argument("Operation type not valid");
        }

        return j;
    }
}