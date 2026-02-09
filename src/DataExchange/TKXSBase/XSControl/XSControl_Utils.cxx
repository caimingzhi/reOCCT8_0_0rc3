

#include <BRep_Builder.hpp>
#include <BRepTools.hpp>
#include <TCollection_HAsciiString.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <MoniTool_Macros.hpp>
#include <Interface_MSG.hpp>
#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Standard_Transient.hpp>
#include <Standard_TypeMismatch.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TCollection_HExtendedString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Compound.hpp>
#include <TopoDS_HShape.hpp>
#include <TopoDS_Iterator.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Shell.hpp>
#include <TopoDS_Wire.hpp>
#include <Transfer_SimpleBinderOfTransient.hpp>
#include <TransferBRep.hpp>
#include <TransferBRep_ShapeBinder.hpp>
#include <TransferBRep_ShapeMapper.hpp>
#include <XSControl_Utils.hpp>

static TCollection_AsciiString    bufasc;
static TCollection_ExtendedString bufext;
static const char16_t*            voidext = {nullptr};

XSControl_Utils::XSControl_Utils() = default;

void XSControl_Utils::TraceLine(const char* line) const
{
  Message_Messenger::StreamBuffer sout = Message::SendInfo();
  sout << line << std::endl;
}

void XSControl_Utils::TraceLines(const occ::handle<Standard_Transient>& lines) const
{
  Message_Messenger::StreamBuffer sout = Message::SendInfo();
  int                             i, nb;
  DeclareAndCast(NCollection_HSequence<occ::handle<TCollection_HAsciiString>>, linha, lines);
  if (!linha.IsNull())
  {
    nb = linha->Length();
    for (i = 1; i <= nb; i++)
      if (!linha->Value(i).IsNull())
        sout << linha->Value(i)->ToCString() << std::endl;
    return;
  }
  DeclareAndCast(NCollection_HSequence<TCollection_AsciiString>, lina, lines);
  if (!lina.IsNull())
  {
    nb = lina->Length();
    for (i = 1; i <= nb; i++)
      sout << lina->Value(i).ToCString() << std::endl;
    return;
  }
  DeclareAndCast(NCollection_HSequence<occ::handle<TCollection_HExtendedString>>, linhe, lines);
  if (!linhe.IsNull())
  {
    nb = linhe->Length();
    for (i = 1; i <= nb; i++)
      if (!linhe->Value(i).IsNull())
        sout << linhe->Value(i)->String() << std::endl;
    return;
  }
  DeclareAndCast(NCollection_HSequence<TCollection_ExtendedString>, linee, lines);
  if (!linee.IsNull())
  {
    nb = linee->Length();
    for (i = 1; i <= nb; i++)
      sout << linee->Value(i) << std::endl;
    return;
  }
  DeclareAndCast(TCollection_HAsciiString, lin1a, lines);
  if (!lin1a.IsNull())
    sout << lin1a->String();
  DeclareAndCast(TCollection_HExtendedString, lin1e, lines);
  if (!lin1e.IsNull())
    sout << lin1e->String();
}

bool XSControl_Utils::IsKind(const occ::handle<Standard_Transient>& item,
                             const occ::handle<Standard_Type>&      what) const
{
  if (item.IsNull())
    return false;
  if (what.IsNull())
    return false;
  return item->IsKind(what);
}

const char* XSControl_Utils::TypeName(const occ::handle<Standard_Transient>& item,
                                      const bool                             nopk) const
{
  if (item.IsNull())
    return "";
  DeclareAndCast(Standard_Type, atype, item);
  if (atype.IsNull())
    atype = item->DynamicType();
  const char* tn = atype->Name();
  if (!nopk)
    return tn;
  for (int i = 0; tn[i] != '\0'; i++)
  {
    if (tn[i] == '_')
      return &tn[i + 1];
  }
  return tn;
}

occ::handle<Standard_Transient> XSControl_Utils::TraValue(
  const occ::handle<Standard_Transient>& seqval,
  const int                              num) const
{
  occ::handle<Standard_Transient> val;
  if (num < 1)
    return val;
  if (seqval.IsNull())
    return val;
  DeclareAndCast(NCollection_HSequence<occ::handle<TCollection_HAsciiString>>, seqs, seqval);
  if (!seqs.IsNull())
  {
    if (num <= seqs->Length())
      val = seqs->Value(num);
    return val;
  }
  DeclareAndCast(NCollection_HSequence<occ::handle<Standard_Transient>>, seqt, seqval);
  if (!seqt.IsNull())
  {
    if (num <= seqt->Length())
      val = seqt->Value(num);
    return val;
  }

  return val;
}

occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> XSControl_Utils::NewSeqTra()
  const
{
  return new NCollection_HSequence<occ::handle<Standard_Transient>>();
}

void XSControl_Utils::AppendTra(
  const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& seqval,
  const occ::handle<Standard_Transient>&                                     traval) const
{
  seqval->Append(traval);
}

const char* XSControl_Utils::DateString(const int yy,
                                        const int mm,
                                        const int dd,
                                        const int hh,
                                        const int mn,
                                        const int ss) const
{
  char ladate[50] = {};
  Interface_MSG::TDate(ladate, yy, mm, dd, hh, mn, ss);
  bufasc.Clear();
  bufasc.AssignCat(ladate);
  return bufasc.ToCString();
}

void XSControl_Utils::DateValues(const char* text,
                                 int&        yy,
                                 int&        mm,
                                 int&        dd,
                                 int&        hh,
                                 int&        mn,
                                 int&        ss) const
{
  Interface_MSG::NDate(text, yy, mm, dd, hh, mn, ss);
}

const char* XSControl_Utils::ToCString(const occ::handle<TCollection_HAsciiString>& strval) const
{

  const char* astr = (const char*)(strval.IsNull() ? "" : strval->ToCString());
  return astr;
}

const char* XSControl_Utils::ToCString(const TCollection_AsciiString& strval) const
{
  return strval.ToCString();
}

occ::handle<TCollection_HAsciiString> XSControl_Utils::ToHString(const char* strcon) const
{
  return new TCollection_HAsciiString(strcon);
}

TCollection_AsciiString XSControl_Utils::ToAString(const char* strcon) const
{
  return TCollection_AsciiString(strcon);
}

const char16_t* XSControl_Utils::ToEString(
  const occ::handle<TCollection_HExtendedString>& strval) const
{
  return (strval.IsNull() ? voidext : strval->ToExtString());
}

const char16_t* XSControl_Utils::ToEString(const TCollection_ExtendedString& strval) const
{
  return strval.ToExtString();
}

occ::handle<TCollection_HExtendedString> XSControl_Utils::ToHString(const char16_t* strcon) const
{
  return new TCollection_HExtendedString(strcon);
}

TCollection_ExtendedString XSControl_Utils::ToXString(const char16_t* strcon) const
{
  return TCollection_ExtendedString(strcon);
}

const char16_t* XSControl_Utils::AsciiToExtended(const char* str) const
{
  bufext.Clear();
  bufext = TCollection_ExtendedString(str);
  return bufext.ToExtString();
}

bool XSControl_Utils::IsAscii(const char16_t* str) const
{
  bufext.Clear();
  bufext.AssignCat(str);
  return bufext.IsAscii();
}

const char* XSControl_Utils::ExtendedToAscii(const char16_t* str) const
{
  bufext.Clear();
  bufext.AssignCat(str);
  bufasc.Clear();
  int i, nb = bufext.Length();
  for (i = 1; i <= nb; i++)
  {
    int unext  = bufext.Value(i);
    unext      = unext & 127;
    char uncar = char(unext);
    bufasc.AssignCat(uncar);
  }
  return bufasc.ToCString();
}

const char* XSControl_Utils::CStrValue(const occ::handle<Standard_Transient>& list,
                                       const int                              num) const
{
  DeclareAndCast(NCollection_HSequence<occ::handle<TCollection_HAsciiString>>, linha, list);
  if (!linha.IsNull())
  {

    const char* astr = (const char*)(num > linha->Length() ? "" : linha->Value(num)->ToCString());
    return astr;
  }

  DeclareAndCast(NCollection_HSequence<TCollection_AsciiString>, lina, list);
  if (!lina.IsNull())
  {

    const char* astr = (const char*)(num > lina->Length() ? "" : lina->Value(num).ToCString());
    return astr;
  }

  DeclareAndCast(NCollection_HSequence<occ::handle<TCollection_HExtendedString>>, linhe, list);
  if (!linhe.IsNull())
  {

    const char* astr =
      (const char*)(num > linhe->Length() ? "" : ExtendedToAscii(linhe->Value(num)->ToExtString()));
    return astr;
  }

  DeclareAndCast(NCollection_HSequence<TCollection_ExtendedString>, linee, list);
  if (!linee.IsNull())
  {

    const char* astr =
      (const char*)(num > linee->Length() ? "" : ExtendedToAscii(linee->Value(num).ToExtString()));
    return astr;
  }

  DeclareAndCast(TCollection_HAsciiString, lin1a, list);
  if (!lin1a.IsNull())
    return lin1a->ToCString();
  DeclareAndCast(TCollection_HExtendedString, lin1e, list);
  if (!lin1e.IsNull())
    return ExtendedToAscii(lin1e->ToExtString());
  return "";
}

