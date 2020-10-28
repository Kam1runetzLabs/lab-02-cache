// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_EXPERIMENTSSCHEDULER_HPP_
#define INCLUDE_EXPERIMENTSSCHEDULER_HPP_

#include <Experiment.hpp>
#include <ExperimentsCreator.hpp>
#include <ResultsPrinter.hpp>
#include <TravelOrders/TravelOrder.hpp>
#include <config.hpp>
#include <ostream>
#include <string>
#include <vector>

class ExperimentsScheduler {
 public:
  ExperimentsScheduler();
  explicit ExperimentsScheduler(ExperimentsCreator *experimentsCreator);
  ExperimentsScheduler(const ExperimentsScheduler &) = delete;
  ExperimentsScheduler(ExperimentsScheduler &&other) noexcept;
  ~ExperimentsScheduler();

  void operator=(const ExperimentsScheduler &) = delete;

  ExperimentsScheduler &operator=(ExperimentsScheduler &&other) noexcept;

  void CreateExperiments(ExperimentsCreator *experimentsCreator);

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

#endif  // INCLUDE_EXPERIMENTSSCHEDULER_HPP_
