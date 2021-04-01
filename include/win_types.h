/*
    Windows Data Types
    https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types
*/

#ifndef WIN_TYPES_H
#define WIN_TYPES_H

#define WINAPI /*__stdcall*/
#define APIENTRY WINAPI
#define CALLBACK /*__stdcall*/
#define CONST const
#define VOID void
#define far 

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef wchar_t WCHAR;

typedef char CHAR;
typedef char CCHAR;

typedef CHAR *LPSTR;
typedef CONST CHAR *LPCSTR;

#ifdef UNICODE
    typedef WCHAR TCHAR;
    typedef WCHAR TBYTE;
    typedef LPCWSTR PCTSTR;
    typedef LPCWSTR LPCTSTR; 
    typedef LPWSTR LPTSTR;
    typedef LPWSTR PTSTR;
#else
    typedef char TCHAR;
    typedef unsigned char TBYTE;
    typedef LPCSTR PCTSTR;
    typedef LPCSTR LPCTSTR;
    typedef LPSTR LPTSTR;
    typedef LPSTR PTSTR;
#endif

typedef unsigned short WORD;
typedef WORD ATOM;
typedef WORD LANGID;

typedef unsigned char BYTE;
typedef BYTE BOOLEAN;
typedef BYTE far *LPBYTE;

typedef int BOOL;
typedef BOOL far *LPBOOL;

typedef unsigned long DWORD;
typedef DWORD COLORREF;
typedef DWORD LCID;
typedef DWORD LCTYPE;
typedef DWORD LGRPID;
typedef DWORD *LPCOLORREF;

typedef unsigned int DWORD32;
typedef unsigned long long DWORD64;

typedef int INT;
typedef long long INT_PTR;
typedef signed char INT8;
typedef signed short INT16;
typedef signed int INT32;
typedef signed long long INT64;

typedef int *PINT;
typedef INT_PTR *PINT_PTR;
typedef INT8 *PINT8;
typedef INT16 *PINT16;
typedef INT32 *PINT32;
typedef INT64 *PINT64;

typedef unsigned int UINT;
typedef unsigned int UINT_PTR;
typedef UINT_PTR *PUINT_PTR;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;

typedef int *LPINT;
typedef UINT *PUINT;
typedef UINT8 *PUINT8;
typedef UINT16 *PUINT16;
typedef UINT32 *PUINT32;
typedef UINT64 *PUINT64;
typedef UINT_PTR WPARAM;

typedef long LONG;
typedef signed int LONG32;
typedef long long LONG64;

typedef LONG HRESULT;

typedef long long LONGLONG;
typedef long long LONG_PTR;
typedef LONG_PTR LPARAM;
typedef long *LPLONG;
typedef LONG *PLONG;
typedef LONGLONG *PLONGLONG;
typedef LONG_PTR *PLONG_PTR;
typedef LONG32 *PLONG32;
typedef LONG64 *PLONG64;

typedef unsigned long long ULONG64;
typedef unsigned long long ULONGLONG;
typedef unsigned long long ULONG_PTR;

typedef unsigned long long DWORDLONG;
typedef ULONG_PTR DWORD_PTR;

typedef float FLOAT;

typedef void *PVOID;
typedef PVOID HANDLE;
typedef HANDLE LHANDLE;
typedef HANDLE HACCEL;
typedef HANDLE HBITMAP;
typedef HANDLE HBRUSH;
typedef HANDLE HCOLORSPACE;
typedef HANDLE HCONV;
typedef HANDLE HCONVLIST;
typedef HANDLE HDC;
typedef HANDLE HDDEDATA;
typedef HANDLE HDESK;
typedef HANDLE HDROP;
typedef HANDLE HDWP;
typedef HANDLE HENHMETAFILE;
typedef HANDLE HFONT;
typedef HANDLE HGDIOBJ;
typedef HANDLE HGLOBAL;
typedef HANDLE HHOOK;
typedef HANDLE HICON;
typedef HANDLE HINSTANCE;
typedef HANDLE HKEY;
typedef HANDLE HKL;
typedef HANDLE HLOCAL;
typedef HANDLE HMENU;
typedef HANDLE HMETAFILE;
typedef HANDLE HPALETTE;
typedef HANDLE HPEN;
typedef HANDLE HRGN;
typedef HANDLE HRSRC;
typedef HANDLE HSZ;
typedef HANDLE WINSTA;
typedef HANDLE HWND;

