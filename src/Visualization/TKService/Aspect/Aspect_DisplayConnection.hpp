#pragma once

#include <Standard_Transient.hpp>

enum Aspect_XAtom
{
  Aspect_XA_DELETE_WINDOW
};

#include <Aspect_FBConfig.hpp>

#include <TCollection_AsciiString.hpp>
#include <NCollection_DataMap.hpp>

struct Aspect_XDisplay;
struct Aspect_XVisualInfo;

class Aspect_DisplayConnection : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Aspect_DisplayConnection, Standard_Transient)
public:
  Standard_EXPORT Aspect_DisplayConnection();

  Standard_EXPORT ~Aspect_DisplayConnection() override;

  Standard_EXPORT Aspect_DisplayConnection(const TCollection_AsciiString& theDisplayName);

  Standard_EXPORT Aspect_DisplayConnection(Aspect_XDisplay* theDisplay);

  Aspect_XDisplay* GetDisplayAspect() { return myDisplay; }

  bool IsOwnDisplay() const { return myIsOwnDisplay; }

  uint64_t GetAtom(const Aspect_XAtom theAtom) const { return myAtoms.Find(theAtom); }

  const TCollection_AsciiString& GetDisplayName() { return myDisplayName; }

  Standard_EXPORT void Init(Aspect_XDisplay* theDisplay);

  Aspect_XVisualInfo* GetDefaultVisualInfo() const { return myDefVisualInfo; }

  Aspect_FBConfig GetDefaultFBConfig() const { return myDefFBConfig; }

  Standard_EXPORT void SetDefaultVisualInfo(Aspect_XVisualInfo* theVisual,
                                            Aspect_FBConfig     theFBConfig);

#ifdef X_PROTOCOL

  Aspect_DisplayConnection(Display* theDisplay)
      : Aspect_DisplayConnection((Aspect_XDisplay*)theDisplay)
  {
  }

  Display* GetDisplay() { return (Display*)myDisplay; }

  XVisualInfo* GetDefaultVisualInfoX() const { return (XVisualInfo*)myDefVisualInfo; }

  void SetDefaultVisualInfo(XVisualInfo* theVisual, Aspect_FBConfig theFBConfig)
  {
    SetDefaultVisualInfo((Aspect_XVisualInfo*)theVisual, theFBConfig);
  }

  Atom GetAtomX(const Aspect_XAtom theAtom) const { return (Atom)GetAtom(theAtom); }

  void Init(Display* theDisplay) { Init((Aspect_XDisplay*)theDisplay); }
#endif

private:
  Aspect_XDisplay*                            myDisplay;
  Aspect_XVisualInfo*                         myDefVisualInfo;
  Aspect_FBConfig                             myDefFBConfig;
  NCollection_DataMap<Aspect_XAtom, uint64_t> myAtoms;
  TCollection_AsciiString                     myDisplayName;
  bool                                        myIsOwnDisplay;

private:
  Aspect_DisplayConnection(const Aspect_DisplayConnection&)            = delete;
  Aspect_DisplayConnection& operator=(const Aspect_DisplayConnection&) = delete;
};
