// Copyright 2020 <Shumeev Ilja (Kam1runetzLabs) notsoserious2017@gmail.com>

#ifndef INCLUDE_TRAVELORDERS_TRAVELORDER_HPP_
#define INCLUDE_TRAVELORDERS_TRAVELORDER_HPP_

/*!
 * @brief Интерфейс классов, реализующих поведение обхода буффера для
 * эксперимента*/

#include <string>
#include <utility>

class TravelOrder {
 public:
  /*! @param aTravelOrderName название варианта обхода (поведения)
   *  @param aCurrentIndex индекс буффера, с которого начинается обход*/
  TravelOrder(std::string aTravelOrderName, std::size_t aCurrentIndex)
      : travelOrderName(std::move(aTravelOrderName)),
        currentBufferIndex(aCurrentIndex),
        bufferSize(0) {}
  virtual ~TravelOrder() = default;

  /*! @brief чисто виртуальный метод, перегружая который вы задаете алгоритм
   * вычисления следующего индекса для обхода*/
  virtual std::size_t GetNextIndex() = 0;

  /*! @brief метод, возвращающий название варианта обхода (поведения)*/
  virtual std::string TravelOrderName() const { return travelOrderName; }

  /*! @brief метод, устанавливающий текущее значение индекса буффера в начальное
   * положение*/
  virtual void SetDefaultIndex() = 0;

  /*! @brief метод, задающий размер обходимого буффера для корректной работы*/
  virtual void SetBufferSize(std::size_t buffSize) { bufferSize = buffSize; }

 protected:
  std::string travelOrderName;
  std::size_t currentBufferIndex;
  std::size_t bufferSize;
};

#endif  // INCLUDE_TRAVELORDERS_TRAVELORDER_HPP_
