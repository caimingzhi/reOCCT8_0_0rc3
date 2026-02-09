#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class IGESData_IGESEntity;
class Standard_NoSuchObject;
class IGESData_IGESType;

class IGESData_FileRecognizer : public Standard_Transient
{

public:
  Standard_EXPORT bool Evaluate(const IGESData_IGESType&          akey,
                                occ::handle<IGESData_IGESEntity>& res);

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Result() const;

  Standard_EXPORT void Add(const occ::handle<IGESData_FileRecognizer>& reco);

  DEFINE_STANDARD_RTTI_INLINE(IGESData_FileRecognizer, Standard_Transient)

protected:
  Standard_EXPORT IGESData_FileRecognizer();

  Standard_EXPORT void SetOK(const occ::handle<IGESData_IGESEntity>& aresult);

  Standard_EXPORT void SetKO();

  Standard_EXPORT virtual void Eval(const IGESData_IGESType& akey) = 0;

private:
  occ::handle<IGESData_IGESEntity>     theres;
  bool                                 hasnext;
  occ::handle<IGESData_FileRecognizer> thenext;
};
