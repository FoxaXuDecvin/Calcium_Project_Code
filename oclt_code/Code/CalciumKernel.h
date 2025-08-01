﻿//Calcium Kernel Base2

//Copyright FoxaXu 2024
// Based on OpenCppLangTab

#include"../shload.h"
#include"../Code/RCapi.h"


//VCODE
// 110(Software Version).1(General).1(Release Version).1(Debug/Preview/preRelease/Release  1 - 4)

void _KernelVersion_LoadText(void) {
	_KV_relver$int = atoi(_KV_releaseVer.c_str());
	_KV_rV_Text = "{Unknown KrV ;  " + _KV_releaseVer + " }";

	if (_KV_releaseVer == _KV_rV_Debug) {
		_KV_rV_Text = _kv_text_debug;
	}
	if (_KV_releaseVer == _KV_rV_Preview) {
		_KV_rV_Text = _kv_text_preview;
	}
	if (_KV_releaseVer == _KV_rV_preRelease) {
		_KV_rV_Text = _kv_text_prerelease;
	}
	if (_KV_releaseVer == _KV_rV_Demo) {
		_KV_rV_Text = _kv_text_demo;
	}
	if (_KV_releaseVer == _KV_rV_Release) {
		_KV_rV_Text = _kv_text_release;
	}
	if (_KV_releaseVer == _KV_rV_Stable) {
		_KV_rV_Text = _kv_text_stable;
	}

	//Other
	if (_KV_releaseVer == _KV_rV_Custom) {
		_KV_rV_Text = _kv_text_custom;
	}
	if (_KV_releaseVer == _KV_rV_Embed) {
		_KV_rV_Text = _kv_text_embed;
	}
	if (_KV_releaseVer == _KV_rV_Deluxe) {
		_KV_rV_Text = _kv_text_deluxe;
	}

	return;
}

//Define-Head
string _runcode_api(string command);
string PartReadA(string Info, string StartMark, string EndMark, int RPartSizeA);

//HeadSpaceClean .  Default = true
bool _gf_hsc = true;
void _gfL_reset(void);
//GetFULL API
bool _gf_status;
string _gf_FLMark = ";";
string _gf_charget;
string _gf_makebuffer,_gf_getbuffer;
string _get_fullLine(string load_script, string EndMark) {
	_gf_FLMark = EndMark;
	if (!check_file_existence(load_script)) {
		return "badfound";
	}
	//Clear Makebuffer
	_gf_makebuffer = "";

	//get and make
	for (; true; _gf_line++) {
		//Reset Char
		for (; true; _gf_cg++) {
			//_p("Road Fresh    Line :   " + to_string(_gf_line));
			//Textread
			_gf_getbuffer = _fileapi_textread(load_script, _gf_line);
			//Check Status Code
			if (_gf_getbuffer == "overline") {
				_gf_status = false;
				return "badread";
			}
			if (_gf_getbuffer == "ReadFailed") {
				_gf_status = false;
				return "badopen";
			}
			if (_gf_getbuffer == "LineError") {
				_gf_status = false;
				return "badParameter";
			}

			if (_gf_hsc == true) {
				_gf_getbuffer = HeadSpaceClean_NoSEM(_gf_getbuffer);
			}

			if (SizeRead(_gf_getbuffer, 2) == "//") {
				_gf_cg = -1;
				_gf_cgmax = 1;
				_gf_line++;
				_gf_charget = "";
				continue;
			}
			if (_gf_getbuffer == "") {
				_gf_cg = -1;
				_gf_cgmax = 1;
				_gf_line++;
				_gf_charget = "";
				continue;
			}

			//GetProcess
			_gf_cgmax = _gf_getbuffer.size();
			//_p("   cg :   " + to_string(_gf_cg) + " cgmax :  " + to_string(_gf_cgmax));

			//OpenProcess
			while (true) {
				//Reset char get
				if (_gf_cg == _gf_cgmax) {
					//_p("Char Reset");
					_gf_cg = -1;
					_gf_cgmax = 1;
					_gf_line++;
					_gf_charget = "";
					break;
				}

				if (_gf_line > _gf_line_maxallow) {
					_gf_status = false;
					return "Over Size";
				}

				//_p("line :  " + to_string(_gf_line) + "   cg :   " + to_string(_gf_cg) + " cgmax :  " + to_string(_gf_cgmax) + "   charMake = " + _gf_makebuffer);

				_gf_charget = _gf_getbuffer[_gf_cg];
				if (_gf_charget == "\\") {
					_gf_cg++;
					_gf_charget = _gf_charget + _gf_getbuffer[_gf_cg];
					_gf_cg++;
					_gf_charget = _gf_charget + _gf_getbuffer[_gf_cg];
				}
				_gf_cg++;
				//_p("charget =  " + _gf_charget);
				_gf_makebuffer = _gf_makebuffer + _gf_charget;
				//_p("_gf_makebuffer = _gf_makebuffer + _gf_charge  ===  _gf_makebuffer  = " + _gf_makebuffer + "  + " + _gf_charget + "$");
				if (_gf_charget == _gf_FLMark) {
					_gf_status = true;
					return _gf_makebuffer;
				}
				//EndProcess
			}
		}

		continue;
	}

	_gf_status = false;
	return "Kernel Exception :   _get_fullLine";
}
//END GETFULL API

//Direct read
string _get_direct_read(string load_script) {;
	if (!check_file_existence(load_script)) {
		return "badfound";
	}
	//Clear Makebuffer
	_gf_getbuffer = "";

	//get and make

	while (true) {
		//_p("D START");
		_gf_getbuffer = LineReader(load_script, _gf_line);
		//_p("DATA :   " + _gf_getbuffer + "    " + to_string(_gf_line));

		if (_gf_getbuffer == "overline") {
			_gf_status = false;
			return "badread";
		}
		if (_gf_getbuffer == "ReadFailed") {
			_gf_status = false;
			return "badopen";
		}
		if (_gf_getbuffer == "LineError") {
			_gf_status = false;
			return "badParameter";
		}

		if (_gf_hsc == true) {
			_gf_getbuffer = HeadSpaceCleanA(_gf_getbuffer);
		}

		if (_gf_getbuffer == "") {
			_logrec_write("[Engine Direct] Find Empty Line --> on :  " + to_string(_gf_line) + "  size :  " + to_string(_gf_cg));
			_gf_line++;
			continue;
		}

		if (SizeRead(_gf_getbuffer, 2) == "//") {
			_gf_line++;
			continue;
		}

		break;
	}

	_gf_line++;

	_gf_status = true;
	//_p("D STOP");
	return _gf_getbuffer;
}


//Main Script Load
bool _CK_ShellMode = false;
string _cmd_marks = "_";
string cmdbuffer;
string _api_result;
bool _stop_exec_script = false;
string _ckapi_scriptload(string load_Script,string Sargs) {
	//_p("Load Main Kernel");
	_logrec_write("This log will be disable no longer");
	ifstream _SessionLock;
	_SessionLock.open(load_Script);
	if (!_language_mode) {
		if (!_kernel_activate) {
			_pv("_$lang.notactivate");
			_pv("_$lang.activatehelp");
			_pv("ScriptAPI _$lang.Access_Denied : ");
			return "ok";
		}
	}
	//_p("Speed check point 1");
	_global_scriptload = load_Script;
	script_args = Sargs;
	_$logfile = _rcbind_logrec + "/" + _Char_Filter_EndFileName(load_Script) + "_LogRec.log";
	//_p("Speed check point 2");
	if (check_file_existence(_$logfile))_fileapi_del(_$logfile);
	if (!check_file_existence(load_Script)) {
		_pv("_$lang.runfail");
		_pv("Error :  _$lang.filenotfound");
		return "nf01";
	}
	//_p("Speed check point 3");
	//Character Process ...
	_api_result = "scriptloadfailed";

	_gfL_reset();

	//_p("Speed check point 4");

	if (_rcset_logrec == true) {
		if (!check_file_existence(_$logfile)) {
			//_pv("_$lang.logfail " + _$logfile);
		}
	}

	//_p("Speed check point 5");

	while (true) {
		_global_scriptload = load_Script;
		//_p("Speed check point 6");
		if (_direct_read_script == false) {
			if (is_TPC_already_Running == true) {
				_fileapi_write(Address_TrackFile, "Method :  Full Line Read.  File :  " + _global_scriptload + " Line :  " + to_string(_gf_line) + "  breakpoint :  " + to_string(_gf_cg));
			}
			cmdbuffer = _get_fullLine(load_Script, ";");
		}
		else {
			if (is_TPC_already_Running == true) {
				_fileapi_write(Address_TrackFile, "Method :  Direct Read.  File :  " + _global_scriptload + " Line :  " + to_string(_gf_line - 1) + "  breakpoint :  " + to_string(_gf_cg));
			}
			cmdbuffer = _get_direct_read(load_Script);
		}
		if (_gf_status == false) {
			_pv("_$lang.stoprun.  Return status code :  " + cmdbuffer + "  . Args :  " + _global_scriptload + "   Line :  " + to_string(_gf_line) + " + " + to_string(_gf_cg));
			return "ok";
		}
		

		if (cmdbuffer == "badread") {
			return "Error :   badread";
		}
		if (cmdbuffer == "badParameter") {
			return "Error :   badParameter";
		}
		if (cmdbuffer == "badopen") {
			return "Error :   badopen";
		}

		//_p("Speed check point 7");

		//Code Analysis
		if (_stop_exec_script == true) {
			_stop_exec_script = false;
		}
		last_return = _api_result = _runcode_api(cmdbuffer);
		//_p("Speed check point 8");
		if (_api_result == "runid.exit") {
			return "runid.exit";
		}
		if (_api_result == "runid.entershell") {
			return "runid.entershell";
		}
		if (_api_result == "runid.coverscript") {
			return "runid.coverscript";
		}


		if (_stop_exec_script == true) {
			return _api_result;
		}

		//_p("Speed check point 9");

		//NEXT
	}

	return _api_result;
}

