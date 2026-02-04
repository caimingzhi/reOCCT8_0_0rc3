#pragma once

#ifdef OCCT_DEBUG
  #include <OSD_Chronometer.hpp>
  #include <TCollection_AsciiString.hpp>
  #include <Standard_OStream.hpp>

// POP pour NT
class TOPKRO : public OSD_Chronometer
{
public:
  TOPKRO(const TCollection_AsciiString& n)
      : myname(n),
        mystart(0),
        mystop(0)
  {
    myname.RightJustify(30, ' ');
  }

  virtual void Start()
  {
    mystart = 1;
    OSD_Chronometer::Start();
  }

  virtual void Stop()
  {
    OSD_Chronometer::Stop();
    mystop = 1;
  }

  void Print(Standard_OStream& OS)
  {
    double s;
    Show(s);
    OS << myname << " : ";
    if (!mystart)
      OS << "(inactif)";
    else
    {
      OS << s << " secondes";
      if (!mystop)
        OS << " (run)";
    }
  }

private:
  TCollection_AsciiString myname;
  int                     mystart, mystop;
};
#endif
