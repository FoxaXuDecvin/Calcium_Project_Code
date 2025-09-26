#pragma once

#include"../shload.h"
#include"../Code/CalciumKernel.h"

#include<signal.h>

bool PreLaunchLoad(void) {
	//Put Preload code here
	//
	
	//Time Bomb
	tbd_year = 2025;
	tbd_month = 10;
	tbd_day = 26;


	//PreLoad
	_CTitle = "Calcium_Project_Rebuild";

	__settings_displaylaunchscreen = false;

	//End
	return true;
}

void TypeHelpMenu() {
	_p("----------------------------------------------------------");
	_p("OpenCppLangTab  " + $version_title + " " + $version_code_str);
	_p("System :    " + _Run_SysKernel);
	_p("----------------------------------------------------------");
	_p("Kernel Version :    " + _KernelVersion + "  " + _KV_rV_Text);
	_p("RCapi Version :     " + _RCapi_Version);
	_p("OpenCalcium Script Platform    .....");
	_p("Github : https://github.com/FoxaXuDecvin/Calcium_Project_Code");
	_p("Language   " + _rcset_lang);
	_p("Copyright FoxaXu " + $year_message);
	return;
}


//Args API
void argsApi(string args$api) {

	//if (argsSetExit) set true
	//Process will close after args run

	//Args Switch
	if (args$api == "-run") {
		_setnextargs_runscript = true;
		_runmode = _runmode_runscript;
		return;
	}

	if (args$api == "-optimi") {
		_setnextargs_runscript = true;
		_runmode = _runmode_optimi;
		return;
	}

	if (args$api == "-pack") {
		_setnextargs_runscript = true;
		_runmode = _runmode_cstpmake;
		return;
	}

	if (args$api == "-unpack") {
		_setnextargs_runscript = true;
		_runmode = _runmode_cstpunpack;
		return;
	}

	if (args$api == "-to") {
		_setnextargs_addo = true;
		return;
	}

	if (args$api == "-debug") {
		_debugMode = true;
		return;
	}

	if (args$api == "-help") {
		_runmode = _runmode_typehelp;
		return;
	}

	if (args$api == "-shell") {
		_runmode = _runmode_openshell;
		return;
	}

	if (args$api == "-version") {
		_runmode = _runmode_listversion;
		return;
	}

	if (args$api == "-anticrash_ok") {
		_anticrash_services = true;
	}

	if (args$api == "-args") {
		_setnextargs_addargs = true;
		return;
	}

	if (args$api == "-direct") {
		_direct_read_script = true;
	}

	if (args$api == "-nolang") {
		_skipcheck_language = true;
	}

	if (args$api == "-loadenv") {
		_setnextargs_loadenv = true;
		return;
	}

	if (args$api == "-runid") {
		_setproces_runid = true;
		return;
	}

	if (args$api == "-%NowIsRunAdmin%") {
		_isAdminOK_ = true;
	}

	if (args$api == "-fastmode") {
		_FastMode = true;
	}

	if (args$api == "-enable-vs-randombreak") {
		_VarSpace_Random_BreakTest = true;
	}

	if (args$api == "--perf-test") {

		_p("Disk Performance Test Result is :  " + to_string(FileWriteSpeedTest()));
		_p("Command Performance Test Result is :  " + to_string(FileCmdProcessSpeedTest()));
		_p("Benchmark Version :  " + _KernelVersion + "    Platform :  " + _Run_SysKernel);

		argsSetExit = true;

		return;
	}

	if (args$api == "-perfid") {
		_setproces_perfid = true;
		return;
	}

	//auto set args
	if (_setnextargs_runscript == true) {
		runscript = args$api;
		_setnextargs_runscript = false;
	}

	if (_setnextargs_addargs == true) {
		script_args = args$api;
		_setnextargs_addargs = false;
	}

	if (_setnextargs_loadenv == true) {
		_setnextargs_loadenv = false;
		charCutB = args$api;

		if (!check_file_existence(charCutB)) {
			_p("EnvLoad Error Fail");
			_p("FileNotExist");
			return;
		}

		VarSpaceMax = atoi(_fileapi_textread(charCutB, 1).c_str());
		VarSpace = _fileapi_textread(charCutB, 2);
		return;
	}

	if (_setnextargs_addo == true) {
		o_info = args$api;
		_setnextargs_addo = false;
	}

	if (_setproces_runid == true) {
		Reg_Proces_runid = args$api;
		_setproces_runid = false;
	}

	if (_setproces_perfid == true) {
		PerfCNT_ID = args$api;

		if (PerfCNT_ID == "unknown.command")PerfCNT_ID = "Unnamed_" + _get_random_s(111111, 999999);

		thread monitor_pfr(Thread_PerfCurrentGet);
		monitor_pfr.detach();

		_setproces_perfid = false;
	}


	return;
}

