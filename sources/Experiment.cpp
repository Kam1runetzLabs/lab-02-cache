// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#include <Experiment.hpp>
#include <chrono>
#include <config.hpp>
#include <random>
#include <stdexcept>
#include <utility>

Experiment::Experiment(char *aBuffer, std::size_t aBufferSize)
    : buffer(aBuffer), bufferSize(aBufferSize), travelOrder(nullptr) {}

void Experiment::WarnUpCache() {
  if (!buffer)
    throw std::runtime_error("Didn't set buffer, experiment can't starting");
  [[maybe_unused]] char k;
  for (std::size_t i = 0; i < bufferSize; ++i) k = buffer[i];
}

std::size_t Experiment::RunExperiment() {
  if (!travelOrder)
    throw std::runtime_error(
        "Didn't set travel order, experiment can't starting");

  if (!buffer)
    throw std::runtime_error("Didn't set buffer, experiment can't starting");
  std::size_t commonDuration{0};
  [[maybe_unused]] char k;

  std::size_t index{0};

  for (std::size_t i = 0; i < IterationsCount; ++i) {
    for (std::size_t j = 0; j < bufferSize; j += CacheLineSize) {
      index = travelOrder->GetNextIndex();
      auto start = std::chrono::high_resolution_clock::now();
      k = buffer[index];
      auto stop = std::chrono::high_resolution_clock::now();
      auto duration = stop - start;
      commonDuration +=
          std::chrono::duration_cast<std::chrono::nanoseconds>(duration)
              .count();
    }
    travelOrder->SetDefaultIndex();
  }
  return commonDuration / IterationsCount / (bufferSize / CacheLineSize);
}

void Experiment::SetTravelOrder(TravelOrder *newOrder) {
  travelOrder = newOrder;
  travelOrder->SetBufferSize(bufferSize);
}

std::string Experiment::CurrentTravelOrder() const {
  return travelOrder ? travelOrder->TravelOrderName() : std::string();
}

std::size_t Experiment::GetBufferSize() const { return bufferSize; }

Experiment::ExperimentResult::ExperimentResult(std::size_t duration,
                                               std::size_t bufferSize,
                                               const std::string &travelOrder)
    : Duration(duration), BufferSize(bufferSize), TravelOrder(travelOrder) {}

bool operator==(const Experiment::ExperimentResult &left,
                const Experiment::ExperimentResult &right) {
  if (left.BufferSize == right.BufferSize && left.Duration == right.Duration &&
      left.TravelOrder == right.TravelOrder)
    return true;
  return false;
}

bool operator!=(const Experiment::ExperimentResult &left,
                const Experiment::ExperimentResult &right) {
  return !(left == right);
}
