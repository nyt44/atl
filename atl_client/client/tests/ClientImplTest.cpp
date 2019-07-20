#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ClientImpl.hpp"

#include <memory>
#include <string>
#include <exception>

#include "mocks/ShmTransporterMock.hpp"

using namespace ::testing;
using namespace atl;
using namespace mocks;

namespace
{
const std::string kExampleConnectionStr{"1-2:1"};
const auto kRequestSize = kExampleConnectionStr.size() + 1;
const std::string kPositiveResponse{"ok"};
const std::string kNegativeResponse{"nok"};
}

class ClientImplTest : public Test
{
 public:
  std::unique_ptr<ClientImpl> CreateTestObj()
  {
    return std::make_unique<ClientImpl>(kExampleConnectionStr, daemon_stream_mock, factory_mock);
  }

  StrictMock<ShmTransporterMock> daemon_stream_mock{};
  StrictMock<MockTransporterFactoryMethod> factory_mock{};
  StrictMock<ShmTransporterMock>* transporter_mock{new StrictMock<ShmTransporterMock>};
  InSequence seq;
};

TEST_F(ClientImplTest, CreateAndDestroyClientIsSuccessfull)
{
  EXPECT_CALL(daemon_stream_mock, Send(_, kRequestSize));
  EXPECT_CALL(daemon_stream_mock, Receive()).WillOnce(Return(kPositiveResponse));
  EXPECT_CALL(factory_mock, CreateTransporterRaw(kExampleConnectionStr)).WillOnce(Return(transporter_mock));
  EXPECT_CALL(daemon_stream_mock, Send(_, kRequestSize));

  EXPECT_NO_THROW(auto test_obj = CreateTestObj(););
}

TEST_F(ClientImplTest, CreateClientRefusedByDaemon)
{
  EXPECT_CALL(daemon_stream_mock, Send(_, kRequestSize));
  EXPECT_CALL(daemon_stream_mock, Receive()).WillOnce(Return(kNegativeResponse));

  EXPECT_THROW(auto test_obj = CreateTestObj();, std::runtime_error);
}

TEST_F(ClientImplTest, ClientDestroyingFailsButDoesNotThrow)
{
  EXPECT_CALL(daemon_stream_mock, Send(_, kRequestSize));
  EXPECT_CALL(daemon_stream_mock, Receive()).WillOnce(Return(kPositiveResponse));
  EXPECT_CALL(factory_mock, CreateTransporterRaw(kExampleConnectionStr)).WillOnce(Return(transporter_mock));
  EXPECT_CALL(daemon_stream_mock, Send(_, kRequestSize)).WillOnce(Throw(std::runtime_error{""}));

  EXPECT_NO_THROW(auto test_obj = CreateTestObj());
}

TEST_F(ClientImplTest, SendTest)
{
  std::string example_data_to_send{"data"};

  EXPECT_CALL(daemon_stream_mock, Send(_, kRequestSize));
  EXPECT_CALL(daemon_stream_mock, Receive()).WillOnce(Return(kPositiveResponse));
  EXPECT_CALL(factory_mock, CreateTransporterRaw(kExampleConnectionStr)).WillOnce(Return(transporter_mock));
  EXPECT_CALL(*transporter_mock, Send(_, example_data_to_send.size()));
  EXPECT_CALL(daemon_stream_mock, Send(_, kRequestSize));

  EXPECT_NO_THROW({
    auto test_obj = CreateTestObj();
    test_obj->Send(static_cast<void*>(example_data_to_send.data()), example_data_to_send.size());
  });

}

TEST_F(ClientImplTest, ReceiveTest)
{
  EXPECT_CALL(daemon_stream_mock, Send(_, kRequestSize));
  EXPECT_CALL(daemon_stream_mock, Receive()).WillOnce(Return(kPositiveResponse));
  EXPECT_CALL(factory_mock, CreateTransporterRaw(kExampleConnectionStr)).WillOnce(Return(transporter_mock));
  EXPECT_CALL(*transporter_mock, Receive());
  EXPECT_CALL(daemon_stream_mock, Send(_, kRequestSize));

  EXPECT_NO_THROW({
    auto test_obj = CreateTestObj();
    test_obj->Receive();
  });

}
