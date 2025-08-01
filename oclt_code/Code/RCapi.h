//RC API 
// Run Config API

//Copyright FoxaXu 2024C
// Based on OpenCppLangTab

#include"../shload.h"
#include"../Code/ThirdPartyCode.h"
#include<thread>


int CL_FMV_ID = 2206; // Calcium Lang Format Version
//_$req_cl_fmv <Version>

/// <VERSION>
//releaseVerKnd
const string _KV_rV_Debug = "1";
const string _KV_rV_Preview = "2";
const string _KV_rV_preRelease = "3";
const string _KV_rV_Demo = "4";
const string _KV_rV_Release = "5";
const string _KV_rV_Stable = "6";

//Other Version
const string _KV_rV_Custom = "7";
const string _KV_rV_Embed = "8";
const string _KV_rV_Deluxe = "9";

//Main Char
string _kv_text_debug = "Debug";
string _kv_text_preview = "Preview";
string _kv_text_prerelease = "Prerelease";
string _kv_text_demo = "Demo";
string _kv_text_release = "Release";
string _kv_text_stable = "stable";

//OV
string _kv_text_custom = "Custom";
string _kv_text_embed = "Embed";
string _kv_text_deluxe = "Deluxe";
//rVK END

//RunIDs
string _CK_Runid = _get_random_s(100000, 999999);

string _KV_softwareVersion = "117"; //(Software Version)

string _KV_gen = "4";//(General)

string _KV_rv = "3";//(Release Version)

string _KV_releaseVer = _KV_rV_Release;//(Debug/Preview/preRelease/demo/Release  1 - 4)

string _mk = ".";

string _KernelVersion = _KV_softwareVersion + _mk + _KV_gen + _mk + _KV_rv + _mk + _KV_releaseVer;

//DEFINE
/// </VERSION>
/// 

void _KernelVersion_LoadText(void);
//Define

const string _rc_false = "false";
const string _rc_true = "true";

//carrige return,
const int _hex_cr = 00001101; // HEX 0D

// new line
const int _hex_nl = 00001010; // HEX 0A

//Build / Release / Prerelease   -  Release ID 
const string _RCapi_Version = "REV_DISUSE";
string buildshell = "/calcium_settings.cfg";
string _shellTitle = "Calcium Kernel  " + _KernelVersion + "   Shell Console>";

bool _isAdminOK_ = false;

//Rc Config var
bool _rcset_syscmd;
bool _rcset_allowdiredit;
bool _rcset_allowtp;
bool _rcset_anticrash;

bool _rcset_directmode;
bool _rcset_trustcheck;
bool _rcset_offlangcheck;

bool _rcset_shelledit,_rcset_scriptedit;

bool _rcset_enforceUTF8;

bool _rcset_aosr;

bool _rcset_useAdmin;

bool _rcset_netwk_confirm;



bool _rcset_crash_reload;

string _rcbind_pluginscript, _rcbind_pluginpath,_rcbind_thirdbind,_rcbind_autorun,_rcbind_autorunargs;
string _rcbind_langpath;
string _rcset_lang;
string _rcset_seclang;
string _rcbind_serverapi;
string _rc_activate_key;
string _rc_exec_address;
string _pagefile_savedir;

int _exec_runtimesleep = 1;

bool _VarSpace_Random_BreakTest = false;
int VarSpaceRandomError = 0;

//Other
bool New_thread_auto_join = false;
bool Thread_Env = false;
std::thread AddNewScript;

void _pv(string info) {
	_p(_Old_VSAPI_TransVar(info));
	return;
}

void _RcApi_vp_load(void) {
	_varspaceadd("{path}", _$GetSelfPath);
	_varspaceadd("{VersionID}", _KernelVersion);
}

string _RcApi_TapiBuffer;
bool _RcLoad_TransApi(string _Rc_ID) {
	_RcApi_TapiBuffer = _load_sipcfg_noreturn(buildshell, _Rc_ID);
	//_p("tapi Buffer :  " + _Rc_ID + "  " + _RcApi_TapiBuffer);
	if (_RcApi_TapiBuffer == _rc_true) {
		return true;
	}
	if (_RcApi_TapiBuffer == _rc_false) {
		return false;
	}

	_p("--------------------------------------------------------------------");
	_p("Null Config Set");
	_p("Setting :   " + _Rc_ID + "       Data :   \"" + _RcApi_TapiBuffer + "\"");
	_p("Data is not true or false");
	_p("Trans Api cannot identify \"" + _RcApi_TapiBuffer + "\"");
	_p("TransApi Return false");
	return false;
}

