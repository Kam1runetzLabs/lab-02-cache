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
#include <fstream>
#include <iostream>

TEST(Example, EmptyTest) {
  std::ofstream out;
  out.open("investigation_result.txt", std::ios::out);
  if (!out.is_open()) {
    FAIL() << "opening out file error" << std::endl;
  }
  ExperimentsScheduler scheduler(
      new DefaultExperimentsCreator(MyL1dCacheSize, MyL3CacheSize));
  scheduler.SetTravelOrder(new DirectTravelOrder());
  scheduler.RunAllExperiments();

  scheduler.SetPrinter(new DefaultPrinter());
  scheduler.Print(out);

  scheduler.SetTravelOrder(new ReverseTravelOrder());
  scheduler.RunAllExperiments();

  scheduler.Print(out);

  scheduler.SetTravelOrder(new RandomTravelOrder());
  scheduler.RunAllExperiments();
  scheduler.Print(out);

  out.close();

  EXPECT_TRUE(true);
}
