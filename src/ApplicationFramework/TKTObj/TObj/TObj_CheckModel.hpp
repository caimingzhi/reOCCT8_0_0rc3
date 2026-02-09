#pragma once

#include <TObj_Model.hpp>
#include <Message_Algorithm.hpp>

class TObj_CheckModel : public Message_Algorithm
{
public:
  TObj_CheckModel(const occ::handle<TObj_Model>& theModel)
      : myModel(theModel),
        myToFix(false)
  {
  }

  void SetToFix(const bool theToFix) { myToFix = theToFix; }

  bool IsToFix() const { return myToFix; }

  const occ::handle<TObj_Model>& GetModel() const { return myModel; }

  ~TObj_CheckModel() override = default;

  virtual Standard_EXPORT bool Perform();

private:
  Standard_EXPORT bool checkReferences();

private:
  occ::handle<TObj_Model> myModel;
  bool                    myToFix;

public:
  DEFINE_STANDARD_RTTIEXT(TObj_CheckModel, Message_Algorithm)
};

#ifdef _MSC_VER
  #pragma once
#endif
