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

  EXPECT_TRUE(true);
}
