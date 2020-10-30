// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#include <Experiment.hpp>
#include <ExperimentsScheduler.hpp>
#include <ResultsPrinter.hpp>
#include <TravelOrders/TravelOrder.hpp>
#include <random>
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

  auto bufferSize = experimentsCreator->GetMaxBufferSize();
  buffer = std::make_unique<char[]>(bufferSize);

  std::random_device rd;
  std::mt19937 randomizer(rd());
  for (std::size_t i = 0; i < bufferSize; ++i) buffer[i] = randomizer();

  experiments = experimentsCreator->CreateExperiments(buffer.get());

  delete experimentsCreator;
}

ExperimentsScheduler::~ExperimentsScheduler() = default;

void ExperimentsScheduler::SetTravelOrder(TravelOrder *newOrder) {
  travelOrder.reset(newOrder);
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
  resultsPrinter.reset(printer);
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
      buffer(std::move(other.buffer)),
      resultsPrinter(std::move(other.resultsPrinter)),
      travelOrder(std::move(other.travelOrder)) {}

ExperimentsScheduler &ExperimentsScheduler::operator=(
    ExperimentsScheduler &&other) noexcept {
  if (&other == this) return *this;

  buffer = std::move(other.buffer);
  travelOrder = std::move(other.travelOrder);
  resultsPrinter = std::move(other.resultsPrinter);

  experiments = std::move(other.experiments);
  expResults = std::move(other.expResults);

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

  auto bufferSize = experimentsCreator->GetMaxBufferSize();
  buffer = std::make_unique<char[]>(bufferSize);
  experiments = experimentsCreator->CreateExperiments(buffer.get());
  delete experimentsCreator;
}
