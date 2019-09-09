// *************************************************************************
//
// Copyright (C) 2019  yaofei zheng
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <unordered_map>
#include <string>
#include <time.h>
using namespace std;

int WebConfigProcess(const char *Cmd)
{
    int iRet = 1;
    if(iRet == 0)
    {}
    else if (0 == memcmp(Cmd, "Get", 3))
    {
        if (!strcmp(Cmd, "Get_SystemAbility.cgi"))
        {}
        else if(!strcmp(Cmd, "GetCommCfg.cgi"))
        {}
        else if (!strcmp(Cmd, "GetDecodeCfg.cgi"))
        {}
        else if (!strcmp(Cmd, "GetListenPort.cgi"))
        {}
        else if(!strcmp(Cmd, "GetDeviceInfo.cgi"))
        {}
        else if(!strcmp(Cmd, "GetAutoMaintainCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetChannelTitleCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetVideoUrl.cgi"))
        {}
        else if(!strcmp(Cmd, "GetRecordUrl.cgi"))
        {}
        else if(!strcmp(Cmd, "GetGeneralNetCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetRecordCtrlCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetPtzProtocol.cgi"))
        {}
        else if(!strcmp(Cmd, "GetPtzCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetPtzPresetCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetPtzTourCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetDiskInfo.cgi"))
        {}
        else if(!strcmp(Cmd, "GetRecordAbility.cgi"))
        {}
        else if(!strcmp(Cmd, "GetRecordCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetTimeCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetCameraState.cgi"))
        {}
        else if(!strcmp(Cmd, "Getbps.cgi"))
        {}
        else if(!strcmp(Cmd, "GetAlarmCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetAlarmOutCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetAlarmOutState.cgi"))
        {}
        else if(!strcmp(Cmd, "GetImageCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetLog.cgi"))
        {}
        else if(!strcmp(Cmd, "GetLogSet.cgi"))
        {}
        else if(!strcmp(Cmd, "GetInterVideoLog.cgi"))
        {}
        else if(!strcmp(Cmd, "GetGeneralCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetAbtsetCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetDiskArrayCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetEncodeAbility.cgi"))
        {}
        else if(!strcmp(Cmd, "GetEncodeCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetSnapAbility.cgi"))
        {}
        else if(!strcmp(Cmd, "GetSnapCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetOsdAbility.cgi"))
        {}
        else if(!strcmp(Cmd, "GetOsdCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetDevTypeNameMap.cgi"))
        {}
        else if(!strcmp(Cmd, "GetSplitCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetTourCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetPureDecodeCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetRoiAbility.cgi"))
        {}
        else if(!strcmp(Cmd, "GetRoiCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "GetIntDetect.cgi"))
        {}
        else if(!strcmp(Cmd, "GetIntDetectCfg.cgi"))
        {}
        else {}
    }
    else if(0 == memcmp(Cmd, "Set", 3))
    {
        if(!strcmp(Cmd, "SetDecodeCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetCommCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetEncodeCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetSnapCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetAutoMaintainCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetChannelTitleCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetRecordCtrlCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetGeneralNetCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetPtzCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetDiskCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetRecordCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetTimeCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetAlarmCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetGeneralCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetAbtsetCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetAlarmOutCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetImageCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetLogSet.cgi"))
        {}
        else if(!strcmp(Cmd, "SetOsdCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetSplitCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetTourCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetPureDecodeCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetRoiCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "SetIntDetect.cgi"))
        {}
        else if(!strcmp(Cmd, "SetIntDetectCfg.cgi"))
        {}
        else {}
    }
    else if(!strcmp(Cmd, "Reboot.cgi"))
    {}
    else if(!strcmp(Cmd, "SyncTime.cgi"))
    {}
    else if(!strcmp(Cmd, "ManualShot.cgi"))
    {}
    else if(!strcmp(Cmd, "QueryRecord.cgi"))
    {}
    else if(!strcmp(Cmd, "PtzCtrl.cgi"))
    {}
    else if(!strcmp(Cmd, "ModPTZPresetCfg.cgi"))
    {}
    else if(!strcmp(Cmd, "ModPtzTourCfg.cgi"))
    {}
    else if(!strcmp(Cmd, "ClearLog.cgi"))
    {}
    else if(!strcmp(Cmd, "ClearInterVideoLog.cgi"))
    {}
    else if (0 == memcmp(Cmd, "Net_", 4))
    {
        if (!strcmp(Cmd, "Net_GetRtspCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_SetRtspCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_GetIPFilterCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_SetIPFilterCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_GetSmtpCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_SetSmtpCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_GetDDNSCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_SetDDNSCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_GetUPNPCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_SetUPNPCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_GetPPPOECfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_SetPPPOECfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_GetNTPCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_SetNTPCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_GetFtpServerCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_SetFtpServerCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_GetFtpAppCfg.cgi"))
        {}
        else if(!strcmp(Cmd, "Net_SetFtpAppCfg.cgi"))
        {}
        else {}
    }
    else if (0 == memcmp(Cmd, "DefaultCfg.cgi", 4))
    {}
    else if (0 == memcmp(Cmd, "User_", 5))
    {
        if(!strcmp(Cmd, "User_QueryUserAuth.cgi"))
        {}
        else if(!strcmp(Cmd, "User_QueryUserGroup.cgi"))
        {}
        else if(!strcmp(Cmd, "User_QueryUser.cgi"))
        {}
        else if(!strcmp(Cmd, "User_AddUser.cgi"))
        {}
        else if(!strcmp(Cmd, "User_ModUser.cgi"))
        {}
        else if(!strcmp(Cmd, "User_ModPwd.cgi"))
        {}
        else if(!strcmp(Cmd, "User_DelUser.cgi"))
        {}
        else if(!strcmp(Cmd, "User_AddUserGroup.cgi"))
        {}
        else if(!strcmp(Cmd, "User_DelUserGroup.cgi"))
        {}
        else if(!strcmp(Cmd, "User_ModUserGroup.cgi"))
        {}
        else {}
    }
    return 0;
}
int WebConfigEntry(const char *uri)
{
    if(0 == memcmp(uri, "GetPic.cgi", strlen("GetPic.cgi")))
    {
        return 0;
    }
    if(0 == memcmp(uri, "GetConfigFile.cgi", strlen("GetConfigFile.cgi")))
    {
        return 0;
    }
    else
    {
        return WebConfigProcess(uri);
    }
    return -1;
}

int main(int argc, char *argv[])
{
    unordered_map<string, int> test_unordered;
    map<string, int> test_order;

    string str[] =
    {
        "GetPic.cgi",
        "GetConfigFile.cgi",
        "Get_SystemAbility.cgi",
        "GetDecodeCfg.cgi",
        "GetListenPort.cgi",
        "GetDeviceInfo.cgi",
        "GetAutoMaintainCfg.cgi",
        "GetChannelTitleCfg.cgi",
        "GetVideoUrl.cgi",
        "GetRecordUrl.cgi",
        "GetGeneralNetCfg.cgi",
        "GetRecordCtrlCfg.cgi",
        "GetPtzProtocol.cgi",
        "GetPtzCfg.cgi",
        "GetPtzPresetCfg.cgi",
        "GetPtzTourCfg.cgi",
        "GetDiskInfo.cgi",
        "GetRecordAbility.cgi",
        "GetRecordCfg.cgi",
        "GetTimeCfg.cgi",
        "GetCameraState.cgi",
        "Getbps.cgi",
        "GetAlarmCfg.cgi",
        "GetAlarmOutCfg.cgi",
        "GetAlarmOutState.cgi",
        "GetImageCfg.cgi",
        "GetLog.cgi",
        "GetLogSet.cgi",
        "GetInterVideoLog.cgi",
        "GetGeneralCfg.cgi",
        "GetAbtsetCfg.cgi",
        "GetDiskArrayCfg.cgi",
        "GetEncodeAbility.cgi",
        "GetEncodeCfg.cgi",
        "GetSnapAbility.cgi",
        "GetSnapCfg.cgi",
        "GetOsdAbility.cgi",
        "GetOsdCfg.cgi",
        "GetDevTypeNameMap.cgi",
        "GetSplitCfg.cgi",
        "GetTourCfg.cgi",
        "GetPureDecodeCfg.cgi",
        "GetRoiAbility.cgi",
        "GetRoiCfg.cgi",
        "GetIntDetect.cgi",
        "GetIntDetectCfg.cgi",
        "SetDecodeCfg.cgi",
        "SetCommCfg.cgi",
        "SetEncodeCfg.cgi",
        "SetSnapCfg.cgi",
        "SetAutoMaintainCfg.cgi",
        "SetChannelTitleCfg.cgi",
        "SetRecordCtrlCfg.cgi",
        "SetGeneralNetCfg.cgi",
        "SetPtzCfg.cgi",
        "SetDiskCfg.cgi",
        "SetRecordCfg.cgi",
        "SetTimeCfg.cgi",
        "SetAlarmCfg.cgi",
        "SetGeneralCfg.cgi",
        "SetAbtsetCfg.cgi",
        "SetAlarmOutCfg.cgi",
        "SetImageCfg.cgi",
        "SetLogSet.cgi",
        "SetOsdCfg.cgi",
        "SetSplitCfg.cgi",
        "SetTourCfg.cgi",
        "SetPureDecodeCfg.cgi",
        "SetRoiCfg.cgi",
        "SetIntDetect.cgi",
        "SetIntDetectCfg.cgi",
        "Reboot.cgi",
        "SyncTime.cgi",
        "ManualShot.cgi",
        "QueryRecord.cgi",
        "PtzCtrl.cgi",
        "ModPTZPresetCfg.cgi",
        "ModPtzTourCfg.cgi",
        "ClearLog.cgi",
        "ClearInterVideoLog.cgi",
        "Net_GetRtspCfg.cgi",
        "Net_SetRtspCfg.cgi",
        "Net_GetIPFilterCfg.cgi",
        "Net_SetIPFilterCfg.cgi",
        "Net_GetSmtpCfg.cgi",
        "Net_SetSmtpCfg.cgi",
        "Net_GetDDNSCfg.cgi",
        "Net_SetDDNSCfg.cgi",
        "Net_GetUPNPCfg.cgi",
        "Net_SetUPNPCfg.cgi",
        "Net_GetPPPOECfg.cgi",
        "Net_SetPPPOECfg.cgi",
        "Net_GetNTPCfg.cgi",
        "Net_SetNTPCfg.cgi",
        "Net_GetFtpServerCfg.cgi",
        "Net_SetFtpServerCfg.cgi",
        "Net_GetFtpAppCfg.cgi",
        "Net_SetFtpAppCfg.cgi",
        "DefaultCfg.cgi",
        "User_QueryUserAuth.cgi",
        "User_QueryUserGroup.cgi",
        "User_QueryUser.cgi",
        "User_AddUser.cgi",
        "User_ModUser.cgi",
        "User_ModPwd.cgi",
        "User_DelUser.cgi",
        "User_AddUserGroup.cgi",
        "User_DelUserGroup.cgi",
        "User_ModUserGroup.cgi"
    };

    for(size_t i; i < sizeof(str) / sizeof(str[0]); i++)
    {
        test_unordered[str[i]] = i;
    }

    for(size_t i; i < sizeof(str) / sizeof(str[0]); i++)
    {
        test_order[str[i]] = i;
    }

    timespec begin;
    timespec end;

    string test_str = "User_ModUserGroup.cgi";

    clock_gettime(CLOCK_REALTIME, &begin);
    test_unordered[test_str.c_str()];
    clock_gettime(CLOCK_REALTIME, &end);

    printf("test_unordered begin seconds: %lu, nano seconds: %lu\n", begin.tv_sec, begin.tv_nsec);
    printf("test_unordered end   seconds: %lu, nano seconds: %lu\n", end.tv_sec, end.tv_nsec);
    printf("time: %ld\n", end.tv_nsec - begin.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &begin);
    test_order[test_str.c_str()];
    clock_gettime(CLOCK_REALTIME, &end);

    printf("test_order begin     seconds: %lu, nano seconds: %lu\n", begin.tv_sec, begin.tv_nsec);
    printf("test_order end       seconds: %lu, nano seconds: %lu\n", end.tv_sec, end.tv_nsec);
    printf("time: %ld\n", end.tv_nsec - begin.tv_nsec);

    clock_gettime(CLOCK_REALTIME, &begin);
    WebConfigEntry(test_str.c_str());
    clock_gettime(CLOCK_REALTIME, &end);

    printf("if else begin        seconds: %lu, nano seconds: %lu\n", begin.tv_sec, begin.tv_nsec);
    printf("if else end          seconds: %lu, nano seconds: %lu\n", end.tv_sec, end.tv_nsec);
    printf("time: %ld\n", end.tv_nsec - begin.tv_nsec);
    return 0;
}