string url_cache;
bool _api_request_download(string Address,string Save) {
	url_cache = _rcbind_serverapi + "/" + Address;
	_p("api server :  " + _rcbind_serverapi);
	_p("request some files...   please wait");
	_p("url :  " + url_cache);
	if (!_urldown_api_nocache(url_cache, Save)){
		_p("URL Request Failed");
		return false;
	}
	return true;
}

bool _api_request_clear(string Address, string Save) {
	url_cache = _rcbind_serverapi + "/" + Address;
	if (!_urldown_api_nocache(url_cache, Save)) {
		return false;
	}
	return true;
}

bool _api_request_clear_cache(string Address, string Save) {
	url_cache = _rcbind_serverapi + "/" + Address;
	if (!_urldown_api(url_cache, Save)) {
		return false;
	}
	return true;
}


string file;
bool _direct_read_script = false;
int _gf_line_maxallow = 32768;
bool _RcApiLoadConfig() {
	//_p("Loading Config");
	file = buildshell;
	if (!check_file_existence(file)) {
		_p("Create New Config");
		_dapi_create_full_path(file);
		_soildwrite_open(file);
		_soildwrite_write(" //BuildShell SipCfg  --Use  true/false");
		_soildwrite_write("$CalciumVersion={null};");
		_soildwrite_write("$EnableSystemCommand=false;");
		_soildwrite_write("$EnableAntiCrash=true;");
		_soildwrite_write("$EnableCrashReload=true;");
		_soildwrite_write("$AllowDirectoryEdit=false;");
		_soildwrite_write("$AllowThirdPartyPlugin=false;");
		_soildwrite_write("$AllowShellEdit=true;");
		_soildwrite_write("$AllowScriptEdit=false;");
		_soildwrite_write("$UseDirectRead=false;");
		_soildwrite_write("$TrustedServerCheck=true;");
		_soildwrite_write("$OffLangCheck=false;");
		_soildwrite_write("$MaxScriptExecuteLine=32768;");
		_soildwrite_write("$AfterExecuteSleepTime=0;");
		_soildwrite_write("$VarSpaceRandomError=0;");
		_soildwrite_write("$NoNetWorkConfirm=false;");
		_soildwrite_write("");
		_soildwrite_write("//ShellSettings");
		_soildwrite_write("$AutoOpenShellAfterRun=true;");
		_soildwrite_write("$UseSuperUser=false;");
		_soildwrite_write("");
		_soildwrite_write("//Bind");
		_soildwrite_write("$AutoRun=null;");
		_soildwrite_write("$AutoRunArgs=null;");
		_soildwrite_write("");
		_soildwrite_write("//PathBind");
		_soildwrite_write("$DefaultPluginPath={path}/Plugin;");
		_soildwrite_write("$DefaultPluginScript={path}/script;");
		_soildwrite_write("$DefaultLanguagePath={path}/lang;");
		_soildwrite_write("$PageFile=script/pagefile.catemp;");
		_soildwrite_write("");
		_soildwrite_write("//Display Settings");
		_soildwrite_write("$Language=en-us;");
		_soildwrite_write("$SecondLanguage=en-us;");
		_soildwrite_write("");
		_soildwrite_write("//Windows Only");
		_soildwrite_write("$EnforceUTF-8=false;");
		_soildwrite_write("");
		_soildwrite_write("//Server");
		_soildwrite_write("$RootAPIServer=http://githubimage.foxaxu.com;");
		_soildwrite_write("$Kernelactivate={Nokey};");
		_soildwrite_write("$ExecuteFile=" + _$GetSelfFull + ";");
		_soildwrite_write("");
		_soildwrite_close();
	}
	_write_sipcfg(file, "CalciumVersion", _KernelVersion);
	_rcset_syscmd = _RcLoad_TransApi("EnableSystemCommand");
	_rcset_anticrash = _RcLoad_TransApi("EnableAntiCrash");
	_rcset_crash_reload = _RcLoad_TransApi("EnableCrashReload");
	_rcset_allowdiredit = _RcLoad_TransApi("AllowDirectoryEdit");
	_rcset_allowtp = _RcLoad_TransApi("AllowThirdPartyPlugin");
	_rcset_shelledit = _RcLoad_TransApi("AllowShellEdit");
	_rcset_scriptedit = _RcLoad_TransApi("AllowScriptEdit");
	_rcset_directmode = _RcLoad_TransApi("UseDirectRead");
	_rcset_trustcheck = _RcLoad_TransApi("TrustedServerCheck");
	_rcset_offlangcheck = _RcLoad_TransApi("OffLangCheck");
	_gf_line_maxallow = atoi(_load_sipcfg_noreturn(file, "MaxScriptExecuteLine").c_str());
	_exec_runtimesleep = atoi(_load_sipcfg_noreturn(file, "AfterExecuteSleepTime").c_str());
	VarSpaceRandomError = atoi(_load_sipcfg_noreturn(file, "VarSpaceRandomError").c_str());
	_rcset_netwk_confirm = _RcLoad_TransApi("NoNetWorkConfirm");

	_rcset_aosr = _RcLoad_TransApi("AutoOpenShellAfterRun");
	_rcset_useAdmin = _RcLoad_TransApi("UseSuperUser");

	//String
	_rcbind_autorun = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "AutoRun"));
	_rcbind_autorunargs = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "AutoRunArgs"));
	_rcbind_pluginpath = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "DefaultPluginPath"));
	_rcbind_pluginscript = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "DefaultPluginScript"));
	_rcbind_langpath = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "DefaultLanguagePath"));
	_pagefile_savedir = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "PageFile"));

	_rcset_lang = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "Language"));
	_rcset_seclang = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "SecondLanguage"));
	//Lang 
	_rcset_enforceUTF8 = _RcLoad_TransApi("EnforceUTF-8");

	_rcbind_serverapi = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "RootAPIServer"));
	_rc_activate_key= _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "Kernelactivate"));
	_rc_exec_address = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "ExecuteFile"));

	//Create Directory
	if (!_rcset_offlangcheck) {
		if (!_dapi_ExistFolder_check(_rcbind_langpath)) {
			_dapi_create_full_path(_rcbind_langpath + "/a.txt");
		}
	}

	//Auto Set
	_direct_read_script = _rcset_directmode;

	//End

	_KernelVersion_LoadText();

	return true;
}


