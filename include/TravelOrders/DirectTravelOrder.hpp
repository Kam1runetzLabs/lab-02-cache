// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_TRAVELORDERS_DIRECTTRAVELORDER_HPP_
#define INCLUDE_TRAVELORDERS_DIRECTTRAVELORDER_HPP_

#include <TravelOrders/TravelOrder.hpp>

class DirectTravelOrder : public TravelOrder {
 public:
  DirectTravelOrder();
  ~DirectTravelOrder() override = default;
  std::size_t GetNextIndex() override;
  void SetDefaultIndex() override;
};

#endif  // INCLUDE_TRAVELORDERS_DIRECTTRAVELORDER_HPP_
