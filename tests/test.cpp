// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <Experiment.hpp>
#include <DefaultExperimentsCreator.hpp>
#include <ExperimentsScheduler.hpp>
#include <TravelOrders/DirectTravelOrder.hpp>
#include <config.hpp>
#include <iostream>

// todo: good exception "what"

TEST(Example, EmptyTest) {
  ExperimentsScheduler scheduler(new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetTravelOrder(new DirectTravelOrder());
  scheduler.RunAllExperiments();
  std::vector<Experiment::ExperimentResult> res =  scheduler.GetResults();

  std::cout << "Test duration: " << res[0].Duration << " ns" << std::endl;
  std::cout << "Test buffer size " << res[0].BufferSize / 1024 << " Kb" << std::endl;
  EXPECT_TRUE(true);
}
