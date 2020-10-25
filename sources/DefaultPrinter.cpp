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

  out << "investigation:" << std::endl;
  out << "  travel_variant: "
      << "\"" << res[0].TravelOrder << "\"" << std::endl
      << std::endl;
  out << "  experiments:" << std::endl;
  for (std::size_t i = 0; i < res.size(); ++i) {
    out << "  - experiment:" << std::endl;
    out << "    number: " << i + 1 << std::endl;
    out << "    input_data:" << std::endl;
    out << "      buffer_size: "
        << "\"" << res[i].BufferSize / 1024 << "Kb\"" << std::endl;
    out << "    results:" << std::endl;
    out << "      duration: "
        << "\"" << res[i].Duration << "ns\"" << std::endl
        << std::endl;
  }
}
