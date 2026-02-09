#ifdef OCCT_DEBUG

  #include <TopOpeBRep_traceSIFF.hpp>
  #include <stdio.h>

TopOpeBRep_traceSIFF::TopOpeBRep_traceSIFF()
{
  Reset();
}

void TopOpeBRep_traceSIFF::Reset()
{
  mybrep1    = "";
  mybrep2    = "";
  myfilename = "";
  myopen     = false;
}

void TopOpeBRep_traceSIFF::Set(const bool b, int n, char** a)
{
  if (n < 3 || !b || a == NULL)
  {
    Reset();
    return;
  }
  mybrep1    = a[0];
  mybrep2    = a[1];
  myfilename = a[2];
}

void TopOpeBRep_traceSIFF::Set(const TCollection_AsciiString& brep1,
                               const TCollection_AsciiString& brep2,
                               const TCollection_AsciiString& filename)
{
  mybrep1    = brep1;
  mybrep2    = brep2;
  myfilename = filename;
}

TCollection_AsciiString TopOpeBRep_traceSIFF::Name1(const int I) const
{
  TCollection_AsciiString s = mybrep1 + "_" + I;
  return s;
}

TCollection_AsciiString TopOpeBRep_traceSIFF::Name2(const int I) const
{
  TCollection_AsciiString s = mybrep2 + "_" + I;
  return s;
}

const TCollection_AsciiString& TopOpeBRep_traceSIFF::File() const
{
  return myfilename;
}

bool TopOpeBRep_traceSIFF::Start(const TCollection_AsciiString& s, Standard_OStream& OS)
{
  const char* cs = myfilename.ToCString();
  myopen         = true;
  if (!myfilebuf.open(cs, std::ios::out))
  {
    myopen = false;
  }
  if (!myopen)
  {
    return myopen;
  }
  std::ostream osfic(&myfilebuf);
  osfic.precision(15);
  if (s.Length())
  {
    OS << s << myfilename << std::endl;
  }
  return myopen;
}

void TopOpeBRep_traceSIFF::Add(const int I1, const int I2)
{
  if (!myopen)
  {
    return;
  }
  TCollection_AsciiString n1 = Name1(I1);
  TCollection_AsciiString n2 = Name2(I2);
  std::ostream            osfic(&myfilebuf);
  osfic << n1 << " " << n2 << "\n";
}

void TopOpeBRep_traceSIFF::End(const TCollection_AsciiString& s, Standard_OStream& OS)
{
  if (!myopen)
  {
    return;
  }
  if (s.Length())
  {
    OS << s << myfilename << std::endl;
  }
  myopen = false;
}

TopOpeBRep_traceSIFF SIFF;

Standard_EXPORT void TopOpeBRep_SettraceSIFF(const bool b, int n, char** a)
{
  SIFF.Set(b, n, a);
}

Standard_EXPORT bool TopOpeBRep_GettraceSIFF()
{
  bool b = (SIFF.File().Length() != 0);
  return b;
}

#endif
