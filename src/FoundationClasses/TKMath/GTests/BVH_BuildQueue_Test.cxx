

#include <gtest/gtest.h>

#include <BVH_BuildQueue.hpp>

#include <thread>
#include <vector>

TEST(BVH_BuildQueueTest, DefaultConstructor)
{
  BVH_BuildQueue aQueue;

  EXPECT_EQ(aQueue.Size(), 0);
  EXPECT_FALSE(aQueue.HasBusyThreads());
}

TEST(BVH_BuildQueueTest, EnqueueSingle)
{
  BVH_BuildQueue aQueue;

  aQueue.Enqueue(42);

  EXPECT_EQ(aQueue.Size(), 1);
}

TEST(BVH_BuildQueueTest, EnqueueMultiple)
{
  BVH_BuildQueue aQueue;

  aQueue.Enqueue(1);
  aQueue.Enqueue(2);
  aQueue.Enqueue(3);

  EXPECT_EQ(aQueue.Size(), 3);
}

TEST(BVH_BuildQueueTest, FetchFromEmptyQueue)
{
  BVH_BuildQueue aQueue;
  bool           wasBusy = false;
  int            aResult = aQueue.Fetch(wasBusy);

  EXPECT_EQ(aResult, -1);
  EXPECT_FALSE(wasBusy);
  EXPECT_FALSE(aQueue.HasBusyThreads());
}

TEST(BVH_BuildQueueTest, FetchSingleItem)
{
  BVH_BuildQueue aQueue;
  aQueue.Enqueue(42);

  bool wasBusy = false;
  int  aResult = aQueue.Fetch(wasBusy);

  EXPECT_EQ(aResult, 42);
  EXPECT_TRUE(wasBusy);
  EXPECT_TRUE(aQueue.HasBusyThreads());
  EXPECT_EQ(aQueue.Size(), 0);
}

TEST(BVH_BuildQueueTest, FetchFIFOOrder)
{
  BVH_BuildQueue aQueue;

  aQueue.Enqueue(10);
  aQueue.Enqueue(20);
  aQueue.Enqueue(30);

  bool wasBusy = false;

  EXPECT_EQ(aQueue.Fetch(wasBusy), 10);
  EXPECT_TRUE(wasBusy);

  EXPECT_EQ(aQueue.Fetch(wasBusy), 20);
  EXPECT_TRUE(wasBusy);

  EXPECT_EQ(aQueue.Fetch(wasBusy), 30);
  EXPECT_TRUE(wasBusy);

  EXPECT_EQ(aQueue.Fetch(wasBusy), -1);
  EXPECT_FALSE(wasBusy);
}

TEST(BVH_BuildQueueTest, ThreadCountTracking)
{
  BVH_BuildQueue aQueue;

  aQueue.Enqueue(1);
  aQueue.Enqueue(2);

  EXPECT_FALSE(aQueue.HasBusyThreads());

  bool wasBusy = false;

  aQueue.Fetch(wasBusy);
  EXPECT_TRUE(wasBusy);
  EXPECT_TRUE(aQueue.HasBusyThreads());

  aQueue.Fetch(wasBusy);
  EXPECT_TRUE(wasBusy);
  EXPECT_TRUE(aQueue.HasBusyThreads());

  aQueue.Fetch(wasBusy);
  EXPECT_FALSE(wasBusy);
  EXPECT_FALSE(aQueue.HasBusyThreads());
}

TEST(BVH_BuildQueueTest, AlternatingEnqueueFetch)
{
  BVH_BuildQueue aQueue;

  aQueue.Enqueue(1);
  EXPECT_EQ(aQueue.Size(), 1);

  bool wasBusy = false;
  EXPECT_EQ(aQueue.Fetch(wasBusy), 1);
  EXPECT_EQ(aQueue.Size(), 0);

  aQueue.Enqueue(2);
  EXPECT_EQ(aQueue.Size(), 1);

  EXPECT_EQ(aQueue.Fetch(wasBusy), 2);
  EXPECT_EQ(aQueue.Size(), 0);
}

TEST(BVH_BuildQueueTest, LargeQueue)
{
  BVH_BuildQueue aQueue;

  const int aCount = 1000;
  for (int i = 0; i < aCount; ++i)
  {
    aQueue.Enqueue(i);
  }

  EXPECT_EQ(aQueue.Size(), aCount);

  bool wasBusy = false;
  for (int i = 0; i < aCount; ++i)
  {
    EXPECT_EQ(aQueue.Fetch(wasBusy), i);
  }

  EXPECT_EQ(aQueue.Size(), 0);
}

TEST(BVH_BuildQueueTest, NegativeValues)
{
  BVH_BuildQueue aQueue;

  aQueue.Enqueue(-1);
  aQueue.Enqueue(-100);
  aQueue.Enqueue(0);

  bool wasBusy = false;

  EXPECT_EQ(aQueue.Fetch(wasBusy), -1);
  EXPECT_EQ(aQueue.Fetch(wasBusy), -100);
  EXPECT_EQ(aQueue.Fetch(wasBusy), 0);
}

