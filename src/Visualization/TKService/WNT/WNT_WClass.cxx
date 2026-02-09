

#if defined(_WIN32)
  #include <windows.h>
#endif

#include <WNT_WClass.hpp>

#include <TCollection_ExtendedString.hpp>
#include <WNT_ClassDefinitionError.hpp>
#include <WNT_Window.hpp>

#if defined(_WIN32) && !defined(OCCT_UWP)

IMPLEMENT_STANDARD_RTTIEXT(WNT_WClass, Standard_Transient)

WNT_WClass::WNT_WClass(const TCollection_AsciiString& theClassName,
                       void* const                    theWndProc,
                       const unsigned int             theStyle,
                       const int                      theClassExtra,
                       const int                      theWindowExtra,
                       const Aspect_Handle            theCursor,
                       const Aspect_Handle            theIcon,
                       const TCollection_AsciiString& theMenuName)
    : myClassName(theClassName),
      myAppInstance(GetModuleHandleW(NULL)),
      myWndProc(NULL)
{
  const TCollection_ExtendedString aClassNameW(theClassName);
  const TCollection_ExtendedString aMenuNameW(theMenuName);
  WNDCLASSW                        aWinClass;
  aWinClass.style         = (UINT)theStyle;
  aWinClass.lpfnWndProc   = theWndProc != NULL ? (WNDPROC)theWndProc : DefWindowProcW;
  aWinClass.cbClsExtra    = theClassExtra;
  aWinClass.cbWndExtra    = theWindowExtra;
  aWinClass.hInstance     = (HINSTANCE)myAppInstance;
  aWinClass.hIcon         = theIcon != NULL ? (HICON)theIcon : LoadIcon(NULL, IDI_APPLICATION);
  aWinClass.hCursor       = theCursor != NULL ? (HCURSOR)theCursor : LoadCursor(NULL, IDC_NO);
  aWinClass.hbrBackground = 0;
  aWinClass.lpszMenuName  = !aMenuNameW.IsEmpty() ? aMenuNameW.ToWideString() : NULL;
  aWinClass.lpszClassName = aClassNameW.ToWideString();
  if (!RegisterClassW(&aWinClass))
  {
    myClassName.Clear();
    throw WNT_ClassDefinitionError("Unable to register window class");
  }
  myWndProc = (void*)aWinClass.lpfnWndProc;
}

WNT_WClass::~WNT_WClass()
{
  if (!myClassName.IsEmpty())
  {
    const TCollection_ExtendedString aClassNameW(myClassName);
    UnregisterClassW(aClassNameW.ToWideString(), (HINSTANCE)myAppInstance);
  }
}

#endif
