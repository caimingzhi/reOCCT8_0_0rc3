#pragma once

#include <Standard.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <IFSelect_ReturnStatus.hpp>
class IFSelect_SessionPilot;

class IFSelect_Activator : public Standard_Transient
{

public:
  Standard_EXPORT static void Adding(const occ::handle<IFSelect_Activator>& actor,
                                     const int                              number,
                                     const char*                            command,
                                     const int                              mode);

  Standard_EXPORT void Add(const int number, const char* command) const;

  Standard_EXPORT void AddSet(const int number, const char* command) const;

  Standard_EXPORT static void Remove(const char* command);

  Standard_EXPORT static bool Select(const char*                      command,
                                     int&                             number,
                                     occ::handle<IFSelect_Activator>& actor);

  Standard_EXPORT static int Mode(const char* command);

  Standard_EXPORT static occ::handle<NCollection_HSequence<TCollection_AsciiString>> Commands(
    const int   mode    = -1,
    const char* command = "");

  Standard_EXPORT virtual IFSelect_ReturnStatus Do(
    const int                                 number,
    const occ::handle<IFSelect_SessionPilot>& pilot) = 0;

  Standard_EXPORT virtual const char* Help(const int number) const = 0;

  Standard_EXPORT const char* Group() const;

  Standard_EXPORT const char* File() const;

  Standard_EXPORT void SetForGroup(const char* group, const char* file = "");

  DEFINE_STANDARD_RTTIEXT(IFSelect_Activator, Standard_Transient)

protected:
  Standard_EXPORT IFSelect_Activator();

private:
  TCollection_AsciiString thegroup;
  TCollection_AsciiString thefile;
};
