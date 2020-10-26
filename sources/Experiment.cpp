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
  std::random_device rd;
  std::mt19937_64 randomizer(rd());
  for (std::size_t i = 0; i < bufferSize; ++i) {
    buffer[i] = randomizer();
  }
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
  if (travelOrder) return travelOrder->TravelOrderName();
  return std::string();
}
std::size_t Experiment::GetBufferSize() const { return bufferSize; }
void Experiment::SetBuffer(char *aBuffer) {
  if (!aBuffer) throw std::runtime_error("Buffer most be not null");
  if (buffer) throw std::runtime_error("Buffer already exist");
  buffer = aBuffer;
}
Experiment::ExperimentResult::ExperimentResult(std::size_t duration,
                                               std::size_t bufferSize,
                                               std::string travelOrder)
    : Duration(duration),
      BufferSize(bufferSize),
      TravelOrder(std::move(travelOrder)) {}
