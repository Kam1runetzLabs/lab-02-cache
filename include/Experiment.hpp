// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef CACHE_EXPERIMENT_HPP
#define CACHE_EXPERIMENT_HPP

#include <TravelOrders/TravelOrder.hpp>
#include <config.hpp>

class Experiment {
 public:
  struct ExperimentResult {
    ExperimentResult(std::size_t duration, std::size_t bufferSize, std::string travelOrder);
    std::size_t Duration;
    std::size_t BufferSize;
    std::string TravelOrder;
  };
  Experiment(char *buffer, std::size_t bufferSize);
  ~Experiment() = default;

  void SetBuffer(char *buffer);

  void SetTravelOrder(TravelOrder *newOrder);
  std::string CurrentTravelOrder() const;

  void WarnUpCache();
  std::size_t RunExperiment();

  std::size_t GetBufferSize() const;

 private:
  char *buffer;
  std::size_t bufferSize;
  TravelOrder *travelOrder;
};

#endif  // CACHE_EXPERIMENT_HPP
