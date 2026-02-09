#pragma once

#include <OpenGl_Element.hpp>
#include <OpenGl_AspectsProgram.hpp>
#include <OpenGl_AspectsTextureSet.hpp>
#include <OpenGl_AspectsSprite.hpp>
#include <Graphic3d_Aspects.hpp>

class OpenGl_Aspects : public OpenGl_Element
{
public:
  Standard_EXPORT OpenGl_Aspects();

  Standard_EXPORT OpenGl_Aspects(const occ::handle<Graphic3d_Aspects>& theAspect);

  const occ::handle<Graphic3d_Aspects>& Aspect() const { return myAspect; }

  Standard_EXPORT void SetAspect(const occ::handle<Graphic3d_Aspects>& theAspect);

  Graphic3d_TypeOfShadingModel ShadingModel() const { return myShadingModel; }

  void SetNoLighting() { myShadingModel = Graphic3d_TypeOfShadingModel_Unlit; }

  const occ::handle<OpenGl_TextureSet>& TextureSet(const occ::handle<OpenGl_Context>& theCtx,
                                                   bool theToHighlight = false) const
  {
    const occ::handle<OpenGl_PointSprite>& aSprite  = myResSprite.Sprite(theCtx, myAspect, false);
    const occ::handle<OpenGl_PointSprite>& aSpriteA = myResSprite.Sprite(theCtx, myAspect, true);
    return myResTextureSet.TextureSet(theCtx, myAspect, aSprite, aSpriteA, theToHighlight);
  }

  const occ::handle<OpenGl_ShaderProgram>& ShaderProgramRes(
    const occ::handle<OpenGl_Context>& theCtx) const
  {
    return myResProgram.ShaderProgram(theCtx, myAspect->ShaderProgram());
  }

  float MarkerSize() const { return myResSprite.MarkerSize(); }

  bool HasPointSprite(const occ::handle<OpenGl_Context>& theCtx) const
  {
    return myResSprite.HasPointSprite(theCtx, myAspect);
  }

  bool IsDisplayListSprite(const occ::handle<OpenGl_Context>& theCtx) const
  {
    return myResSprite.IsDisplayListSprite(theCtx, myAspect);
  }

  const occ::handle<OpenGl_PointSprite>& SpriteRes(const occ::handle<OpenGl_Context>& theCtx,
                                                   bool theIsAlphaSprite) const
  {
    return myResSprite.Sprite(theCtx, myAspect, theIsAlphaSprite);
  }

  Standard_EXPORT void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const override;
  Standard_EXPORT void Release(OpenGl_Context* theContext) override;

  void SynchronizeAspects() override { SetAspect(myAspect); }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  mutable OpenGl_AspectsProgram    myResProgram;
  mutable OpenGl_AspectsTextureSet myResTextureSet;
  mutable OpenGl_AspectsSprite     myResSprite;

  occ::handle<Graphic3d_Aspects> myAspect;
  Graphic3d_TypeOfShadingModel   myShadingModel;

public:
  DEFINE_STANDARD_ALLOC
};
