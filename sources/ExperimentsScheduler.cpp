// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#include <Experiment.hpp>
#include <ExperimentsScheduler.hpp>
#include <ResultsPrinter.hpp>
#include <TravelOrders/TravelOrder.hpp>
#include <stdexcept>
#include <string>
#include <vector>

ExperimentsScheduler::ExperimentsScheduler(
    ExperimentsCreator *experimentsCreator)
    : expResults(),
      buffer(nullptr),
      resultsPrinter(nullptr),
      travelOrder(nullptr) {
  if (!experimentsCreator)
    throw std::runtime_error(
        "Didn't set experiments creator, scheduler can't work");
  experiments = experimentsCreator->CreateExperiments();
  buffer = new char[experimentsCreator->GetMaxBufferSize()];
  for (auto &exp : experiments) exp.SetBuffer(buffer);
  delete experimentsCreator;
}
ExperimentsScheduler::~ExperimentsScheduler() {
  delete[] buffer;
  delete resultsPrinter;
  delete travelOrder;
}
void ExperimentsScheduler::SetTravelOrder(TravelOrder *newOrder) {
  delete travelOrder;
  travelOrder = newOrder;
  for (auto &exp : experiments) exp.SetTravelOrder(newOrder);
  expResults.clear();
}
std::string ExperimentsScheduler::CurrentTravelOrder() const {
  return travelOrder->TravelOrderName();
}
void ExperimentsScheduler::RunAllExperiments() {
  for (auto &exp : experiments) {
    exp.WarnUpCache();
    std::size_t duration = exp.RunExperiment();
    expResults.emplace_back(duration, exp.GetBufferSize(),
                            exp.CurrentTravelOrder());
  }
}
Experiment::ExperimentResult ExperimentsScheduler::RunExperiment(
    std::size_t index) {
  if (index >= experiments.size())
    throw std::runtime_error("No experiment with such index");
  experiments[index].WarnUpCache();
  std::size_t duration = experiments[index].RunExperiment();
  return Experiment::ExperimentResult(duration,
                                      experiments[index].GetBufferSize(),
                                      experiments[index].CurrentTravelOrder());
}
std::vector<Experiment::ExperimentResult> ExperimentsScheduler::GetResults()
    const {
  return expResults;
}
std::size_t ExperimentsScheduler::GetExperimentsCount() const {
  return experiments.size();
}
void ExperimentsScheduler::SetPrinter(ResultsPrinter *printer) {
  delete resultsPrinter;
  resultsPrinter = printer;
}
void ExperimentsScheduler::Print(std::ostream &out) const {
  if (!resultsPrinter)
    throw std::runtime_error(
        "Didn't set printer for printing experiment results");
  resultsPrinter->Print(expResults, out);
}
bool ExperimentsScheduler::IsValid() const {
  return buffer != nullptr && travelOrder != nullptr;
}
ExperimentsScheduler::ExperimentsScheduler(
    ExperimentsScheduler &&other) noexcept
    : expResults(std::move(other.expResults)),
      experiments(std::move(other.experiments)),
      buffer(other.buffer),
      resultsPrinter(other.resultsPrinter),
      travelOrder(other.travelOrder) {
  other.travelOrder = nullptr;
  other.buffer = nullptr;
  other.resultsPrinter = nullptr;
}

ExperimentsScheduler &ExperimentsScheduler::operator=(
    ExperimentsScheduler &&other) noexcept {
  if (&other == this) return *this;
  delete[] buffer;
  delete travelOrder;
  delete resultsPrinter;

  buffer = other.buffer;
  travelOrder = other.travelOrder;
  resultsPrinter = other.resultsPrinter;

  experiments = std::move(other.experiments);
  expResults = std::move(other.expResults);

  other.resultsPrinter = nullptr;
  other.travelOrder = nullptr;
  other.buffer = nullptr;

  return *this;
}
ExperimentsScheduler::ExperimentsScheduler()
    : expResults(),
      experiments(),
      buffer(nullptr),
      resultsPrinter(nullptr),
      travelOrder(nullptr) {}
void ExperimentsScheduler::CreateExperiments(
    ExperimentsCreator *experimentsCreator) {
  if (!experimentsCreator)
    throw std::runtime_error(
        "Experiments creator most be non-null, scheduler can't work");
  experiments.clear();
  expResults.clear();
  delete[] buffer;

  experiments = experimentsCreator->CreateExperiments();
  buffer = new char[experimentsCreator->GetMaxBufferSize()];
  delete experimentsCreator;
}
