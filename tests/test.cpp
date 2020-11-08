// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#include <gtest/gtest.h>

#include <CSVPrinter.hpp>
#include <DefaultExperimentsCreator.hpp>
#include <DefaultPrinter.hpp>
#include <Experiment.hpp>
#include <ExperimentsScheduler.hpp>
#include <TravelOrders/DirectTravelOrder.hpp>
#include <TravelOrders/RandomTravelOrder.hpp>
#include <TravelOrders/ReverseTravelOrder.hpp>
#include <config.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

const auto CSVResultFileName = "result.csv";

TEST(ResultsSaving, CSV) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetPrinter(new CSVPrinter);

  std::ofstream csvResult;
  csvResult.open(CSVResultFileName, std::ios::out);
  if (!csvResult.is_open())
    FAIL() << "Unable to open results file" << std::endl;

  scheduler.SetTravelOrder(new DirectTravelOrder);
  scheduler.RunAllExperiments();
  scheduler.Print(csvResult);

  scheduler.SetTravelOrder(new ReverseTravelOrder);
  scheduler.RunAllExperiments();
  scheduler.Print(csvResult);

  scheduler.SetTravelOrder(new RandomTravelOrder);
  scheduler.RunAllExperiments();
  scheduler.Print(csvResult);

  csvResult.close();
}

TEST(ErrorHandling, NullCreatorForCoustructor) {
  EXPECT_THROW(ExperimentsScheduler scheduler(nullptr), std::runtime_error);
}

TEST(ErrorHandling, NullCreatorForCreateExperimentsMethod) {
  ExperimentsScheduler scheduler;
  EXPECT_THROW(scheduler.CreateExperiments(nullptr), std::runtime_error);
}

TEST(ErrorHandling, NullTravelOrder) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  EXPECT_THROW(scheduler.RunAllExperiments(), std::runtime_error);
}

TEST(ErrorHandling, NullPrinter) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetTravelOrder(new DirectTravelOrder);
  scheduler.RunAllExperiments();
  EXPECT_THROW(scheduler.Print(std::cout), std::runtime_error);
}

TEST(ErrorHandling, RunNonExistingExperiment) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  auto count = scheduler.GetExperimentsCount();
  EXPECT_THROW(scheduler.RunExperiment(count + 10), std::runtime_error);
}

TEST(ErrorHandling, ExperimentStartingWithoutBuffer) {
  std::size_t someSize = 100;
  Experiment experiment(nullptr, someSize);
  EXPECT_THROW(experiment.WarnUpCache(), std::runtime_error);
  EXPECT_THROW(experiment.RunExperiment(), std::runtime_error);
}

TEST(ErrorHandling, ExperimentStartingWithoutTravelOrder) {
  std::size_t someSize = 100;
  auto someBuffer = std::make_unique<char[]>(someSize);
  Experiment experiment(someBuffer.get(), someSize);
  experiment.WarnUpCache();
  EXPECT_THROW(experiment.RunExperiment(), std::runtime_error);
}

TEST(UseCases, DefaultExperiment) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetPrinter(new DefaultPrinter);
  scheduler.SetTravelOrder(new DirectTravelOrder);
  scheduler.RunAllExperiments();
  scheduler.Print(std::cout);

  scheduler.SetTravelOrder(new ReverseTravelOrder);
  scheduler.RunAllExperiments();
  scheduler.Print(std::cout);

  scheduler.SetTravelOrder(new RandomTravelOrder);
  scheduler.RunAllExperiments();
  scheduler.Print(std::cout);
  SUCCEED();
}

TEST(UseCases, SingleExperiment) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetTravelOrder(new DirectTravelOrder);

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
  scheduler.SetTravelOrder(new ReverseTravelOrder);

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

  scheduler.SetTravelOrder(new RandomTravelOrder);
  EXPECT_TRUE(scheduler.IsValid());
}

TEST(UseCases, MovingConstructor) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetTravelOrder(new DirectTravelOrder);
  scheduler.SetPrinter(new DefaultPrinter);
  scheduler.RunAllExperiments();
  auto results = scheduler.GetResults();
  auto expCount = scheduler.GetExperimentsCount();

  ExperimentsScheduler movedScheduler(std::move(scheduler));

  auto movedResults = movedScheduler.GetResults();
  auto movedExpCount = movedScheduler.GetExperimentsCount();

  EXPECT_EQ(expCount, movedExpCount);

  for (std::size_t i = 0; i < expCount; ++i)
    if (results[i] != movedResults[i]) {
      FAIL() << "results don't matching";
    }
  SUCCEED();
}

TEST(UseCases, MovingOperator) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));

  scheduler.SetTravelOrder(new DirectTravelOrder);
  scheduler.SetPrinter(new DefaultPrinter);
  scheduler.RunAllExperiments();

  auto results = scheduler.GetResults();
  auto expCount = scheduler.GetExperimentsCount();

  auto movedScheduler = std::move(scheduler);

  auto movedResults = movedScheduler.GetResults();
  auto movedExpCount = movedScheduler.GetExperimentsCount();

  EXPECT_EQ(expCount, movedExpCount);

  for (std::size_t i = 0; i < expCount; ++i)
    if (results[i] != movedResults[i]) {
      FAIL() << "results don't matching";
    }
  SUCCEED();
}

TEST(UseCases, CreatingSchedulerFromEmpyState) {
  ExperimentsScheduler scheduler;
  EXPECT_FALSE(scheduler.IsValid());
  scheduler.CreateExperiments(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetTravelOrder(new ReverseTravelOrder);
  scheduler.SetPrinter(new DefaultPrinter);
  EXPECT_TRUE(scheduler.IsValid());
}
