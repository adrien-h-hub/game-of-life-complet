; Inno Setup Script for Conway's Game of Life v1.1.0
; Enhanced Edition - Complete Installer
; Compatible with Inno Setup 6.x

#define MyAppName "Conway's Game of Life - Enhanced Edition"
#define MyAppVersion "1.1.0"
#define MyAppPublisher "Your Name"
#define MyAppURL "https://github.com/yourusername/GameOfLife"
#define MyAppExeName "GameOfLife.exe"
#define MyAppAssocName "Game of Life Pattern File"
#define MyAppAssocExt ".gol"
#define MyAppAssocKey StringChange(MyAppAssocName, " ", "") + MyAppAssocExt

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{8F3D9E2A-4B1C-4D2E-9F3A-7B5C8D6E4F1A}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DisableProgramGroupPage=yes
LicenseFile=..\LICENSE
InfoBeforeFile=..\docs\INSTALLATION_INFO.txt
InfoAfterFile=..\docs\QUICK_START.txt
; Remove the following line to run in administrative install mode
PrivilegesRequired=lowest
PrivilegesRequiredOverridesAllowed=dialog
OutputDir=.
OutputBaseFilename=GameOfLife_Setup_v1.1.0
; SetupIconFile=..\assets\icon.ico
Compression=lzma2/ultra64
SolidCompression=yes
WizardStyle=modern
; WizardImageFile=..\assets\installer_image.bmp
; WizardSmallImageFile=..\assets\installer_small.bmp

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 6.1; Check: not IsAdminInstallMode

[Files]
; Main executable and DLLs
Source: "..\..\GameOfLife_App\GameOfLife.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\GameOfLife_App\*.dll"; DestDir: "{app}"; Flags: ignoreversion

; Font file
Source: "..\..\GameOfLife_App\arial.ttf"; DestDir: "{app}"; Flags: ignoreversion skipifsourcedoesntexist
Source: "C:\Windows\Fonts\arial.ttf"; DestDir: "{app}"; Flags: external skipifsourcedoesntexist

; Pattern files
Source: "..\..\GameOfLife_App\patterns\*"; DestDir: "{app}\patterns"; Flags: ignoreversion recursesubdirs createallsubdirs skipifsourcedoesntexist

; Documentation
Source: "..\README.md"; DestDir: "{app}"; Flags: ignoreversion isreadme
Source: "..\LICENSE"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\docs\*"; DestDir: "{app}\docs"; Flags: ignoreversion recursesubdirs createallsubdirs

; Screenshots (for documentation)
Source: "..\screenshots\*"; DestDir: "{app}\screenshots"; Flags: ignoreversion skipifsourcedoesntexist

; Source code (optional, for developers)
Source: "..\src\*"; DestDir: "{app}\src"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\include\*"; DestDir: "{app}\include"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\Makefile"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\*.cpp"; DestDir: "{app}"; Flags: ignoreversion skipifsourcedoesntexist
Source: "..\*.hpp"; DestDir: "{app}"; Flags: ignoreversion skipifsourcedoesntexist

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Registry]
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocExt}\OpenWithProgids"; ValueType: string; ValueName: "{#MyAppAssocKey}"; ValueData: ""; Flags: uninsdeletevalue
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocName}"; Flags: uninsdeletekey
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""
Root: HKA; Subkey: "Software\Classes\Applications\{#MyAppExeName}\SupportedTypes"; ValueType: string; ValueName: ".gol"; ValueData: ""

[Code]
function InitializeSetup(): Boolean;
begin
  Result := True;
  MsgBox('Welcome to Conway''s Game of Life v1.1.0 Setup!' + #13#10 + #13#10 +
         'This wizard will guide you through the installation process.' + #13#10 + #13#10 +
         'Features:' + #13#10 +
         '• 8 Beautiful color themes' + #13#10 +
         '• Pattern detection system' + #13#10 +
         '• Time travel (rewind/forward)' + #13#10 +
         '• Auto-pause on stable patterns' + #13#10 +
         '• Interactive drawing' + #13#10 + #13#10 +
         'Click Next to continue.', mbInformation, MB_OK);
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  if CurStep = ssPostInstall then
  begin
    // You can add post-installation tasks here
  end;
end;
