!include "MUI2.nsh"
!include "x64.nsh"

!define MUI_ABORTWARNING

!define MOD_NAME	"Mafia2-Online"
!define	MOD_VERS	"v0.1 RC5"
!define MOD_NAME_S	"M2Online"
!define MOD_OUTPUT	"m2online-client-rc5.exe"
!define REG_NODE	"SOFTWARE\Wow6432Node\${MOD_NAME}"
!define MOD_DIR 	"$PROGRAMFILES\${MOD_NAME}"

!define MUI_ICON 	"../Binary/icons/install.ico"
!define MUI_UNICON 	"../Binary/icons/install.ico"

Name "${MOD_NAME}"
Caption "${MOD_NAME} Installer"

OutFile "..\Binary\${MOD_OUTPUT}"
SetCompressor /SOLID lzma
BrandingText /TRIMCENTER "${MOD_NAME} Setup"
ShowInstDetails show
ShowUninstDetails show
RequestExecutionLevel admin

# Pages
!define MUI_DIRECTORYPAGE_TEXT_TOP "Please choose the location where you want to install ${MOD_NAME}."
!define MUI_PAGE_CUSTOMFUNCTION_PRE ChooseM2MPDirectory
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE OnChosenM2MPDirectory
!insertmacro MUI_PAGE_DIRECTORY

!define MUI_DIRECTORYPAGE_TEXT_TOP "Please location your Mafia II (PC) directory."
!define MUI_PAGE_CUSTOMFUNCTION_PRE FindMafia2Directory
!define MUI_PAGE_CUSTOMFUNCTION_LEAVE ConfirmMafia2Directory
!insertmacro MUI_PAGE_DIRECTORY

!insertmacro MUI_PAGE_LICENSE "License.txt"

!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE "English"

Var MODDIR
Var GAMEDIR

!macro VerifyUserIsAdmin
	UserInfo::GetAccountType
	pop $0
	${If} $0 != "admin"
		MessageBox MB_ICONSTOP "Administrator rights required!"
		SetErrorLevel 740
		Quit
	${EndIf}
!macroend

Function .onInit
	SetShellVarContext all
	!insertmacro VerifyUserIsAdmin
FunctionEnd

# Choose the Mafia 2 Multiplayer install location
Function ChooseM2MPDirectory
	ReadRegStr $MODDIR HKLM "${REG_NODE}" "InstallLocation"
	${If} $MODDIR == ""
		StrCpy $INSTDIR "$PROGRAMFILES\${MOD_NAME}"
	${Else}
		StrCpy $INSTDIR "$MODDIR"
	${EndIf}
FunctionEnd

# After they choose the Mafia 2 Multiplayer directory
Function OnChosenM2MPDirectory
	StrCpy $MODDIR "$INSTDIR"
FunctionEnd

# Find the Mafia 2 install directory
Function FindMafia2Directory
	ReadRegStr $GAMEDIR HKLM "${REG_NODE}" "GameDir"
	${If} $GAMEDIR != ""
		StrCpy $INSTDIR $GAMEDIR

		goto exit
	${EndIf}

	ReadRegStr $0 HKLM "SOFTWARE\Wow6432Node\2K Games\Mafia II" "Installfolder"
	${If} $0 == ""
		ReadRegStr $0 HKLM "SOFTWARE\Wow6432Node\Valve\Steam" "InstallPath"
		${If} $0 != ""
			StrCpy $INSTDIR "$0\steamapps\common\mafia ii"
		${EndIf}
	${Else}
		StrCpy $INSTDIR $0
	${EndIf}

	exit:
FunctionEnd

# Confirm the selected Mafia 2 directory is valid
Function ConfirmMafia2Directory
	IfFileExists "$INSTDIR\pc\APEX_Clothing.dll" skip
		MessageBox MB_OK|MB_ICONSTOP "Invalid directory specified. Please select only the /mafia ii/ folder and not any sub-directories."
		Abort
	skip:
	StrCpy $GAMEDIR $INSTDIR
FunctionEnd

