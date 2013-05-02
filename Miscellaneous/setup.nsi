; *** THIS FILE IS ENCODED IN codepage 932 TO WRITE JAPANESE TEXTS ***

; Setup script for Alissa's PDF Thumbnail Trimmer
; Based on a script generated by the HM NIS Edit Script Wizard.

SetCompressor /SOLID /FINAL lzma

; Product Identity and other general config
!define PRODUCT_NAME "Alissa's PDF Thumbnail Trimmer"
!define PRODUCT_VERSION "1.0.9.0"
!define PRODUCT_PUBLISHER "Alissa Sabre"
!define PRODUCT_WEB_SITE "http://alissa-sabre.cocolog-nifty.com/"

!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

!define PRODUCT_README_EN "Readme.txt"
!define PRODUCT_README_JA "Readme (Japanese).txt"

; VersionInfo resource for the installer (and uninstaller)
VIProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey ProductVersion  "${PRODUCT_VERSION}"
VIAddVersionKey ProductName     "${PRODUCT_NAME}"
VIAddVersionKey CompanyName     "${PRODUCT_PUBLISHER}"
VIAddVersionKey LegalCopyright  "Written by ${PRODUCT_PUBLISHER}"
VIAddVersionKey FileVersion     "${PRODUCT_VERSION}"
VIAddVersionKey FileDescription "Installer of ${PRODUCT_NAME}"
VIAddVersionKey InternalName    "PDFThumbTrimmer-Setup"

