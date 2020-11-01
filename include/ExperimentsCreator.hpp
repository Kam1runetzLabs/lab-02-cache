// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_EXPERIMENTSCREATOR_HPP_
#define INCLUDE_EXPERIMENTSCREATOR_HPP_

/*!
 * @brief интерфейс класса, создающего набор экспериментов
 * @details классы, реализующие данный интерфейс, реализуя фабричный метод
 * CreateExperiments задают поведение создания экспериментов для планировщика
 * ExperimentsScheduler
 * */

#include <Experiment.hpp>
#include <vector>

class ExperimentsCreator {
 public:
  /*!
   * @param aL1CacheSize размер кэша данных первого уровня
   * @param aL2CacheSize размер кэша второго уровня
   * @param aL3CacheSize размер кэша третьего уровня*/
  ExperimentsCreator(std::size_t aL1CacheSize, std::size_t aL2CacheSize,
                     std::size_t aL3CacheSize)
      : L1CacheSize(aL1CacheSize),
        L2CacheSize(aL2CacheSize),
        L3CacheSize(aL3CacheSize) {}
  virtual ~ExperimentsCreator() = default;
  /*!
   * @brief чисто виртуальный фабричный метод, перегружая который вы задаете
   * алгоритм создания набора экспериментов
   * @param buffer буффер, на котором будут проводиться эксперименты*/
  virtual std::vector<Experiment> CreateExperiments(char *buffer) = 0;
  /*!
   * @brief возврашает максимальный размер буффера, использующийся в
   * экспериментах для создания оного
   * @return размер буффера*/
  virtual std::size_t GetMaxBufferSize() const = 0;

  /*!
   * @example
   * @code
   * auto creator = new SomeExperimentsCreator(<args>);
   * auto bufferSize = creator->GetMaxBufferSize();
   * buffer = std::make_unique<char[]>(bufferSize);
   * auto experiments = creator->CreateExperiments(buffer.get());
   * ... or
   * auto scheduler = std::make_unique<ExperimentsScheduler>(new
   * SomeExperimentCreator(<args>);
   * @endcode*/

 protected:
  std::size_t L1CacheSize;
  std::size_t L2CacheSize;
  std::size_t L3CacheSize;
};

#endif  // INCLUDE_EXPERIMENTSCREATOR_HPP_
