#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "daemon_loop.hpp"

#include "mocks/shm_transporter_mock.hpp"
#include "mocks/connection_diary_mock.hpp"

using namespace atl;
using namespace testing;
using namespace mocks;

namespace
{
const std::string kQuitCommand{"quit"};
const std::string kUnknownCommand{"qwerty"};
const std::string kExampleConnectionStr{"1-2:1"};
const std::string kOkResponse{"ok"};
const std::string kNokResponse{"nok"};
}

class DaemonLoopTest : public Test
{
 public:
  DaemonLoopTest() : transporter_mock{}, diary_mock{}, test_obj{transporter_mock, diary_mock} {}

  StrictMock<ShmTransporterMock> transporter_mock;
  StrictMock<ConnectionDiaryMock> diary_mock;
  DaemonLoop test_obj;
  InSequence seq;
};

TEST_F(DaemonLoopTest, DaemonLoopIsTerminatedWhenQuitCommandIsReceived)
{
  EXPECT_CALL(transporter_mock, Receive()).WillOnce(Return(kQuitCommand));
  test_obj.Run();
}

TEST_F(DaemonLoopTest, UnknownCommandIsIgnored)
{
  EXPECT_CALL(transporter_mock, Receive()).WillOnce(Return(kUnknownCommand));
  EXPECT_CALL(transporter_mock, Receive()).WillOnce(Return(kQuitCommand));
  test_obj.Run();
}

TEST_F(DaemonLoopTest, WhenCommandStartingWithPlusThenConnectionIsAdded)
{
  EXPECT_CALL(transporter_mock, Receive()).WillOnce(Return("+" + kExampleConnectionStr));
  EXPECT_CALL(diary_mock, AddConnection(kExampleConnectionStr)).WillOnce(Return(true));
  EXPECT_CALL(transporter_mock, Send(kOkResponse));
  EXPECT_CALL(transporter_mock, Receive()).WillOnce(Return(kQuitCommand));

  test_obj.Run();
}

TEST_F(DaemonLoopTest, WhenCommandStartingWithMinusThenConnectionIsDeleted)
{
  EXPECT_CALL(transporter_mock, Receive()).WillOnce(Return("-" + kExampleConnectionStr));
  EXPECT_CALL(diary_mock, DeleteConnection(kExampleConnectionStr)).WillOnce(Return(true));
  EXPECT_CALL(transporter_mock, Send(kOkResponse));
  EXPECT_CALL(transporter_mock, Receive()).WillOnce(Return(kQuitCommand));

  test_obj.Run();
}

TEST_F(DaemonLoopTest, WhenAddingConnectionFailsThenDaemonSendsNok)
{
  EXPECT_CALL(transporter_mock, Receive()).WillOnce(Return("+" + kExampleConnectionStr));
  EXPECT_CALL(diary_mock, AddConnection(kExampleConnectionStr)).WillOnce(Return(false));
  EXPECT_CALL(transporter_mock, Send(kNokResponse));
  EXPECT_CALL(transporter_mock, Receive()).WillOnce(Return(kQuitCommand));

  test_obj.Run();
}

TEST_F(DaemonLoopTest, WhenDeletingConnectionFailsThenDaemonSendsNok)
{
  EXPECT_CALL(transporter_mock, Receive()).WillOnce(Return("-" + kExampleConnectionStr));
  EXPECT_CALL(diary_mock, DeleteConnection(kExampleConnectionStr)).WillOnce(Return(false));
  EXPECT_CALL(transporter_mock, Send(kNokResponse));
  EXPECT_CALL(transporter_mock, Receive()).WillOnce(Return(kQuitCommand));

  test_obj.Run();
}
