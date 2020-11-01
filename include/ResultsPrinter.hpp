// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

/*!
 * @brief Интерфейс класса, визуализируещего результаты исследования
 * @details Классы, реализующие данный интерфейс, задают поведение вывода данных
 * для планировщика ExperimentsScheduler
 * */

#ifndef INCLUDE_RESULTSPRINTER_HPP_
#define INCLUDE_RESULTSPRINTER_HPP_

#include <Experiment.hpp>
#include <ostream>
#include <vector>

class ResultsPrinter {
 public:
  virtual ~ResultsPrinter() = default;
  /*!
   * @brief чисто виртуальный метод, перегружая который вы задаете поведение
   * вывода результатов исследования
   * @param results вектор результатов экспериментов
   * @param out поток вывода результатов*/
  virtual void Print(const std::vector<Experiment::ExperimentResult> &results,
                     std::ostream &out) = 0;
};

#endif  // INCLUDE_RESULTSPRINTER_HPP_