string fitback,fitbuffer;
string _Char_Filter_EndFileName(string fitchar) {
	fitchar = ReplaceChar(fitchar, "\\", "/");
	fitback = "";

	for (int fullsize = fitchar.size(); true; fullsize--) {
		fitbuffer = fitchar[fullsize];
		if (fitbuffer == "/") {
			fitback = cutendchar(fitback);
			return fitback;
		}

		fitback = fitbuffer + fitback;

	}

	return "LineError";
}


string cachecstp;
string filiter_mfh;
string cache_filepath;
string getfile;
string verifyGet;
string _cstp_file_write = "a.cstp";
int readptr = 1;
bool AntiDoubleCopy = false;
bool CstpOutput = true;

bool _$cstp_writeapiN(string file) {
	if (!check_file_existence(file)) {
		if (CstpOutput)_pv("Cstp _$lang.loadfail :  _$lang.filenotfound");
		return false;
	}
	cache_filepath = ReplaceChar(file, filiter_mfh, "");
	_soildwrite_write("$CSTP_FILE_RECORD_MARK_ID_START(" + cache_filepath + ");");

	for (int readptr = 1; true; readptr++) {
		cachecstp = LineReader(file, readptr);
		if (cachecstp == "overline") {
			if(CstpOutput)_p("End LoadScript. Total :  " + to_string(readptr));
			break;
		}
		if (cachecstp == "ReadFailed") {
			return false;
		}
		_soildwrite_write(cachecstp);
	}
	_soildwrite_write("$CSTP_FILE_RECORD_MARK_ID_END(" + cache_filepath + ");");
	return true;
}
bool _cstp_makerN(string make_file_header,string file) {
	CreateFileMap_txt("makedirmap.txt", make_file_header);
	_cstp_file_write = file;
	filiter_mfh = make_file_header;
	make_file_header = "makedirmap.txt";
	_p("Execute Pack Directory " + _cstp_file_write);
	if (check_file_existence(_cstp_file_write)) {
		_fileapi_del(_cstp_file_write);
	}
	_soildwrite_open(_cstp_file_write);
	if (!check_file_existence(make_file_header)) {
		if (CstpOutput)_pv("Cstp Make failed :   _$lang.filenotfound");
		return false;
	}
	_soildwrite_write("Calcium_Text_Pack_File  New Format");
	_soildwrite_write("//START EXTRACT");
	for (int readptr = 1; true; readptr++) {
		getfile = cachecstp = LineReader(make_file_header, readptr);
		if (cachecstp == "overline") {
			break;
		}
		if (cachecstp == "ReadFailed") {
			break;
		}
		if (CstpOutput)_p("\r                                                             \r Add File :   " + cachecstp);
		if (_$cstp_writeapiN(cachecstp)) {
			//_pv("Cstp File :  " + getfile);
		}
		else {
			//_pv("Failed :  " + getfile);
		}
		continue;
	}
	if (CstpOutput)_pv("cstp make _$lang.complete");
	_fileapi_del("makedirmap.txt");
	_fileapi_del("empty.txt");
	return true;
}
bool _$cstp_unpackapiN(string file,string resourcefile,int startline,string extract_dir) {

	_dapi_create_full_path(extract_dir + "/" + file);
	readptr++;
	if (CstpOutput)cout << "\r                                                             \r Extract File :  " + file;
	if (check_file_existence(extract_dir + "/" + file)) {
		_fileapi_del(extract_dir + "/" + file);
	}
	creatpath(extract_dir + "/" + file);
	_soildwrite_open(extract_dir + "/" + file);
	for (; true; readptr++) {
		cachecstp = LineReader(resourcefile, readptr);
		if (cachecstp == "overline") {
			break;
		}
		if (cachecstp == "ReadFailed") {
			return false;
		}
		if (SizeRead(cachecstp, 29) == "$CSTP_FILE_RECORD_MARK_ID_END") {
			verifyGet = PartReadA(cachecstp, "(", ")", 1);
			if (verifyGet == getfile) {
				break;
			}
		}
		_soildwrite_write(cachecstp);
	}
	_soildwrite_close();
	if (!check_file_existence(extract_dir + "/" + file)) {
		_p("failed to write file " + file);
		return false;
	}
	else {
		return true;
	}

	return false;
}
bool _cstp_unpackN(string unpack_path, string file) {
	if (CstpOutput)_p("Extract Package " + file);
	if (!check_file_existence(file)) {
		if (CstpOutput)_pv("Cstp Unpack failed :   _$lang.filenotfound " + file);
		return false;
	}
	for (; true; readptr++) {
		getfile = cachecstp = LineReader(file, readptr);
		if (cachecstp == "overline") {
			break;
		}
		if (cachecstp == "ReadFailed") {
			break;
		}
			if (SizeRead(cachecstp, 31) == "$CSTP_FILE_RECORD_MARK_ID_START") {
				getfile = PartReadA(cachecstp, "(", ")", 1);
				if (!_$cstp_unpackapiN(getfile, file, readptr, unpack_path)) {
					if (CstpOutput)_pv("Failed :  " + getfile);
				}
		}
		continue;
	}
	if (CstpOutput)_pv("cstp unpack _$lang.complete");
	return true;
}


