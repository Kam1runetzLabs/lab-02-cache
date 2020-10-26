// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#include <gtest/gtest.h>

#include <DefaultExperimentsCreator.hpp>
#include <DefaultPrinter.hpp>
#include <Experiment.hpp>
#include <ExperimentsScheduler.hpp>
#include <TravelOrders/DirectTravelOrder.hpp>
#include <TravelOrders/RandomTravelOrder.hpp>
#include <TravelOrders/ReverseTravelOrder.hpp>
#include <config.hpp>
#include <iostream>
#include <stdexcept>

TEST(Example, EmptyTest) { EXPECT_TRUE(true); }

TEST(ErrorHandling, NullCreator) {
  EXPECT_THROW(ExperimentsScheduler scheduler(nullptr), std::runtime_error);
}

TEST(ErrorHandling, NullTravelOrder) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  EXPECT_THROW(scheduler.RunAllExperiments(), std::runtime_error);
}

TEST(ErrorHandling, NullPrinter) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetTravelOrder(new DirectTravelOrder());
  scheduler.RunAllExperiments();
  EXPECT_THROW(scheduler.Print(std::cout), std::runtime_error);
}

TEST(ErrorHandling, RunNonExistingExperiment) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  auto count = scheduler.GetExperimentsCount();
  EXPECT_THROW(scheduler.RunExperiment(count + 10), std::runtime_error);
}

TEST(ErrorHandling, SetingExperimentNullBuffer) {
  std::size_t someSize = 100;
  Experiment experiment(nullptr, someSize);
  EXPECT_THROW(experiment.SetBuffer(nullptr), std::runtime_error);
}

TEST(ErrorHandling, ExperimentRewritingExistingBuffer) {
  std::size_t someSize = 100;
  char *someBuffer = new char[someSize];
  char *otherBuffer = new char[someSize];
  Experiment experiment(someBuffer, someSize);
  EXPECT_THROW(experiment.SetBuffer(otherBuffer), std::runtime_error);
  delete[] someBuffer;
  delete[] otherBuffer;
}

TEST(ErrorHandling, ExperimentStartingWithoutBuffer) {
  std::size_t someSize = 100;
  Experiment experiment(nullptr, someSize);
  EXPECT_THROW(experiment.WarnUpCache(), std::runtime_error);
  EXPECT_THROW(experiment.RunExperiment(), std::runtime_error);
}

TEST(ErrorHandling, ExperimentStartingWithoutTravelOrder) {
  std::size_t someSize = 100;
  char *someBuffer = new char[someSize];
  Experiment experiment(someBuffer, someSize);
  experiment.WarnUpCache();
  EXPECT_THROW(experiment.RunExperiment(), std::runtime_error);
}

TEST(UseCases, DefaultExperiment) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetPrinter(new DefaultPrinter());
  scheduler.SetTravelOrder(new DirectTravelOrder());
  scheduler.RunAllExperiments();
  scheduler.Print(std::cout);

  scheduler.SetTravelOrder(new ReverseTravelOrder());
  scheduler.RunAllExperiments();
  scheduler.Print(std::cout);

  scheduler.SetTravelOrder(new RandomTravelOrder());
  scheduler.RunAllExperiments();
  scheduler.Print(std::cout);
  SUCCEED();
}

TEST(UseCases, SingleExperiment) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetTravelOrder(new DirectTravelOrder());

  if (scheduler.GetExperimentsCount() != 0) {
    Experiment::ExperimentResult result = scheduler.RunExperiment(0);
    std::cout << "Travel order: " << result.TravelOrder << std::endl;
    std::cout << "Size: " << result.BufferSize << "Kb" << std::endl;
    std::cout << "Duration: " << result.Duration << "ns" << std::endl;
    SUCCEED();
  } else {
    FAIL() << "Undefined error (no experiments), send error report to "
              "<notsoserious2017@gmail.com>"
           << std::endl;
  }
}

TEST(UseCases, ResultProcessingWithoutPrinting) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetTravelOrder(new ReverseTravelOrder());

  scheduler.RunAllExperiments();
  std::vector<Experiment::ExperimentResult> results = scheduler.GetResults();

  // some processing
  for (auto &res : results) {
    [[maybe_unused]] std::string travelOrder = res.TravelOrder;
    [[maybe_unused]] std::size_t duration = res.Duration;
    [[maybe_unused]] std::size_t bufferSize = res.BufferSize;
  }
  // end of processing
}

TEST(UseCases, CheckSchedulerValidity) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  EXPECT_FALSE(scheduler.IsValid());

  scheduler.SetTravelOrder(new RandomTravelOrder());
  EXPECT_TRUE(scheduler.IsValid());
}