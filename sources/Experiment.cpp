//
// Created by w1ckedente on 24.10.2020.
//

#include <Experiment.hpp>
#include <chrono>
#include <config.hpp>
#include <functional>
#include <random>
#include <stdexcept>
#include <utility>

std::size_t getExecutingTime(const std::function<void(void)> &foo) {
  auto start = std::chrono::high_resolution_clock::now();
  foo();
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = stop - start;
  return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
}

Experiment::Experiment(char *aBuffer, std::size_t aBufferSize)
    : buffer(aBuffer), bufferSize(aBufferSize), travelOrder(nullptr) {}

void Experiment::WarnUpCache() {
  std::random_device rd;
  std::mt19937_64 randomizer(rd());
  for (std::size_t i = 0; i < bufferSize; ++i) {
    buffer[i] = randomizer();
  }
}

std::size_t Experiment::RunExperiment() {
  if (!travelOrder) throw std::runtime_error("Travel order most be not null");
  std::size_t commonDuration{0};
  for (std::size_t i = 0; i < IterationsCount; ++i) {
    commonDuration += getExecutingTime([=] {
      char k = buffer[travelOrder->GetNextIndex()];
      ++k;
    });
  }
  return commonDuration / IterationsCount;
}
void Experiment::SetTravelOrder(TravelOrder *newOrder) {
  delete travelOrder;
  travelOrder = newOrder;
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
    : Duration(duration), BufferSize(bufferSize), TravelOrder(std::move(travelOrder)) {}
