#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_DefSwitch.hpp>
#include <Interface_EntityList.hpp>
#include <Standard_Transient.hpp>
#include <IGESData_DefType.hpp>
#include <IGESData_DefList.hpp>
#include <Standard_CString.hpp>
class TCollection_HAsciiString;
class IGESData_IGESType;
class IGESData_LineFontEntity;
class IGESData_LevelListEntity;
class IGESData_ViewKindEntity;
class IGESData_TransfEntity;
class IGESData_LabelDisplayEntity;
class IGESData_ColorEntity;
class gp_GTrsf;
class Interface_EntityIterator;

class IGESData_IGESEntity : public Standard_Transient
{

public:
  Standard_EXPORT IGESData_IGESType IGESType() const;

  Standard_EXPORT int TypeNumber() const;

  Standard_EXPORT int FormNumber() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> DirFieldEntity(const int fieldnum) const;

  Standard_EXPORT bool HasStructure() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> Structure() const;

  Standard_EXPORT virtual IGESData_DefType DefLineFont() const;

  Standard_EXPORT int RankLineFont() const;

  Standard_EXPORT occ::handle<IGESData_LineFontEntity> LineFont() const;

  Standard_EXPORT virtual IGESData_DefList DefLevel() const;

  Standard_EXPORT int Level() const;

  Standard_EXPORT occ::handle<IGESData_LevelListEntity> LevelList() const;

  Standard_EXPORT virtual IGESData_DefList DefView() const;

  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> View() const;

  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> SingleView() const;

  Standard_EXPORT occ::handle<IGESData_ViewKindEntity> ViewList() const;

  Standard_EXPORT bool HasTransf() const;

  Standard_EXPORT occ::handle<IGESData_TransfEntity> Transf() const;

  Standard_EXPORT bool HasLabelDisplay() const;

  Standard_EXPORT occ::handle<IGESData_LabelDisplayEntity> LabelDisplay() const;

  Standard_EXPORT int BlankStatus() const;

  Standard_EXPORT int SubordinateStatus() const;

  Standard_EXPORT int UseFlag() const;

  Standard_EXPORT int HierarchyStatus() const;

  Standard_EXPORT int LineWeightNumber() const;

  Standard_EXPORT double LineWeight() const;

  Standard_EXPORT virtual IGESData_DefType DefColor() const;

  Standard_EXPORT int RankColor() const;

  Standard_EXPORT occ::handle<IGESData_ColorEntity> Color() const;

  Standard_EXPORT bool CResValues(const char* res1, const char* res2) const;

  Standard_EXPORT bool HasShortLabel() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ShortLabel() const;

  Standard_EXPORT virtual bool HasSubScriptNumber() const;

  Standard_EXPORT int SubScriptNumber() const;

  Standard_EXPORT void InitDirFieldEntity(const int                               fieldnum,
                                          const occ::handle<IGESData_IGESEntity>& ent);

  Standard_EXPORT void InitTransf(const occ::handle<IGESData_TransfEntity>& ent);

  Standard_EXPORT void InitView(const occ::handle<IGESData_ViewKindEntity>& ent);

  Standard_EXPORT void InitLineFont(const occ::handle<IGESData_LineFontEntity>& ent,
                                    const int                                   rank = 0);

  Standard_EXPORT void InitLevel(const occ::handle<IGESData_LevelListEntity>& ent,
                                 const int                                    val = 0);

  Standard_EXPORT void InitColor(const occ::handle<IGESData_ColorEntity>& ent, const int rank = 0);

  Standard_EXPORT void InitStatus(const int blank,
                                  const int subordinate,
                                  const int useflag,
                                  const int hierarchy);

  Standard_EXPORT void SetLabel(const occ::handle<TCollection_HAsciiString>& label,
                                const int                                    sub = -1);

  Standard_EXPORT void InitMisc(const occ::handle<IGESData_IGESEntity>&         str,
                                const occ::handle<IGESData_LabelDisplayEntity>& lab,
                                const int                                       weightnum);

  Standard_EXPORT bool HasOneParent() const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> UniqueParent() const;

  Standard_EXPORT gp_GTrsf Location() const;

  Standard_EXPORT gp_GTrsf VectorLocation() const;

  Standard_EXPORT gp_GTrsf CompoundLocation() const;

  Standard_EXPORT bool HasName() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> NameValue() const;

  Standard_EXPORT bool ArePresentAssociativities() const;

  Standard_EXPORT int NbAssociativities() const;

  Standard_EXPORT Interface_EntityIterator Associativities() const;

  Standard_EXPORT int NbTypedAssociativities(const occ::handle<Standard_Type>& atype) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TypedAssociativity(
    const occ::handle<Standard_Type>& atype) const;

  Standard_EXPORT void Associate(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT void Dissociate(const occ::handle<IGESData_IGESEntity>& ent) const;

  Standard_EXPORT bool ArePresentProperties() const;

  Standard_EXPORT int NbProperties() const;

  Standard_EXPORT Interface_EntityIterator Properties() const;

  Standard_EXPORT int NbTypedProperties(const occ::handle<Standard_Type>& atype) const;

  Standard_EXPORT occ::handle<IGESData_IGESEntity> TypedProperty(
    const occ::handle<Standard_Type>& atype,
    const int                         anum = 0) const;

  Standard_EXPORT void AddProperty(const occ::handle<IGESData_IGESEntity>& ent);

  Standard_EXPORT void RemoveProperty(const occ::handle<IGESData_IGESEntity>& ent);

  Standard_EXPORT void SetLineWeight(const double defw, const double maxw, const int gradw);

  friend class IGESData_ReadWriteModule;
  friend class IGESData_GeneralModule;
  friend class IGESData_IGESReaderTool;
  friend class IGESData_DirChecker;

  DEFINE_STANDARD_RTTIEXT(IGESData_IGESEntity, Standard_Transient)

protected:
  Standard_EXPORT IGESData_IGESEntity();

  Standard_EXPORT void InitTypeAndForm(const int typenum, const int formnum);

  Standard_EXPORT void LoadAssociativities(const Interface_EntityList& list);

  Standard_EXPORT void LoadProperties(const Interface_EntityList& list);

  Standard_EXPORT void ClearProperties();

private:
  Standard_EXPORT void Clear();

  Standard_EXPORT void AddAssociativity(const occ::handle<IGESData_IGESEntity>& ent);

  Standard_EXPORT void RemoveAssociativity(const occ::handle<IGESData_IGESEntity>& ent);

  Standard_EXPORT void ClearAssociativities();

  int                                   theType;
  int                                   theForm;
  occ::handle<IGESData_IGESEntity>      theStructure;
  IGESData_DefSwitch                    theDefLineFont;
  occ::handle<IGESData_IGESEntity>      theLineFont;
  int                                   theDefLevel;
  occ::handle<IGESData_IGESEntity>      theLevelList;
  occ::handle<IGESData_IGESEntity>      theView;
  occ::handle<IGESData_IGESEntity>      theTransf;
  occ::handle<IGESData_IGESEntity>      theLabDisplay;
  int                                   theStatusNum;
  int                                   theLWeightNum;
  double                                theLWeightVal;
  IGESData_DefSwitch                    theDefColor;
  occ::handle<IGESData_IGESEntity>      theColor;
  char                                  theRes1[9];
  char                                  theRes2[9];
  occ::handle<TCollection_HAsciiString> theShortLabel;
  int                                   theSubScriptN;
  Interface_EntityList                  theAssocs;
  Interface_EntityList                  theProps;
};