; CLSIDs and IIDs (both mine and others')
!define CLSID_PDFThumbTrimmer	"{0ADA2DB4-A310-40BC-8AD8-423B6A333D5A}"
!define CLSID_PDFShellExtension	"{F9DB5320-233E-11D1-9F84-707F02C10627}"
!define IID_IExtractImage	"{BB2E617C-0920-11d1-9A0B-00C04FC2D6C1}"

; MUI 1.67 compatible ------

!include "MUI.nsh"
#include "MUI2.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\win-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\win-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_SHOWREADME "$(LocalizedReadme)"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files -- Note that we have no install language selector,
; so adding many languages here is pointless.  Better to keep the
; list minimum, with the first language to be English.
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Japanese"

; MUI end ------

Name "${PRODUCT_NAME}"
OutFile "PDFThumbTrimmer-Setup.exe"
InstallDir "$PROGRAMFILES\Alissa\PDFThumbTrimmer"
ShowInstDetails hide
ShowUnInstDetails hide

!include x64.nsh

# SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
!define SHChangeNotify "System::Call 'shell32.dll::SHChangeNotify(i, i, i, i) v (0x08000000, 0, 0, 0)'"

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite on

  File "..\Release\PDFThumbTrimmer.dll"
${If} ${RunningX64}
  File "..\x64\Release\PDFThumbTrimmer64.dll"
${EndIf}

  File "${PRODUCT_README_EN}"
${If} $LANGUAGE == ${LANG_JAPANESE}
  File "${PRODUCT_README_JA}"
${EndIf}

  ; Redirect the PDF IExtractImage settings to our class
  ; Note that Adobe Reader 8.X through 10.X use "*.7" ProgID and 11.X uses "*.11".
  WriteRegStr    HKCR "AcroExch.Document.7\ShellEx\${IID_IExtractImage}" ""             "${CLSID_PDFThumbTrimmer}"
  WriteRegStr    HKCR "AcroExch.Document.11\ShellEx\${IID_IExtractImage}" ""            "${CLSID_PDFThumbTrimmer}"

  ; COM registry entries for 32 bit DLL
  WriteRegStr    HKCR "CLSID\${CLSID_PDFThumbTrimmer}"                   ""             "${PRODUCT_NAME}"
  WriteRegStr    HKCR "CLSID\${CLSID_PDFThumbTrimmer}\InprocServer32"    ""             "$INSTDIR\PDFThumbTrimmer.dll"
  WriteRegStr    HKCR "CLSID\${CLSID_PDFThumbTrimmer}\InprocServer32"    ThreadingModel "Apartment"

${If} ${RunningX64}

  ; Additional entries for 32 bit DLL so that it can interwork with 64 bit DLL
  ; They must be in 32 bit view.
  WriteRegStr    HKCR "CLSID\${CLSID_PDFThumbTrimmer}"                   AppId          "${CLSID_PDFThumbTrimmer}"
  WriteRegStr    HKCR "AppID\${CLSID_PDFThumbTrimmer}"                   DllSurrogate   ""
  
  ; COM registry entries for 64 bit DLL
  SetRegView 64
  WriteRegStr    HKCR "CLSID\${CLSID_PDFThumbTrimmer}"                   ""             "${PRODUCT_NAME} (64 bit proxy)"
  WriteRegStr    HKCR "CLSID\${CLSID_PDFThumbTrimmer}\InprocServer32"    ""             "$INSTDIR\PDFThumbTrimmer64.dll"
  WriteRegStr    HKCR "CLSID\${CLSID_PDFThumbTrimmer}\InprocServer32"    ThreadingModel "Apartment"
  SetRegView 32

${EndIf}

SectionEnd

LangString LocalizedReadme ${LANG_ENGLISH}  "${PRODUCT_README_EN}"
LangString LocalizedReadme ${LANG_JAPANESE} "${PRODUCT_README_JA}"

Section -Post

  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Readme" "$INSTDIR\$(LocalizedReadme)"

  ${SHChangeNotify}

; ; Always show the readme (release note) without asking...
; ExecShell "open" "$INSTDIR\$(LocalizedReadme)"

SectionEnd

; I like a taciturn uninstaller.  The only UI you will see during
; a successful uninstall session will be just one confirmation dialog.

LangString ConfirmMessage ${LANG_ENGLISH}  "Do you want to uninstall ${PRODUCT_NAME}?"
LangString ConfirmMessage ${LANG_JAPANESE} "${PRODUCT_NAME}をアンインストールしますか?"

Function un.onInit
  MessageBox MB_ICONEXCLAMATION|MB_YESNO|MB_DEFBUTTON2 "$(ConfirmMessage)" IDYES +2
  Abort
FunctionEnd

Section Uninstall

  ; Restore the original IExtractImage handler for PDF files.
  ; Note that Adobe Reader 8.X through 10.X use "*.7" ProgID and 11.X uses "*.11".
  WriteRegStr HKCR "AcroExch.Document.7\ShellEx\${IID_IExtractImage}" "" "${CLSID_PDFShellExtension}"
  WriteRegStr HKCR "AcroExch.Document.11\ShellEx\${IID_IExtractImage}" "" "${CLSID_PDFShellExtension}"

  ; Remove PDFThumbTrimmer from COM registry.
  DeleteRegKey HKCR "CLSID\${CLSID_PDFTHumbTrimmer}"
  DeleteRegKey HKCR "AppID\${CLSID_PDFTHumbTrimmer}"
  SetRegView 64
  DeleteRegKey HKCR "CLSID\${CLSID_PDFTHumbTrimmer}"
  SetRegView 32

  ; Let the Shell to know the change.
  ${SHChangeNotify}

  ; Remove the installed files and directory.
  Delete "$INSTDIR\${PRODUCT_README_EN}"
  Delete "$INSTDIR\${PRODUCT_README_JA}"
  Delete "$INSTDIR\PDFThumbTrimmer.dll"
  Delete "$INSTDIR\PDFThumbTrimmer64.dll"
  Delete "$INSTDIR\uninst.exe"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"

  ; Show the progress and completion of uninstallation.  Changed the policy by popular demands. :-)
  # SetAutoClose true

SectionEnd

;;; 
;;; Following is a kind of a _hot_fix_ against NSIS supplied Japanese.nsh
;;; MakeNSIS generates a warning on it, but it is necessary
LangString MUI_TEXT_FINISH_SHOWREADME ${LANG_JAPANESE} "Readmeを読む(&S)"
