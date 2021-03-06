#include "tll-common.h"

#define MAX_SAT_COUNT 64
#define MAX_LNB_COUNT 40
#define MAX_DVBS_COUNT 7520
#define MAX_TP_COUNT 2400

struct LV184_AnalogChannel
{
  byte t1[8];
  TLL_SignalSource SignalSource;
  byte t1b;
  word ChannelTransponder1;
  word ProgramNr;
  word LogicalProgramNr1;
  word t2[2];
  byte Favorites1;
  byte t2b;
  word Frequency1Div50;
  word APID1;
  byte ChannelNumberInBand;
  byte ChannelBand;
  byte t3[2];
  char CH_Name1[40];
  byte CH_NameLength1;
  byte t4[1];
  word SID1;
  byte t5a[16];
  word ChannelTransponder2;
  dword Frequency;
  byte t6[2];
  word ONID;
  word TSID;
  byte t7[19];
  word ChannelTransponder3;
  word ProgramNr2;
  word LogicalProgramNr2;
  byte t8b;
  word ChannelTransponder4;
  byte Favorites2;
  byte LockSkipHide;
  word SID2;
  byte ServiceType; 
  byte CH_NameLength2;
  char CH_Name2[40];
  word Frequency2Div50;
  word APID2;
  byte t11[4];
};


struct LV184_DvbCtChannel
{
  byte t1[8];
  TLL_SignalSource SignalSource;
  byte t1b;
  word ChannelTransponder1;
  word ProgramNr;
  word LogicalProgramNr2;
  word t2[2];
  byte Favorites1;
  byte t2d;
  word PcrPid1;
  word APID1;
  word VPID1;
  byte t3[2];
  char CH_Name1[40];
  byte CH_NameLength1;
  byte t4;
  word SID1;
  byte t5a[16];
  word ChannelTransponder2;
  dword Frequency;
  byte t6[2];
  word ONID;
  word TSID;
  byte t7[19];
  word ChannelTransponder3;
  word ProgramNr2;
  word LogicalProgramNr2;
  byte t8b;
  word ChannelTransponder4;
  byte Favorites2;
  byte LockSkipHide;
  word SID2;
  byte ServiceType; 
  byte CH_NameLength2;
  char CH_Name2[40];
  word PcrPid2;
  word APID2;
  byte t11[4];
};

struct LV184_AnalogBlock
{
  dword BlockSize; 
  dword ChannelCount;
  LV184_AnalogChannel Channels[ChannelCount];
};

struct LV184_FirmwareBlock
{
  dword BlockSize;
  byte Data[BlockSize];
};

struct LV184_DvbCTBlock
{
  dword BlockSize;
  dword ChannelCount;
  LV184_DvbCtChannel Channels[ChannelCount];
};

struct LV184_DvbsHeaderSubblock
{
  dword Crc32;
  byte DVBS_S2_Tag[8];
  word Temp03[2];
};

struct LV184_Satellite
{
  char Name[32]; 
  byte PosDeg; 
  byte PosCDeg; 
  word Unknown1;
  word Unknown2;
  word Unknown3;
  word TransponderCount;
  word Unknown4;
};

struct LV184_DvbsSatelliteSubblock
{
  dword Crc32;
  word Unknown1;
  byte SatAllocationBitmap[MAX_SAT_COUNT/8];
  word Unknown2;
  word SatCount;
  byte SatOrder[MAX_SAT_COUNT];
  word Unknown3;
  LV184_Satellite Satellites[MAX_SAT_COUNT];
};

struct LV184_Transponder
{
  byte t1[10];
  word TP_Number;
  word TP_Freq;
  byte t2[4]; 
  word NID; 
  word TID; 
  byte t3[3];
  word SRate;
  byte t4[9]; 
  byte SatIndexTimes2; 
  byte t5[3]; 
};

struct LV184_DvbsTransponderSubblock
{
  dword Crc32;
  word Unknown1;
  word Unknown2;
  word Unknown3;
  word Unknown4;
  word TransponderCount;
  byte AllocationBitmap[MAX_TP_COUNT/8];
  struct LV184_DvbsTransponderTable1
  {
    word Prev;
    word Next;
    word Current;
  } TransponderTable1[MAX_TP_COUNT];
  word Unknown5;
  LV184_Transponder Transponder[MAX_TP_COUNT];  
};

struct LV184_SatChannel
{
  word LnbIndex;  
  byte t2[2];
  TLL_SignalSource SignalSource;
  word TP_Number; 
  byte t2b;
  word CH_Number; 
  word CH_NumberFixed;
  word TP_Number2;
  byte t3b;
  byte EditFlag;   
  word SID;       
  byte ServiceType;
  byte CH_NameLength; 
  char CH_Name[40];
  word VID; 
  word AID; 
  word t4;  
  byte t5[2];
};

struct LV184_DvbsChannelSubblock
{
  dword Crc32; 
  word Unknown[2];
  word LinkedListStartIndex;
  word LinkedListEndIndex1;
  word LinkedListEndIndex2;
  word ChannelCount;
  byte AllocationBitmap[MAX_DVBS_COUNT/8];
  struct LV184_LinkedChannelList
  {
    word Prev;
    word Next;
    word Current;
    word Zero;
  } LinkedList[MAX_DVBS_COUNT];
  LV184_SatChannel Channels[MAX_DVBS_COUNT];
};

struct LV184_Lnb
{
  byte SettingsID; 
  byte t2[3];
  byte SatelliteID;
  byte t3[3];
  char FrequenceName[12]; 
  word LOF1; 
  byte t4[2]; 
  word LOF2; 
  byte t5[18]; 
};

struct LV184_DvbsLnbSubblock
{
  dword Crc32;
  word Unknown1;
  byte AllocationBitmap[5];
  byte Unknown2;
  LV184_Lnb Lnb[MAX_LNB_COUNT];
};

struct LV184_DvbSBlock
{
  dword BlockSize;
  LV184_DvbsHeaderSubblock HeaderBlock;
  LV184_DvbsSatelliteSubblock SatelliteBlock;
  LV184_DvbsTransponderSubblock TransponderBlock;
  LV184_DvbsChannelSubblock ChannelBlock;
  LV184_DvbsLnbSubblock LnbBlock;
};

struct LV184_SettingsBlock
{
  dword BlockSize;
  byte Data[BlockSize]; 
};

public struct LV184
{
  byte Header[4];  
  LV184_AnalogBlock Analog;
  LV184_FirmwareBlock Firmware;
  LV184_DvbCTBlock DvbCT;
  LV184_DvbSBlock DvbS;
  LV184_SettingsBlock Settings;
};