Section "Install"
	SetOverwrite on

	CreateDirectory "$MODDIR"
	CreateDirectory "$MODDIR\cache"
	CreateDirectory "$MODDIR\data"
	CreateDirectory "$MODDIR\data\browser"
	CreateDirectory "$MODDIR\data\game"
	CreateDirectory "$MODDIR\data\gui"
	CreateDirectory "$MODDIR\data\gui\fonts"
	CreateDirectory "$MODDIR\data\gui\images"
	CreateDirectory "$MODDIR\data\gui\skins"
	CreateDirectory "$MODDIR\logs"
	CreateDirectory "$MODDIR\screenshots"

	SetOutPath "$MODDIR"
	File ..\Binary\release\m2online.exe
	File ..\Binary\release\m2online.dll
	File ..\Binary\bass.dll

	SetOutPath "$MODDIR\data\game"
	File ..\Binary\gamefiles\0.m2o
	File ..\Binary\gamefiles\1.m2o
	File ..\Binary\gamefiles\2.m2o
	File ..\Binary\gamefiles\3.m2o

	SetOutPath "$MODDIR\data\gui\fonts"
	File ..\Binary\guifiles\tahoma.ttf
	File ..\Binary\guifiles\tahoma-bold.ttf
	File ..\Binary\guifiles\verdana.ttf
	File ..\Binary\guifiles\verdana-bold.ttf
	File ..\Binary\guifiles\aurora-bold-condensed-bt.ttf

	SetOutPath "$MODDIR\data\gui\images"
	File ..\Binary\guifiles\1.png
	File ..\Binary\guifiles\2.png
	File ..\Binary\guifiles\3.png
	File ..\Binary\guifiles\4.png
	File ..\Binary\guifiles\5.png
	File ..\Binary\guifiles\loadingscreen.png
	File ..\Binary\guifiles\loadingscreen_logos.png
	File ..\Binary\guifiles\logo.png
	File ..\Binary\guifiles\logo_m2mp.png
	File ..\Binary\guifiles\logo_raknet.jpg
	File ..\Binary\guifiles\quick_connect.png
	File ..\Binary\guifiles\connect.png
	File ..\Binary\guifiles\disconnect.png
	File ..\Binary\guifiles\refresh.png
	File ..\Binary\guifiles\settings.png
	File ..\Binary\guifiles\quit.png
	File ..\Binary\guifiles\locked.png

	SetOutPath "$MODDIR\data\gui\skins"
	File ..\Binary\guifiles\default.png
	File ..\Binary\guifiles\default.xml
	File ..\Binary\guifiles\default.looknfeel.xml
	File ..\Binary\guifiles\default.imageset.xml

	SetOutPath "$GAMEDIR\pc\sds\missionscript"
	File ..\Binary\gamefiles\freeraid_m2mp.sds

	SetOutPath "$GAMEDIR\edit"
	File ..\Binary\gamefiles\sdsmpconf.bin

	SetOutPath "$GAMEDIR\edit\tables"
	File ..\Binary\gamefiles\StreamM2MP.bin
	
	SetOutPath "$GAMEDIR\pc\sds\cars"
	File ..\Binary\gamefiles\cars\chaffeque.sds
	File ..\Binary\gamefiles\cars\chaffeque_z.sds
	File ..\Binary\gamefiles\cars\delizia_grandeamerica.sds
	File ..\Binary\gamefiles\cars\delizia_grandeamerica_z.sds
	File ..\Binary\gamefiles\cars\desta.sds
	File ..\Binary\gamefiles\cars\elysium.sds
	File ..\Binary\gamefiles\cars\elysium_z.sds
	File ..\Binary\gamefiles\cars\roller.sds
	File ..\Binary\gamefiles\cars\roller_z.sds
	File ..\Binary\gamefiles\cars\waybar.sds
	File ..\Binary\gamefiles\cars\waybar_z.sds
	File ..\Binary\gamefiles\cars\payback.sds
	File ..\Binary\gamefiles\cars\payback_z.sds
	File ..\Binary\gamefiles\cars\shubert_pickup.sds
	File ..\Binary\gamefiles\cars\shubert_pickup_z.sds
	File ..\Binary\gamefiles\cars\shubert_34.sds
	File ..\Binary\gamefiles\cars\shubert_34_z.sds
	File ..\Binary\gamefiles\cars\trautenberg_grande.sds
	File ..\Binary\gamefiles\cars\trautenberg_grande_z.sds
	File ..\Binary\gamefiles\cars\cadilla_miller_meteor_1959.sds
	
	SetOutPath "$GAMEDIR\edit\materials"
	File ..\Binary\gamefiles\default.mtl
	
	SetOutPath "$GAMEDIR\pc\sds_ru\text"
	File ..\Binary\gamefiles\text_default.sds
	
	SetOutPath "$GAMEDIR\pc\sds\mp"
	File ..\Binary\gamefiles\tables.sds
	
	SetOutPath "$GAMEDIR\pc"
	File ..\Binary\gamefiles\pc\Mafia2.exe
	File ..\Binary\gamefiles\pc\steam_api.dll
	File ..\Binary\gamefiles\pc\steam_appid.txt
	File ..\Binary\gamefiles\pc\Steamclient.dll
	
	SetOutPath "$GAMEDIR\pc\sds\hchar"
	File ..\Binary\gamefiles\hchar\brianc.sds
	File ..\Binary\gamefiles\hchar\derek.sds
	File ..\Binary\gamefiles\hchar\eddies.sds
	File ..\Binary\gamefiles\hchar\joebryl.sds
	File ..\Binary\gamefiles\hchar\joeciv.sds
	File ..\Binary\gamefiles\hchar\joeneup.sds
	File ..\Binary\gamefiles\hchar\leospo.sds
	File ..\Binary\gamefiles\hchar\steve.sds
	File ..\Binary\gamefiles\hchar\marty.sds
	
	SetOutPath "$GAMEDIR\pc\sds\skins_m2o"
	File ..\Binary\gamefiles\skins_m2o\amvoj1.sds
	File ..\Binary\gamefiles\skins_m2o\amvoj2.sds
	File ..\Binary\gamefiles\skins_m2o\amvojs.sds
	File ..\Binary\gamefiles\skins_m2o\balls.sds
	File ..\Binary\gamefiles\skins_m2o\bpvest1.sds
	File ..\Binary\gamefiles\skins_m2o\bpvest2.sds
	File ..\Binary\gamefiles\skins_m2o\brianv.sds
	File ..\Binary\gamefiles\skins_m2o\brianvz.sds
	File ..\Binary\gamefiles\skins_m2o\bruno.sds
	File ..\Binary\gamefiles\skins_m2o\butcher.sds
	File ..\Binary\gamefiles\skins_m2o\carlo.sds
	File ..\Binary\gamefiles\skins_m2o\carloz.sds
	File ..\Binary\gamefiles\skins_m2o\cat.sds
	File ..\Binary\gamefiles\skins_m2o\ccerb4.sds
	File ..\Binary\gamefiles\skins_m2o\ccerml4.sds
	File ..\Binary\gamefiles\skins_m2o\ccertl.sds
	File ..\Binary\gamefiles\skins_m2o\ccertl_kabat.sds
	File ..\Binary\gamefiles\skins_m2o\ccertl_kabatkrev.sds
	File ..\Binary\gamefiles\skins_m2o\ccindo.sds
	File ..\Binary\gamefiles\skins_m2o\ccinfet1.sds
	File ..\Binary\gamefiles\skins_m2o\ccinfet2.sds
	File ..\Binary\gamefiles\skins_m2o\cdete3.sds
	File ..\Binary\gamefiles\skins_m2o\cdozo1.sds
	File ..\Binary\gamefiles\skins_m2o\cdozo2.sds
	File ..\Binary\gamefiles\skins_m2o\cdozte.sds
	File ..\Binary\gamefiles\skins_m2o\celgre.sds
	File ..\Binary\gamefiles\skins_m2o\chem1.sds
	File ..\Binary\gamefiles\skins_m2o\chlid3.sds
	File ..\Binary\gamefiles\skins_m2o\chlid4.sds
	File ..\Binary\gamefiles\skins_m2o\chlid5.sds
	File ..\Binary\gamefiles\skins_m2o\cirhar.sds
	File ..\Binary\gamefiles\skins_m2o\citeri.sds
	File ..\Binary\gamefiles\skins_m2o\citeriz.sds
	File ..\Binary\gamefiles\skins_m2o\citga6fz.sds
	File ..\Binary\gamefiles\skins_m2o\citga7fz.sds
	File ..\Binary\gamefiles\skins_m2o\citga10z.sds
	File ..\Binary\gamefiles\skins_m2o\citgiu.sds
	File ..\Binary\gamefiles\skins_m2o\citklav2.sds
	File ..\Binary\gamefiles\skins_m2o\cmech1.sds
	File ..\Binary\gamefiles\skins_m2o\cmech2.sds
	File ..\Binary\gamefiles\skins_m2o\cmrtvlo.sds
	File ..\Binary\gamefiles\skins_m2o\corporal.sds
	File ..\Binary\gamefiles\skins_m2o\cpol5bp.sds
	File ..\Binary\gamefiles\skins_m2o\cpolfal1.sds
	File ..\Binary\gamefiles\skins_m2o\cpolfal2.sds
	File ..\Binary\gamefiles\skins_m2o\cpoli1.sds
	File ..\Binary\gamefiles\skins_m2o\cpoli2.sds
	File ..\Binary\gamefiles\skins_m2o\cpoli3.sds
	File ..\Binary\gamefiles\skins_m2o\cpoli4.sds
	File ..\Binary\gamefiles\skins_m2o\cpr4z.sds
	File ..\Binary\gamefiles\skins_m2o\cpr6.sds
	File ..\Binary\gamefiles\skins_m2o\cpradl.sds
	File ..\Binary\gamefiles\skins_m2o\cpros1nzad.sds
	File ..\Binary\gamefiles\skins_m2o\cpros2n.sds
	File ..\Binary\gamefiles\skins_m2o\cpros3f.sds
	File ..\Binary\gamefiles\skins_m2o\cpros3nak.sds
	File ..\Binary\gamefiles\skins_m2o\cpros3z_fmv.sds
	File ..\Binary\gamefiles\skins_m2o\cpros4n.sds
	File ..\Binary\gamefiles\skins_m2o\cpros5.sds
	File ..\Binary\gamefiles\skins_m2o\cpros6f.sds
	File ..\Binary\gamefiles\skins_m2o\cpros7n.sds
	File ..\Binary\gamefiles\skins_m2o\cpump3.sds
	File ..\Binary\gamefiles\skins_m2o\csicmu2.sds
	File ..\Binary\gamefiles\skins_m2o\csicmu4.sds
	File ..\Binary\gamefiles\skins_m2o\cvez1n_t.sds
	File ..\Binary\gamefiles\skins_m2o\cvez2n_t.sds
	File ..\Binary\gamefiles\skins_m2o\cvez3n_t.sds
	File ..\Binary\gamefiles\skins_m2o\cvez8.sds
	File ..\Binary\gamefiles\skins_m2o\cvez9.sds
	File ..\Binary\gamefiles\skins_m2o\cvez10.sds
	File ..\Binary\gamefiles\skins_m2o\cvez11.sds
	File ..\Binary\gamefiles\skins_m2o\cvez12.sds
	File ..\Binary\gamefiles\skins_m2o\cvez13.sds
	File ..\Binary\gamefiles\skins_m2o\cvez14.sds
	File ..\Binary\gamefiles\skins_m2o\cvezci1n_t.sds
	File ..\Binary\gamefiles\skins_m2o\cvezci2n_t.sds
	File ..\Binary\gamefiles\skins_m2o\doncal.sds
	File ..\Binary\gamefiles\skins_m2o\eddieo.sds
	File ..\Binary\gamefiles\skins_m2o\faluct.sds
	File ..\Binary\gamefiles\skins_m2o\franca_naked.sds
	File ..\Binary\gamefiles\skins_m2o\gorntl.sds
	File ..\Binary\gamefiles\skins_m2o\gorntlz.sds
	File ..\Binary\gamefiles\skins_m2o\hen40s.sds
	File ..\Binary\gamefiles\skins_m2o\hen40sz.sds
	File ..\Binary\gamefiles\skins_m2o\itcam1.sds
	File ..\Binary\gamefiles\skins_m2o\itcam2.sds
	File ..\Binary\gamefiles\skins_m2o\itvoj1.sds
	File ..\Binary\gamefiles\skins_m2o\itvoj2.sds
	File ..\Binary\gamefiles\skins_m2o\izak.sds
	File ..\Binary\gamefiles\skins_m2o\joed1.sds
	File ..\Binary\gamefiles\skins_m2o\joed2.sds
	File ..\Binary\gamefiles\skins_m2o\joeksl.sds
	File ..\Binary\gamefiles\skins_m2o\joeksl2.sds
	File ..\Binary\gamefiles\skins_m2o\joel1.sds
	File ..\Binary\gamefiles\skins_m2o\joel2.sds
	File ..\Binary\gamefiles\skins_m2o\joeobd.sds
	File ..\Binary\gamefiles\skins_m2o\joeobld.sds
	File ..\Binary\gamefiles\skins_m2o\joeobld2.sds
	File ..\Binary\gamefiles\skins_m2o\joepra.sds
	File ..\Binary\gamefiles\skins_m2o\joespo.sds
	File ..\Binary\gamefiles\skins_m2o\joetel.sds
	File ..\Binary\gamefiles\skins_m2o\joeukl.sds
	File ..\Binary\gamefiles\skins_m2o\joeukl_knirek.sds
	File ..\Binary\gamefiles\skins_m2o\joeup.sds
	File ..\Binary\gamefiles\skins_m2o\joevez.sds
	File ..\Binary\gamefiles\skins_m2o\joezml.sds
	File ..\Binary\gamefiles\skins_m2o\kungfu.sds
	File ..\Binary\gamefiles\skins_m2o\leoobd.sds
	File ..\Binary\gamefiles\skins_m2o\leovez.sds
	File ..\Binary\gamefiles\skins_m2o\lucca.sds
	File ..\Binary\gamefiles\skins_m2o\luccaz.sds
	File ..\Binary\gamefiles\skins_m2o\marco.sds
	File ..\Binary\gamefiles\skins_m2o\marco2.sds
	File ..\Binary\gamefiles\skins_m2o\martydeath.sds
	File ..\Binary\gamefiles\skins_m2o\mgngstr1.sds
	File ..\Binary\gamefiles\skins_m2o\mgngstr2.sds
	File ..\Binary\gamefiles\skins_m2o\mike.sds
	File ..\Binary\gamefiles\skins_m2o\owner.sds
	File ..\Binary\gamefiles\skins_m2o\ownerz.sds
	File ..\Binary\gamefiles\skins_m2o\panchu.sds
	File ..\Binary\gamefiles\skins_m2o\parker.sds
	File ..\Binary\gamefiles\skins_m2o\pepeob.sds
	File ..\Binary\gamefiles\skins_m2o\pepeve.sds
	File ..\Binary\gamefiles\skins_m2o\pepevez.sds
	File ..\Binary\gamefiles\skins_m2o\pes_cerny.sds
	File ..\Binary\gamefiles\skins_m2o\pes_hnedy.sds
	File ..\Binary\gamefiles\skins_m2o\pete.sds
	File ..\Binary\gamefiles\skins_m2o\pietro.sds
	File ..\Binary\gamefiles\skins_m2o\polchief.sds
	File ..\Binary\gamefiles\skins_m2o\rtrvez.sds
	File ..\Binary\gamefiles\skins_m2o\sailor1.sds
	File ..\Binary\gamefiles\skins_m2o\sailor2.sds
	File ..\Binary\gamefiles\skins_m2o\tomang.sds
	File ..\Binary\gamefiles\skins_m2o\tomangd.sds
	File ..\Binary\gamefiles\skins_m2o\vitbik.sds
	File ..\Binary\gamefiles\skins_m2o\vitcow.sds
	File ..\Binary\gamefiles\skins_m2o\vitm1.sds
	File ..\Binary\gamefiles\skins_m2o\vitmat.sds
	File ..\Binary\gamefiles\skins_m2o\vitnaho.sds
	File ..\Binary\gamefiles\skins_m2o\vitreb.sds
	File ..\Binary\gamefiles\skins_m2o\vitschool.sds
	File ..\Binary\gamefiles\skins_m2o\vitstar.sds
	File ..\Binary\gamefiles\skins_m2o\vitsuit.sds
	File ..\Binary\gamefiles\skins_m2o\vittel_kab.sds
	File ..\Binary\gamefiles\skins_m2o\vittux.sds
	File ..\Binary\gamefiles\skins_m2o\vitvezo.sds
	File ..\Binary\gamefiles\skins_m2o\vitvezoc.sds
	File ..\Binary\gamefiles\skins_m2o\williams.sds
	File ..\Binary\gamefiles\skins_m2o\witness.sds
	File ..\Binary\gamefiles\skins_m2o\wong.sds

	SetOutPath "$MODDIR\data\sounds"
	File ..\Binary\sounds\menu.mp3

	# Write the uninstaller
	WriteUninstaller "$MODDIR\Uninstall.exe"

	# Create the desktop shortcut
	SetOutPath "$MODDIR"
	CreateShortCut "$DESKTOP\${MOD_NAME}.lnk" "$MODDIR\m2online.exe"

	# Create the start menu shortcuts
	CreateDirectory "$SMPROGRAMS\${MOD_NAME}"
	CreateShortCut "$SMPROGRAMS\${MOD_NAME}\${MOD_NAME}.lnk" "$MODDIR\m2online.exe"
	CreateShortCut "$SMPROGRAMS\${MOD_NAME}\Uninstall.lnk" "$MODDIR\Uninstall.exe"

	# Write the registry keys
	WriteRegStr HKLM "${REG_NODE}" "DisplayName" "${MOD_NAME}"
	WriteRegStr HKLM "${REG_NODE}" "InstallLocation" "$MODDIR"
	WriteRegStr HKLM "${REG_NODE}" "GameDir" "$GAMEDIR"
	WriteRegStr HKLM "${REG_NODE}" "Version" "${MOD_VERS}"

	# Write the URI scheme
	WriteRegStr HKCR "m2online" "" "Mafia2-Online Protocol"
	WriteRegStr HKCR "m2online" "URL Protocol" ""
	WriteRegStr HKCR "m2online\DefaultIcon" "" "$\"$MODDIR\m2online.exe$\",1"
	WriteRegStr HKCR "m2online\shell\open\command" "" "$\"$MODDIR\m2online.exe$\" $\"-uri %1$\""

SectionEnd

Function un.onInit

	SetShellVarContext all

	# Verify they want to uninstall
	MessageBox MB_OKCANCEL "Are you sure you want to uninstall ${MOD_NAME}?" IDOK next
		Abort

	next:
		!insertmacro VerifyUserIsAdmin

FunctionEnd

Section "Uninstall"

	ReadRegStr $GAMEDIR HKLM "${REG_NODE}" "GameDir"
	ReadRegStr $MODDIR HKLM "${REG_NODE}" "InstallLocation"

	Delete "$GAMEDIR\..\sds\missionscript\freeraid_m2o.sds"
	Delete "$GAMEDIR\..\..\edit\tables\StreamM2O.bin"
	RMDir /r "$MODDIR"

	# Delete the desktop shortcut
	Delete "$DESKTOP\${MOD_NAME}.lnk"

	# Delete the start menu items
	RMDir /r "$SMPROGRAMS\${MOD_NAME}"

	# Delete the registry keys
	DeleteRegKey HKLM "${REG_NODE}"

SectionEnd