//Legacy CSTP
bool _Legacy_$cstp_writeapi(string file) {
	if (!check_file_existence(file)) {
		_pv("Cstp _$lang.loadfail :  _$lang.filenotfound");
		return false;
	}
	cache_filepath = ReplaceChar(file, filiter_mfh, "");
	_soildwrite_write("$sign_file_output(" + cache_filepath + ");");

	for (int readptr = 1; true; readptr++) {
		cachecstp = LineReader(file, readptr);
		if (cachecstp == "overline") {
			_p("End LoadScript. Total :  " + to_string(readptr));
			break;
		}
		if (cachecstp == "ReadFailed") {
			return false;
		}
		_soildwrite_write(cachecstp);
	}
	_soildwrite_write("$sign_file_close;");
	return true;
}
bool _Legacy_cstp_maker(string make_file_header, string file) {
	CreateFileMap_txt("makedirmap.txt", make_file_header);
	_cstp_file_write = file;
	filiter_mfh = make_file_header;
	make_file_header = "makedirmap.txt";
	if (CstpOutput)_p("Execute Pack Directory " + _cstp_file_write);
	if (check_file_existence(_cstp_file_write)) {
		_fileapi_del(_cstp_file_write);
	}
	_soildwrite_open(_cstp_file_write);
	if (!check_file_existence(make_file_header)) {
		_pv("Cstp Make failed :   _$lang.filenotfound");
		return false;
	}
	_soildwrite_write("calcium_script_text_package");
	_soildwrite_write("//Text Package");
	for (int readptr = 1; true; readptr++) {
		getfile = cachecstp = LineReader(make_file_header, readptr);
		if (cachecstp == "overline") {
			break;
		}
		if (cachecstp == "ReadFailed") {
			break;
		}
		if (CstpOutput)_p("Add File :   " + cachecstp);
		if (_Legacy_$cstp_writeapi(cachecstp)) {
			if (CstpOutput)_pv("Cstp File :  " + getfile);
		}
		else {
			if (CstpOutput)_pv("Failed :  " + getfile);
		}
		continue;
	}
	if (CstpOutput)_pv("cstp make _$lang.complete");
	_fileapi_del("makedirmap.txt");
	_fileapi_del("empty.txt");
	return true;
}
bool _Legacy_$cstp_unpackapi(string file, string resourcefile, int startline, string extract_dir) {
	_dapi_create_full_path(extract_dir + "/" + file);
	readptr++;
	if (CstpOutput)cout << "\r                                                             \r Extract File :  " + file;
	if (check_file_existence(extract_dir + "/" + file)) {
		_fileapi_del(extract_dir + "/" + file);
	}
	creatpath(file);
	_soildwrite_open(extract_dir + "/" + file);
	for (; true; readptr++) {
		cachecstp = LineReader(resourcefile, readptr);
		if (cachecstp == "overline") {
			break;
		}
		if (cachecstp == "ReadFailed") {
			return false;
		}
		if (SizeRead(cachecstp, 16) == "$sign_file_close") {
			break;
		}
		_soildwrite_write(cachecstp);
	}
	_soildwrite_close();
	if (!check_file_existence(extract_dir + "/" + file)) {
		_p("failed to write file " + file);
		return false;
	}
	else {
		return true;
	}

	return false;
}
bool _Legacy_cstp_unpack(string unpack_path, string file) {
	if (CstpOutput)_p("Extract Package " + file);
	if (!check_file_existence(file)) {
		_pv("Cstp Unpack failed :   _$lang.filenotfound " + file);
		return false;
	}
	for (; true; readptr++) {
		getfile = cachecstp = LineReader(file, readptr);
		if (cachecstp == "overline") {
			break;
		}
		if (cachecstp == "ReadFailed") {
			break;
		}
		if (SizeRead(cachecstp, 17) == "$sign_file_output") {
			getfile = PartReadA(cachecstp, "(", ")", 1);
			if (!_Legacy_$cstp_unpackapi(getfile, file, readptr, unpack_path)) {
				_pv("Failed :  " + getfile);
			}
		}
		continue;
	}
	_pv("cstp unpack _$lang.complete");
	return true;
}

