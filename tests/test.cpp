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
  EXPECT_TRUE(true);
}
