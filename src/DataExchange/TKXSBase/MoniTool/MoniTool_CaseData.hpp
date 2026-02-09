#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
class TopoDS_Shape;
class gp_XYZ;
class gp_XY;
class Message_Msg;

class MoniTool_CaseData : public Standard_Transient
{

public:
  Standard_EXPORT MoniTool_CaseData(const char* caseid = "", const char* name = "");

  Standard_EXPORT void SetCaseId(const char* caseid);

  Standard_EXPORT void SetName(const char* name);

  Standard_EXPORT const char* CaseId() const;

  Standard_EXPORT const char* Name() const;

  Standard_EXPORT bool IsCheck() const;

  Standard_EXPORT bool IsWarning() const;

  Standard_EXPORT bool IsFail() const;

  Standard_EXPORT void ResetCheck();

  Standard_EXPORT void SetWarning();

  Standard_EXPORT void SetFail();

  Standard_EXPORT void SetChange();

  Standard_EXPORT void SetReplace(const int num);

  Standard_EXPORT void AddData(const occ::handle<Standard_Transient>& val,
                               const int                              kind,
                               const char*                            name = "");

  Standard_EXPORT void AddRaised(const Standard_Failure& theException, const char* name = "");

  Standard_EXPORT void AddShape(const TopoDS_Shape& sh, const char* name = "");

  Standard_EXPORT void AddXYZ(const gp_XYZ& aXYZ, const char* name = "");

  Standard_EXPORT void AddXY(const gp_XY& aXY, const char* name = "");

  Standard_EXPORT void AddReal(const double val, const char* name = "");

  Standard_EXPORT void AddReals(const double v1, const double v2, const char* name = "");

  Standard_EXPORT void AddCPU(const double lastCPU, const double curCPU = 0, const char* name = "");

  Standard_EXPORT double GetCPU() const;

  Standard_EXPORT bool LargeCPU(const double maxCPU,
                                const double lastCPU,
                                const double curCPU = 0) const;

  Standard_EXPORT void AddGeom(const occ::handle<Standard_Transient>& geom, const char* name = "");

  Standard_EXPORT void AddEntity(const occ::handle<Standard_Transient>& ent, const char* name = "");

  Standard_EXPORT void AddText(const char* text, const char* name = "");

  Standard_EXPORT void AddInteger(const int val, const char* name = "");

  Standard_EXPORT void AddAny(const occ::handle<Standard_Transient>& val, const char* name = "");

  Standard_EXPORT void RemoveData(const int num);

  Standard_EXPORT int NbData() const;

  Standard_EXPORT occ::handle<Standard_Transient> Data(const int nd) const;

  Standard_EXPORT bool GetData(const int                         nd,
                               const occ::handle<Standard_Type>& type,
                               occ::handle<Standard_Transient>&  val) const;

  Standard_EXPORT int Kind(const int nd) const;

  Standard_EXPORT const TCollection_AsciiString& Name(const int nd) const;

  Standard_EXPORT int NameNum(const char* name) const;

  Standard_EXPORT TopoDS_Shape Shape(const int nd) const;

  Standard_EXPORT bool XYZ(const int nd, gp_XYZ& val) const;

  Standard_EXPORT bool XY(const int nd, gp_XY& val) const;

  Standard_EXPORT bool Reals(const int nd, double& v1, double& v2) const;

  Standard_EXPORT bool Real(const int nd, double& val) const;

  Standard_EXPORT bool Text(const int nd, const char*& text) const;

  Standard_EXPORT bool Integer(const int nd, int& val) const;

  Standard_EXPORT Message_Msg Msg() const;

  Standard_EXPORT static void SetDefWarning(const char* acode);

  Standard_EXPORT static void SetDefFail(const char* acode);

  Standard_EXPORT static int DefCheck(const char* acode);

  Standard_EXPORT static void SetDefMsg(const char* casecode, const char* mesdef);

  Standard_EXPORT static const char* DefMsg(const char* casecode);

  DEFINE_STANDARD_RTTIEXT(MoniTool_CaseData, Standard_Transient)

private:
  int                                                   thecheck;
  int                                                   thesubst;
  TCollection_AsciiString                               thecase;
  TCollection_AsciiString                               thename;
  NCollection_Sequence<occ::handle<Standard_Transient>> thedata;
  NCollection_Sequence<int>                             thekind;
  NCollection_Sequence<TCollection_AsciiString>         thednam;
};