string dircache;
bool _packsetup(string packid) {
	dircache = _$GetSelfPath + "/Setup_" + _get_random_s(1,10000);
	if (!_api_request_download(packid,dircache)) {
		if (!_api_request_clear_cache(packid, dircache)) {
			_pv("_packsetup _$lang.fail :  " + packid);
			return false;
		}
	}

	_Legacy_cstp_unpack(_rcbind_pluginscript, dircache);
	_p("complete ...");

	_fileapi_del(dircache);

	return true;
}

int tbd_year;
int tbd_month;
int tbd_day;
bool _TBD_WARNING;
string TBD_STR;
string TBD_cache;
bool _Time_Bomb_Detect(string CurrentRV) {
	TBD_STR = to_string(tbd_year) + "/" + to_string(tbd_month) + "/" + to_string(tbd_day);
	TBD_cache = __GetCurrentTimeAPI(__Time_Year, false) + "/" + to_string(_GetCurrentTimeAPI(__Time_Month, false)) + "/" + to_string(_GetCurrentTimeAPI(__Time_Day, false));

	_TBD_WARNING = false;
	if (atoi(CurrentRV.c_str()) > 4) {
		return false;
	}

	//P1
	_p("TBD Notification  :     Current Time :  <" + TBD_cache + ">     TBD Date :   <" + TBD_STR + ">");
	if (TBD_STR == TBD_cache) {
		_TBD_WARNING = true;
		return false;
	}

	//P2

	if (tbd_year < _GetCurrentTimeAPI(__Time_Year, false)) {
		_p("Year Outdate");
		_p(" [TBD]  Out of Date");
		return true;
	}

	if (tbd_month < _GetCurrentTimeAPI(__Time_Month, false)) {
		_p("Month Outdate");
		_p(" [TBD]  Out of Date");
		return true;
	}

	if (tbd_day < _GetCurrentTimeAPI(__Time_Day, false)) {
		_p("Day Outdate");
		_p(" [TBD]  Out of Date");
		return true;
	}


	_p(" [TBD]  Time check pass");
	return false;
}

