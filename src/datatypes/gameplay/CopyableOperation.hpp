//
// Created by jonas on 07.05.20.
//

#ifndef LIBCOMMON_COPYABLEOPERATION_HPP
#define LIBCOMMON_COPYABLEOPERATION_HPP

#include "BaseOperation.hpp"

namespace spy::gameplay {
    template<typename Derived>
    class CopyableOperation : public BaseOperation {
        public:
            [[nodiscard]] std::shared_ptr<BaseOperation> clone() const override {
                return std::make_shared<Derived>(static_cast<const Derived &>(*this));
            }
    };
}

#endif //LIBCOMMON_COPYABLEOPERATION_HPP
