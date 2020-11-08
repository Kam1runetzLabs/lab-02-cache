// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_DEFAULTPRINTER_HPP_
#define INCLUDE_DEFAULTPRINTER_HPP_

/*!
 * @brief стандартная реализация интерфейса ResultsPrinter, печатает данные в
 * заданный поток в формате yaml*/

#include <Experiment.hpp>
#include <ResultsPrinter.hpp>
#include <ostream>
#include <vector>

class DefaultPrinter : public ResultsPrinter {
  void Print(const std::vector<Experiment::ExperimentResult> &,
             std::ostream &out) override;
};

#endif  // INCLUDE_DEFAULTPRINTER_HPP_