string activate_id;
string at_cache;
bool _TrustedServer;
bool _activate_calcium(string Key_Register) {
	if (_rcset_trustcheck == true) {
		if (!_urldown_api_nocache("http://githubimage.foxaxu.com/TrustedServer.txt", "TrustedList.txt")) {
			_TrustedServer = false;
		}
		else {
			if (FindCharLine(1, "TrustedList.txt", _rcbind_serverapi) == -4) {
				_TrustedServer = false;
			}
			else {
				_TrustedServer = true;
			}
			_fileapi_del("TrustedList.txt");
		}
	}
	else {
		_TrustedServer = false;
	}
	
	if (_KV_relver$int > 4) {
		//No Verify
		if (_rc_exec_address != _$GetSelfFull) {
			_write_sipcfg(buildshell, "ExecuteFile", _$GetSelfFull);
			_rc_exec_address = _Old_VSAPI_TransVar(_load_sipcfg(buildshell, "ExecuteFile"));
		}
		return true;
	}
	if (SizeRead(Key_Register, 10) != "USER-SIGN-") {
		return false;
	}
	activate_id = PartReadA(Key_Register, "(", ")", 1);

	if (_TrustedServer == false) {
		_p("You are trying to activate Calcium using an untrusted server.");
		_p("Please use a trusted server. you can read this list http://githubimage.foxaxu.com/TrustedServer.txt");
		return false;
	}
	if (_TBD_WARNING == true) {
		_p("ERROR :  End of evaluation period");
		return false;
	}

	if (!_api_request_clear("activateRequest/" + activate_id, "activateSign.tmp")) {
		_p("Your activation code is invalid");
		return false;
	}

	at_cache = _fileapi_textread("activateSign.tmp", 1);
	_fileapi_del("activateSign.tmp");

	if (Key_Register == at_cache) {
		return true;
	}
	if (at_cache == "violation") {
		_pv("_$lang.false.violation");
		return false;
	}

	_p("You entered an activation code that is not the current product");
	return false;
}

bool _activate_request(string key_reg) {
	_kernel_activate = _activate_calcium(key_reg);
	if (_kernel_activate == true) {
		if (key_reg != "{Nokey}") {
			_write_sipcfg(buildshell, "Kernelactivate", key_reg);
		}
	}

	return _kernel_activate;
}

void _var_typetext(string file) {
	if (_existfile(file)) {
		int maxdocsize = getdocmax(file);

		maxdocsize++;

		for (int startRoll = 1; maxdocsize != startRoll; startRoll++) {
			_p(_Old_VSAPI_TransVar(_fileapi_textread(file, startRoll)));
		}
		return;
	}
	else {
		_sh_throw_error("FileAPI.TypeText :  File Not Exist");
		return;
	}
}

void _Create_Analysis_File(string savefile) {
	_soildwrite_open(savefile);
	_soildwrite_write("::Calcium Analysis File");
	_soildwrite_write("::Copyright FoxaXu " + $year_message);
	_soildwrite_write("::Kernel Message");
	_soildwrite_write("-Execute File Path :   " + _$GetSelfFull);
	_soildwrite_write("-System :  " + _Run_SysKernel);
	_soildwrite_write("-Calcium Activate Status :  " + to_string(_kernel_activate));
	_soildwrite_write("-Language :  " + _rcset_lang + "    Second Language :  " + _rcset_seclang);
	_soildwrite_write("-Version :  " + _KernelVersion);
	_soildwrite_write("-Created Time :  " + __GetFullTime());
	_soildwrite_write("");
	_soildwrite_write("");
	_soildwrite_write("");
	_soildwrite_write("----Project ID----");
	_soildwrite_write("-CID  :    " + _CTitle);
	_soildwrite_write("-VerText :     " + _KV_rV_Text);
	_soildwrite_write("-InsideVersion :     " + InsideVersion);
	_soildwrite_write("----OpenCppLangTab----");
	_soildwrite_write("-OCLT ID :  " + $version_title);
	_soildwrite_write("-OCLT Release :  " + $version_msg);
	_soildwrite_write("-OCLT CodeName :   " + $codename);
	_soildwrite_write("-OCLT RID :    " + $version_code_str);
	_soildwrite_write("-OCLT BuildTime :  " + $buildtime);
	_soildwrite_write("+ Debug ++++++++++++++++++++++++++++++++");
	_soildwrite_write("");
	_soildwrite_write("---- VarSpace Map-----");
	_soildwrite_write(VarSpace);
	_soildwrite_write("----End varspace ----");
	_soildwrite_write("");
	_soildwrite_write("----Execute Address----");
	_soildwrite_write("Script File :  " + _global_scriptload + " Line :  " + to_string(_gf_line) + "  breakpoint :  " + to_string(_gf_cg));
	_soildwrite_write("---- End address----");
	_soildwrite_write("");
}

