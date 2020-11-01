// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_DEFAULTEXPERIMENTSCREATOR_HPP_
#define INCLUDE_DEFAULTEXPERIMENTSCREATOR_HPP_

/*!
 * @brief стандартная реализация интерфеса ExperimentCreator */

#include <Experiment.hpp>
#include <ExperimentsCreator.hpp>
#include <vector>

class DefaultExperimentsCreator : public ExperimentsCreator {
 public:
  /*! @brief результат зависит только от максимального и минимального размеров
   * кэша*/
  DefaultExperimentsCreator(std::size_t minCacheSize, std::size_t maxCacheSize);
  /*! @brief фабричный метод, создающий эесперименты с размерами буфферов,
   * вычисляемыми следующим образом: 1 / 2 * cache['min'] < 2^x < 2^(x + 1) <
   * ... < 3 / 2 * cache['max'] */
  std::vector<Experiment> CreateExperiments(char *buffer) override;

  std::size_t GetMaxBufferSize() const override;

 private:
  std::size_t maxBufferSize;
};

#endif  // INCLUDE_DEFAULTEXPERIMENTSCREATOR_HPP_
