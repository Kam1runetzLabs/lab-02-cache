//
// Created by w1ckedente on 24.10.2020.
//
#include <Experiment.hpp>
#include <ExperimentsScheduler.hpp>
#include <ResultsPrinter.hpp>
#include <TravelOrders/TravelOrder.hpp>
#include <stdexcept>
#include <string>
#include <vector>

ExperimentsScheduler::ExperimentsScheduler(
    ExperimentsCreator *experimentsCreator)
    : expResults(), resultsPrinter(nullptr), travelOrder(nullptr) {
  if (!experimentsCreator)
    throw std::runtime_error("Experiments creator most be not null");
  experiments = experimentsCreator->CreateExperiments();
  buffer = new char[experimentsCreator->GetMaxBufferSize()];
  for (auto &exp : experiments) exp.SetBuffer(buffer);
  delete experimentsCreator;
}
ExperimentsScheduler::~ExperimentsScheduler() {
  delete buffer;
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
    expResults.emplace_back(Experiment::ExperimentResult(
        duration, exp.GetBufferSize(), exp.CurrentTravelOrder()));
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
  if (!resultsPrinter) throw std::runtime_error("Printer wasn't seted");
  resultsPrinter->Print(expResults, out);
}
bool ExperimentsScheduler::IsValid() const {
  return buffer != nullptr && travelOrder != nullptr;
}
