

#include <OpenGl_AspectsTextureSet.hpp>

#include <OpenGl_Context.hpp>
#include <OpenGl_PointSprite.hpp>
#include <OpenGl_TextureSet.hpp>

#include <Graphic3d_TextureParams.hpp>

void OpenGl_AspectsTextureSet::Release(OpenGl_Context* theCtx)
{
  if (myTextures[0].IsNull())
  {
    return;
  }

  if (!myTextures[1].IsNull())
  {

    myTextures[1]->InitZero();
  }

  for (OpenGl_TextureSet::Iterator aTextureIter(myTextures[0]); aTextureIter.More();
       aTextureIter.Next())
  {
    occ::handle<OpenGl_Texture>& aTextureRes = aTextureIter.ChangeValue();
    if (aTextureRes.IsNull())
    {
      continue;
    }

    if (theCtx != nullptr)
    {
      if (aTextureRes->ResourceId().IsEmpty())
      {
        theCtx->DelayedRelease(aTextureRes);
      }
      else
      {

        const TCollection_AsciiString aName = aTextureRes->ResourceId();
        aTextureRes.Nullify();
        theCtx->ReleaseResource(aName, true);
      }
    }
    aTextureRes.Nullify();
  }
  myIsTextureReady = false;
}

void OpenGl_AspectsTextureSet::UpdateRediness(const occ::handle<Graphic3d_Aspects>& theAspect)
{
  const occ::handle<Graphic3d_TextureSet>& aNewTextureSet = theAspect->TextureSet();

  const int aNbTexturesOld = !myTextures[0].IsNull() ? myTextures[0]->Size() : 0;
  int       aNbTexturesNew =
    !aNewTextureSet.IsNull() && theAspect->ToMapTexture() ? aNewTextureSet->Size() : 0;
  if (theAspect->IsMarkerSprite())
  {
    ++aNbTexturesNew;
  }

  if (aNbTexturesOld != aNbTexturesNew)
  {
    myIsTextureReady = false;
    return;
  }
  if (aNbTexturesOld == 0 || !theAspect->ToMapTexture())
  {
    return;
  }

  Graphic3d_TextureSet::Iterator aTextureIter(aNewTextureSet);
  OpenGl_TextureSet::Iterator    aResIter(myTextures[0]);
  for (; aTextureIter.More(); aResIter.Next(), aTextureIter.Next())
  {
    const occ::handle<OpenGl_Texture>&       aResource = aResIter.Value();
    const occ::handle<Graphic3d_TextureMap>& aTexture  = aTextureIter.Value();
    if (aTexture.IsNull() != aResource.IsNull())
    {
      myIsTextureReady = false;
      return;
    }
    else if (aTexture.IsNull())
    {
      continue;
    }

    const TCollection_AsciiString& aTextureKey = aTexture->GetId();
    if (aTextureKey.IsEmpty() || aResource->ResourceId() != aTextureKey)
    {
      myIsTextureReady = false;
      return;
    }
    else if (aResource->Revision() != aTexture->Revision())
    {
      myIsTextureReady = false;
      return;
    }
    else
    {

      aResource->Sampler()->SetParameters(aTexture->GetParams());
      aResIter.ChangeUnit() = aResource->Sampler()->Parameters()->TextureUnit();
    }
  }
}

