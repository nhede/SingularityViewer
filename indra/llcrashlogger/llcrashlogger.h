/** 
* @file llcrashlogger.h
* @brief Crash Logger Definition
*
* $LicenseInfo:firstyear=2003&license=viewergpl$
* 
* Copyright (c) 2003-2009, Linden Research, Inc.
* 
* Second Life Viewer Source Code
* The source code in this file ("Source Code") is provided by Linden Lab
* to you under the terms of the GNU General Public License, version 2.0
* ("GPL"), unless you have obtained a separate licensing agreement
* ("Other License"), formally executed by you and Linden Lab.  Terms of
* the GPL can be found in doc/GPL-license.txt in this distribution, or
* online at http://secondlifegrid.net/programs/open_source/licensing/gplv2
* 
* There are special exceptions to the terms and conditions of the GPL as
* it is applied to this Source Code. View the full text of the exception
* in the file doc/FLOSS-exception.txt in this software distribution, or
* online at
* http://secondlifegrid.net/programs/open_source/licensing/flossexception
* 
* By copying, modifying or distributing this software, you acknowledge
* that you have read and understood your obligations described above,
* and agree to abide by those obligations.
* 
* ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
* WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
* COMPLETENESS OR PERFORMANCE.
* $/LicenseInfo$
*/
#ifndef LLCRASHLOGGER_H
#define LLCRASHLOGGER_H

#include "linden_common.h"

#include <vector>

#include "llapp.h"
#include "llsd.h"
#include "llcontrol.h"

class AIHTTPTimeoutPolicy;

class LLCrashLogger : public LLApp
{
public:
	LLCrashLogger();
	virtual ~LLCrashLogger();
	S32 loadCrashBehaviorSetting();
	void gatherFiles();
	virtual void gatherPlatformSpecificFiles() {}
	bool saveCrashBehaviorSetting(S32 crash_behavior);
	bool sendCrashLogs();
	LLSD constructPostData();
	virtual void updateApplication(const std::string& message = LLStringUtil::null);
	virtual bool init();
	virtual bool mainLoop() = 0;
	virtual bool cleanup() { return true; }
	void setUserText(const std::string& text) { mCrashInfo["UserNotes"] = text; }
	S32 getCrashBehavior() { return mCrashBehavior; }
	bool runCrashLogPost(std::string host, LLSD data, std::string msg, int retries);
protected:
	S32 mCrashBehavior;
	BOOL mCrashInPreviousExec;
	std::map<std::string, std::string> mFileMap;
	std::string mGridName;
	LLControlGroup mCrashSettings;
	std::string mProductName;
	LLSD mCrashInfo;
	std::string mCrashHost;
	std::string mAltCrashHost;
	LLSD mDebugLog;
	bool mSentCrashLogs;
};

class LLCrashLoggerText : public LLCrashLogger
{
public:
	LLCrashLoggerText(void) {}
	~LLCrashLoggerText(void) {}

	virtual bool mainLoop();
	virtual void updateApplication(const std::string& message = LLStringUtil::null);
};


#endif //LLCRASHLOGGER_H
