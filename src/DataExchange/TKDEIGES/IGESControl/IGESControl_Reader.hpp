#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <XSControl_Reader.hpp>
#include <Standard_Integer.hpp>

enum IFSelect_PrintFail
{
  IFSelect_FailOnly,
  IFSelect_FailAndWarn
};

#include <IFSelect_PrintCount.hpp>

class IGESData_IGESModel;

class IGESControl_Reader : public XSControl_Reader
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESControl_Reader();

  Standard_EXPORT IGESControl_Reader(const occ::handle<XSControl_WorkSession>& WS,
                                     const bool                                scratch = true);

  void SetReadVisible(const bool ReadRoot);

  bool GetReadVisible() const;

  Standard_EXPORT occ::handle<IGESData_IGESModel> IGESModel() const;

  Standard_EXPORT int NbRootsForTransfer() override;

  Standard_EXPORT void PrintTransferInfo(const IFSelect_PrintFail  failwarn,
                                         const IFSelect_PrintCount mode) const;

protected:
  Standard_EXPORT DE_ShapeFixParameters GetDefaultShapeFixParameters() const override;

  Standard_EXPORT ShapeProcess::OperationsFlags GetDefaultShapeProcessFlags() const override;

private:
  bool theReadOnlyVisible;
};

inline void IGESControl_Reader::SetReadVisible(const bool ReadRoot)
{
  theReadOnlyVisible = ReadRoot;
}

inline bool IGESControl_Reader::GetReadVisible() const
{
  return theReadOnlyVisible;
}