int thread_debug_status;
int _Thread_CreateScript(string File,string argument_s) {
	thread_debug_status = _system_autoRun(_$GetSelfFull, _$GetSelfFull + "  -run \"" + File + "\" -args \"" + argument_s + "\" -threadmode -anticrash_ok");
	return thread_debug_status;
}

void _gfL_reset(void) {
	_gf_cg = 0;
	_gf_cgmax = 1;
	_gf_line = 1;
	return;
}
string langfile;
string seclangfile;
bool _skipcheck_language = false;
bool LanguageLoad() {
	langfile = _rcbind_langpath + "/" + _rcset_lang;
	seclangfile = _rcbind_langpath + "/" + _rcset_seclang;
	if (!check_file_existence(langfile)) {
		return false;
	}
	_logrec_write("Loading  Language :   " + langfile);
	_language_mode = true;
	_ckapi_scriptload(seclangfile, "langmode");
	_gfL_reset();
	_ckapi_scriptload(langfile, "langmode");
	_gfL_reset();
	_ckapi_scriptload(_rcbind_langpath + "/errcode_list.txt", "langmode");
	_gfL_reset();
	_language_mode = false;
	_stop_exec_script = false;
	return true;
}

string varbufA;
string charCutA, charCutB, CharCutC, CharCutD;
string chartempA, chartempB, chartempC, chartempD;
string _rc_varid, _rc_varinfo;
int intCutA, intCutB, intCutC;
int dbA, dbB, dbC, dbD;
long long LdbA, LdbB, LdbC, LdbD;
float FdbA, FdbB, FdbC, FdbD;
double HdbA, HdbB, HdbC, HdbD;
bool sw_a, sw_b, sw_c;
bool _debug_type_detected = false;
bool _var_auto_void = false;
bool _shell_lock = false;
bool _if_reverse = false;
string lost_memory;
//KernelCommand

int ModifyCount;
int procesid_ccode;
char CK_ConvertTemp[1024];
string Net_script_nameid;
int __CreateNewThreads(string Script,string args,string originEnv,string proces_runid) {
	procesid_ccode = _system_autoRun(_$GetSelfFull, "-run \"" + Script + "\" -args \"" + args + "\" -loadenv \"" + originEnv + "\" -runid \"" + proces_runid + "\" -fastmode");
	return procesid_ccode;
}