string _user_typebuffer;
bool CK_Shell_open(void) {
	_global_scriptload = "{ShellMode}";
	_CK_ShellMode = true;
	_pn();
	_pn();
	_p("----------------------------------------------------------");
	if (atoi(_KV_releaseVer.c_str()) < 5) {
		_pv("_$lang.cfgver");
		_pv("_$lang.timebomb " + TBD_STR);
	}
	if (_TBD_WARNING == true) {
		_pv("_$lang.tbd.warning ");
	}
	_p("Calcium Shell Console");
	if (_kernel_activate == false) {
		_pv("_$lang.act_info .  _use _$activate(%Key%) to Activate");
	}
	if (_rcset_trustcheck == true) {
		if (_TrustedServer == false) {
			_pv("_$lang.untrusted.server");
		}
	}
	else {
		_pv("_$lang.untrusted.server");
	}
	_p("----------------------------------------------------------");
	_pv("_$lang.language :  _$lang.about .....  " + _rcset_lang);
	_p("type command,   use \"_exit\" to exit.");

	while (true) {
		_global_scriptload = "{ShellMode}";
		_pn();
		_prts(_shellTitle);
		_user_typebuffer = _getline_type() + ";";



		last_return = _api_result = _runcode_api(_user_typebuffer);

		if (_api_result == "runid.exit") {
			_pn();
			_p("Exit Calcium Shell Console");
			return true;
		}

		if (_api_result == "runid.entershell") {
			_p("The current environment is in Shell Mode");
		}

		if (_api_result == "runid.crash.harddrv.error") {
			_p("[Error] Unexpected Error. File Location was Broken");
			_p("[Error] Please check your hard drive or file system.");
		}

		if (_stop_exec_script == true) {
			if (_shell_lock) {
				_pn();
				_p("  -Stop_exec_Script is true  :   return data = " + _api_result);
				_stop_exec_script = false;
			}
			else {
				_pn();
				_p("  -Shell Closed :   return data = " + _api_result);
				return 0;
			}
		}

		continue;
	}


	return true;
}


//ATEXIT RegOut Exit
void regout_atexit_noparameter() {
	_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
	return;
}

void regout_atexit(int TNum) {
	_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
	exit(TNum);
}


