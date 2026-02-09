#pragma once

#include <NCollection_List.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

class Aspect_DisplayConnection;
class Graphic3d_GraphicDriver;
class Graphic3d_GraphicDriverFactory;

class Graphic3d_GraphicDriverFactory : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_GraphicDriverFactory, Standard_Transient)
public:
  Standard_EXPORT static void RegisterFactory(
    const occ::handle<Graphic3d_GraphicDriverFactory>& theFactory,
    bool                                               theIsPreferred = false);

  Standard_EXPORT static void UnregisterFactory(const TCollection_AsciiString& theName);

  Standard_EXPORT static occ::handle<Graphic3d_GraphicDriverFactory> DefaultDriverFactory();

  Standard_EXPORT static const NCollection_List<occ::handle<Graphic3d_GraphicDriverFactory>>&
    DriverFactories();

public:
  virtual occ::handle<Graphic3d_GraphicDriver> CreateDriver(
    const occ::handle<Aspect_DisplayConnection>& theDisp) = 0;

  const TCollection_AsciiString& Name() const { return myName; }

protected:
  Standard_EXPORT Graphic3d_GraphicDriverFactory(const TCollection_AsciiString& theName);

protected:
  TCollection_AsciiString myName;
};
