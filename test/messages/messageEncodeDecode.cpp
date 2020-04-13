/**
 * @author Jonas
 * @brief Tests message encoding/decoding consistency
 */

#include <gtest/gtest.h>
#include <network/messages/EquipmentChoice.hpp>
#include <network/messages/Error.hpp>
#include <network/messages/GameLeft.hpp>
#include <network/messages/GameLeave.hpp>
#include <network/messages/GameOperation.hpp>
#include <network/messages/GamePause.hpp>
#include <network/messages/GameStarted.hpp>
#include <network/messages/GameStatus.hpp>
#include <network/messages/Hello.hpp>
#include <network/messages/HelloReply.hpp>
#include <network/messages/ItemChoice.hpp>
#include <network/messages/Reconnect.hpp>
#include <network/messages/RequestEquipmentChoice.hpp>
#include <network/messages/RequestGameOperation.hpp>
#include <network/messages/RequestGamePause.hpp>
#include <network/messages/RequestItemChoice.hpp>
#include <network/messages/RequestMetaInformation.hpp>
#include <network/messages/RequestReplay.hpp>
#include <network/messages/StatisticsMessage.hpp>
#include <network/messages/Strike.hpp>
#include <network/messages/MetaInformation.hpp>

nlohmann::json exampleScenarioJson = R"({ "scenario": [
		["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"],
		["WALL", "FIREPLACE", "WALL", "BAR_TABLE",      "BAR_SEAT", "FREE", "WALL"],
		["WALL", "FREE",      "FREE", "FREE",           "FREE",     "FREE", "WALL"],
		["WALL", "BAR_TABLE", "FREE", "ROULETTE_TABLE", "FREE",     "FREE", "WALL"],
		["WALL", "BAR_SEAT",  "FREE", "WALL",           "FREE",     "FREE", "WALL"],
		["WALL", "FREE",      "FREE", "FREE",           "FREE",     "SAFE", "WALL"],
		["WALL", "WALL",      "WALL", "WALL",           "WALL",     "WALL", "WALL"]
	    ]})"_json;

class MessageEncodeDecode : public ::testing::Test {
    protected:
        spy::util::UUID exampleUUID1 = spy::util::UUID{"6a1333d0-2317-4044-9d37-047d29205011"};
        spy::util::UUID exampleUUID2 = spy::util::UUID{"6a1333d1-2318-5044-9d37-047d29205012"};
        spy::gameplay::Operation exampleOperation = {spy::gameplay::OperationEnum::MOVEMENT, true, {3, 3},
                                                     exampleUUID2};
        spy::scenario::Scenario exampleScenario = exampleScenarioJson.get<spy::scenario::Scenario>();
        spy::scenario::FieldMap exampleMap = spy::scenario::FieldMap{exampleScenario};
        spy::character::Character char1 = {exampleUUID1, "TestChar1"};
        spy::character::Character char2 = {exampleUUID2, "TestChar2"};
        spy::gameplay::State exampleState = {7, exampleMap, {1337, 420}, {char1, char2}, spy::util::Point{1, 2},
                                             spy::util::Point{5, 1}};
};


template<typename MessageType>
void testEncodeDecode(const MessageType &message) {
    // Prevent this from using MessageContainer, which would result in testing the container only.
    static_assert(!std::is_same<MessageType, spy::network::MessageContainer>::value,
                  "This should test specific messages, not MessageContainer.");

    nlohmann::json jsonMessage = message;
    std::string encodedMessage = jsonMessage.dump();
    nlohmann::json parsedJson = nlohmann::json::parse(encodedMessage);
    auto genericMessage = parsedJson.get<spy::network::MessageContainer>();
    ASSERT_EQ(genericMessage.getType(), message.getType());

    auto decodedMessage = parsedJson.get<MessageType>();
    EXPECT_EQ(message, decodedMessage);
}