const char16_t* XSControl_Utils::EStrValue(const occ::handle<Standard_Transient>& list,
                                           const int                              num) const
{
  DeclareAndCast(NCollection_HSequence<occ::handle<TCollection_HAsciiString>>, linha, list);
  if (!linha.IsNull())
    return (num > linha->Length() ? voidext : AsciiToExtended(linha->Value(num)->ToCString()));

  DeclareAndCast(NCollection_HSequence<TCollection_AsciiString>, lina, list);
  if (!lina.IsNull())
    (num > lina->Length() ? voidext : AsciiToExtended(lina->Value(num).ToCString()));

  DeclareAndCast(NCollection_HSequence<occ::handle<TCollection_HExtendedString>>, linhe, list);
  if (!linhe.IsNull())
    return (num > linhe->Length() ? voidext : linhe->Value(num)->ToExtString());

  DeclareAndCast(NCollection_HSequence<TCollection_ExtendedString>, linee, list);
  if (!linee.IsNull())
    return (num > linee->Length() ? voidext : linee->Value(num).ToExtString());

  DeclareAndCast(TCollection_HAsciiString, lin1a, list);
  if (!lin1a.IsNull())
    return AsciiToExtended(lin1a->ToCString());
  DeclareAndCast(TCollection_HExtendedString, lin1e, list);
  if (!lin1e.IsNull())
    return lin1e->ToExtString();
  return voidext;
}

occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> XSControl_Utils::
  NewSeqCStr() const
{
  return new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
}

void XSControl_Utils::AppendCStr(
  const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& seqval,
  const char*                                                                      strval) const
{
  seqval->Append(new TCollection_HAsciiString(strval));
}

occ::handle<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>> XSControl_Utils::
  NewSeqEStr() const
{
  return new NCollection_HSequence<occ::handle<TCollection_HExtendedString>>();
}

void XSControl_Utils::AppendEStr(
  const occ::handle<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>>& seqval,
  const char16_t*                                                                     strval) const
{
  seqval->Append(new TCollection_HExtendedString(strval));
}

TopoDS_Shape XSControl_Utils::CompoundFromSeq(
  const occ::handle<NCollection_HSequence<TopoDS_Shape>>& seqval) const
{
  BRep_Builder    B;
  TopoDS_Compound C;
  B.MakeCompound(C);
  int i, n = seqval->Length();
  for (i = 1; i <= n; i++)
    B.Add(C, seqval->Value(i));
  return C;
}

TopAbs_ShapeEnum XSControl_Utils::ShapeType(const TopoDS_Shape& shape, const bool compound) const
{
  if (shape.IsNull())
    return TopAbs_SHAPE;
  TopAbs_ShapeEnum res = shape.ShapeType();
  if (!compound || res != TopAbs_COMPOUND)
    return res;
  res = TopAbs_SHAPE;
  for (TopoDS_Iterator iter(shape); iter.More(); iter.Next())
  {
    const TopoDS_Shape& sh = iter.Value();
    if (sh.IsNull())
      continue;
    TopAbs_ShapeEnum typ = sh.ShapeType();
    if (typ == TopAbs_COMPOUND)
      typ = ShapeType(sh, compound);
    if (res == TopAbs_SHAPE)
      res = typ;

    else if (res == TopAbs_EDGE && typ == TopAbs_WIRE)
      res = typ;
    else if (res == TopAbs_WIRE && typ == TopAbs_EDGE)
      continue;
    else if (res == TopAbs_FACE && typ == TopAbs_SHELL)
      res = typ;
    else if (res == TopAbs_SHELL && typ == TopAbs_FACE)
      continue;
    else if (res != typ)
      return TopAbs_COMPOUND;
  }
  return res;
}

