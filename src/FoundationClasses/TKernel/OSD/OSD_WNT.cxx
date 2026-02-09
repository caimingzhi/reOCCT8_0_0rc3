#ifdef _WIN32

  #include <OSD_WNT.hpp>

  #include <strsafe.h>
  #include <wchar.h>
  #include <stdlib.h>

  #include <Standard_Macro.hpp>

  #ifndef OCCT_UWP
static void Init(void);

class Init_OSD_WNT
{

public:
  Init_OSD_WNT() { Init(); }
};

static Init_OSD_WNT initOsdWnt;
  #endif

static BOOL   fInit = FALSE;
static PSID*  predefinedSIDs;
static HANDLE hHeap;

static MOVE_DIR_PROC     _move_dir_proc;
static COPY_DIR_PROC     _copy_dir_proc;
static RESPONSE_DIR_PROC _response_dir_proc;

  #define PREDEFINED_SIDs_COUNT 9
  #define UNIVERSAL_PREDEFINED_SIDs_COUNT 5

  #define SID_INTERACTIVE 0
  #define SID_NETWORK 1
  #define SID_LOCAL 2
  #define SID_DIALUP 3
  #define SID_BATCH 4
  #define SID_CREATOR_OWNER 5
  #define SID_ADMIN 6
  #define SID_WORLD 7
  #define SID_NULL 8

  #ifndef OCCT_UWP

PSECURITY_DESCRIPTOR AllocSD(void)
{

  PSECURITY_DESCRIPTOR retVal =
    (PSECURITY_DESCRIPTOR)HeapAlloc(hHeap, 0, sizeof(SECURITY_DESCRIPTOR));

  if (retVal != NULL && !InitializeSecurityDescriptor(retVal, SECURITY_DESCRIPTOR_REVISION))
  {

    HeapFree(hHeap, 0, (PVOID)retVal);
    retVal = NULL;
  }

  return retVal;
}

void FreeSD(PSECURITY_DESCRIPTOR pSD)
{

  BOOL fPresent;
  BOOL fDaclDefaulted;
  PACL pACL;

  if (GetSecurityDescriptorDacl(pSD, &fPresent, &pACL, &fDaclDefaulted) && fPresent)

    HeapFree(hHeap, 0, (PVOID)pACL);

  HeapFree(hHeap, 0, (PVOID)pSD);
}

    #if defined(__CYGWIN32__) || defined(__MINGW32__)
      #define __try
      #define __finally
      #define __leave return buffer
    #endif

LPVOID GetTokenInformationEx(HANDLE hToken, TOKEN_INFORMATION_CLASS tic)
{

  DWORD  errVal;
  DWORD  dwSize;
  DWORD  dwSizeNeeded = 0;
  LPVOID buffer       = NULL;
  BOOL   fOK          = FALSE;

  __try
  {

    do
    {

      dwSize = dwSizeNeeded;
      errVal = ERROR_SUCCESS;

      if (!GetTokenInformation(hToken, tic, buffer, dwSize, &dwSizeNeeded))
      {

        if ((errVal = GetLastError()) != ERROR_INSUFFICIENT_BUFFER)

          __leave;

        if ((buffer = HeapAlloc(hHeap, 0, dwSizeNeeded)) == NULL)

          __leave;
      }

    } while (errVal != ERROR_SUCCESS);

    fOK = TRUE;
  }

  __finally
  {

    if (!fOK && buffer != NULL)
    {

      HeapFree(hHeap, 0, buffer);
      buffer = NULL;
    }
  }

    #ifdef VAC
leave:;
    #endif

  return buffer;
}

    #if defined(__CYGWIN32__) || defined(__MINGW32__)
      #undef __try
      #undef __finally
      #undef __leave
    #endif

void FreeTokenInformation(LPVOID lpvTkInfo)
{

  HeapFree(hHeap, 0, lpvTkInfo);
}

