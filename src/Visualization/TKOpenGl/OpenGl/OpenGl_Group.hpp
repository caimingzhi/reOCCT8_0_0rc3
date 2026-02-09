#pragma once

#include <Graphic3d_Group.hpp>
#include <Graphic3d_Structure.hpp>

#include <OpenGl_Aspects.hpp>
#include <OpenGl_Element.hpp>

class OpenGl_Structure;

struct OpenGl_ElementNode
{
  OpenGl_Element*     elem;
  OpenGl_ElementNode* next;
  DEFINE_STANDARD_ALLOC
};

class OpenGl_Group : public Graphic3d_Group
{
public:
  Standard_EXPORT OpenGl_Group(const occ::handle<Graphic3d_Structure>& theStruct);

  Standard_EXPORT void Clear(const bool theToUpdateStructureMgr) override;

  occ::handle<Graphic3d_Aspects> Aspects() const override
  {
    return myAspects != nullptr ? myAspects->Aspect() : occ::handle<Graphic3d_Aspects>();
  }

  bool HasPersistence() const
  {
    return !myTrsfPers.IsNull()
           || (myStructure != nullptr && !myStructure->TransformPersistence().IsNull());
  }

  Standard_EXPORT void SetGroupPrimitivesAspect(
    const occ::handle<Graphic3d_Aspects>& theAspect) override;

  Standard_EXPORT void SetPrimitivesAspect(
    const occ::handle<Graphic3d_Aspects>& theAspect) override;

  Standard_EXPORT void SynchronizeAspects() override;

  Standard_EXPORT void ReplaceAspects(
    const NCollection_DataMap<occ::handle<Graphic3d_Aspects>, occ::handle<Graphic3d_Aspects>>&
      theMap) override;

  Standard_EXPORT void AddPrimitiveArray(const Graphic3d_TypeOfPrimitiveArray      theType,
                                         const occ::handle<Graphic3d_IndexBuffer>& theIndices,
                                         const occ::handle<Graphic3d_Buffer>&      theAttribs,
                                         const occ::handle<Graphic3d_BoundBuffer>& theBounds,
                                         const bool theToEvalMinMax) override;

  Standard_EXPORT void AddText(const occ::handle<Graphic3d_Text>& theTextParams,
                               const bool                         theToEvalMinMax) override;

  Standard_EXPORT void SetFlippingOptions(const bool    theIsEnabled,
                                          const gp_Ax2& theRefPlane) override;

  Standard_EXPORT void SetStencilTestOptions(const bool theIsEnabled) override;

public:
  OpenGl_Structure* GlStruct() const
  {
    return (OpenGl_Structure*)(myStructure->CStructure().operator->());
  }

  Standard_EXPORT void AddElement(OpenGl_Element* theElem);

  Standard_EXPORT virtual void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const;
  Standard_EXPORT virtual void Release(const occ::handle<OpenGl_Context>& theGlCtx);

  const OpenGl_ElementNode* FirstNode() const { return myFirst; }

  const OpenGl_Aspects* GlAspects() const { return myAspects; }

  bool IsRaytracable() const { return myIsRaytracable; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT ~OpenGl_Group() override;

private:
  Standard_EXPORT bool renderFiltered(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                      OpenGl_Element*                      theElement) const;

protected:
  OpenGl_Aspects*     myAspects;
  OpenGl_ElementNode* myFirst;
  OpenGl_ElementNode* myLast;
  bool                myIsRaytracable;

public:
  DEFINE_STANDARD_RTTIEXT(OpenGl_Group, Graphic3d_Group)
};