TopoDS_Shape XSControl_Utils::SortedCompound(const TopoDS_Shape&    shape,
                                             const TopAbs_ShapeEnum type,
                                             const bool             explore,
                                             const bool             compound) const
{
  if (shape.IsNull())
    return shape;
  TopAbs_ShapeEnum typ = shape.ShapeType();
  TopoDS_Shape     sh, sh0;
  int              nb = 0;

  if (typ == TopAbs_COMPOUND || typ == TopAbs_COMPSOLID)
  {
    TopoDS_Compound C;
    BRep_Builder    B;
    B.MakeCompound(C);
    for (TopoDS_Iterator it(shape); it.More(); it.Next())
    {
      sh0 = SortedCompound(it.Value(), type, explore, compound);
      if (sh0.IsNull())
        continue;
      sh  = sh0;
      typ = sh.ShapeType();
      if (typ == TopAbs_COMPOUND && !compound)
      {
        for (TopoDS_Iterator it2(sh); it2.More(); it2.Next())
        {
          nb++;
          sh = it2.Value();
          B.Add(C, sh);
        }
      }
      else
      {
        nb++;
        B.Add(C, sh);
      }
    }
    if (nb == 0)
      C.Nullify();
    else if (nb == 1)
      return sh;
    return C;
  }

  if (typ == type)
    return shape;
  if (typ == TopAbs_EDGE && type == TopAbs_WIRE)
  {
    BRep_Builder B;
    TopoDS_Wire  W;
    B.MakeWire(W);
    B.Add(W, shape);
    return W;
  }
  if (typ == TopAbs_FACE && type == TopAbs_SHELL)
  {
    BRep_Builder B;
    TopoDS_Shell S;
    B.MakeShell(S);
    B.Add(S, shape);
    S.Closed(BRep_Tool::IsClosed(S));
    return S;
  }

  if (!explore)
  {
    TopoDS_Shape nulsh;
    return nulsh;
  }

  if (typ == TopAbs_SOLID && compound)
  {
    TopoDS_Compound C;
    BRep_Builder    B;
    B.MakeCompound(C);
    for (TopoDS_Iterator it(shape); it.More(); it.Next())
    {
      sh0 = SortedCompound(it.Value(), type, explore, compound);
      if (sh0.IsNull())
        continue;
      sh = sh0;
      nb++;
      B.Add(C, sh);
    }
    if (nb == 0)
      C.Nullify();
    else if (nb == 1)
      return sh;
    return C;
  }

  TopoDS_Compound CC;
  BRep_Builder    BB;
  BB.MakeCompound(CC);
  for (TopExp_Explorer aExp(shape, type); aExp.More(); aExp.Next())
  {
    nb++;
    sh = aExp.Current();
    BB.Add(CC, sh);
  }
  if (nb == 0)
    CC.Nullify();
  else if (nb == 1)
    return sh;
  return CC;
}

TopoDS_Shape XSControl_Utils::ShapeValue(
  const occ::handle<NCollection_HSequence<TopoDS_Shape>>& seqval,
  const int                                               num) const
{
  TopoDS_Shape shape;
  if (seqval.IsNull())
    return shape;
  if (num > 0 && num <= seqval->Length())
    shape = seqval->Value(num);
  return shape;
}

occ::handle<NCollection_HSequence<TopoDS_Shape>> XSControl_Utils::NewSeqShape() const
{
  return new NCollection_HSequence<TopoDS_Shape>();
}

void XSControl_Utils::AppendShape(const occ::handle<NCollection_HSequence<TopoDS_Shape>>& seqval,
                                  const TopoDS_Shape& shape) const
{
  seqval->Append(shape);
}

occ::handle<Standard_Transient> XSControl_Utils::ShapeBinder(const TopoDS_Shape& shape,
                                                             const bool          hs) const
{
  if (hs)
    return new TopoDS_HShape(shape);
  else
    return new TransferBRep_ShapeBinder(shape);
}

TopoDS_Shape XSControl_Utils::BinderShape(const occ::handle<Standard_Transient>& tr) const
{
  TopoDS_Shape sh;
  DeclareAndCast(Transfer_Binder, sb, tr);
  if (!sb.IsNull())
    return TransferBRep::ShapeResult(sb);
  DeclareAndCast(TransferBRep_ShapeMapper, sm, tr);
  if (!sm.IsNull())
    return sm->Value();
  DeclareAndCast(TopoDS_HShape, hs, tr);
  if (!hs.IsNull())
    return hs->Shape();
  return sh;
}