void OpenGl_AspectsTextureSet::build(const occ::handle<OpenGl_Context>&     theCtx,
                                     const occ::handle<Graphic3d_Aspects>&  theAspect,
                                     const occ::handle<OpenGl_PointSprite>& theSprite,
                                     const occ::handle<OpenGl_PointSprite>& theSpriteA)
{
  const occ::handle<Graphic3d_TextureSet>& aNewTextureSet = theAspect->TextureSet();

  const bool hasSprite      = theAspect->IsMarkerSprite();
  const int  aNbTexturesOld = !myTextures[0].IsNull() ? myTextures[0]->Size() : 0;
  int        aNbTexturesNew =
    !aNewTextureSet.IsNull() && theAspect->ToMapTexture() ? aNewTextureSet->Size() : 0;
  if (hasSprite)
  {
    ++aNbTexturesNew;
  }

  if (aNbTexturesOld != aNbTexturesNew)
  {
    Release(theCtx.get());
    if (aNbTexturesNew > 0)
    {
      myTextures[0] = new OpenGl_TextureSet(aNbTexturesNew);
    }
    else
    {
      myTextures[0].Nullify();
      myTextures[1].Nullify();
    }
  }
  if (myTextures[0].IsNull())
  {
    return;
  }

  if (theSprite == theSpriteA)
  {
    myTextures[1].Nullify();
  }
  else
  {
    if (myTextures[1].IsNull() || myTextures[1]->Size() != myTextures[0]->Size())
    {
      myTextures[1] = new OpenGl_TextureSet(aNbTexturesNew);
    }
    else
    {
      myTextures[1]->InitZero();
    }
  }

  int& aTextureSetBits = myTextures[0]->ChangeTextureSetBits();
  aTextureSetBits      = Graphic3d_TextureSetBits_NONE;
  int aPrevTextureUnit = -1;
  if (theAspect->ToMapTexture())
  {
    Graphic3d_TextureSet::Iterator aTextureIter(aNewTextureSet);
    OpenGl_TextureSet::Iterator    aResIter0(myTextures[0]);
    for (; aTextureIter.More(); aResIter0.Next(), aTextureIter.Next())
    {
      occ::handle<OpenGl_Texture>&             aResource = aResIter0.ChangeValue();
      const occ::handle<Graphic3d_TextureMap>& aTexture  = aTextureIter.Value();
      if (!aResource.IsNull())
      {
        if (!aTexture.IsNull() && aTexture->GetId() == aResource->ResourceId()
            && aTexture->Revision() != aResource->Revision())
        {
          if (aResource->Init(theCtx, aTexture))
          {
            aResIter0.ChangeUnit() = aResource->Sampler()->Parameters()->TextureUnit();
            if (aResIter0.Unit() < aPrevTextureUnit)
            {
              throw Standard_ProgramError(
                "Graphic3d_TextureMap defines texture units in non-ascending order");
            }
            aPrevTextureUnit = aResIter0.Unit();
            aResource->Sampler()->SetParameters(aTexture->GetParams());
            aResource->SetRevision(aTexture->Revision());
          }
        }

        if (aResource->ResourceId().IsEmpty())
        {
          theCtx->DelayedRelease(aResource);
          aResource.Nullify();
        }
        else
        {
          const TCollection_AsciiString aTextureKey = aResource->ResourceId();
          aResource.Nullify();
          theCtx->ReleaseResource(aTextureKey, true);
        }
      }

      if (!aTexture.IsNull())
      {
        const TCollection_AsciiString& aTextureKeyNew = aTexture->GetId();
        if (aTextureKeyNew.IsEmpty()
            || !theCtx->GetResource<occ::handle<OpenGl_Texture>>(aTextureKeyNew, aResource))
        {
          aResource = new OpenGl_Texture(aTextureKeyNew, aTexture->GetParams());

          if (aResource->Init(theCtx, aTexture))
          {
            aResource->SetRevision(aTexture->Revision());
          }
          if (!aTextureKeyNew.IsEmpty())
          {
            theCtx->ShareResource(aTextureKeyNew, aResource);
          }
        }
        else
        {
          if (aTexture->Revision() != aResource->Revision())
          {
            if (aResource->Init(theCtx, aTexture))
            {
              aResource->SetRevision(aTexture->Revision());
            }
          }
          aResource->Sampler()->SetParameters(aTexture->GetParams());
        }

        const Graphic3d_TextureUnit aTexUnit = aResource->Sampler()->Parameters()->TextureUnit();
        aResIter0.ChangeUnit()               = aTexUnit;
        if (aResIter0.Unit() < aPrevTextureUnit)
        {
          throw Standard_ProgramError(
            "Graphic3d_TextureMap defines texture units in non-ascending order");
        }
        aPrevTextureUnit = aResIter0.Unit();
        if (aTexUnit >= Graphic3d_TextureUnit_0 && aTexUnit <= Graphic3d_TextureUnit_5)
        {
          aTextureSetBits |= (1 << int(aTexUnit));
        }
      }
    }
  }

  if (hasSprite)
  {
    myTextures[0]->ChangeLast()     = theSprite;
    myTextures[0]->ChangeLastUnit() = theCtx->SpriteTextureUnit();

    if (!theSprite.IsNull())
    {
      theSprite->Sampler()->Parameters()->SetTextureUnit(theCtx->SpriteTextureUnit());
    }
    if (!theSpriteA.IsNull())
    {
      theSpriteA->Sampler()->Parameters()->SetTextureUnit(theCtx->SpriteTextureUnit());
    }
  }
  if (myTextures[1].IsNull())
  {
    return;
  }

  myTextures[1]->ChangeTextureSetBits() = aTextureSetBits;
  for (OpenGl_TextureSet::Iterator aResIter0(myTextures[0]), aResIter1(myTextures[1]);
       aResIter0.More();
       aResIter0.Next(), aResIter1.Next())
  {
    aResIter1.ChangeValue() = aResIter0.Value();
    aResIter1.ChangeUnit()  = aResIter0.Unit();
  }
  if (hasSprite)
  {
    myTextures[1]->ChangeLast()     = theSpriteA;
    myTextures[1]->ChangeLastUnit() = theCtx->SpriteTextureUnit();
  }
}