TEST(BVH_BuildQueueTest, ConcurrentEnqueue)
{
  BVH_BuildQueue aQueue;

  const int                aThreadCount    = 4;
  const int                aItemsPerThread = 100;
  std::vector<std::thread> aThreads;

  for (int t = 0; t < aThreadCount; ++t)
  {
    aThreads.emplace_back(
      [&aQueue, t, aItemsPerThread = aItemsPerThread]()
      {
        for (int i = 0; i < aItemsPerThread; ++i)
        {
          aQueue.Enqueue(t * aItemsPerThread + i);
        }
      });
  }

  for (auto& aThread : aThreads)
  {
    aThread.join();
  }

  EXPECT_EQ(aQueue.Size(), aThreadCount * aItemsPerThread);
}

TEST(BVH_BuildQueueTest, ConcurrentFetch)
{
  BVH_BuildQueue aQueue;

  const int aItemCount = 400;
  for (int i = 0; i < aItemCount; ++i)
  {
    aQueue.Enqueue(i);
  }

  const int                aThreadCount = 4;
  std::vector<std::thread> aThreads;
  std::vector<int>         aFetchedCounts(aThreadCount, 0);

  for (int t = 0; t < aThreadCount; ++t)
  {
    aThreads.emplace_back(
      [&aQueue, t, &aFetchedCounts]()
      {
        bool wasBusy = false;
        while (true)
        {
          int aItem = aQueue.Fetch(wasBusy);
          if (aItem == -1)
            break;
          aFetchedCounts[t]++;
        }
      });
  }

  for (auto& aThread : aThreads)
  {
    aThread.join();
  }

  int aTotalFetched = 0;
  for (int aCount : aFetchedCounts)
  {
    aTotalFetched += aCount;
  }

  EXPECT_EQ(aTotalFetched, aItemCount);
  EXPECT_EQ(aQueue.Size(), 0);
}

TEST(BVH_BuildQueueTest, ConcurrentEnqueueAndFetch)
{
  BVH_BuildQueue aQueue;

  const int                aProducerCount    = 2;
  const int                aConsumerCount    = 2;
  const int                aItemsPerProducer = 100;
  std::vector<std::thread> aThreads;
  std::atomic<int>         aFetchedCount{0};
  std::atomic<bool>        aDone{false};

  for (int t = 0; t < aProducerCount; ++t)
  {
    aThreads.emplace_back(
      [&aQueue, t, aItemsPerProducer = aItemsPerProducer]()
      {
        for (int i = 0; i < aItemsPerProducer; ++i)
        {
          aQueue.Enqueue(t * aItemsPerProducer + i);
        }
      });
  }

  for (int t = 0; t < aConsumerCount; ++t)
  {
    aThreads.emplace_back(
      [&aQueue, &aFetchedCount, &aDone]()
      {
        bool wasBusy = false;
        while (!aDone.load() || aQueue.Size() > 0)
        {
          int aItem = aQueue.Fetch(wasBusy);
          if (aItem != -1)
          {
            aFetchedCount.fetch_add(1);
          }
        }
      });
  }

  for (int i = 0; i < aProducerCount; ++i)
  {
    aThreads[i].join();
  }

  aDone.store(true);

  for (int i = aProducerCount; i < aProducerCount + aConsumerCount; ++i)
  {
    aThreads[i].join();
  }

  EXPECT_EQ(aFetchedCount.load(), aProducerCount * aItemsPerProducer);
  EXPECT_EQ(aQueue.Size(), 0);
}

TEST(BVH_BuildQueueTest, RepeatedFetchFromEmpty)
{
  BVH_BuildQueue aQueue;
  bool           wasBusy = false;

  for (int i = 0; i < 10; ++i)
  {
    int aResult = aQueue.Fetch(wasBusy);
    EXPECT_EQ(aResult, -1);
    EXPECT_FALSE(wasBusy);
  }

  EXPECT_FALSE(aQueue.HasBusyThreads());
}

TEST(BVH_BuildQueueTest, EnqueueZero)
{
  BVH_BuildQueue aQueue;

  aQueue.Enqueue(0);
  EXPECT_EQ(aQueue.Size(), 1);

  bool wasBusy = false;
  EXPECT_EQ(aQueue.Fetch(wasBusy), 0);
  EXPECT_TRUE(wasBusy);
}

TEST(BVH_BuildQueueTest, DuplicateValues)
{
  BVH_BuildQueue aQueue;

  aQueue.Enqueue(5);
  aQueue.Enqueue(5);
  aQueue.Enqueue(5);

  EXPECT_EQ(aQueue.Size(), 3);

  bool wasBusy = false;
  EXPECT_EQ(aQueue.Fetch(wasBusy), 5);
  EXPECT_EQ(aQueue.Fetch(wasBusy), 5);
  EXPECT_EQ(aQueue.Fetch(wasBusy), 5);
}

TEST(BVH_BuildQueueTest, SingleThreadWorkflow)
{
  BVH_BuildQueue aQueue;

  aQueue.Enqueue(0);

  bool wasBusy = false;
  int  aNode   = aQueue.Fetch(wasBusy);

  EXPECT_EQ(aNode, 0);
  EXPECT_TRUE(wasBusy);

  aQueue.Enqueue(1);
  aQueue.Enqueue(2);

  EXPECT_EQ(aQueue.Size(), 2);

  aNode = aQueue.Fetch(wasBusy);
  EXPECT_EQ(aNode, 1);

  aNode = aQueue.Fetch(wasBusy);
  EXPECT_EQ(aNode, 2);

  aNode = aQueue.Fetch(wasBusy);
  EXPECT_EQ(aNode, -1);
  EXPECT_FALSE(wasBusy);
}