string _runcode_api(string command) {
	CommandSpeed_CountNum++;
	//cout << "Origin Execute Command :   " << command << endl;
	sleepapi_ms(_exec_runtimesleep);

	_logrec_write("[Reset] --------------------------------New Command---------------------------------------------------------");
	if (_gf_hsc == true) {
		command = HeadSpaceCleanA(command);
	}
	string oldcmd = command;
	command = _Old_VSAPI_TransVar(command);
	//_logrec_write("[INFO] _var api :   --> " + oldcmd + " | to |  " + command);
	if (oldcmd == command) {
		_var_auto_void = false;
	}
	else {
		_var_auto_void = true;
	}
	if (_debug_type_detected == true) {
		_p("Detect command :   " + command);
		_p("Detect Resource   :   " + oldcmd);
	}
	//Command Process

	_logrec_write("[Execute] Command :   " + command + "   Old :  " + oldcmd);
	if (atoi(command.c_str()) != 0) {
		if (atoi(command.c_str()) != 1) {
			return command;
		}
	}
	if (command == "") {
		if (_debug_type_detected == true) {
			_p("command is empty");
		}
		return"empty";
	}
	if (SizeRead(command, 1) == ":") {
		if (_debug_type_detected == true) {
			_p("command is goto mark");
		}
		return"empty";
	}
	if (SizeRead(command, 1) == ";") {
		if (_debug_type_detected == true) {
			_p("command is empty with ;(EndMark)");
		}
		return"empty";
	}
	if (command == "1") {
		return "true";
	}
	if (command == "0") {
		return "false";
	}
	if (command == "true") {
		return "true";
	}
	if (command == "false") {
		return "false";
	}

	if (SizeRead(command,1) == "1") {
		return "true";
	}
	if (SizeRead(command, 1) == "0") {
		return "false";
	}
	if (SizeRead(command, 4) == "true") {
		return "true";
	}
	if (SizeRead(command, 5) == "false") {
		return "false";
	}

	if (SizeRead(command, 12) == "_$req_cl_fmv") {
		//Request CL Format Version

		charCutA = PartReadA(oldcmd, " ", PartRead_FMend, 1);

		intCutA = atoi(charCutA.c_str());

		if (CL_FMV_ID >= intCutA) {
			return "allow";
		}
		else {
			_pv("_$lang.req.clfmv " + charCutA);
			_pause();
			return "runid.exit";
		}



		_p(charCutB);
		return "error";
	}

	//Memory Control
	kernelenvVid = "3.21";
	if (SizeRead(command, 23) == "_enable_var_randombreak") {
		_VarSpace_Random_BreakTest = true;
		_p("Var Space Random Error is True");
		return "ok";
	}
	if (SizeRead(command, 5) == "_var ") {
		string _rc_varbind;
		if (checkChar(command, "=")) {
			//Detecd illegal char = 

		

			_rc_varbind = HeadSpaceCleanA(PartRead(oldcmd, " ", "=", false));
			_rc_varinfo = _runcode_api(HeadSpaceCleanA(PartRead(oldcmd, "=", "$FROMEND$",false)));

			

		}
		else {
			_rc_varbind = HeadSpaceCleanA(PartReadA(command, " ", "$FROMEND$", 1));
			_rc_varinfo = "{null}";
		}
		_logrec_write("[Exec] Create VarSpace");
		intCutA = _get_random(0, _rc_varinfo.size());
		if(_VarSpace_Random_BreakTest == true)for (int count_addr = 0; count_addr != intCutA; count_addr++) {
			//Need Break ?
			intCutC = _get_random(1, 100);
			if (VarSpaceRandomError < intCutC)break;
			//lC
			intCutB = _rc_varinfo.size();
			intCutB--;
		ENullREGETRANDOMBRK:
			ModifyCount = _get_random(1, intCutB);

			if (_rc_varinfo[ModifyCount] == ';') goto ENullREGETRANDOMBRK;
			if (_rc_varinfo[ModifyCount] == '=') goto ENullREGETRANDOMBRK;

			_rc_varinfo[ModifyCount] = '?';
		}
		//_p("Report ENV  " + to_string(ModifyCount) + " VRB:  " + to_string(VarSpaceRandomError) + "  AllBreak Num  " + to_string(intCutA) + "   B " + to_string(intCutB) + "   C " + to_string(intCutC));
		_varspaceadd(_rc_varbind, _rc_varinfo);
		_logrec_write("[INFO]  varid --> " + _rc_varbind + "   varinfo --> " + _rc_varinfo);

		return "ok";
	}
	if (SizeRead(command, 10) == "_var_reset") {
		VarSpace = "varspace;";
		VarSpaceMax = 0;
		return "ok";
	}
	if (SizeRead(command, 6) == "_free ") {
		_rc_varid = HeadSpaceCleanA(PartReadA(oldcmd, " ", "$FROMEND$", 1));
		_varspacedelete(_rc_varid);
		_logrec_write("VarSpace Delete  --> " + _rc_varid);

		return "ok";
	}
	if (SizeRead(command, 1) == "\"") {
		if (charTotal(command, "\"") < 2) {
			_p("[ERROR]  Quotation Format illegal  --> " + command);
			_logrec_write("[ERROR]  Quotation Format illegal-- > " + command);
			return "illegal_format";
		}
		charCutA = PartReadA(command, "\"", "\"", 1);
		//
		charCutA = CharFilter_(charCutA);
		//
		_logrec_write("[INFO] Return char" + _$quo + charCutA + _$quo);
		return charCutA;
	}
	if (SizeRead(command, 1) == "\'") {
		if (charTotal(oldcmd, "\'") < 2) {
			_p("[ERROR]  Quotation Format illegal  --> " + oldcmd);
			_logrec_write("[ERROR]  Quotation Format illegal-- > " + oldcmd);
			return "illegal_format";
		}
		charCutA = PartReadA(oldcmd, "\'", "\'", 1);

		charCutA = CharFilter_(charCutA);

		_logrec_write("[INFO] (No Var ) Return char " + _$quo + charCutA + _$quo);
		return charCutA;
	}

	if (SizeRead(command, 5) == "_exit") {
		ProcessReqStop = true;
		while (!TPC_all_exit) {
			cout << "Waiting TPC Service Exit" << endl;
		}
		return "runid.exit";
	}
	if (SizeRead(command, 4) == "exit") {
		ProcessReqStop = true;
		while (!TPC_all_exit) {
			cout << "Waiting TPC Service Exit" << endl;
		}
		return "runid.exit";
	}
	if (SizeRead(command, 7) == "_return") {
		charCutA = _runcode_api(PartReadA(oldcmd, " ", PartRead_FMend, 1));

		_logrec_write("_Exec Return Data :  " + charCutA);
		_stop_exec_script = true;
		return charCutA;
	}

	//CONFIG
	if (SizeRead(command, 8) == "_envsave") {
		charCutA = PartReadA(oldcmd, " ", PartRead_FMend, 1);
		_logrec_write("[EnvSave] Save :  -->  " + charCutA);
		charCutB = _runcode_api(charCutA);

		if (check_file_existence(charCutB))_fileapi_del(charCutB);

		_fileapi_write(charCutB, to_string(VarSpaceMax));
		_fileapi_write(charCutB, VarSpace);


		return "ok.save";
	}
	if (SizeRead(command, 8) == "_envload") {
		charCutA = PartReadA(oldcmd, " ", PartRead_FMend, 1);
		_logrec_write("[EnvSave] Load :  -->  " + charCutA);
		charCutB = _runcode_api(charCutA);

		if (!check_file_existence(charCutB)) {
			_p("EnvLoad Error Fail");
			_p("FileNotExist");
			return "failfile";
		}

		VarSpaceMax = atoi(_fileapi_textread(charCutB, 1).c_str());
		VarSpace = _fileapi_textread(charCutB, 2);

		return "ok.save";
	}
	if (SizeRead(command, 9) == "_cfgedit ") {
		_logrec_write("[KernelManager] CFGEDIT");

		if (_CK_ShellMode == false) {
			//ScriptMode
			if (_rcset_scriptedit == false) {
				_pv("_$lang.sys.t1  " + buildshell);
				_p("Please set AllowScriptEdit  == true");
				_logrec_write("[KernelManager][WARNING] Access is Denied");
				return "denied";
			}
		}
		if (_CK_ShellMode == true) {
			//ShellMode
			if (_rcset_shelledit == false) {
				_pv("_$lang.sys.t1  " + buildshell);
				_p("Please set AllowShellEdit  == true");
				_logrec_write("[KernelManager][WARNING] Access is Denied");
				return "denied";
			}
		}
		if (checkChar(command, "=")) {
			_rc_varid = HeadSpaceCleanA(PartReadA(command, " ", "=", 1));
			_rc_varinfo = HeadSpaceCleanA(PartReadA(command, "=", "$FROMEND$", 1));

			_rc_varinfo = ReplaceChar(_rc_varinfo, ";", "");

			_write_sipcfg(buildshell, _rc_varid, _rc_varinfo);
			_logrec_write("[KernelManager] Set :  " + _rc_varid + " = " + _rc_varinfo);
			_pv("_$lang.cfgedit.r");
			return "ok";
		}
		else {
			_rc_varid = HeadSpaceCleanA(PartReadA(command, " ", "$FROMEND$", 1));
			_p("Config " + _rc_varid + " == " + _load_sipcfg(buildshell, _rc_varid));
			return "ok";
		}
		return "falseproblem";
	}
	if (SizeRead(command, 9) == "_cfgread ") {
		_logrec_write("[KernelManager] Config Read");

		if (_CK_ShellMode == false) {
			//ScriptMode
			if (_rcset_scriptedit == false) {
				_pv("_$lang.sys.t1  " + buildshell);
				_p("Please set AllowScriptEdit  == true");
				_logrec_write("[KernelManager][WARNING] Access is Denied");
				return "denied";
			}
		}
		if (_CK_ShellMode == true) {
			//ShellMode
			if (_rcset_shelledit == false) {
				_pv("_$lang.sys.t1  " + buildshell);
				_p("Please set AllowShellEdit  == true");
				_logrec_write("[KernelManager][WARNING] Access is Denied");
				return "denied";
			}
		}
		_rc_varid = HeadSpaceCleanA(PartReadA(command, " ", "$FROMEND$", 1));
		_logrec_write("[KernelManager] Read Settings :  " + _rc_varid);
		charCutA = _load_sipcfg(buildshell, _rc_varid);
		_logrec_write("[KernelManager] Return Value -->  " + charCutA);
		return charCutA;
	}
	if (SizeRead(command, 7) == "_reload") {
		_logrec_write("[KernelManager] RCapi Reload");
		_pv("_$lang.reloading");
		_gf_cg = 0;
		_gf_cgmax = 1;
		_gf_line = 1;
		_sipcfg_reset();
		if (!_RcApiLoadConfig()) {
			_p("Failed to Load RCapi.");
			_p("Config file is missing :  " + buildshell);
			_p("try to repair and try again.");
			_pause();
			return "false";
		}
		LanguageLoad();
		_pv("_$lang.reload");
		return "ok";
	}
	if (SizeRead(command, 10) == "_$analysis") {
		_Create_Analysis_File(_$GetSelfPath + "/~Calcium_Analysis_File.log");
		_p("File is created on " + _$GetSelfPath + "/~Calcium_Analysis_File.log");
		return "ok";
	}

	//Verify PRODUCT
	kernelSecureVid = "3.41";
	if (SizeRead(command, 10) == "_$activate") {
		if (_kernel_activate == false) {
			if (command == "_$activate") {
				_prts("Write your activation code here >");
				charCutA = _getline_type();
			}
			else {
				charCutA = PartReadA(oldcmd, "(", ")", 1);
			}
			if (!_activate_request(charCutA)) {
				_pv("_$lang.act_fail");
			}
			else {
				_pv("_$lang.act_succ_t1");
				_pv("_$lang.act_succ.t2");
				_write_sipcfg(buildshell, "ExecuteFile", _$GetSelfFull);
				_rc_exec_address = _Old_VSAPI_TransVar(_load_sipcfg(buildshell, "ExecuteFile"));
			}
			return "ok";
		}
	}
	if (!_language_mode) {
		if (!_kernel_activate) {
			_pv("_$lang.notactivate");
			_pv("_$lang.activatehelp");
			_pv("_$lang.act_need : " + command);
			return "ok";
		}
		if (_rc_exec_address != _$GetSelfFull) {
			_pv("_$lang.activateModified");
			_pv("_$lang.activateRe");
			_kernel_activate = false;
			return "ok";
		}
	}

	//Open Command
	//oldcmd = command;

	kernelcmdVid = "5.13";
	_logrec_write("[Execute] Full : " + oldcmd);
	if (SizeRead(command, 4) == "_prt") {
		charCutA = PartReadA(oldcmd, " ", PartRead_FMend, 1);
		_logrec_write("[Output Exec] Command :  -->  " + charCutA);
		charCutB = _runcode_api(charCutA);

		_logrec_write("[Exec] PRINT :  " + _$quo + charCutB + _$quo);

		_prts(charCutB);
		return "ok.print:<" + charCutB + ">";
	}
	if (SizeRead(command, 5) == "_cout") {
		charCutA = PartReadA(oldcmd, " ", PartRead_FMend, 1);
		_logrec_write("[Output Exec] Command :  -->  " + charCutA);
		charCutB = _runcode_api(charCutA);

		_logrec_write("[Exec] COUT :  " + _$quo + charCutB + _$quo);
		_p(charCutB);
		return "ok.print:<" + charCutB + ">";
	}
	if (SizeRead(command, 7) == "_system") {
		if (_rcset_syscmd == false) {
			_pv("_$lang.sys.t1  " + buildshell);
			_pv("_$lang.sys.t2");
			_pv("_$lang.sys.t3 :   _cfgedit EnableSystemCommand = true;");
			_logrec_write("[WARNING] System Command Disabled");

			return "denied";
		}
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		charCutB = _runcode_api(charCutA);
		_logrec_write("[Exec] Run System Command   --> " + charCutB);
		_str_system(charCutB);

		return "ok";
	}
	if (SizeRead(command, 6) == "_pause") {
		$_pause = _Old_VSAPI_TransVar("_$lang.pause");
		_pause();
		return"ok";
	}
	if (SizeRead(command, 6) == "_sleep") {
		charCutA = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1)));
		if (charCutA == "true") charCutA = "1";
		if (charCutA == "0") {
			_pv("Error :  _sleep(0) _$lang.notNum");
			return "ok";
		}
		intCutA = atoi(charCutA.c_str());
		if (intCutA == 0) {
			_pv("Error :  _sleep(" + charCutA + ") _$lang.notNum.");
			return "ok";
		}

		_logrec_write("_Program Sleep " + charCutA);
		sleepapi(intCutA);
		return "ok";
	}
	if (SizeRead(command, 9) == "_ms_sleep") {
		charCutA = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1)));
		if (charCutA == "true") charCutA = "1";
		if (charCutA == "0") {
			_pv("Error :  _sleep(0) _$lang.notNum");
			return "ok";
		}
		intCutA = atoi(charCutA.c_str());
		if (intCutA == 0) {
			_pv("Error :  _sleep(" + charCutA + ") _$lang.notNum.");
			return "ok";
		}

		_logrec_write("_Program Sleep " + charCutA);
		sleepapi_ms(intCutA);
		return "ok";
	}
	if (SizeRead(command, 8) == "_execute") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ")", "$FROMEND$", 1)));

		//_p("Execute Command :   " + _rc_varid + " " + _rc_varinfo);
		if (!check_file_existence(_rc_varid)) {
			if (check_file_existence(_rcbind_pluginpath + "/" + _rc_varid)) {
				_rc_varid = _rcbind_pluginpath + "/" + _rc_varid;
			}
			else {
				_pv("Execute Error :   _$lang.filenotfound");
				return "filenotfound";
			}
		}
		_logrec_write("[Exec] Run Application :   " + _rc_varid + "  Argument :  " + _rc_varinfo);
		intCutA = _system_autoRun(_rc_varid, _rc_varinfo);

		return to_string(intCutA);
	}
	if (SizeRead(command, 6) == "_goto ") {
		if (_CK_ShellMode == true) {
			_p("Calcium Kernel is running on Shell Mode");
			_p("Please use this command on script");
			return "false";
		}
		charCutA = PartRead(oldcmd, " ", PartRead_FMend, false);
		if (_direct_read_script == true) {
			_gf_line--;
		}
		intCutA = _FindAllLine(1, _gf_line, _global_scriptload, charCutA);
		if (_direct_read_script == true) {
			_gf_line++;
		}
		if (intCutA == -4) {
			_p("_goto Error");
			_p("No Head :   ---> " + charCutA);
			_p("Execution termination");
			return "runid.exit";
		}

		if (_debug_type_detected == true) {
			_p("Find char mark in " + to_string(intCutA));
		}

		intCutA++;

		_gf_cg = 0;
		_gf_cgmax = 1;
		_gf_line = intCutA;
		_gf_charget = "";

		return "runid.line_reset";
	}
	if (SizeRead(command, 6) == "_clear") {
		cleanConsole();
		return "ok";
	}
	if (SizeRead(command, 7) == "_script") {

		charCutB = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "<", ">", 1)));
		chartempA = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ">", "$FROMEND$", 1)));

		if (!check_file_existenceA(charCutB)) {
			if (check_file_existence(_rcbind_pluginscript + "/" + charCutB)) {
				charCutB = _rcbind_pluginscript + "/" + charCutB;
				goto markstartExecuteScript;
			}
			if (check_file_existence(_$GetSelfPath + "/" + charCutB)) {
				charCutB = _$GetSelfPath + "/" + charCutB;
				goto markstartExecuteScript;
			}

			_p("_runscript Error:  File not Exist");
			_p(charCutB);
			return "filenotfound";
		}

		markstartExecuteScript:

		//Backup old GFapi data;

		int _old$_gf_cg = _gf_cg;
		int _old$_gf_cgmax = _gf_cgmax;
		int _old$_gf_line = _gf_line;
		bool _old$_direct_read_script = _direct_read_script;
		bool _old$_rcset_logrec = _rcset_logrec;
		string _old$_args = script_args;
		string _old$_logfile = _$logfile;
		bool _old$_CK_ShellMode = _CK_ShellMode;
		string _old$_global_scriptload = _global_scriptload;

		//Create New Space

		_gf_cg = 0;
		_gf_cgmax = 1;
		_gf_line = 1;
		_gf_charget = "";
		_direct_read_script = false;
		_CK_ShellMode = false;

		//Run
	COVERRUNTAGS:
		//_p("LoadScript :  " + charCutB);
		CharCutC = _ckapi_scriptload(charCutB, chartempA);
		//_p("LoadScriptEnd Result :  " + CharCutC);
		if (CharCutC == "runid.coverscript") {
			//_p("Detect Cover");
			charCutB = $coverscript;
			chartempA = $coverscript_args;
			goto COVERRUNTAGS;
		}

		if (_stop_exec_script == true) {
			_stop_exec_script = false;
		}

		//Recovery old GFapi Data;
		_gf_cg = _old$_gf_cg;
		_gf_cgmax = _old$_gf_cgmax;
		_gf_line = _old$_gf_line;
		_gf_charget = "";
		script_args = _old$_args;
		_direct_read_script = _old$_direct_read_script;
		_rcset_logrec = _old$_rcset_logrec;
		_$logfile = _old$_logfile;
		_CK_ShellMode = _old$_CK_ShellMode;
		_global_scriptload = _old$_global_scriptload;

		if (CharCutC == "runid.exit") {
			return CharCutC;
		}
		if (CharCutC == "runid.entershell") {
			return CharCutC;
		}
		return CharCutC;
	}
	if (SizeRead(command, 11) == "_url_script") {
		Net_script_nameid = _$GetSelfPath + "/script/Temp~urlscript_" + _get_random_s(10000, 99999) + "_.ca";

		_fileapi_del(Net_script_nameid);

		charCutB = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "<", ">", 1)));

		//Download Script
		if (!_urldown_api_nocache(charCutB, Net_script_nameid)) {
			cout << "[Error] Download URL Script failed .  please check your Internet and try again" << endl;
			return "false";
		};

		charCutB = Net_script_nameid;

		chartempA = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ">", "$FROMEND$", 1)));

		if (!check_file_existenceA(charCutB)) {
			if (check_file_existence(_rcbind_pluginscript + "/" + charCutB)) {
				charCutB = _rcbind_pluginscript + "/" + charCutB;
				goto markstartExecuteScript_TAP;
			}
			if (check_file_existence(_$GetSelfPath + "/" + charCutB)) {
				charCutB = _$GetSelfPath + "/" + charCutB;
				goto markstartExecuteScript_TAP;
			}

			_p("_runscript Error:  File not Exist");
			_p(charCutB);
			return "filenotfound";
		}

	markstartExecuteScript_TAP:

		//Backup old GFapi data;

		int _old$_gf_cg = _gf_cg;
		int _old$_gf_cgmax = _gf_cgmax;
		int _old$_gf_line = _gf_line;
		bool _old$_direct_read_script = _direct_read_script;
		bool _old$_rcset_logrec = _rcset_logrec;
		string _old$_args = script_args;
		string _old$_logfile = _$logfile;
		bool _old$_CK_ShellMode = _CK_ShellMode;
		string _old$_global_scriptload = _global_scriptload;

		//Create New Space

		_gf_cg = 0;
		_gf_cgmax = 1;
		_gf_line = 1;
		_gf_charget = "";
		_direct_read_script = false;
		_CK_ShellMode = false;

		//Run
	COVERRUNTAGS_TAP:
		//_p("LoadScript :  " + charCutB);
		CharCutC = _ckapi_scriptload(charCutB, chartempA);
		_fileapi_del(Net_script_nameid);
		//_p("LoadScriptEnd Result :  " + CharCutC);
		if (CharCutC == "runid.coverscript") {
			//_p("Detect Cover");
			charCutB = $coverscript;
			chartempA = $coverscript_args;
			goto COVERRUNTAGS_TAP;
		}

		if (_stop_exec_script == true) {
			_stop_exec_script = false;
		}

		//Recovery old GFapi Data;
		_gf_cg = _old$_gf_cg;
		_gf_cgmax = _old$_gf_cgmax;
		_gf_line = _old$_gf_line;
		_gf_charget = "";
		script_args = _old$_args;
		_direct_read_script = _old$_direct_read_script;
		_rcset_logrec = _old$_rcset_logrec;
		_$logfile = _old$_logfile;
		_CK_ShellMode = _old$_CK_ShellMode;
		_global_scriptload = _old$_global_scriptload;


		if (CharCutC == "runid.exit") {
			return CharCutC;
		}
		if (CharCutC == "runid.entershell") {
			return CharCutC;
		}
		return CharCutC;
	}
	if (SizeRead(command, 6) == "_cover") {

		charCutB = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "<", ">", 1)));
		chartempA = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ">", "$FROMEND$", 1)));

		if (!check_file_existenceA(charCutB)) {
			if (check_file_existence(_rcbind_pluginscript + "/" + charCutB)) {
				charCutB = _rcbind_pluginscript + "/" + charCutB;
				goto StartExecuteMode;
			}
			if (check_file_existence(_$GetSelfPath + "/" + charCutB)) {
				charCutB = _$GetSelfPath + "/" + charCutB;
				goto StartExecuteMode;
			}

			_p("_runscript Error:  File not Exist");
			_p(charCutB);
			return "filenotfound";
		}

		StartExecuteMode:
		$coverscript = charCutB;
		$coverscript_args = chartempA;
		//_p("Cover Script : " + $coverscript);
		//_p("Cover Script Args : " + $coverscript_args);
		return "runid.coverscript";

	}
	if (SizeRead(command, 12) == "_new_thread ") {
		chartempC = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, " ", "<", 1))); //TaskID
		charCutB = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "<", ">", 1)));  //TaskFile
		chartempA = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ">", "$FROMEND$", 1))); //Task Argument
		
		if (!check_file_existenceA(charCutB)) {
			if (check_file_existence(_rcbind_pluginscript + "/" + charCutB)) {
				charCutB = _rcbind_pluginscript + "/" + charCutB;
				goto CmarkstartExecuteScript;
			}
			if (check_file_existence(_$GetSelfPath + "/" + charCutB)) {
				charCutB = _$GetSelfPath + "/" + charCutB;
				goto CmarkstartExecuteScript;
			}

			_p("_runscript Error:  File not Exist");
			_p(charCutB);
			return "filenotfound";
		}

	CmarkstartExecuteScript:

		//Create New Page File

		_fileapi_del(_pagefile_savedir);

		_fileapi_write(_pagefile_savedir, to_string(VarSpaceMax));
		_fileapi_write(_pagefile_savedir, VarSpace);

		//Add New Threads
		thread sec(__CreateNewThreads, charCutB, chartempA, _pagefile_savedir,chartempC);
		sec.detach();

		return "ok";
	}
	if (SizeRead(command, 12) == "_thread_live") {
		charCutA = _runcode_api(PartReadA(oldcmd, " ", PartRead_FMend, 1)); //GET Task id
		
		__settings_throwErrorMode = false;

		if (_load_sipcfg(Reg_Process_Map, charCutA) == "alive") return _str_true;
		if (_load_sipcfg(Reg_Process_Map, charCutA) != "alive") return _str_false;

		//End

		return "status Error : Report this bugs";
	}
	if (SizeRead(command, 13) == "_set_pagefile") {
		charCutA = PartReadA(oldcmd, " ", PartRead_FMend, 1);
		charCutB = _runcode_api(charCutA);
		_pagefile_savedir = charCutB;
		return "ok";
	}

	//PERF
	if (SizeRead(command, 15) == "_perftest-write") {
		return to_string(FileWriteSpeedTest());
	}
	if (SizeRead(command, 13) == "_perftest-cmd") {
		return to_string(FileCmdProcessSpeedTest());
	}

	if (SizeRead(command, 7) == "_invoke") {

		charCutB = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "<", ">", 1)));
		chartempA = _Old_VSAPI_TransVar(PartReadA(oldcmd, ">", "$FROMEND$", 1));

		if (!check_file_existenceA(charCutB)) {
			charCutB = _rcbind_pluginscript + "/" + charCutB;
			if (!check_file_existenceA(charCutB)) {
				_p("_runscript Error:  File not Exist");
				_p(charCutB);
				return "filenotfound";
			}
		}

		//Backup old GFapi data;

		int _old$_gf_cg = _gf_cg;
		int _old$_gf_cgmax = _gf_cgmax;
		int _old$_gf_line = _gf_line;
		bool _old$_direct_read_script = _direct_read_script;
		bool _old$_rcset_logrec = _rcset_logrec;
		string _old$_args = script_args;
		string _old$_logfile = _$logfile;
		bool _old$_CK_ShellMode = _CK_ShellMode;
		string _old$_global_scriptload = _global_scriptload;

		//Create New Space

		_gf_cg = 0;
		_gf_cgmax = 1;
		_gf_line = 1;
		_gf_charget = "";
		_direct_read_script = false;
		_CK_ShellMode = false;

		//Run

		CharCutC = _ckapi_scriptload(charCutB, chartempA);

		if (_stop_exec_script == true) {
			_stop_exec_script = false;
		}

		//Recovery old GFapi Data;
		_gf_cg = _old$_gf_cg;
		_gf_cgmax = _old$_gf_cgmax;
		_gf_line = _old$_gf_line;
		_gf_charget = "";
		script_args = _old$_args;
		_direct_read_script = _old$_direct_read_script;
		_rcset_logrec = _old$_rcset_logrec;
		_$logfile = _old$_logfile;
		_CK_ShellMode = _old$_CK_ShellMode;
		_global_scriptload = _old$_global_scriptload;

		if (CharCutC == "runid.exit") {
			return CharCutC;
		}
		if (CharCutC == "runid.entershell") {
			return CharCutC;
		}
		return CharCutC;
	}
	if (SizeRead(command, 3) == "_if") {
		_if_reverse = false;
		//_p("LaoDeng");
		CharCutD = "(" + PartRead(oldcmd, "(", "|", true);

		charCutA = (PartRead(CharCutD, "(", ")", true));

		if (SizeRead(charCutA, 1) == "!") {
			_if_reverse = true;
			charCutA = (PartRead(CharCutD, "!", ")", true));
		}

		//_p("Ready to XinDeng");

		charCutB = _runcode_api(charCutA);

		//_p("XinDeng");

		if (_if_reverse == true) {
			if (charCutB == _str_true) {
				charCutB = _str_false;
			}
			else {
				charCutB = _str_true;
			}
		}

		if (charCutB == _str_true) {
			CharCutC = (PartRead(oldcmd, "|", "$FROMEND$", true));

			CharCutD = _runcode_api(CharCutC);

			return CharCutD;
		}
		if (charCutB == _str_false) {
			return "notrue";
		}

		_pv("_$lang.if.err.t1");
		_pv("_$lang.if.err.t2 " + charCutB);
		return "NullReturn";
	}
	
	//Compare
	if (SizeRead(command, 3) == "_cp") {

		_rc_varid = _runcode_api((PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", "(", ",", 1)));

		_rc_varinfo = _runcode_api((PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", ",", ")", 1)));

		_logrec_write("[CP]1 = " + _rc_varid);
		_logrec_write("[CP]2 = " + _rc_varinfo);

		if (_rc_varid == _rc_varinfo) {
			return "true";
		}
		else {
			return "false";
		}

		return "FAIL";
	}
	if (SizeRead(command, 2) == "_<") {

		_rc_varid = _runcode_api((PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", "(", ",", 1)));

		_rc_varinfo = _runcode_api((PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", ",", ")", 1)));

		_logrec_write("[CP <]1 = " + _rc_varid);
		_logrec_write("[CP <]2 = " + _rc_varinfo);

		if (atoi(_rc_varid.c_str()) < atoi(_rc_varinfo.c_str())) {
			return "true";
		}
		else {
			return "false";
		}

		return "FAIL";
	}
	if (SizeRead(command, 3) == "_=<") {

		_rc_varid = _runcode_api((PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", "(", ",", 1)));

		_rc_varinfo = _runcode_api((PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", ",", ")", 1)));

		_logrec_write("[CP <=]1 = " + _rc_varid);
		_logrec_write("[CP <=]2 = " + _rc_varinfo);

		if (atoi(_rc_varid.c_str()) <= atoi(_rc_varinfo.c_str())) {
			return "true";
		}
		else {
			return "false";
		}

		return "FAIL";
	}
	if (SizeRead(command, 2) == "_>") {

		_rc_varid = _runcode_api((PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", "(", ",", 1)));

		_rc_varinfo = _runcode_api((PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", ",", ")", 1)));

		_logrec_write("[CP >]1 = " + _rc_varid);
		_logrec_write("[CP >]2 = " + _rc_varinfo);

		if (atoi(_rc_varid.c_str()) > atoi(_rc_varinfo.c_str())) {
			return "true";
		}
		else {
			return "false";
		}

		return "FAIL";
	}
	if (SizeRead(command, 3) == "_=>") {

		_rc_varid = _runcode_api((PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", "(", ",", 1)));

		_rc_varinfo = _runcode_api((PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", ",", ")", 1)));

		_logrec_write("[CP >=]1 = " + _rc_varid);
		_logrec_write("[CP >=]2 = " + _rc_varinfo);

		if (atoi(_rc_varid.c_str()) >= atoi(_rc_varinfo.c_str())) {
			return "true";
		}
		else {
			return "false";
		}

		return "FAIL";
	}

	//IntMath
	if (SizeRead(command, 2) == "_+") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";
		_logrec_write("Calculator Function +");
		_logrec_write("full line data:  -->   " + tempbase);

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		_logrec_write("Get Part A :   " + calc_A);
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));
		_logrec_write("Get Part B :   " + calc_B);

		dbA = atoi(calc_A.c_str());
		dbB = atoi(calc_B.c_str());

		dbC = dbA + dbB;

		charCutA = to_string(dbC);
		_logrec_write("return result :  _" + charCutA);
		return charCutA;
	}
	if (SizeRead(command, 2) == "_-") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";
		_logrec_write("Calculator Function -");
		_logrec_write("full line data:  -->   " + tempbase);

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		_logrec_write("Get Part A :   " + calc_A);
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));
		_logrec_write("Get Part B :   " + calc_B);

		dbA = atoi(calc_A.c_str());
		dbB = atoi(calc_B.c_str());

		dbC = dbA - dbB;

		charCutA = to_string(dbC);
		_logrec_write("return result :  _" + charCutA);
		return charCutA;
	}
	if (SizeRead(command, 2) == "_*") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";
		_logrec_write("Calculator Function *");
		_logrec_write("full line data:  -->   " + tempbase);

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		_logrec_write("Get Part A :   " + calc_A);
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));
		_logrec_write("Get Part B :   " + calc_B);

		dbA = atoi(calc_A.c_str());
		dbB = atoi(calc_B.c_str());

		dbC = dbA * dbB;

		charCutA = to_string(dbC);
		_logrec_write("return result :  _" + charCutA);
		return charCutA;
	}
	if (SizeRead(command, 2) == "_/") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";
		_logrec_write("Calculator Function /");
		_logrec_write("full line data:  -->   " + tempbase);

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		_logrec_write("Get Part A :   " + calc_A);
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));
		_logrec_write("Get Part B :   " + calc_B);

		dbA = atoi(calc_A.c_str());
		dbB = atoi(calc_B.c_str());

		if (dbB == 0) {
			_p("Exception::Integer_division_by_zero");
			return "0";
		}

		dbC = dbA / dbB;

		charCutA = to_string(dbC);
		_logrec_write("return result :  _" + charCutA);
		return charCutA;
	}
	if (SizeRead(command, 2) == "_%") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		dbA = atoi(calc_A.c_str());
		dbB = atoi(calc_B.c_str());

		if (dbB == 0) {
			_p("Exception::Integer_division_by_zero");
			return "0";
		}

		dbC = dbA % dbB;

		charCutA = to_string(dbC);
		_logrec_write("return result :  _" + charCutA);
		return charCutA;
	}

	if (SizeRead(command, 3) == "_l+") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		LdbA = stoll(calc_A);
		LdbB = stoll(calc_B);

		LdbC = LdbA + LdbB;

		charCutA = to_string(LdbC);
		return charCutA;
	}
	if (SizeRead(command, 3) == "_l-") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		LdbA = stoll(calc_A);
		LdbB = stoll(calc_B);

		LdbC = LdbA - LdbB;

		charCutA = to_string(LdbC);
		return charCutA;
	}
	if (SizeRead(command, 3) == "_l*") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		LdbA = stoll(calc_A);
		LdbB = stoll(calc_B);

		LdbC = LdbA * LdbB;

		charCutA = to_string(LdbC);
		return charCutA;
	}
	if (SizeRead(command, 3) == "_l/") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		LdbA = stoll(calc_A);
		LdbB = stoll(calc_B);

		if (LdbB == 0) {
			_p("Exception::Integer_division_by_zero");
			return "0";
		}

		LdbC = LdbA / LdbB;

		charCutA = to_string(LdbC);
		return charCutA;
	}
	if (SizeRead(command, 3) == "_l%") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		LdbA = stoll(calc_A);
		LdbB = stoll(calc_B);

		if (LdbB == 0) {
			_p("Exception::Integer_division_by_zero");
			return "0";
		}

		LdbC = LdbA % LdbB;

		charCutA = to_string(LdbC);
		return charCutA;
	}

	//Float Compute
	if (SizeRead(command, 3) == "_f+") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		FdbA = stof(calc_A.c_str());
		FdbB = stof(calc_B.c_str());

		FdbC = FdbA + FdbB;

		charCutA = to_string(FdbC);
		return charCutA;
	}
	if (SizeRead(command, 3) == "_f-") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		FdbA = stof(calc_A.c_str());
		FdbB = stof(calc_B.c_str());

		FdbC = FdbA - FdbB;

		charCutA = to_string(FdbC);
		return charCutA;
	}
	if (SizeRead(command, 3) == "_f*") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		FdbA = stof(calc_A.c_str());
		FdbB = stof(calc_B.c_str());

		FdbC = FdbA * FdbB;

		charCutA = to_string(FdbC);
		return charCutA;
	}
	if (SizeRead(command, 3) == "_f/") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		FdbA = stof(calc_A.c_str());
		FdbB = stof(calc_B.c_str());

		FdbC = FdbA / FdbB;

		charCutA = to_string(FdbC);
		return charCutA;
	}

	//Double Compute
	if (SizeRead(command, 3) == "_d+") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		HdbA = stod(calc_A.c_str());
		HdbB = stod(calc_B.c_str());

		HdbC = HdbA + HdbB;

		charCutA = to_string(HdbC);
		return charCutA;
	}
	if (SizeRead(command, 3) == "_d-") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		HdbA = stod(calc_A.c_str());
		HdbB = stod(calc_B.c_str());

		HdbC = HdbA - HdbB;

		charCutA = to_string(HdbC);
		return charCutA;
	}
	if (SizeRead(command, 3) == "_d*") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		HdbA = stod(calc_A.c_str());
		HdbB = stod(calc_B.c_str());

		HdbC = HdbA * HdbB;

		charCutA = to_string(HdbC);
		return charCutA;
	}
	if (SizeRead(command, 3) == "_d/") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));

		HdbA = stod(calc_A.c_str());
		HdbB = stod(calc_B.c_str());

