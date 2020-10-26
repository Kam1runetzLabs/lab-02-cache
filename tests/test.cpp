// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

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
