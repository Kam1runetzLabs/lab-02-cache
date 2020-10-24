//
// Created by w1ckedente on 25.10.2020.
//
#include <DefaultPrinter.hpp>

void DefaultPrinter::Print(std::vector<Experiment::ExperimentResult> res,
                           std::ostream& out) {
  if (res.empty()) {
    out << "No experiments results" << std::endl;
    return;
  }


}
