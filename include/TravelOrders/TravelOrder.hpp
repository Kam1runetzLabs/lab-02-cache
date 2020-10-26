// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_TRAVELORDERS_TRAVELORDER_HPP_
#define INCLUDE_TRAVELORDERS_TRAVELORDER_HPP_

#include <string>
#include <utility>

class TravelOrder {
 public:
  TravelOrder(std::string aTravelOrderName, std::size_t aCurrentIndex)
      : travelOrderName(std::move(aTravelOrderName)),
        currentBufferIndex(aCurrentIndex), bufferSize(0) {}
  virtual ~TravelOrder() = default;

  virtual std::size_t GetNextIndex() = 0;

  virtual std::string TravelOrderName() const { return travelOrderName; }

  virtual void SetDefaultIndex() = 0;

  virtual void SetBufferSize(std::size_t buffSize) { bufferSize = buffSize; };

 protected:
  std::string travelOrderName;
  std::size_t currentBufferIndex;
  std::size_t bufferSize;
};

#endif  // INCLUDE_TRAVELORDERS_TRAVELORDER_HPP_