int ExecCache;
string _PluginExecuteAPI(string execplugin,string script,int address) {
	if (!check_file_existenceA(execplugin)) {
		execplugin = _rcbind_pluginpath + "/" + execplugin;
			if (!check_file_existenceA(execplugin)) {
				_p("Fail load error:  File not Exist");
				_p(execplugin);
				return "pluginnotfound";
			}
	}

	ExecCache = _system_autoRun(execplugin, _$quo + script + _$quo + " " + to_string(address));


}

//New Goto API
// -4 NotFound
int fal_cache,cd_cache;
string fal_buffer;
int _FindAllLine(int startline, int skipline, string file, string charData) {
	cd_cache = charData.size();
	fal_cache = FindCharLineA(startline, skipline, file, charData);
	if (fal_cache == -4) return -4;

	fal_buffer = LineReader(file, fal_cache);
	fal_buffer = HeadSpaceClean_NoSEM(fal_buffer);

	if (SizeRead(fal_buffer,cd_cache) != charData) while (true) {
		fal_cache++;
		fal_cache = FindCharLineA(fal_cache, skipline, file, charData);
		if (fal_cache == -4) return -4;
		fal_buffer = LineReader(file, fal_cache);
		fal_buffer = HeadSpaceClean_NoSEM(fal_buffer);
		if (SizeRead(fal_buffer, cd_cache) != charData) continue;
		break;
	}

	return fal_cache;
}

int FC_A, FC_B, CP_POINT;
string CP_CACHE_A, CP_CACHE_B;
bool FileCompare_(string fileA, string fileB) {

	if (!check_file_existence(fileA))return false;
	if (!check_file_existence(fileB))return false;

	FC_A = _textapi_getdocmax(fileA);
	FC_B = _textapi_getdocmax(fileB);

	if (FC_A != FC_B)return false;

	CP_POINT = 1;

	for (; 1; CP_POINT++) {

		CP_CACHE_A = _fileapi_textread(fileA, CP_POINT);
		CP_CACHE_B = _fileapi_textread(fileB, CP_POINT);

		if (CP_CACHE_A == "badread") {
			return false;
		}
		if (CP_CACHE_A == "badParameter") {
			return false;
		}
		if (CP_CACHE_A == "badopen") {
			return false;
		}

		if (CP_CACHE_B == "badread") {
			return false;
		}
		if (CP_CACHE_B == "badParameter") {
			return false;
		}
		if (CP_CACHE_B == "badopen") {
			return false;
		}

		//Check Over
		if (CP_CACHE_A == CP_CACHE_B) {
			if (CP_CACHE_A == "overline") return true;
		}

		if (CP_CACHE_A != CP_CACHE_B) return false;

		continue;
	}
	//P2
}

string CharFilter_(string msg) {
	msg = ReplaceChar(msg, "\\r", "\r");

	msg = ReplaceChar(msg, "\\t", "\t");

	msg = ReplaceChar(msg, "\\n", "\n");

	msg = ReplaceChar(msg, "\\b", "\b");

	return msg;
}

//DiskPerfTest

bool SWTTStop = false;
int TotalWrtSize;
int SpeedWriteTestThread() {
	//File WriteStream
	while (SWTTStop == false) {
		_fileapi_write(_$GetSelfPath + "/bmwf.tmp", "This is Calcium File Write Performance Test");
		TotalWrtSize++;
	}

	return 0;
}



int FileWriteSpeedTest() {
	SWTTStop = false;
	TotalWrtSize = 1;
	_fileapi_write(_$GetSelfPath + "/bmwf.tmp","Start BenchMark");
	thread SpeedWrite(SpeedWriteTestThread);
	SpeedWrite.detach();
	sleepapi_ms(3000);
	SWTTStop = true;
	
	sleepapi_ms(1000);
	_fileapi_del(_$GetSelfPath + "/bmwf.tmp");

	TotalWrtSize = TotalWrtSize / 3;

	return TotalWrtSize;
}