int AntiCrash_Return_Code;
string ckapi_result;
string langpackfile;
string AC_FAILCODE = "{Null}";
//Put Code Here
int _HeadMainLoad() {
	//CopyVersion
	if (SizeRead(_$GetSelfPath, 2) == "\\\\") {
		_p("Network Drive Not Support");
		_p("Calcium Running on Network Path");
		_p("But Windows Command is not support Network Path");
		_p("Please use Network mapping and running on mapping path");
		_p("");
		_p("��֧�ֵ�����������");
		_p("Calcium ��������������������");
		_p("Console �޷��ڵ�ǰ·������");
		_p("Ϊ��֤��������ʹ�ñ���·���򽫵�ǰ·��ӳ�䵽�������� ");
		_pause();
		return 0;
	}

	//_p("Use local dir");
	buildshell = _$GetSelfPath + "/calcium_settings.cfg";

	if (!_dapi_ExistFolder_check(_$GetSelfPath)) {
		_p("Unable to access the currently running directory");
		_p("Calcium cannot be run in the current directory");
		_p("�޷�����Calcium���е�Ŀ¼");
		_p("�볢�Խ�Calcium����������Ŀ¼��ʹ�ù���ԱȨ������");
		_pause();
		return 1;
	}
	if (_anticrash_services == false) {
		//History Code
	}

	_RcApi_vp_load();
	if (!_RcApiLoadConfig()) {
		_p("Failed to Load RCapi.");
		_p("Config file is missing :  " + buildshell);
		_p("try to repair and try again.");
		_pause();
		return -1;
	}

	if (!_FastMode) {
		if (_rcset_offlangcheck) {
			_skipcheck_language = true;
		}
		else {
			if (_skipcheck_language == false) {
				if (!LanguageLoad()) {
						langpackfile = _$GetSelfPath + "/" + "temp_languagepack.pack";
						_p("Download Language files");

						if (_Run_SysKernel == Linux_kernel) {
							_p("Use Linux Language");
							if (!_api_request_download("lang/linux.txt", langpackfile)) {
								_p("Install Failed");
							}
						}
						if (_Run_SysKernel == Win32_kernel) {
							_p("Use Windows Language");
							if (!_api_request_download("lang/win.txt", langpackfile)) {
								_p("Install Failed");
							}
						}
						_system_autoRun(_$GetSelfFull, "-nolang -unpack \"" + langpackfile + "\" -to \"" + _rcbind_langpath + "\"");
						_p("Complete Install Language");
						_fileapi_del(langpackfile);
						sleepapi(1);
						cleanConsole();

						LanguageLoad();
				}
			}
		}
	}

	if (_Run_SysKernel == Win32_kernel) {
		//Execute Code
		if (_rcset_enforceUTF8 == true) {
			system("chcp 65001 >nul");
		}
	}

	_gf_cg = 0;
	_gf_cgmax = 1;
	_gf_line = 1;
	_gf_charget = "";
	
	if (!_FastMode) {
		if (check_file_existence(_$GetSelfPath + "/Calcium.pdb")) {
			//Debug Mode
			_rcset_anticrash = false;
			_p("Detected PDB File.  AntiCrash Service is Disabled");
		}

		if (_rcset_useAdmin) {
			if (!_isAdminOK_) {
				_system_autoRun_admin(_$GetSelfFull, native_argument + " -%NowIsRunAdmin%");
				return 0;
			}
		}

		if (_rcset_anticrash == true) {
			if (_anticrash_services == false) {
			Crash_Reload_service:
				AntiCrash_Return_Code = _system_autoRun(_$GetSelfFull, native_argument + " \"-anticrash_ok\"");
				if (AntiCrash_Return_Code == 0) {
					return 0;
				}

				AC_FAILCODE = _Old_VSAPI_TransVar("_erc_" + to_string(AntiCrash_Return_Code));

				if (AC_FAILCODE == "_erc_" + to_string(AntiCrash_Return_Code)) {
					AC_FAILCODE = "UNKNOWN_KERNEL_STATUS";
				}

				cleanConsole();
				_pn();
				_pv("_$lang.crash.title");
				_pn();
				_pv("     _$lang.crash.t1");
				_pv("       _$lang.crash.t2");
				_pv("       _$lang.crash.t3");
				_pv("       _$lang.crash.errcode --> " + AC_FAILCODE);
				_pv("       _$lang.crash.kcode :  " + to_string(AntiCrash_Return_Code));
				_pv("     _$lang.runargs :  " + native_argument);
				_pn();
				_pv("  _$lang.presskey");
				_pv("  _$lang.crash.report");
				_pn();
				_pn();
				_pause();
				if (_rcset_crash_reload) {
					cleanConsole();
					goto Crash_Reload_service;
				}
				else {
					return 0;
				}
			}
		}
		else {
			//_p("Anti Crash Services is " + to_string(_rcset_anticrash));
		}

		if (_Time_Bomb_Detect(_KV_releaseVer)) return 661;
		
		if (_activate_request(_rc_activate_key) == false) {
			_p(" [TBD]  Current product is not activated");
		}
		else {
			_p(" [TBD]  Current product activate Succeed");
		}

		if (_rcbind_autorun != "null") {
			_runmode = _runmode_runscript;
			runscript = _rcbind_autorun;
			script_args = _rcbind_autorunargs;

			ckapi_result = _ckapi_scriptload(runscript, script_args);
			if (ckapi_result == "runid.entershell") {
				_runmode = _runmode_openshell;
			}
			else {
				return 0;
			}
		}

		if (_debugMode == true) {
			_p("Runmode ID " + _runmode);
			_p("runscript :  " + runscript);
			_p("Argument :  " + script_args);
			_p("o info :  " + o_info);
			_pause();
			return 0;
		}
	}

	if (_activate_request(_rc_activate_key) == false) {
		_p("Activate Calcium");
	}

	if (Reg_Proces_runid == "NoNameProcess") {
		Reg_Proces_runid = _get_random_s(10000000, 99999999) + "~DiaReg";
	}

	//Register Session Dialogue
	
	Reg_Process_Map = _$GetSelfPath + "/session_map.txt";
	
	if (!check_file_existence(Reg_Process_Map)) {
		_fileapi_write(Reg_Process_Map, "//  Calcium Dialogue Register");
	}

	_write_sipcfg(Reg_Process_Map, Reg_Proces_runid, "alive");

	//Config at process Exit 
	// 
	
	signal(SIGINT, regout_atexit);
	signal(SIGTERM, regout_atexit);
	signal(SIGILL, regout_atexit);
	signal(SIGFPE, regout_atexit);
	signal(SIGSEGV, regout_atexit);
 	signal(SIGABRT, regout_atexit);

	//main
	if (_runmode == _runmode_null) {
		TypeHelpMenu();
		_pause();
		if (_rcset_aosr == true) {
			_runmode = _runmode_openshell;
		}
		else {
			_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
			return 0;
		}
	}
	if (_runmode == _runmode_optimi) {
		readbufferA = runscript + "_optimi.ca";
		_p("Optimi Mode");
		if (runscript == "{null}") {
			_p("Command :  <program.exe> -optimi <file>");
			_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
			return 0;
		}
		_p("Optimi Script :  " + runscript);
		_p("Output Script :  " + readbufferA);
		if (!check_file_existence(runscript)) {
			_p("File Not Found :  " + runscript);
			_p("Command :  <program.exe> -optimi <file>");
			_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
			return 0;
		}
		_soildwrite_open(readbufferA);
		_soildwrite_write("_$directmode;");
		_soildwrite_write("_$nolog;");
		while(true) {
			charCutA = _get_fullLine(runscript, ";");
			_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
			if (_gf_status == false) break;
			_soildwrite_write(charCutA);
		}
		_soildwrite_close();

		_p("Optimi Complete");
		_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
		return 0;
	}
	if (_runmode == _runmode_cstpmake) {
		_Legacy_cstp_maker(runscript, o_info);
		_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
		return 0;
	}
	if (_runmode == _runmode_cstpunpack) {
		_Legacy_cstp_unpack(o_info,runscript);
		_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
		return 0;
	}
	if (_runmode == _runmode_typehelp) {
		TypeHelpMenu();
		_pause();
		_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
		return 0;
	}
	if (_runmode == _runmode_autoexit) {
		_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
		return 0;
	}
	if (_runmode == _runmode_runscript) {
		ckapi_result = _ckapi_scriptload(runscript, script_args);
		if (ckapi_result == "runid.crash.harddrv.error") {
			return 25581;
		}
		if (ckapi_result == "runid.entershell") {
			_runmode = _runmode_openshell;
		}
		else {
			_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
			return 0;
		}
		

	}
	if (_runmode == _runmode_openshell) {
		CK_Shell_open();
		_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
		return 0;
	}
	if (_runmode == _runmode_listversion) {
		_pn();
		_p("Calcium Project   " + _KernelVersion + "(" + _KV_rV_Text + ")");
		_p("RCapi Version :   " + _RCapi_Version);
		_p("Inside Version :   " + InsideVersion);
		_pn();
		_p("OpenCppLangTab Version :  " + $version_code_str + "  (" + $codename + ")");
		_p("OCLT Timestamp :   " + $buildtime);
		_p("Operating system :   " + _Run_SysKernel);
		_p("Run Command Argument :  " + native_argument);
		_p("File Path :  " + _$GetSelfFull);
		_p("Local Config :   " + buildshell);
		_pn();
		_p("Copyright FoxaXu");
		_p($year_message);
		_p("All rights reserved.");
		_pause();
		_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
		return 0;
	}

	_remove_sipcfg(Reg_Process_Map, Reg_Proces_runid);
	return 0;
}