typedef HINSTANCE HMODULE;

typedef int HFILE;

typedef int HALF_PTR;

typedef HICON HCURSOR;

typedef CONST void *LPCVOID;
typedef CONST WCHAR *LPCWSTR;
typedef DWORD *LPDWORD;
typedef HANDLE *LPHANDLE;

typedef void *LPVOID;
typedef WORD *LPWORD;
typedef WCHAR *LPWSTR;
typedef LONG_PTR LRESULT;
typedef BOOL *PBOOL;
typedef BOOLEAN *PBOOLEAN;
typedef BYTE *PBYTE;
typedef CHAR *PCHAR;
typedef CONST CHAR *PCSTR;

typedef CONST WCHAR *PCWSTR;
typedef DWORD *PDWORD;
typedef DWORDLONG *PDWORDLONG;
typedef DWORD_PTR *PDWORD_PTR;
typedef DWORD32 *PDWORD32;
typedef DWORD64 *PDWORD64;
typedef FLOAT *PFLOAT;

typedef HALF_PTR *PHALF_PTR;

typedef HANDLE *PHANDLE;
typedef HKEY *PHKEY;
typedef PDWORD PLCID;
typedef short SHORT;
typedef SHORT *PSHORT;
typedef ULONG_PTR SIZE_T;
typedef LONG_PTR SSIZE_T;
typedef SIZE_T *PSIZE_T;
typedef SSIZE_T *PSSIZE_T;
typedef CHAR *PSTR;
typedef TBYTE *PTBYTE;
typedef TCHAR *PTCHAR;

typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;

typedef unsigned int UHALF_PTR;
typedef UHALF_PTR *PUHALF_PTR;

typedef unsigned long ULONG;
typedef ULONG *PULONG;
typedef ULONGLONG *PULONGLONG;
typedef ULONG_PTR *PULONG_PTR;
typedef unsigned int ULONG32;
typedef ULONG32 *PULONG32;
typedef ULONG64 *PULONG64;
typedef unsigned short USHORT;
typedef USHORT *PUSHORT;
typedef WCHAR *PWCHAR;
typedef WORD *PWORD;
typedef WCHAR *PWSTR;
typedef unsigned long long QWORD;
typedef HANDLE SC_HANDLE;
typedef LPVOID SC_LOCK;
typedef HANDLE SERVICE_STATUS_HANDLE;

/*
typedef struct _UNICODE_STRING {
    USHORT  Length;
    USHORT  MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING;

typedef UNICODE_STRING *PUNICODE_STRING;
typedef const UNICODE_STRING *PCUNICODE_STRING;
*/
typedef LONGLONG USN;

/* https://docs.microsoft.com/en-us/previous-versions/ms915433(v=msdn.10) */

#define LF_FACESIZE 32

typedef struct tagLOGFONT { 
    LONG lfHeight; 
    LONG lfWidth; 
    LONG lfEscapement; 
    LONG lfOrientation; 
    LONG lfWeight; 
    BYTE lfItalic; 
    BYTE lfUnderline; 
    BYTE lfStrikeOut; 
    BYTE lfCharSet; 
    BYTE lfOutPrecision ; 
    BYTE lfClipPrecision ; 
    BYTE lfQuality ; 
    BYTE lfPitchAndFamily ; 
    TCHAR lfFaceName[LF_FACESIZE] ; 
} LOGFONT, *PLOGFONT;

#endif