TEST_F(MessageEncodeDecode, EquipmentChoice) {
    using namespace spy::gadget;
    std::set<GadgetEnum> chosenGadgets1 = {GadgetEnum::HAIRDRYER, GadgetEnum::JETPACK};
    std::set<GadgetEnum> chosenGadgets2 = {GadgetEnum::POISON_PILLS, GadgetEnum::FOG_TIN, GadgetEnum::LASER_COMPACT};
    spy::network::messages::EquipmentChoice testMessage{exampleUUID1, {{exampleUUID1, chosenGadgets1},
                                                                       {exampleUUID2, chosenGadgets2}}};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, Error) {
    spy::network::messages::Error testMessage{exampleUUID1, spy::network::ErrorTypeEnum::TOO_MANY_STRIKES};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, GameLeave) {
    spy::network::messages::GameLeave testMessage{exampleUUID1};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, GameLeft) {
    spy::network::messages::GameLeft testMessage{exampleUUID1, exampleUUID2};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, GameOperation) {
    spy::network::messages::GameOperation testMessage{exampleUUID1, exampleOperation};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, GamePause) {
    spy::network::messages::GamePause testMessage{exampleUUID1, true, false};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, GameStarted) {
    spy::network::messages::GameStarted testMessage{exampleUUID1, exampleUUID2, exampleUUID1, "P1", "P2", exampleUUID2};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, GameStatus) {
    spy::network::messages::GameStatus testMessage{exampleUUID1, exampleUUID2, {exampleOperation, exampleOperation},
                                                   exampleState, false};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, Hello) {
    spy::network::messages::Hello testMessage{exampleUUID1, "Name", spy::network::RoleEnum::PLAYER};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, HelloReply) {
    spy::network::messages::HelloReply testMessage{exampleUUID1, exampleUUID2, {}, {}, {{}}};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, ItemChoice) {
    spy::network::messages::ItemChoice testMessage{exampleUUID1, exampleUUID2};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, ItemChoice_Gadget) {
    spy::network::messages::ItemChoice testMessage{exampleUUID1, spy::gadget::GadgetEnum::HAIRDRYER};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, Reconnect) {
    spy::network::messages::Reconnect testMessage{exampleUUID1, exampleUUID2};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, RequestEquipmentChoice) {
    spy::network::messages::RequestEquipmentChoice testMessage{exampleUUID1, {exampleUUID1, exampleUUID2},
                                                               {spy::gadget::GadgetEnum::LASER_COMPACT,
                                                                spy::gadget::GadgetEnum::FOG_TIN}};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, RequestGameOperation) {
    spy::network::messages::RequestGameOperation testMessage{exampleUUID1, exampleUUID2};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, RequestGamePause) {
    spy::network::messages::RequestGamePause testMessage{exampleUUID1, true};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, RequestItemChoice) {
    spy::network::messages::RequestItemChoice testMessage{exampleUUID1, {exampleUUID1, exampleUUID2},
                                                          {spy::gadget::GadgetEnum::LASER_COMPACT,
                                                           spy::gadget::GadgetEnum::FOG_TIN}};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, RequestMetaInformation) {
    spy::network::messages::RequestMetaInformation testMessage{exampleUUID1, {"key1", "key2"}};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, RequestReplay) {
    spy::network::messages::RequestReplay testMessage{exampleUUID1};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, StatisticsMessage) {
    spy::network::messages::StatisticsMessage testMessage{exampleUUID1,
                                                          spy::statistics::Statistics{{{"Cocktails", "Who drank the most?", "17", "3"}}},
                                                          exampleUUID1,
                                                          spy::statistics::VictoryEnum::VICTORY_BY_DRINKING, false};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, Strike) {
    spy::network::messages::Strike testMessage{exampleUUID1, 7, 8, "Stealing cocktails from players"};
    testEncodeDecode(testMessage);
}

TEST_F(MessageEncodeDecode, MetaInformation) {
    using namespace spy::network::messages;

    MetaInformation testMessage{exampleUUID1, {{"Spectator.Count", 1},
                                               {"Spectator.Members", std::vector<std::string>{"Jonas"}},
                                               {"Configuration.Scenario", spy::scenario::Scenario{}},
                                               {"Configuration.Matchconfig", spy::MatchConfig{}},
                                               {"Configuration.CharacterInformation",
                                                std::vector<spy::character::CharacterInformation>{}},
                                               {"Game.RemainingPauseTime", 7},
                                               {"Faction.Player1",
                                                std::vector<spy::util::UUID>{exampleUUID1, exampleUUID2}},
                                               {"Faction.Player2",
                                                std::vector<spy::util::UUID>{exampleUUID1, exampleUUID2}},
                                               {"Faction.Neutral",
                                                std::vector<spy::util::UUID>{exampleUUID1, exampleUUID2}},
                                               {"Gadgets.Player1",
                                                std::vector<spy::gadget::GadgetEnum>{
                                                        spy::gadget::GadgetEnum::POISON_PILLS,
                                                        spy::gadget::GadgetEnum::HAIRDRYER}},
                                               {"Gadgets.Player2",
                                                std::vector<spy::gadget::GadgetEnum>{
                                                        spy::gadget::GadgetEnum::POISON_PILLS,
                                                        spy::gadget::GadgetEnum::HAIRDRYER}}}};
    testEncodeDecode(testMessage);
}