#pragma once

#include <Media_Frame.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>

struct SwsContext;

class Media_Scaler : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_Scaler, Standard_Transient)
public:
  Standard_EXPORT Media_Scaler();

  Standard_EXPORT ~Media_Scaler() override;

  Standard_EXPORT void Release();

  Standard_EXPORT bool Init(const NCollection_Vec2<int>& theSrcDims,
                            int                          theSrcFormat,
                            const NCollection_Vec2<int>& theResDims,
                            int                          theResFormat);

  Standard_EXPORT bool Convert(const occ::handle<Media_Frame>& theSrc,
                               const occ::handle<Media_Frame>& theRes);

  bool IsValid() const { return mySwsContext != nullptr; }

protected:
  SwsContext*           mySwsContext;
  NCollection_Vec2<int> mySrcDims;
  int                   mySrcFormat;
  NCollection_Vec2<int> myResDims;
  int                   myResFormat;
};