int XSControl_Utils::SeqLength(const occ::handle<Standard_Transient>& seqval) const
{
  if (seqval.IsNull())
    return 0;
  DeclareAndCast(NCollection_HSequence<occ::handle<TCollection_HAsciiString>>, seqs, seqval);
  if (!seqs.IsNull())
    return seqs->Length();
  DeclareAndCast(NCollection_HSequence<TCollection_AsciiString>, seqa, seqval);
  if (!seqa.IsNull())
    return seqa->Length();
  DeclareAndCast(NCollection_HSequence<occ::handle<TCollection_HExtendedString>>, seqe, seqval);
  if (!seqe.IsNull())
    return seqe->Length();
  DeclareAndCast(NCollection_HSequence<occ::handle<TCollection_HExtendedString>>, seqx, seqval);
  if (!seqx.IsNull())
    return seqx->Length();

  DeclareAndCast(NCollection_HSequence<occ::handle<Standard_Transient>>, seqt, seqval);
  if (!seqt.IsNull())
    return seqt->Length();
  DeclareAndCast(NCollection_HSequence<TopoDS_Shape>, seqh, seqval);
  if (!seqh.IsNull())
    return seqh->Length();
  DeclareAndCast(NCollection_HSequence<int>, seqi, seqval);
  if (!seqi.IsNull())
    return seqi->Length();

  return 0;
}

occ::handle<Standard_Transient> XSControl_Utils::SeqToArr(
  const occ::handle<Standard_Transient>& seqval,
  const int                              first) const
{
  int                             i, lng;
  occ::handle<Standard_Transient> val;
  if (seqval.IsNull())
    return val;
  DeclareAndCast(NCollection_HSequence<occ::handle<TCollection_HAsciiString>>, seqs, seqval);
  if (!seqs.IsNull())
  {
    lng = seqs->Length();
    occ::handle<NCollection_HArray1<occ::handle<TCollection_HAsciiString>>> arrs =
      new NCollection_HArray1<occ::handle<TCollection_HAsciiString>>(first, lng - first + 1);
    for (i = 1; i <= lng; i++)
      arrs->SetValue(i - first + 1, seqs->Value(i));
    return arrs;
  }
  DeclareAndCast(NCollection_HSequence<occ::handle<Standard_Transient>>, seqt, seqval);
  if (!seqt.IsNull())
  {
    lng = seqt->Length();
    occ::handle<NCollection_HArray1<occ::handle<Standard_Transient>>> arrt =
      new NCollection_HArray1<occ::handle<Standard_Transient>>(first, lng - first + 1);
    for (i = 1; i <= lng; i++)
      arrt->SetValue(i - first + 1, seqt->Value(i));
    return arrt;
  }
  throw Standard_TypeMismatch("XSControl_Utils::SeqToArr");
}

occ::handle<Standard_Transient> XSControl_Utils::ArrToSeq(
  const occ::handle<Standard_Transient>& arrval) const
{
  int                             i, first, last;
  occ::handle<Standard_Transient> val;
  if (arrval.IsNull())
    return val;
  DeclareAndCast(NCollection_HArray1<occ::handle<TCollection_HAsciiString>>, arrs, arrval);
  if (!arrs.IsNull())
  {
    first = arrs->Lower();
    last  = arrs->Upper();
    occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> seqs =
      new NCollection_HSequence<occ::handle<TCollection_HAsciiString>>();
    for (i = first; i <= last; i++)
      seqs->Append(arrs->Value(i));
    return seqs;
  }
  DeclareAndCast(NCollection_HArray1<occ::handle<Standard_Transient>>, arrt, arrval);
  if (!arrt.IsNull())
  {
    first = arrt->Lower();
    last  = arrt->Upper();
    occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> seqt =
      new NCollection_HSequence<occ::handle<Standard_Transient>>();
    for (i = first; i <= last; i++)
      seqt->Append(arrt->Value(i));
    return seqt;
  }
  throw Standard_TypeMismatch("XSControl_Utils::ArrToSeq");
}

int XSControl_Utils::SeqIntValue(const occ::handle<NCollection_HSequence<int>>& seqval,
                                 const int                                      num) const
{
  if (seqval.IsNull())
    return 0;
  return seqval->Value(num);
}