static void Init(void)
{

  SID_IDENTIFIER_AUTHORITY sidIDAnull    = SECURITY_NULL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY sidIDAworld   = SECURITY_WORLD_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY sidIDANT      = SECURITY_NT_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY sidIDAlocal   = SECURITY_LOCAL_SID_AUTHORITY;
  SID_IDENTIFIER_AUTHORITY sidIDAcreator = SECURITY_CREATOR_SID_AUTHORITY;

  if (!fInit)
  {

    predefinedSIDs = (PSID*)HeapAlloc(hHeap = GetProcessHeap(),
                                      HEAP_GENERATE_EXCEPTIONS | HEAP_ZERO_MEMORY,
                                      PREDEFINED_SIDs_COUNT * sizeof(PSID*));

    AllocateAndInitializeSid(&sidIDANT,
                             2,
                             SECURITY_BUILTIN_DOMAIN_RID,
                             DOMAIN_ALIAS_RID_ADMINS,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             &predefinedSIDs[SID_ADMIN]);

    AllocateAndInitializeSid(&sidIDAworld,
                             1,
                             SECURITY_WORLD_RID,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             &predefinedSIDs[SID_WORLD]);

    AllocateAndInitializeSid(&sidIDANT,
                             1,
                             SECURITY_INTERACTIVE_RID,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             &predefinedSIDs[SID_INTERACTIVE]);

    AllocateAndInitializeSid(&sidIDANT,
                             1,
                             SECURITY_NETWORK_RID,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             &predefinedSIDs[SID_NETWORK]);

    AllocateAndInitializeSid(&sidIDAlocal,
                             1,
                             SECURITY_LOCAL_RID,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             &predefinedSIDs[SID_LOCAL]);

    AllocateAndInitializeSid(&sidIDANT,
                             1,
                             SECURITY_DIALUP_RID,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             &predefinedSIDs[SID_DIALUP]);

    AllocateAndInitializeSid(&sidIDANT,
                             1,
                             SECURITY_BATCH_RID,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             &predefinedSIDs[SID_BATCH]);

    AllocateAndInitializeSid(&sidIDAcreator,
                             1,
                             SECURITY_CREATOR_OWNER_RID,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             &predefinedSIDs[SID_CREATOR_OWNER]);

    AllocateAndInitializeSid(&sidIDAnull,
                             1,
                             SECURITY_NULL_RID,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             &predefinedSIDs[SID_NULL]);

    fInit = TRUE;
  }
}

BOOL PredefinedSid(PSID pSID)
{

  int i;

  for (i = 0; i < PREDEFINED_SIDs_COUNT; ++i)

    if (EqualSid(pSID, predefinedSIDs[i]))

      return TRUE;

  return FALSE;
}

BOOL NtPredefinedSid(PSID pSID)
{

  int                       i;
  PSID_IDENTIFIER_AUTHORITY pTestIDA;
  SID_IDENTIFIER_AUTHORITY  ntIDA = SECURITY_NT_AUTHORITY;
  PDWORD                    pdwTestSA;

  for (i = 0; i < UNIVERSAL_PREDEFINED_SIDs_COUNT; ++i)

    if (EqualSid(pSID, predefinedSIDs[i]))

      return TRUE;

  pTestIDA = GetSidIdentifierAuthority(pSID);

  if (memcmp(pTestIDA, &ntIDA, sizeof(SID_IDENTIFIER_AUTHORITY)) == 0)
  {

    pdwTestSA = GetSidSubAuthority(pSID, 0);

    if (*pdwTestSA == SECURITY_LOGON_IDS_RID)

      return TRUE;
  }

  return FALSE;
}

PSID AdminSid(void)
{

  return predefinedSIDs[SID_ADMIN];
}

PSID WorldSid(void)
{

  return predefinedSIDs[SID_WORLD];
}

PSID InteractiveSid(void)
{

  return predefinedSIDs[SID_INTERACTIVE];
}

PSID NetworkSid(void)
{

  return predefinedSIDs[SID_NETWORK];
}

PSID LocalSid(void)
{

  return predefinedSIDs[SID_LOCAL];
}

PSID DialupSid(void)
{

  return predefinedSIDs[SID_DIALUP];
}

PSID BatchSid(void)
{

  return predefinedSIDs[SID_BATCH];
}

PSID CreatorOwnerSid(void)
{

  return predefinedSIDs[SID_CREATOR_OWNER];
}

