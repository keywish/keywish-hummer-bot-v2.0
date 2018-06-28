#ifndef   _PROTOCOLPARSER_H_
#define   _PROTOCOLPARSER_H_
#include "Arduino.h"
#include "Protocol.h"
#include <stdint.h>

#define BUFFER_SIZE 64

class ProtocolParser  
{  
public:  
    ProtocolParser(byte header = PROTOCOL_START_CODE, byte end = PROTOCOL_END_CODE);
    ~ProtocolParser();  
    bool RecevData(char *data, size_t len);
    bool RecevData(void);
    bool ParserPackage(char *data = NULL);

    E_TYPE GetRobotType();
    uint8_t GetRobotAddr();
    E_CONTOROL_FUNC GetRobotControlFun();
    int GetRobotSpeed();
    int GetRobotDegree();
    bool SendPackage(ST_PROTOCOL *send_dat,int len);
  
private:
    char buffer[BUFFER_SIZE];
    byte m_StartCode, m_EndCode;
    ST_PROTOCOL *recv;
    uint8_t protocol_data_len;
    bool m_recv_flag, m_send_success;  // recevive flag
    byte *m_pHeader;        // protocol header 
    uint8_t m_PackageLength;     // recevie package length  
    uint16_t m_CheckSum;
    uint8_t m_RecvDataIndex;//记录接收数据的索引  
  
    char GetHeader(size_t index);//获取协议首部指定索引的字符  
    uint8_t GetProtocolDataLength();           //获取控制协议数据长度
    uint8_t GetPackageLength();             //获取接收到一帧数据包的长度  
    uint16_t GetCheckSum(); // get package check sum
};  

#endif // _PROTOCOLPARSER_H_
