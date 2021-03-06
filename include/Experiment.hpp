// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_EXPERIMENT_HPP_
#define INCLUDE_EXPERIMENT_HPP_

#include <TravelOrders/TravelOrder.hpp>
#include <config.hpp>
#include <string>

class Experiment {
 public:
  struct ExperimentResult {
    ExperimentResult(std::size_t duration, std::size_t bufferSize,
                     std::string travelOrder);
    std::size_t Duration;
    std::size_t BufferSize;
    std::string TravelOrder;

    friend bool operator==(const ExperimentResult &left,
                           const ExperimentResult &right);
    friend bool operator!=(const ExperimentResult &left,
                           const ExperimentResult &right);
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

#endif  // INCLUDE_EXPERIMENT_HPP_
