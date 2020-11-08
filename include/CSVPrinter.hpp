// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_CSVPRINTER_HPP_
#define INCLUDE_CSVPRINTER_HPP_

#include <Experiment.hpp>
#include <ResultsPrinter.hpp>
#include <vector>

/*!
 * @brief стандартная реализация интерфейса ResultsPrinter, печатает данные в
 * заданный поток в формате CSV
 */

class CSVPrinter : public ResultsPrinter {
  void Print(const std::vector<Experiment::ExperimentResult> &results,
             std::ostream &out) override;
};

#endif  // INCLUDE_CSVPRINTER_HPP_