//		if (HdbB == 0) {
//			_pv("_$lang.calc.zero");
//			return "NaN";
//		}

		HdbC = HdbA / HdbB;

		charCutA = to_string(HdbC);
		return charCutA;
	}

	//SRQT
	if (SizeRead(command, 7) == "_d_sqrt") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ")", false)));

		HdbA = stod(calc_A.c_str());

		//		if (HdbB == 0) {
		//			_pv("_$lang.calc.zero");
		//			return "NaN";
		//		}

		HdbB = sqrt(HdbA);

		charCutA = to_string(HdbB);
		return charCutA;
	}
	if (SizeRead(command, 7) == "_f_sqrt") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ")", false)));

		FdbA = stof(calc_A.c_str());

		FdbB = sqrt(FdbA);

		charCutA = to_string(FdbB);
		return charCutA;
	}
	if (SizeRead(command, 7) == "_l_sqrt") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ")", false)));

		LdbA = stoll(calc_A);

		LdbB = sqrt(LdbA);

		charCutA = to_string(LdbB);
		return charCutA;
	}

	//Other Compute
	if (SizeRead(command, 6) == "_m_abs") {
		charCutA = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1)));

		intCutA = atoi(charCutA.c_str());
		intCutA = abs(intCutA);

		return to_string(intCutA);
	}

	//Get
	gethookVid = "5.12";
	if (SizeRead(command, 7) == "_getenv") {
		charCutA = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1)));
		return _SystemAPI_getenv(charCutA);
	}
	if (SizeRead(command, 12) == "_getpagefile") {
		return _pagefile_savedir;
	}
	if (SizeRead(command, 9) == "_getrunid") {
		return _CK_Runid;
	}
	if (SizeRead(command, 8) == "_getline") {
		charCutA = _getline_type();
		if (charCutA == "@fxtools_closescript") {
			_stop_exec_script = true;
			return "runid.exit";
		}
		return charCutA;
	}
	if (SizeRead(command, 8) == "_getargs") {
		return script_args;
	}
	if (SizeRead(command, 8) == "_getfile") {
		return _global_scriptload;
	}
	if (SizeRead(command, 8) == "_getexec") {
		return _$GetSelfFull;
	}
	if (SizeRead(command, 8) == "_getrand") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", ",", ")", 1)));

		intCutA = atoi(_rc_varid.c_str());
		intCutB = atoi(_rc_varinfo.c_str());

		intCutC = _get_random(intCutA, intCutB);

		charCutA = to_string(intCutC);
		return charCutA;
	}
	if (SizeRead(command, 10) == "_getkernel") {
		return InsideVersion;
	}
	if (SizeRead(command, 8) == "_getpath") {
		return _$GetSelfPath;
	}
	if (SizeRead(command, 12) == "_getfulltime") {
		return __GetFullTime();
	}
	if (SizeRead(command, 8) == "_getdate") {
		return __GetFullDate();
	}
	if (SizeRead(command, 9) == "_getclock") {
		return __GetFullClock();
	}
	if (SizeRead(command, 14) == "_get_thread_id") {
		return Reg_Proces_runid;
	}

	//IsTest
	isGetVid = "5.11";
	if (SizeRead(command, 7) == "_isNum ") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		_logrec_write("[IsGet] _is Num  :  -->  " + charCutA);
		if (atoi(_runcode_api(charCutA).c_str()) != 0) {
			_logrec_write("[IsGet] Num is True   " + charCutA);
			return _rc_true;
		}
		else {
			_logrec_write("[IsGet] Num is False   " + charCutA);
			return _rc_false;
		}

		return "_KernelFail_Status: Unknown";
	}

	//Debug
	if (SizeRead(command, 12) == "_detect.mode") {
		if (_debug_type_detected == true) {
			_p("Detect Mode is Disabled");
			_debug_type_detected = false;
			return "ok";
		}
		if (_debug_type_detected == false) {
			_p("Detect Mode is Enabled");
			_debug_type_detected = true;
			return "ok";
		}

		return " BadEffect";
	}
	if (SizeRead(command, 13) == "_get.lastcode") {
		_p("Last Return is :   <" + last_return + ">");
		return "ok";
	}
	if (SizeRead(command, 11) == "_entershell") {
		return"runid.entershell";
	}
	if (SizeRead(command, 11) == "_shelltitle") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		_logrec_write("[Output Exec] Command :  -->  " + charCutA);
		charCutB = _runcode_api(charCutA);

		_shellTitle = charCutB;
		return "ok";
	}
	if (SizeRead(command, 9) == "_pathlist") {
		_logrec_write("[Debug] List Path");

		_p("PluginPath =   " + _rcbind_pluginpath);
		_p("PluginScript = " + _rcbind_pluginscript);
		return "ok";
	}
	if (SizeRead(command, 9) == "_fun_test") {
		string CCFK =  NULL;

		_prtoutmsg(CCFK);

		return "ok";
	}
	if (SizeRead(command, 13) == "_random_break") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		intCutA = atoi(charCutA.c_str());
		//PROC
		//Random Char Break
		for (int count_addr = 0; count_addr != intCutA; count_addr++) {
			//lC
			intCutB = VarSpace.size();
			intCutB--;
			NullREGETRANDOMBRK:
			ModifyCount = _get_random(1, intCutB);
			
			if (VarSpace[ModifyCount] == ';') goto NullREGETRANDOMBRK;
			if (VarSpace[ModifyCount] == '=') goto NullREGETRANDOMBRK;

			VarSpace[ModifyCount] = '?';
			_p("Address : " + to_string(ModifyCount) + " data is break.  Max Data :  " + to_string(intCutB) + "  Request Break :  " + to_string(intCutA) + "  Current :  " + to_string(count_addr));
		}
		return "ok";
	}
	//Settings
	if (SizeRead(command, 12) == "_$directmode") {
		_logrec_write("[Settings] Script using direct mode to read");
		_direct_read_script = true;
		return "ok";
	}
	if (SizeRead(command, 7) == "_$nolog") {
		_logrec_write("[Close] Script Closed Log Record");
		_logrec_write("-----------------------------------------------Closed");
		_rcset_logrec = false;
		return "ok";
	}
	if (SizeRead(command, 15) == "_$no_err_report") {
		__settings_throwErrorMode = false;
		return "ok";
	}
	if (SizeRead(command, 12) == "_$shell_lock") {
		_shell_lock = true;
		return "ok";
	}
	if (SizeRead(command, 12) == "_$exec_speed") {
		_rc_varid = _runcode_api(PartReadA(oldcmd, " ", PartRead_FMend, 1));

		_exec_runtimesleep = atoi(_rc_varid.c_str());

		_p("Sleep time is :  " + _rc_varid);

		return "ok";
	}
	if (SizeRead(command, 16) == "_$no_cstp_output") {
		CstpOutput = false;

		return "ok";
	}
	if (SizeRead(command, 18) == "_$open_cstp_output") {
		CstpOutput = true;

		return "ok";
	}
	if (SizeRead(command, 20) == "_$enable_perf_record") {
		if (is_TPC_already_Running == true) {
			cout << "Performance Record Service is already running.  use _$disable_perf_record to stop this service" << endl;
			return "ok";
		}

		PerfCNT_ID = _runcode_api(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		
		if (PerfCNT_ID == "unknown.command")PerfCNT_ID = "Unnamed_" + _get_random_s(111111,999999);

		thread monitor_pfr(Thread_PerfCurrentGet);
		monitor_pfr.detach();

		cout << "Service Start." <<endl;

		return "ok";
	}
	if (SizeRead(command, 21) == "_$disable_perf_record") {
		ProcessReqStop = true;
		cout << "Service Stop." << endl;
		return "ok";
	}

	//System
	sysexecVid = "4.54";
	if (SizeRead(command, 11) == "_file_exist") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		_logrec_write("[File] Check File Exist..  command -->  " + charCutA);
		charCutB = _runcode_api(charCutA);
		_logrec_write("[File] check file :  " + charCutB);

		if (check_file_existence(charCutB)) {
			return "true";
		}
		else {
			return "false";
		}
	}
	if (SizeRead(command, 12) == "_file_rename") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		if (!check_file_existence(_rc_varid)) {
			_p("[FileSystemIO] RenameFile A " + _rc_varid + " is not Exist");
			return "false";
		}

		rename(_rc_varid.c_str(), _rc_varinfo.c_str());

		if (check_file_existence(_rc_varinfo)) {
			return "true";
		}
		else {
			_p("[FileSystemIO] RenameFile B " + _rc_varinfo + " failed. Access Denied");
			return "false";
		}
	}
	if (SizeRead(command, 9) == "_dir_make") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		_logrec_write("[Dir] Create Directory ..  command -->  " + charCutA);
		charCutB = _runcode_api(charCutA);
		_logrec_write("[Dir] Directory :  " + charCutB);

		if (_dapi_mkdir(charCutB)) {
			return "true";
		}
		else {
			return "false";
		}
	}
	if (SizeRead(command, 11) == "_dir_remove") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		_logrec_write("[Dir] Remove Directory ..  command -->  " + charCutA);
		charCutB = _runcode_api(charCutA);
		_logrec_write("[Dir] Directory :  " + charCutB);

		if (_dapi_rmdir(charCutB)) {
			return "true";
		}
		else {
			return "false";
		}
	}
	if (SizeRead(command, 10) == "_dir_exist") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		_logrec_write("[Dir] Check Directory Exist..  command -->  " + charCutA);
		charCutB = _runcode_api(charCutA);
		_logrec_write("[Dir] check directory :  " + charCutB);

		if (_dapi_ExistFolder_check(charCutB)) {
			return "true";
		}
		else {
			return "false";
		}
	}
	if (SizeRead(command, 9) == "_dir_list") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));
		CreateFileMap_txt(_rc_varid, _rc_varinfo);
		return "true";
	}
	if (SizeRead(command, 10) == "_file_list") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));
		CreateDirMap_txt(_rc_varid, _rc_varinfo);
		//cout << "Save File :    " << _rc_varid << endl;
		//cout << "DIRECTORY :   " << _rc_varinfo << endl;
		return "true";
	}
	if (SizeRead(command, 9) == "_dir_full") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		charCutB = _runcode_api(charCutA);

		creatpath(charCutB);
		return "true";
	}

	//FileSystemIO
	if (SizeRead(command, 10) == "_file_copy") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		if (!check_file_existence(_rc_varid)) {
			_p("[FileSystemIO] CopyFile A " + _rc_varid + " is not Exist");
			return "false";
		}

		_fileapi_CpFile(_rc_varid, _rc_varinfo);

		if (check_file_existence(_rc_varinfo)) {
			return "true";
		}
		else {
			_p("[FileSystemIO] CopyFile B " + _rc_varinfo + " failed. Access Denied");
			return "false";
		}
	}
	if (SizeRead(command, 9) == "_file_del") {
		//del task
		_rc_varid = _runcode_api(PartReadA(oldcmd, " ", PartRead_FMend, 1));

		if (!check_file_existence(_rc_varid)) {
			return "true";
		}

		_fileapi_del(_rc_varid);

		if (!check_file_existence(_rc_varid)) {
			return "true";
		}
		else {
			_p("[FileSystemIO] Delete File " + _rc_varinfo + " failed. Access Denied");
			return "false";
		}
	}
	if (SizeRead(command, 11) == "_file_open ") {
		_rc_varid = _runcode_api(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		_logrec_write("[FileWrite] SoildWrite is Open :  " + _rc_varid);
		_soildwrite_open(_rc_varid);
		return "ok";
	}
	if (SizeRead(command, 12) == "_file_write ") {
		_rc_varid = _runcode_api(PartReadA(oldcmd, " ", PartRead_FMend, 1));

		_rc_varid = ReplaceChar(_rc_varid, "%fulltime%", __GetFullTime());
		_rc_varid = ReplaceChar(_rc_varid, "%date%", __GetFullDate());
		_rc_varid = ReplaceChar(_rc_varid, "%time%", __GetFullClock());


		_soildwrite_write(_rc_varid);
		return "ok";
	}
	if (SizeRead(command, 14) == "_file_replace ") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, " ", "(", 1)));
		CharCutC = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		BatchFileReplace_(_rc_varid, CharCutC, _rc_varinfo);

		return "ok";
	}


	//Toolkit
	ThirdExecVid = "4.13";
	if (SizeRead(command, 10) == "_file_read") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		_logrec_write("[API] File Read :   " + _rc_varid + "  Line :  " + _rc_varinfo);

		charCutA = _fileapi_textread(_rc_varid, atoi(_rc_varinfo.c_str()));

		_logrec_write("[API] File Read Return :   " + charCutA);

		return charCutA;
	}
	if (SizeRead(command, 10) == "_textprint") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		charCutB = _runcode_api(charCutA);

		_logrec_write("[Exec] Print Text File   " + charCutB);

		if (!check_file_existenceA(charCutB)) {
			_pv("_$lang.filenotfound   " + charCutB);
			_p("Null._textprint()");
			return "nofile";
		}

		_textapi_typetext(charCutB);
		return "ok";
	}
	if (SizeRead(command, 9) == "_typefile") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		charCutB = _runcode_api(charCutA);

		_logrec_write("[Exec] Print Text File   " + charCutB);

		if (!check_file_existenceA(charCutB)) {
			_pv("_$lang.filenotfound   " + charCutB);
			_p("Null._textprint()");
			return "nofile";
		}

		_var_typetext(charCutB);
		return "ok";
	}
	if (SizeRead(command, 8) == "_url_get") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		_logrec_write("[Internet] Request _url_get");
		_logrec_write("[Internet] URL :  " + _rc_varid);
		_logrec_write("[Internet] Save Path :  " + _rc_varinfo);

		if (!_urldown_api_nocache(_rc_varid, _rc_varinfo)) {
			_logrec_write("[ERROR] Get url failed");
			_p("_URL_GET failed access url :  " + _rc_varid);
			return "false";
		}
		if (!check_file_existence(_rc_varinfo)) {
			_logrec_write("[ERROR] Save file failed");
			_p("_url_get save file failed :  " + _rc_varid);
			return "false";
		}

		return "ok";
	}
	if (SizeRead(command, 11) == "_packsetup ") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1)));
		if (!_packsetup(_rc_varid)) {
			_p("_packsetup failed");
			return "false";
		}
		else {
			return "ok";
		}

		return "ok";
	}
	if (SizeRead(command, 9) == "_textfind") {
		charCutB = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		chartempA = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));
		//_p("A :  " + charCutB + "   B: " + chartempA);
		if (checkChar(charCutB, chartempA)) {
			return _str_true;
		}
		return _str_false;
	}
	if (SizeRead(command, 8) == "_url_msg") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		_logrec_write("[GetHttp] GET URL -->  " + charCutA);
		charCutB = _runcode_api(charCutA);

		CharCutD = _get_random_s(111111, 999999);

		if (!_urldown_api_nocache(charCutB, CharCutD)) {
			_p("[GetHttp] Fail Get URL " + charCutB);
			return "fail";
		}

		charCutB = _fileapi_textread(CharCutD, 1);

		_fileapi_del(CharCutD);

		return charCutB;
	}
	if (SizeRead(command, 8) == "_file_cp") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		_logrec_write("[FileCP] FileCompare");
		_logrec_write("[FileCP] A :  " + _rc_varid);
		_logrec_write("[FileCP] B :  " + _rc_varinfo);

		sw_a = FileCompare_(_rc_varid, _rc_varinfo);

		if (sw_a == true)return "true";
		if (sw_a == false)return "false";

		return "false";
	}
	if (SizeRead(command, 12) == "_str_replace") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, " ", "(", 1)));
		CharCutC = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		return ReplaceCharA(_rc_varid, CharCutC, _rc_varinfo);
	}
	if (SizeRead(command, 6) == "_found") {
		CharCutC = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		if (checkChar(CharCutC, _rc_varinfo))return "true";
		else return "false";

	}
	if (SizeRead(command, 13) == "_string_fetch") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));
		
		intCutA = atoi(_rc_varinfo.c_str());
		intCutB = _rc_varid.size();
		//cout << "INFO " << intCutA << "MEM2 " << intCutB << endl;
		if (intCutA >= intCutB) {
			cout << "string fetch out of size" <<endl;
			return "0";
		}
		if (intCutA < 0) {
			cout << "string fetch below of size" << endl;
			return "0";
		}

		charCutA = _rc_varid[intCutA];

		return charCutA;
	}
	if (SizeRead(command, 13) == "_string_edit ") {
		CharCutC = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, " ", "(", 1))); //Modify Address
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1))); //Origin Data
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));  //Modify char

		int intCutA = atoi(CharCutC.c_str());
		if (_rc_varid.length() >= intCutA) {
			_rc_varid[intCutA] = _rc_varinfo[0];
		}
		else {
			return "length.out.of.edit";
		}

		return _rc_varid;
	}

	//pack/unpack Tools
	if (SizeRead(command, 10) == "_file_pack") {
		readptr = 1;
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		if (!_dapi_ExistFolder_check(_rc_varid)) {
			_p("Error.FilePack.  Access Denied or not exist");
			return "fails";
		}
		if (check_file_existence(_rc_varinfo)) {
			_fileapi_del(_rc_varinfo);
			if (check_file_existence(_rc_varinfo)) {
				_p("Error.FilePack.  Pack file is exist, delete fail");
				return "fails";
			}
		}

		_Legacy_cstp_maker(_rc_varid, _rc_varinfo);

		return "Complete";
	}
	if (SizeRead(command, 12) == "_file_unpack") {
		readptr = 1;
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		if (!check_file_existence(_rc_varid)) {
			_p("Error.UnFilePack.  File Access Denied or not exist");
			return "fails";
		}

		_Legacy_cstp_unpack(_rc_varinfo, _rc_varid);

		return "Complete";
	}

	//New Pack Format
	if (SizeRead(command, 10) == "_file_cstp") {
		readptr = 1;
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		if (!_dapi_ExistFolder_check(_rc_varid)) {
			_p("Error.FilePack.  Access Denied or not exist");
			return "fails";
		}
		if (check_file_existence(_rc_varinfo)) {
			_fileapi_del(_rc_varinfo);
			if (check_file_existence(_rc_varinfo)) {
				_p("Error.FilePack.  Pack file is exist, delete fail");
				return "fails";
			}
		}

		_cstp_makerN(_rc_varid, _rc_varinfo);

		return "Complete";
	}
	if (SizeRead(command, 12) == "_file_uncstp") {
		readptr = 1;
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ")", 1)));

		if (!check_file_existence(_rc_varid)) {
			_p("Error.UnFilePack.  File Access Denied or not exist");
			return "fails";
		}

		_cstp_unpackN(_rc_varinfo, _rc_varid);

		return "Complete";
	}

	//SipCfg Native
	if (SizeRead(command, 13) == "_sipcfg.open ") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, " ", PartRead_FMend, 1));
		_logrec_write("[Output Exec] Command :  -->  " + charCutA);
		charCutB = _runcode_api(charCutA);

		if (!check_file_existenceA(charCutB)) {
			_fileapi_createmark(charCutB, "//default   --Simple Config File");
		}

		nt_sipcfg_open = charCutB;

		return "ok";
	}
	if (SizeRead(command, 15) == "_sipcfg.remove ") {
		_logrec_write("[SipCfg] Native SipCfg");
		_rc_varinfo = _Old_VSAPI_TransVar(HeadSpaceCleanA(PartReadA(command, " ", PartRead_FMend, 1)));
		_rc_varinfo = ReplaceChar(_rc_varinfo, ";", "");

		_remove_sipcfg(nt_sipcfg_open, _rc_varinfo);
		_logrec_write("[SipCfg] Sipcfg Remove :  " + _rc_varinfo + "");
		return "ok";
	}
	if (SizeRead(command, 8) == "_sipcfg ") {
		_logrec_write("[SipCfg] Native SipCfg");

		if (checkChar(command, "=")) {
			_rc_varid = _Old_VSAPI_TransVar(HeadSpaceCleanA(PartReadA(command, " ", "=", 1)));
			_rc_varinfo = HeadSpaceCleanA(PartReadA(oldcmd, "=", PartRead_FMend, 1));

			_rc_varinfo = ReplaceChar(_rc_varinfo, ";", "");
			_rc_varinfo = _runcode_api(_rc_varinfo);

			_write_sipcfg(nt_sipcfg_open, _rc_varid, _rc_varinfo);
			_logrec_write("[SipCfg] Sipcfg Set :  " + _rc_varid + " = " + _rc_varinfo);
			return "ok";
		}
		else {
			_rc_varid = HeadSpaceCleanA(PartReadA(command, " ", "$FROMEND$", 1));
			//_Old_VSAPI_TransVar(_load_sipcfg(nt_sipcfg_open, _rc_varid));
			return _Old_VSAPI_TransVar(_load_sipcfg(nt_sipcfg_open, _rc_varid));
		}
		return "falseproblem";
	}

	//Self Monitor Analysis  --API
	if (SizeRead(command, 5) == "_sma ") {
		charCutA = _runcode_api(_Old_VSAPI_TransVar(PartReadA(command, " ", PartRead_FMend, 1)));

		if (charCutA == "test") {
			return "true";
		}
		if (charCutA == "help") {
			_p("Calcium SMA Command :  Self-Monitoring Analysis");
			_p("This is kernel api");
			return "ok";
		}
		if (charCutA == "cname") {
			return _CTitle;
		}
		if (charCutA == "codename") {
			return $codename;
		}
		if (charCutA == "kerV") {
			return InsideVersion;
		}
		if (charCutA == "ocltV") {
			return $version_title + "  " + $version_msg;
		}
		//KernelMSG
		if (charCutA == "kvget") {
			return _KernelVersion;
		}
		if (charCutA == "rcvget") {
			return _RCapi_Version;
		}
		//Get VID
		if (charCutA == "kcvid") {
			return kernelcmdVid;
		}
		if (charCutA == "kevid") {
			return kernelenvVid;
		}
		if (charCutA == "ghvid") {
			return gethookVid;
		}
		if (charCutA == "igvid") {
			return isGetVid;
		}
		if (charCutA == "sevid") {
			return sysexecVid;
		}
		if (charCutA == "tevid") {
			return ThirdExecVid;
		}
		if (charCutA == "ksvid") {
			return kernelSecureVid;
		}
		if (charCutA == "getsys") {
			return _Run_SysKernel;
		}
		if (charCutA == "clfmv") {
			return to_string(CL_FMV_ID);
		}

		return "null";
	}

	if (_var_auto_void == true) {
		_logrec_write("[WARNING] Return Value :  -->  " + command);
		return command;
	}
	_logrec_write("[ERROR]Unknown COMMAND   " + command);
	_pv("_$lang.nullcmd   :  <" + _global_scriptload + ">  Line " + to_string(_gf_line) + "  INFO --> " + command + "    (Resource -->  " + oldcmd + ")");
	return "unknown.command";
}