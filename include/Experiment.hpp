// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_EXPERIMENT_HPP_
#define INCLUDE_EXPERIMENT_HPP_

/*!
 * @brief главный класс программы, представляющий сущность эксперимента*/

#include <TravelOrders/TravelOrder.hpp>
#include <config.hpp>
#include <string>

class Experiment {
 public:
  /*!
   * @brief структура результата эксперимента*/
  struct ExperimentResult {
    ExperimentResult(std::size_t duration, std::size_t bufferSize,
                     const std::string &travelOrder);
    std::size_t Duration;
    std::size_t BufferSize;
    std::string TravelOrder;

    friend bool operator==(const ExperimentResult &left,
                           const ExperimentResult &right);
    friend bool operator!=(const ExperimentResult &left,
                           const ExperimentResult &right);
  };
  /*!@param  buffer буффер на котором проводится эксперимент
   * @param bufferSize размер буффера */
  Experiment(char *buffer, std::size_t bufferSize);
  ~Experiment() = default;

  /*!@brief устанавливает вариант обхода буффера
   * @param  newOrder объект класса, реализующего интерфейс TravelOrder,
   * которому делегируется работа по обходу буффера
   * @throw std::runtime_error при newOrder == nullptr*/
  void SetTravelOrder(TravelOrder *newOrder);
  /*!@brief возвращает название текущего варианта поведения обхода
   * @return пустую строку если travelOrder == nullptr, иначе название текущего
   * варианта поведения обхода */
  std::string CurrentTravelOrder() const;

  /*!@brief "разогревает" кэш
   * @throw std::runtime_error при не заданном буффере (buffer == nullptr) */
  void WarnUpCache();
  /*!@brief запускает эксперимент на заданном буффере
   * @return среднее время доступа к одному элементу буффера в наносекундах
   * @throw std::runtime_error при не заданном буффере (buffer == nullptr)
   * @throw std::runtime_error при не заданном варианте поведения обхода
   * (travelOrder == nullptr) */
  std::size_t RunExperiment();

  /*!@brief возвращает размер буффера
   * @return размер буффера в байтах */
  std::size_t GetBufferSize() const;

 private:
  char *buffer;
  std::size_t bufferSize;
  TravelOrder *travelOrder;
};

#endif  // INCLUDE_EXPERIMENT_HPP_
