#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_Integer.hpp>
#include <TDF_Label.hpp>
#include <NCollection_List.hpp>
class TFunction_Logbook;

class TFunction_Driver : public Standard_Transient
{

public:
  Standard_EXPORT void Init(const TDF_Label& L);

  TDF_Label Label() const;

  Standard_EXPORT virtual void Validate(occ::handle<TFunction_Logbook>& log) const;

  Standard_EXPORT virtual bool MustExecute(const occ::handle<TFunction_Logbook>& log) const;

  Standard_EXPORT virtual int Execute(occ::handle<TFunction_Logbook>& log) const = 0;

  Standard_EXPORT virtual void Arguments(NCollection_List<TDF_Label>& args) const;

  Standard_EXPORT virtual void Results(NCollection_List<TDF_Label>& res) const;

  DEFINE_STANDARD_RTTIEXT(TFunction_Driver, Standard_Transient)

protected:
  Standard_EXPORT TFunction_Driver();

private:
  TDF_Label myLabel;
};

inline TDF_Label TFunction_Driver::Label() const
{
  return myLabel;
}
