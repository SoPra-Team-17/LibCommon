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

auto exampleUUID1 = spy::util::UUID{"6a1333d0-2317-4044-9d37-047d29205011"};
auto exampleUUID2 = spy::util::UUID{"6a1333d1-2318-5044-9d37-047d29205012"};
auto exampleOperation = spy::gameplay::Operation{spy::gameplay::OperationEnum::MOVEMENT, true, {3, 3}, exampleUUID2};
auto exampleState = spy::gameplay::State{};


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

TEST(MessageEncodeDecode, EquipmentChoice) {
    using namespace spy::gadget;
    std::set<GadgetEnum> chosenGadgets1 = {GadgetEnum::HAIRDRYER, GadgetEnum::JETPACK};
    std::set<GadgetEnum> chosenGadgets2 = {GadgetEnum::POISON_PILLS, GadgetEnum::FOG_TIN, GadgetEnum::LASER_COMPACT};
    spy::network::messages::EquipmentChoice testMessage{exampleUUID1, {{exampleUUID1, chosenGadgets1},
                                                                       {exampleUUID2, chosenGadgets2}}};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, Error) {
    spy::network::messages::Error testMessage{exampleUUID1, spy::network::ErrorTypeEnum::TOO_MANY_STRIKES};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, GameLeave) {
    spy::network::messages::GameLeave testMessage{exampleUUID1};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, GameLeft) {
    spy::network::messages::GameLeft testMessage{exampleUUID1, exampleUUID2};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, GameOperation) {
    spy::network::messages::GameOperation testMessage{exampleUUID1, exampleOperation};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, GamePause) {
    spy::network::messages::GamePause testMessage{exampleUUID1, true, false};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, GameStarted) {
    spy::network::messages::GameStarted testMessage{exampleUUID1, exampleUUID2, exampleUUID1, "P1", "P2", exampleUUID2};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, GameStatus) {
    spy::network::messages::GameStatus testMessage{exampleUUID1, exampleUUID2, {exampleOperation, exampleOperation},
                                                   exampleState, false};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, Hello) {
    spy::network::messages::Hello testMessage{exampleUUID1, "Name", spy::network::RoleEnum::PLAYER};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, HelloReply) {
    spy::network::messages::HelloReply testMessage{exampleUUID1, exampleUUID2, {}, {}, {{}}};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, ItemChoice) {
    spy::network::messages::ItemChoice testMessage{exampleUUID1, exampleUUID2};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, ItemChoice_Gadget) {
    spy::network::messages::ItemChoice testMessage{exampleUUID1, spy::gadget::GadgetEnum::HAIRDRYER};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, Reconnect) {
    spy::network::messages::Reconnect testMessage{exampleUUID1, exampleUUID2};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, RequestEquipmentChoice) {
    spy::network::messages::RequestEquipmentChoice testMessage{exampleUUID1, {exampleUUID1, exampleUUID2},
                                                               {spy::gadget::GadgetEnum::LASER_COMPACT,
                                                                spy::gadget::GadgetEnum::FOG_TIN}};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, RequestGameOperation) {
    spy::network::messages::RequestGameOperation testMessage{exampleUUID1, exampleUUID2};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, RequestGamePause) {
    spy::network::messages::RequestGamePause testMessage{exampleUUID1, true};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, RequestItemChoice) {
    spy::network::messages::RequestItemChoice testMessage{exampleUUID1, {exampleUUID1, exampleUUID2},
                                                          {spy::gadget::GadgetEnum::LASER_COMPACT,
                                                           spy::gadget::GadgetEnum::FOG_TIN}};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, RequestMetaInformation) {
    spy::network::messages::RequestMetaInformation testMessage{exampleUUID1, {"key1", "key2"}};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, RequestReplay) {
    spy::network::messages::RequestReplay testMessage{exampleUUID1};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, StatisticsMessage) {
    spy::network::messages::StatisticsMessage testMessage{exampleUUID1,
                                                          spy::statistics::Statistics{{{"Cocktails", "Who drank the most?", "17", "3"}}},
                                                          exampleUUID1,
                                                          spy::statistics::VictoryEnum::VICTORY_BY_DRINKING, false};
    testEncodeDecode(testMessage);
}

TEST(MessageEncodeDecode, Strike) {
    spy::network::messages::Strike testMessage{exampleUUID1, 7, 8, "Stealing cocktails from players"};
    testEncodeDecode(testMessage);
}