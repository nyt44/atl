#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "connection_diary.hpp"

#include "connection_map_wrapper_interface.hpp"
#include "mocks/connection_map_wrapper_mock.hpp"

using namespace ::testing;
using namespace atl;
using namespace mocks;

namespace
{
const std::string kExampleConnectionStr{"1-2:1"};
}

class ConnectionDiaryTest : public Test
{
 public:
  ConnectionDiaryTest() : map_wrapper_mock{}, test_obj{map_wrapper_mock} {}

  StrictMock<ConnectionMapWrapperMock> map_wrapper_mock;
  ConnectionDiary test_obj;
  InSequence seq;
};

TEST_F(ConnectionDiaryTest, AddEntryIfNotExistsInMapIsSuccessfull)
{
  EXPECT_CALL(map_wrapper_mock, EntryExists(kExampleConnectionStr)).WillOnce(Return(false));
  EXPECT_CALL(map_wrapper_mock, AddEntry(kExampleConnectionStr)).WillOnce(Return(true));

  EXPECT_TRUE(test_obj.AddConnection(kExampleConnectionStr));
}

TEST_F(ConnectionDiaryTest, AddEntryIfExistsInMapIsSuccessfull)
{
  EXPECT_CALL(map_wrapper_mock, EntryExists(kExampleConnectionStr)).WillOnce(Return(true));
  EXPECT_CALL(map_wrapper_mock, IncreaseEntryRefCount(kExampleConnectionStr));

  EXPECT_TRUE(test_obj.AddConnection(kExampleConnectionStr));
}

TEST_F(ConnectionDiaryTest, IfAddEntryFailsAddConnectionAlsoFails)
{
  EXPECT_CALL(map_wrapper_mock, EntryExists(kExampleConnectionStr)).WillOnce(Return(false));
  EXPECT_CALL(map_wrapper_mock, AddEntry(kExampleConnectionStr)).WillOnce(Return(false));

  EXPECT_FALSE(test_obj.AddConnection(kExampleConnectionStr));
}

TEST_F(ConnectionDiaryTest, DeleteConnectionIsSuccessfullIfEntryExistsWithRefCountIs1)
{
    EXPECT_CALL(map_wrapper_mock, EntryExists(kExampleConnectionStr)).WillOnce(Return(true));
    EXPECT_CALL(map_wrapper_mock, GetEntryRefCount(kExampleConnectionStr)).WillOnce(Return(1));
    EXPECT_CALL(map_wrapper_mock, DeleteEntry(kExampleConnectionStr)).WillOnce(Return(true));

    EXPECT_TRUE(test_obj.DeleteConnection(kExampleConnectionStr));
}

TEST_F(ConnectionDiaryTest, DeleteConnectionFailsIfEntryDoesNotExist)
{
    EXPECT_CALL(map_wrapper_mock, EntryExists(kExampleConnectionStr)).WillOnce(Return(false));

    EXPECT_FALSE(test_obj.DeleteConnection(kExampleConnectionStr));
}

TEST_F(ConnectionDiaryTest, DeleteConnectionIsSuccessfullIfEntryExistsWithRefCountGreaterThan1)
{
    EXPECT_CALL(map_wrapper_mock, EntryExists(kExampleConnectionStr)).WillOnce(Return(true));
    EXPECT_CALL(map_wrapper_mock, GetEntryRefCount(kExampleConnectionStr)).WillOnce(Return(2));
    EXPECT_CALL(map_wrapper_mock, DecreaseEntryRefCount(kExampleConnectionStr));

    EXPECT_TRUE(test_obj.DeleteConnection(kExampleConnectionStr));
}

TEST_F(ConnectionDiaryTest, IfDeleteEntryFailsDeleteConnectionAlsoFails)
{
    EXPECT_CALL(map_wrapper_mock, EntryExists(kExampleConnectionStr)).WillOnce(Return(true));
    EXPECT_CALL(map_wrapper_mock, GetEntryRefCount(kExampleConnectionStr)).WillOnce(Return(1));
    EXPECT_CALL(map_wrapper_mock, DeleteEntry(kExampleConnectionStr)).WillOnce(Return(false));

    EXPECT_FALSE(test_obj.DeleteConnection(kExampleConnectionStr));
}
