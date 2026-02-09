#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESData_DefType.hpp>
#include <IGESData_DefList.hpp>
class Interface_UndefinedContent;
class IGESData_IGESReaderData;
class IGESData_DirPart;
class Interface_Check;
class IGESData_ParamReader;
class IGESData_IGESWriter;

class IGESData_UndefinedEntity : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESData_UndefinedEntity();

  Standard_EXPORT occ::handle<Interface_UndefinedContent> UndefinedContent() const;

  Standard_EXPORT occ::handle<Interface_UndefinedContent> ChangeableContent();

  Standard_EXPORT void SetNewContent(const occ::handle<Interface_UndefinedContent>& cont);

  Standard_EXPORT bool IsOKDirPart() const;

  Standard_EXPORT int DirStatus() const;

  Standard_EXPORT void SetOKDirPart();

  Standard_EXPORT IGESData_DefType DefLineFont() const override;

  Standard_EXPORT IGESData_DefList DefLevel() const override;

  Standard_EXPORT IGESData_DefList DefView() const override;

  Standard_EXPORT IGESData_DefType DefColor() const override;

  Standard_EXPORT bool HasSubScriptNumber() const override;

  Standard_EXPORT virtual bool ReadDir(const occ::handle<IGESData_IGESReaderData>& IR,
                                       IGESData_DirPart&                           DP,
                                       occ::handle<Interface_Check>&               ach);

  Standard_EXPORT virtual void ReadOwnParams(const occ::handle<IGESData_IGESReaderData>& IR,
                                             IGESData_ParamReader&                       PR);

  Standard_EXPORT virtual void WriteOwnParams(IGESData_IGESWriter& IW) const;

  DEFINE_STANDARD_RTTIEXT(IGESData_UndefinedEntity, IGESData_IGESEntity)

private:
  int                                     thedstat;
  occ::handle<Interface_UndefinedContent> thecont;
};
