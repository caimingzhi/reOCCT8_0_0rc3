#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <IGESData_DirPart.hpp>
#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <IGESData_ReadStage.hpp>
#include <Interface_LineBuffer.hpp>
#include <Interface_FloatWriter.hpp>
#include <Standard_CString.hpp>
#include <Standard_OStream.hpp>

class IGESData_IGESModel;
class IGESData_Protocol;
class IGESData_GlobalSection;
class IGESData_IGESEntity;
class TCollection_HAsciiString;
class gp_XY;
class gp_XYZ;

class IGESData_IGESWriter
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESData_IGESWriter(const occ::handle<IGESData_IGESModel>& amodel);

  Standard_EXPORT IGESData_IGESWriter();

  Standard_EXPORT IGESData_IGESWriter(const IGESData_IGESWriter& other);

  Standard_EXPORT Interface_FloatWriter& FloatWriter();

  Standard_EXPORT int& WriteMode();

  Standard_EXPORT void SendStartLine(const char* startline);

  Standard_EXPORT void SendModel(const occ::handle<IGESData_Protocol>& protocol);

  Standard_EXPORT void SectionS();

  Standard_EXPORT void SectionG(const IGESData_GlobalSection& header);

  Standard_EXPORT void SectionsDP();

  Standard_EXPORT void SectionT();

  Standard_EXPORT void DirPart(const occ::handle<IGESData_IGESEntity>& anent);

  Standard_EXPORT void OwnParams(const occ::handle<IGESData_IGESEntity>& anent);

  Standard_EXPORT void Associativities(const occ::handle<IGESData_IGESEntity>& anent);

  Standard_EXPORT void Properties(const occ::handle<IGESData_IGESEntity>& anent);

  Standard_EXPORT void EndEntity();

  Standard_EXPORT void SendVoid();

  Standard_EXPORT void Send(const int val);

  Standard_EXPORT void SendBoolean(const bool val);

  Standard_EXPORT void Send(const double val);

  Standard_EXPORT void Send(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void Send(const occ::handle<IGESData_IGESEntity>& val,
                            const bool                              negative = false);

  template <class T>
  void Send(const occ::handle<T>& val,
            bool                  negative = false,
            typename opencascade::std::enable_if<
              opencascade::std::is_base_of<IGESData_IGESEntity, T>::value>::type* = nullptr)
  {
    Send((const occ::handle<IGESData_IGESEntity>&)val, negative);
  }

  Standard_EXPORT void SendString(const occ::handle<TCollection_HAsciiString>& val);

  Standard_EXPORT void Send(const gp_XY& val);

  Standard_EXPORT void Send(const gp_XYZ& val);

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  SectionStrings(const int numsec) const;

  Standard_EXPORT bool Print(Standard_OStream& S) const;

private:
  Standard_EXPORT void AddString(const occ::handle<TCollection_HAsciiString>& val,
                                 const int                                    more = 0);

  Standard_EXPORT void AddString(const char* val, const int lnval = 0, const int more = 0);

  Standard_EXPORT void AddChar(const char val, const int more = 0);

private:
  occ::handle<IGESData_IGESModel>                                           themodel;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thestar;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thehead;
  char                                                                      thesep;
  char                                                                      theendm;
  NCollection_Array1<IGESData_DirPart>                                      thedirs;
  NCollection_Array1<int>                                                   thepnum;
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thepars;
  int                                                                       thesect;
  IGESData_ReadStage                                                        thestep;
  Interface_LineBuffer                                                      thecurr;
  int                                                                       themodew;
  Interface_FloatWriter                                                     thefloatw;
};
