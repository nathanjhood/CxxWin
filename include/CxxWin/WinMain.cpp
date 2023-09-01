/***************************************************************************//**
 * @file WinMain.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief Contains the definitions of 'WinMain'.
 * @version 1.0.0-init
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

#include "WinMain.h"

#if !defined(UNICODE) || !defined(_UNICODE)
int WINAPI WinMain  (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
#endif
{
    // Initialize common controls (legacy support)
    // INITCOMMONCONTROLSEX icc;
    // icc.dwSize = sizeof(icc);
    // icc.dwICC = ICC_WIN95_CLASSES;
    // InitCommonControlsEx(&icc);

    MainComponent win;

    if (!win.Create(win.ClassName(), WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }

    ShowWindow(win.Window(), nShowCmd);

    MSG msg = { };

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

#if defined(RC_INVOKED)
LANGUAGE 0, 0
CREATEPROCESS_MANIFEST_RESOURCE_ID RT_MANIFEST MOVEABLE PURE DISCARDABLE
BEGIN
  "<?xml version=""1.0"" encoding=""UTF-8"" standalone=""yes""?>\n"
  "<assembly xmlns=""urn:schemas-microsoft-com:asm.v1"" manifestVersion=""1.0"">\n"
  "<assemblyIdentity name=""CxxWin"" processorArchitecture=""*"" version=""1.0.0.0"" type=""win32"" />\n"
  "  <trustInfo xmlns=""urn:schemas-microsoft-com:asm.v3"">\n"
  "    <security>\n"
  "      <requestedPrivileges>\n"
  "        <requestedExecutionLevel level=""asInvoker""/>\n"
  "      </requestedPrivileges>\n"
  "    </security>\n"
  "  </trustInfo>\n"
  "  <compatibility xmlns=""urn:schemas-microsoft-com:compatibility.v1"">\n"
  "    <application>\n"
  "      <!--The ID below indicates application support for Windows Vista -->\n"
  "      <supportedOS Id=""{e2011457-1546-43c5-a5fe-008deee3d3f0}""/>\n"
  "      <!--The ID below indicates application support for Windows 7 -->\n"
  "      <supportedOS Id=""{35138b9a-5d96-4fbd-8e2d-a2440225f93a}""/>\n"
  "      <!--The ID below indicates application support for Windows 8 -->\n"
  "      <supportedOS Id=""{4a2f28e3-53b9-4441-ba9c-d69d4a4a6e38}""/>\n"
  "      <!--The ID below indicates application support for Windows 8.1 -->\n"
  "      <supportedOS Id=""{1f676c76-80e1-4239-95bb-83d0f6d0da78}""/> \n"
  "      <!--The ID below indicates application support for Windows 10 -->\n"
  "      <supportedOS Id=""{8e0f7a12-bfb3-4fe8-b9a5-48fd50a15a9a}""/> \n"
  "    </application>\n"
  "  </compatibility>\n"
  "  <dependency>\n"
  "    <dependentAssembly>\n"
  "      <assemblyIdentity type=""Win32"" name=""Microsoft.Windows.Common-Controls"" version=""6.0.0.0"" processorArchitecture=""*"" publicKeyToken=""6595b64144ccf1df"" language=""*""/>\n"
  "    </dependentAssembly>\n"
  "  </dependency>\n"
  "  <asmv3:application>\n"
  "    <asmv3:windowsSettings>\n"
  "      <dpiAware xmlns=""http://schemas.microsoft.com/SMI/2005/WindowsSettings"">true</dpiAware>\n"
  "      <dpiAwareness xmlns=""http://schemas.microsoft.com/SMI/2016/WindowsSettings"">PerMonitorV2</dpiAwareness>\n"
  "    </asmv3:windowsSettings>\n"
  "  </asmv3:application>\n"
  "</assembly>\n"
END
VS_VERSION_INFO VERSIONINFO
FILEVERSION     1,0,0,0
PRODUCTVERSION  1,0,0,0
FILEFLAGSMASK VS_FFI_FILEFLAGSMASK
FILEFLAGS 0
FILEOS VOS_NT_WINDOWS32
FILETYPE VFT_APP
FILESUBTYPE VFT2_UNKNOWN
BEGIN
	BLOCK "StringFileInfo"
	BEGIN
		BLOCK "080904b0"
		BEGIN
			VALUE "CompanyName", "StoneyDSP"
			VALUE "FileDescription", "Win32 API from C++."
			VALUE "FileVersion", "1.0.0.0"
			VALUE "InternalName", "CxxWin"
			VALUE "LegalCopyright", "Copyright (c) 2023 Nathan J. Hood (nathanjhood@googlemail.com)"
			VALUE "OriginalFilename", "executable.exe"
			VALUE "ProductName", "CxxWin"
			VALUE "ProductVersion", "1.0.0.0"
		END
	END
	BLOCK "VarFileInfo"
	BEGIN
		VALUE "Translation", 0x809, 1200
	END
END
#endif