PSID NullSid(void)
{

  return predefinedSIDs[SID_NULL];
}

    #if defined(__CYGWIN32__) || defined(__MINGW32__)
      #define __try
      #define __finally
      #define __leave return retVal
    #endif

PSECURITY_DESCRIPTOR GetFileSecurityEx(LPCWSTR fileName, SECURITY_INFORMATION si)
{

  DWORD                errVal;
  DWORD                dwSize;
  DWORD                dwSizeNeeded = 0;
  PSECURITY_DESCRIPTOR retVal       = NULL;
  BOOL                 fOK          = FALSE;

  __try
  {

    do
    {

      dwSize = dwSizeNeeded;
      errVal = ERROR_SUCCESS;

      if (!GetFileSecurityW(fileName, si, retVal, dwSize, &dwSizeNeeded))
      {

        if ((errVal = GetLastError()) != ERROR_INSUFFICIENT_BUFFER)
          __leave;

        if ((retVal = (PSECURITY_DESCRIPTOR)HeapAlloc(hHeap, 0, dwSizeNeeded)) == NULL)
          __leave;
      }

    } while (errVal != ERROR_SUCCESS);

    fOK = TRUE;
  }

  __finally
  {

    if (!fOK && retVal != NULL)
    {

      HeapFree(hHeap, 0, retVal);
      retVal = NULL;
    }
  }

    #ifdef VAC
leave:;
    #endif

  return retVal;
}

    #if defined(__CYGWIN32__) || defined(__MINGW32__)
      #undef __try
      #undef __finally
      #undef __leave
    #endif

void FreeFileSecurity(PSECURITY_DESCRIPTOR pSD)
{

  HeapFree(hHeap, 0, (LPVOID)pSD);
}

PACL CreateAcl(DWORD dwAclSize)
{

  PACL retVal;

  retVal = (PACL)HeapAlloc(hHeap, 0, dwAclSize);

  if (retVal != NULL)

    InitializeAcl(retVal, dwAclSize, ACL_REVISION);

  return retVal;
}

void FreeAcl(PACL pACL)
{

  HeapFree(hHeap, 0, (PVOID)pACL);
}

PVOID AllocAccessAllowedAce(DWORD dwMask, BYTE flags, PSID pSID)
{

  PFILE_ACE retVal;
  WORD      wSize;

  wSize = (WORD)(sizeof(ACE_HEADER) + sizeof(DWORD) + GetLengthSid(pSID));

  retVal = (PFILE_ACE)HeapAlloc(hHeap, 0, wSize);

  if (retVal != NULL)
  {

    retVal->header.AceType  = ACCESS_ALLOWED_ACE_TYPE;
    retVal->header.AceFlags = flags;
    retVal->header.AceSize  = wSize;

    retVal->dwMask = dwMask;

    CopySid(GetLengthSid(pSID), &retVal->pSID, pSID);
  }

  return retVal;
}

void FreeAce(PVOID pACE)
{

  HeapFree(hHeap, 0, pACE);
}
  #endif
  #define WILD_CARD L"/*.*"
  #define WILD_CARD_LEN (sizeof(WILD_CARD))

