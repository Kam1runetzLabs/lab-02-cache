// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef CACHE_EXPERIMENTSSCHEDULER_HPP
#define CACHE_EXPERIMENTSSCHEDULER_HPP

#include <Experiment.hpp>
#include <ExperimentsCreator.hpp>
#include <TravelOrders/TravelOrder.hpp>
#include <ResultsPrinter.hpp>
#include <config.hpp>
#include <string>
#include <vector>
#include <ostream>


class ExperimentsScheduler {
 public:
  explicit ExperimentsScheduler(ExperimentsCreator *experimentsCreator);
  ~ExperimentsScheduler();

  void SetTravelOrder(TravelOrder *newOrder);
  std::string CurrentTravelOrder() const;

  void RunAllExperiments();
  Experiment::ExperimentResult RunExperiment(std::size_t index);

  std::vector<Experiment::ExperimentResult> GetResults() const;

  std::size_t GetExperimentsCount() const;

  void SetPrinter(ResultsPrinter *printer);
  void Print(std::ostream &out) const;

  [[nodiscard]] bool IsValid() const;

 private:
  std::vector<Experiment::ExperimentResult> expResults;
  std::vector<Experiment> experiments;
  char *buffer;
  ResultsPrinter *resultsPrinter;
  TravelOrder *travelOrder;
};

#endif  // CACHE_EXPERIMENTSSCHEDULER_HPP
