//
// Created by jonas on 28.04.20.
//

#include <gtest/gtest.h>
#include <datatypes/gameplay/State.hpp>
#include <datatypes/gameplay/GadgetAction.hpp>
#include <datatypes/execution/ActionExecutor.hpp>

class GadgetTest : public ::testing::Test {
    public:
        GadgetTest() {
            state.getCharacters().getByUUID(u1)->setCoordinates({1, 2});
            state.getCharacters().getByUUID(u2)->setCoordinates({2, 2});
        }

    protected:
        spy::util::UUID u1 = spy::util::UUID::generate();
        spy::util::UUID u2 = spy::util::UUID::generate();

        nlohmann::json input = R"({ "scenario": [
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"],
            ["WALL", "FIREPLACE", "WALL", "BAR_TABLE",      "BAR_SEAT", "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_TABLE", "WALL", "ROULETTE_TABLE", "FREE",     "FREE", "WALL"],
            ["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE",     "FREE", "WALL"],
            ["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE", "WALL"],
            ["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
            ]})"_json;

        spy::scenario::Scenario decodedScenario = input.get<spy::scenario::Scenario>();

        spy::scenario::FieldMap field{decodedScenario};

        spy::gameplay::State state{0, field, {}, {{u1, "dummy"}, {u2, "dummy"}}, std::nullopt, std::nullopt};
};


TEST_F(GadgetTest, HairDryer_Execute) {

    using spy::character::PropertyEnum;
    auto c1 = state.getCharacters().getByUUID(u1);
    auto c2 = state.getCharacters().getByUUID(u2);

    c2->setProperties({PropertyEnum::CLAMMY_CLOTHES});
    ASSERT_TRUE(c2->getProperties().find(PropertyEnum::CLAMMY_CLOTHES) != c2->getProperties().end());

    spy::gameplay::GadgetAction a{false, c2->getCoordinates().value(), u1, spy::gadget::GadgetEnum::HAIRDRYER};
    spy::gameplay::ActionExecutor::execute(state, std::make_shared<spy::gameplay::GadgetAction>(a));

    // Expect CLAMMY_CLOTHES to be removed from character 2
    EXPECT_TRUE(c2->getProperties().find(PropertyEnum::CLAMMY_CLOTHES) == c2->getProperties().end());
}