static BOOL MoveDirectory(const wchar_t* oldDir, const wchar_t* newDir, DWORD& theRecurseLevel)
{
  wchar_t* driveSrc = NULL;
  wchar_t* driveDst = NULL;
  wchar_t* pathSrc  = NULL;
  wchar_t* pathDst  = NULL;
  BOOL     retVal   = FALSE;
  if (theRecurseLevel == 0)
  {
    ++theRecurseLevel;
    BOOL fFind = FALSE;
    if ((driveSrc = (wchar_t*)HeapAlloc(hHeap, 0, _MAX_DRIVE * sizeof(wchar_t))) != NULL
        && (driveDst = (wchar_t*)HeapAlloc(hHeap, 0, _MAX_DRIVE * sizeof(wchar_t))) != NULL
        && (pathSrc = (wchar_t*)HeapAlloc(hHeap, 0, _MAX_DIR * sizeof(wchar_t))) != NULL
        && (pathDst = (wchar_t*)HeapAlloc(hHeap, 0, _MAX_DIR * sizeof(wchar_t))) != NULL)
    {
      _wsplitpath(oldDir, driveSrc, pathSrc, NULL, NULL);
      _wsplitpath(newDir, driveDst, pathDst, NULL, NULL);
      if (wcscmp(driveSrc, driveDst) == 0 && wcscmp(pathSrc, pathDst) == 0)
      {
      retry:
        retVal = MoveFileExW(oldDir, newDir, MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED);
        fFind  = TRUE;
        if (!retVal)
        {
          if (_response_dir_proc != NULL)
          {
            const DIR_RESPONSE response = _response_dir_proc(oldDir);
            if (response == DIR_RETRY)
            {
              goto retry;
            }
            else if (response == DIR_IGNORE)
            {
              retVal = TRUE;
            }
          }
        }
        else if (_move_dir_proc != NULL)
        {
          _move_dir_proc(oldDir, newDir);
        }
      }
    }

    if (pathDst != NULL)
    {
      HeapFree(hHeap, 0, pathDst);
    }
    if (pathSrc != NULL)
    {
      HeapFree(hHeap, 0, pathSrc);
    }
    if (driveDst != NULL)
    {
      HeapFree(hHeap, 0, driveDst);
    }
    if (driveSrc != NULL)
    {
      HeapFree(hHeap, 0, driveSrc);
    }

    if (fFind)
    {
      --theRecurseLevel;
      return retVal;
    }
  }
  else
  {
    ++theRecurseLevel;
  }

  WIN32_FIND_DATAW* pFD          = NULL;
  wchar_t*          pName        = NULL;
  wchar_t*          pFullNameSrc = NULL;
  wchar_t*          pFullNameDst = NULL;
  HANDLE            hFindFile    = INVALID_HANDLE_VALUE;
  retVal                         = CreateDirectoryW(newDir, NULL);
  if (retVal || (!retVal && GetLastError() == ERROR_ALREADY_EXISTS))
  {
    size_t anOldDirLength;
    StringCchLengthW(oldDir, MAX_PATH, &anOldDirLength);
    const size_t aNameLength = anOldDirLength + WILD_CARD_LEN + sizeof(L'\x00');
    if ((pFD = (WIN32_FIND_DATAW*)HeapAlloc(hHeap, 0, sizeof(WIN32_FIND_DATAW))) != NULL
        && (pName = (wchar_t*)HeapAlloc(hHeap, 0, aNameLength)) != NULL)
    {
      StringCchCopyW(pName, aNameLength, oldDir);
      StringCchCatW(pName, aNameLength, WILD_CARD);
      retVal    = TRUE;
      hFindFile = FindFirstFileExW(pName, FindExInfoStandard, pFD, FindExSearchNameMatch, NULL, 0);
      for (BOOL fFind = hFindFile != INVALID_HANDLE_VALUE; fFind;
           fFind      = FindNextFileW(hFindFile, pFD))
      {
        if ((pFD->cFileName[0] == L'.' && pFD->cFileName[1] == L'\0')
            || (pFD->cFileName[0] == L'.' && pFD->cFileName[1] == L'.'
                && pFD->cFileName[2] == L'\0'))
        {
          continue;
        }

        size_t aNewDirLength = 0, aFileNameLength = 0;
        StringCchLengthW(newDir, MAX_PATH, &aNewDirLength);
        StringCchLengthW(pFD->cFileName,
                         sizeof(pFD->cFileName) / sizeof(pFD->cFileName[0]),
                         &aFileNameLength);
        const size_t aFullNameSrcLength =
          anOldDirLength + aFileNameLength + sizeof(L'/') + sizeof(L'\x00');
        const size_t aFullNameDstLength =
          aNewDirLength + aFileNameLength + sizeof(L'/') + sizeof(L'\x00');
        if ((pFullNameSrc = (wchar_t*)HeapAlloc(hHeap, 0, aFullNameSrcLength)) == NULL
            || (pFullNameDst = (wchar_t*)HeapAlloc(hHeap, 0, aFullNameDstLength)) == NULL)
        {
          break;
        }

        StringCchCopyW(pFullNameSrc, aFullNameSrcLength, oldDir);
        StringCchCatW(pFullNameSrc, aFullNameSrcLength, L"/");
        StringCchCatW(pFullNameSrc, aFullNameSrcLength, pFD->cFileName);

        StringCchCopyW(pFullNameDst, aFullNameDstLength, newDir);
        StringCchCatW(pFullNameDst, aFullNameDstLength, L"/");
        StringCchCatW(pFullNameDst, aFullNameDstLength, pFD->cFileName);

        if ((pFD->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
        {
          retVal = MoveDirectory(pFullNameSrc, pFullNameDst, theRecurseLevel);
          if (!retVal)
          {
            break;
          }
        }
        else
        {
        retry_1:
          retVal = MoveFileExW(pFullNameSrc,
                               pFullNameDst,
                               MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED);
          if (!retVal)
          {
            if (_response_dir_proc != NULL)
            {
              const DIR_RESPONSE response = _response_dir_proc(pFullNameSrc);
              if (response == DIR_ABORT)
              {
                break;
              }
              else if (response == DIR_RETRY)
              {
                goto retry_1;
              }
              else if (response == DIR_IGNORE)
              {
                retVal = TRUE;
              }
              else
              {
                break;
              }
            }
          }
          else if (_move_dir_proc != NULL)
          {
            _move_dir_proc(pFullNameSrc, pFullNameDst);
          }
        }

        HeapFree(hHeap, 0, pFullNameDst);
        HeapFree(hHeap, 0, pFullNameSrc);
        pFullNameSrc = pFullNameDst = NULL;
      }
    }
  }

  if (hFindFile != INVALID_HANDLE_VALUE)
  {
    FindClose(hFindFile);
  }

  if (pFullNameSrc != NULL)
  {
    HeapFree(hHeap, 0, pFullNameSrc);
  }
  if (pFullNameDst != NULL)
  {
    HeapFree(hHeap, 0, pFullNameDst);
  }
  if (pName != NULL)
  {
    HeapFree(hHeap, 0, pName);
  }
  if (pFD != NULL)
  {
    HeapFree(hHeap, 0, pFD);
  }

  if (retVal)
  {
  retry_2:
    retVal = RemoveDirectoryW(oldDir);
    if (!retVal)
    {
      if (_response_dir_proc != NULL)
      {
        const DIR_RESPONSE response = _response_dir_proc(oldDir);
        if (response == DIR_RETRY)
        {
          goto retry_2;
        }
        else if (response == DIR_IGNORE)
        {
          retVal = TRUE;
        }
      }
    }
  }

  --theRecurseLevel;
  return retVal;
}

BOOL MoveDirectory(const wchar_t* oldDir, const wchar_t* newDir)
{
  DWORD aRecurseLevel = 0;
  return MoveDirectory(oldDir, newDir, aRecurseLevel);
}

BOOL CopyDirectory(const wchar_t* dirSrc, const wchar_t* dirDst)
{
  WIN32_FIND_DATAW* pFD          = NULL;
  wchar_t*          pName        = NULL;
  wchar_t*          pFullNameSrc = NULL;
  wchar_t*          pFullNameDst = NULL;
  HANDLE            hFindFile    = INVALID_HANDLE_VALUE;

  BOOL retVal = CreateDirectoryW(dirDst, NULL);
  if (retVal || (!retVal && GetLastError() == ERROR_ALREADY_EXISTS))
  {
    size_t aDirSrcLength = 0;
    StringCchLengthW(dirSrc, MAX_PATH, &aDirSrcLength);
    const size_t aNameLength = aDirSrcLength + WILD_CARD_LEN + sizeof(L'\x00');
    if ((pFD = (WIN32_FIND_DATAW*)HeapAlloc(hHeap, 0, sizeof(WIN32_FIND_DATAW))) != NULL
        && (pName = (wchar_t*)HeapAlloc(hHeap, 0, aNameLength)) != NULL)
    {
      StringCchCopyW(pName, aNameLength, dirSrc);
      StringCchCatW(pName, aNameLength, WILD_CARD);

      retVal    = TRUE;
      hFindFile = FindFirstFileExW(pName, FindExInfoStandard, pFD, FindExSearchNameMatch, NULL, 0);
      for (BOOL fFind = hFindFile != INVALID_HANDLE_VALUE; fFind;
           fFind      = FindNextFileW(hFindFile, pFD))
      {
        if ((pFD->cFileName[0] == L'.' && pFD->cFileName[1] == L'\0')
            || (pFD->cFileName[0] == L'.' && pFD->cFileName[1] == L'.'
                && pFD->cFileName[2] == L'\0'))
        {
          continue;
        }

        size_t aDirDstLength = 0, aFileNameLength = 0;
        StringCchLengthW(dirDst, MAX_PATH, &aDirDstLength);
        StringCchLengthW(pFD->cFileName,
                         sizeof(pFD->cFileName) / sizeof(pFD->cFileName[0]),
                         &aFileNameLength);
        const size_t aFullNameSrcLength =
          aDirSrcLength + aFileNameLength + sizeof(L'/') + sizeof(L'\x00');
        const size_t aFullNameDstLength =
          aDirDstLength + aFileNameLength + sizeof(L'/') + sizeof(L'\x00');
        if ((pFullNameSrc = (wchar_t*)HeapAlloc(hHeap, 0, aFullNameSrcLength)) == NULL
            || (pFullNameDst = (wchar_t*)HeapAlloc(hHeap, 0, aFullNameDstLength)) == NULL)
        {
          break;
        }

        StringCchCopyW(pFullNameSrc, aFullNameSrcLength, dirSrc);
        StringCchCatW(pFullNameSrc, aFullNameSrcLength, L"/");
        StringCchCatW(pFullNameSrc, aFullNameSrcLength, pFD->cFileName);

        StringCchCopyW(pFullNameDst, aFullNameDstLength, dirDst);
        StringCchCatW(pFullNameDst, aFullNameDstLength, L"/");
        StringCchCatW(pFullNameDst, aFullNameDstLength, pFD->cFileName);
        if ((pFD->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
        {
          retVal = CopyDirectory(pFullNameSrc, pFullNameDst);
          if (!retVal)
          {
            break;
          }
        }
        else
        {
        retry:
  #ifndef OCCT_UWP
          retVal = CopyFileW(pFullNameSrc, pFullNameDst, FALSE);
  #else
          retVal = (CopyFile2(pFullNameSrc, pFullNameDst, FALSE) == S_OK) ? TRUE : FALSE;
  #endif
          if (!retVal)
          {
            if (_response_dir_proc != NULL)
            {
              const DIR_RESPONSE response = _response_dir_proc(pFullNameSrc);
              if (response == DIR_ABORT)
              {
                break;
              }
              else if (response == DIR_RETRY)
              {
                goto retry;
              }
              else if (response == DIR_IGNORE)
              {
                retVal = TRUE;
              }
              else
              {
                break;
              }
            }
          }
          else if (_copy_dir_proc != NULL)
          {
            _copy_dir_proc(pFullNameSrc, pFullNameDst);
          }
        }

        HeapFree(hHeap, 0, pFullNameDst);
        HeapFree(hHeap, 0, pFullNameSrc);
        pFullNameSrc = pFullNameDst = NULL;
      }
    }
  }

  if (hFindFile != INVALID_HANDLE_VALUE)
  {
    FindClose(hFindFile);
  }

  if (pFullNameSrc != NULL)
  {
    HeapFree(hHeap, 0, pFullNameSrc);
  }
  if (pFullNameDst != NULL)
  {
    HeapFree(hHeap, 0, pFullNameDst);
  }
  if (pName != NULL)
  {
    HeapFree(hHeap, 0, pName);
  }
  if (pFD != NULL)
  {
    HeapFree(hHeap, 0, pFD);
  }

  return retVal;
}

void SetMoveDirectoryProc(MOVE_DIR_PROC proc)
{

  _move_dir_proc = proc;
}

void SetCopyDirectoryProc(COPY_DIR_PROC proc)
{

  _copy_dir_proc = proc;
}

void SetResponseDirectoryProc(RESPONSE_DIR_PROC proc)
{

  _response_dir_proc = proc;
}

#endif
