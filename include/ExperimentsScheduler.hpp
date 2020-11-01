// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_EXPERIMENTSSCHEDULER_HPP_
#define INCLUDE_EXPERIMENTSSCHEDULER_HPP_

/*!
 * @brief Планировщик экспериментов*/

#include <Experiment.hpp>
#include <ExperimentsCreator.hpp>
#include <ResultsPrinter.hpp>
#include <TravelOrders/TravelOrder.hpp>
#include <config.hpp>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

class ExperimentsScheduler {
 public:
  /*!
   * @brief создает объект пустого планировщика*/
  ExperimentsScheduler();
  /*!
   * @brief При вызове данного конструктора сразу создается набор экспериментов
   * @param experimentsCreator объект класса, реализующего интерфейс
   * ExperimentsCreator, которому планировщик делегирует работу по созданию
   * экспериментов
   * @throw std::runtime_error при experimentsCreator == nullptr*/
  explicit ExperimentsScheduler(ExperimentsCreator *experimentsCreator);
  ExperimentsScheduler(const ExperimentsScheduler &) = delete;
  ExperimentsScheduler(ExperimentsScheduler &&other) noexcept;
  ~ExperimentsScheduler();

  void operator=(const ExperimentsScheduler &) = delete;

  ExperimentsScheduler &operator=(ExperimentsScheduler &&other) noexcept;

  /*!
   * @brief Создает набор экспериментов
   * @param experimentsCreator объект класса, реализующего интерфейс
   * ExperimentsCreator, которому планировщик делегирует работу по созданию
   * экспериментов
   * @throw std::runtime_error при experimentsCreator == nullptr
   * @details в случае, если набор экспериментов и буффер, на котором они
   * проводятся уже существуют - они перезапишутся, иначе создадуться*/
  void CreateExperiments(ExperimentsCreator *experimentsCreator);

  /*!
   * @brief устанавливает вариант поведения обхода буффера для всех
   * экспериментов
   * @param newOrder объект класса, реализующего интерфейс TravelOrder, которому
   * эксперименты делегируют работу по обходу буффера
   * @throw std::runtime_error при newOrder == nullptr
   * @details затирает уже существующие результаты экспериментов*/
  void SetTravelOrder(TravelOrder *newOrder);
  /*!
   * @brief возвращает название варианта поведения обхода
   * @return название текущего варианта поведения обхода, либо пустую строку,
   * при неустановленном варианте*/
  std::string CurrentTravelOrder() const;

  /*!
   * @brief последовательно запускает все эксперименты из набора и сохраняет
   * результат (перед запуском каждого эксперимента ему прогревается кэш)
   * @throw std::runtime_error при неустановленном варианте поведения обхода
   * (travelOrder == nullptr)
   * @throw std::runtime_error при каком-либо неявном сбросе buffer в nullptr
   * (например из дружественных классов)*/
  void RunAllExperiments();
  /*!
   * @brief запускает (предварительно прогрев кэш) один эксперимент с заданным
   * индексом
   * @param index индекс эксперимента
   * @return структура ExperimentResult с результатом проведенного эксперимента
   * @throw std::runtime_error при отсутствии в планировщике эксперимента с
   * заданным индексом*/
  Experiment::ExperimentResult RunExperiment(std::size_t index);

  /*!
   * @brief возвращает результаты всех экспериментов*/
  std::vector<Experiment::ExperimentResult> GetResults() const;

  /*!
   * @brief возвращает количество экспериментов в планировщике*/
  std::size_t GetExperimentsCount() const;

  /*!
   * @brief устанавливает вариант поведения печати результатов
   * @param printer объект класса, реализующего интерфейс ResultsPrinter,
   * которому планировщик делегирует работу по печати результатов*/
  void SetPrinter(ResultsPrinter *printer);
  /*!
   * @brief печатает результаты экспериментов
   * @param out поток вывода
   * @throw std::runtime_error при не установленном resultsPrinter*/
  void Print(std::ostream &out) const;

  /*!
   * @brief возвращает статус планировщика
   * @return true - валидный (можно проводить эксперементы), иначе false*/
  [[nodiscard]] bool IsValid() const;

 private:
  std::vector<Experiment::ExperimentResult> expResults;
  std::vector<Experiment> experiments;
  std::unique_ptr<char[]> buffer;
  std::unique_ptr<ResultsPrinter> resultsPrinter;
  std::unique_ptr<TravelOrder> travelOrder;
};

#endif  // INCLUDE_EXPERIMENTSSCHEDULER_HPP_