//COmmand ProcessAPI

bool CMDPROCStop = false;
int TotalProcSize;
int OperateSize, OSA, OSB;

int FileCmdProcThread() {
	while(CMDPROCStop == false) {
		LineReader(_$GetSelfPath + "/bmwf.tmp", 1);
		OperateSize = _get_random(1, 100);
		OSA = _get_random(1, 100);
		OSB = _get_random(1, 100);
		OperateSize = OperateSize * OSA;
		OperateSize = OperateSize * OSB;
		TotalProcSize++;
	}
	return 0;
}


int FileCmdProcessSpeedTest() {
	_fileapi_write(_$GetSelfPath + "/bmwf.tmp","Start Analysis Test: OOOOOOOOOOOOOOOOOOOOQQQQQQQQQQQQQQQQQQQQQQAAAAAAAAAAAAAAAAAA");

	CMDPROCStop = false;
	TotalProcSize = 0;

	thread ProcessCmd(FileCmdProcThread);
	ProcessCmd.detach();
	sleepapi_ms(3000);
	CMDPROCStop = true;
	sleepapi_ms(1000);

	_fileapi_del(_$GetSelfPath + "/bmwf.tmp");

	TotalProcSize = TotalProcSize / 3;

	return TotalProcSize;
}



int CommandSpeed_CountNum = 0;
int LastCache_TPC = 0;
int TotalCommandExec_TPC = 0;

int LastCache_TPD = 0;
int TotalCE_TPD = 0;

int MAX_TPC, MAX_TPD;

bool ProcessReqStop = false;
bool is_TPC_already_Running = false;
bool TPC_all_exit = true;
string PerfCNT_ID,PerfCNT_File,Address_TrackFile;
int Thread_PerfCurrentGet() {
	//StartLE

	Address_TrackFile = _$GetSelfPath + "/StepTrack " + PerfCNT_ID + ".txt";

	LastCache_TPC = 0;
	TPC_all_exit = false;
	ProcessReqStop = false;
	TotalCommandExec_TPC = 0;
	CommandSpeed_CountNum = 0;
	is_TPC_already_Running = true;

	LastCache_TPD = 0;
	TotalCE_TPD = 0;

	MAX_TPC = 0;
	MAX_TPD = 0;

	CommandSpeed_CountNum = 0;
	LRBuffer_Count = 0;

	while (1) {
		sleepapi_ms(1000);
		//CPU
		LastCache_TPC = CommandSpeed_CountNum;
		CommandSpeed_CountNum = 0;
		TotalCommandExec_TPC = TotalCommandExec_TPC + LastCache_TPC;
		if (MAX_TPC < LastCache_TPC)MAX_TPC = LastCache_TPC;

		LastCache_TPD = LRBuffer_Count;
		LRBuffer_Count = 0;
		TotalCE_TPD = TotalCE_TPD + LastCache_TPD;
		if (MAX_TPD < LastCache_TPD)MAX_TPD = LastCache_TPD;

		PerfCNT_File = _$GetSelfPath + "/api_cpspeed_id " + PerfCNT_ID + ".txt";

		_fileapi_del(PerfCNT_File);
		_fileapi_write(PerfCNT_File, "Calcium Performance Record Tool");
		_fileapi_write(PerfCNT_File, "Current Command Speed :   " + to_string(LastCache_TPC) + " / Every second     MaxSpeed:  " + to_string(MAX_TPC));
		_fileapi_write(PerfCNT_File, "Total Execute Command :    " + to_string(TotalCommandExec_TPC));
		_fileapi_write(PerfCNT_File, " ");
		_fileapi_write(PerfCNT_File, "Disk IO :   " + to_string(LastCache_TPD) + " / Every second     MaxSpeed:  " + to_string(MAX_TPD));
		_fileapi_write(PerfCNT_File, "Total Disk CR :    " + to_string(TotalCE_TPD));
		_fileapi_write(PerfCNT_File, " ");
		_fileapi_write(PerfCNT_File, "Processing address.  File :  " + _global_scriptload + " Line :  " + to_string(_gf_line) + "  breakpoint :  " + to_string(_gf_cg));
		if (ProcessReqStop == true) break;
		
		continue;
	}

	is_TPC_already_Running = false;
	_fileapi_del(PerfCNT_File);
	_fileapi_del(Address_TrackFile);
	TPC_all_exit = true;

	return 0;
}