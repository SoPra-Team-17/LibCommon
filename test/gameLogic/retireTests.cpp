//
// Created by Carolin on 02.05.2020.
//

#include <gtest/gtest.h>
#include <gameLogic/validation/ActionValidator.hpp>
#include <gameLogic/execution/ActionExecutor.hpp>

TEST(Retire, validate) {
    spy::gameplay::RetireAction retire;
    EXPECT_TRUE(spy::gameplay::ActionValidator::validate({}, std::make_shared<const spy::gameplay::RetireAction>(retire), {}));
}

TEST(Retire, execute) {
    spy::gameplay::RetireAction retire (spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"});
    spy::character::Character c {spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"}, "someName"};
    c.setActionPoints(5);
    c.setMovePoints(5);
    spy::gameplay::State s ({}, {}, {}, {c}, {}, {});
    EXPECT_TRUE(spy::gameplay::ActionExecutor::execute(s, std::make_shared<const spy::gameplay::RetireAction>(retire), {}));
    EXPECT_EQ(s.getCharacters().getByUUID(spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"})->getMovePoints(), 0);
    EXPECT_EQ(s.getCharacters().getByUUID(spy::util::UUID{"123e4567-e89b-12d3-a456-426655440000"})->getActionPoints(), 0);
}