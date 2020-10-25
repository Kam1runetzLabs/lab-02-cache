// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <DefaultExperimentsCreator.hpp>
#include <DefaultPrinter.hpp>
#include <ExperimentsScheduler.hpp>
#include <TravelOrders/DirectTravelOrder.hpp>
#include <TravelOrders/RandomTravelOrder.hpp>
#include <TravelOrders/ReverseTravelOrder.hpp>
#include <chrono>
#include <config.hpp>
#include <iostream>

// todo: good exception "what"

TEST(Example, EmptyTest) {
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetTravelOrder(new DirectTravelOrder());
  scheduler.RunAllExperiments();

  scheduler.SetPrinter(new DefaultPrinter());
  scheduler.Print(std::cout);

  scheduler.SetTravelOrder(new ReverseTravelOrder());
  scheduler.RunAllExperiments();

  scheduler.Print(std::cout);

  scheduler.SetTravelOrder(new RandomTravelOrder());
  scheduler.RunAllExperiments();
  scheduler.Print(std::cout);

  //  auto start = std::chrono::high_resolution_clock::now();
  //  [[maybe_unused]] char k = 0;
  //  auto stop = std::chrono::high_resolution_clock::now();
  //  auto dur = stop - start;
  //  std::cout <<
  //  std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count() <<
  //  std::endl;
  EXPECT_TRUE(true);
}
