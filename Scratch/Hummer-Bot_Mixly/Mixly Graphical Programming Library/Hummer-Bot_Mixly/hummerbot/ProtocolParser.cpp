#include "Protocol.h"
#include "ProtocolParser.h"
#define DEBUG_LEVEL DEBUG_LEVEL_ERR
#include "debug.h"
#include "SmartCar.h"

#if ARDUINO > 10609
ProtocolParser::ProtocolParser(byte startcode = PROTOCOL_START_CODE, byte endcode = PROTOCOL_END_CODE)
#else
ProtocolParser::ProtocolParser(byte startcode , byte endcode )
#endif
{
    m_recv_flag = false;
    m_send_success = false;
    m_StartCode = startcode;
    m_EndCode = endcode;
    m_pHeader = buffer;        // protocol header
    protocol_data_len = 0;     // protocol->data length
    m_PackageLength = 0;       // recevie all package length
    m_CheckSum = 0x0000;
    m_RecvDataIndex = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = 0;
    }
}

ProtocolParser::~ProtocolParser(void)
{
    m_pHeader = NULL;
}
#if ARDUINO > 10609
bool ProtocolParser::ParserPackage(char *data = NULL)
#else
bool ProtocolParser::ParserPackage(char *data )
#endif
{
    if (m_recv_flag) {
        m_recv_flag = false;
        if (data != NULL) {
            m_pHeader = (byte *)data;
        } else {
            m_pHeader = buffer;
        }
        unsigned short int check_sum = 0;
        recv->start_code = buffer[0];
        recv->len = buffer[1];
        for (int i = 1; i < m_PackageLength - 3; i++) {
            check_sum += buffer[i];
        }
        if ((check_sum & 0xFFFF) != GetCheckSum()) {
             DEBUG_ERR("check sum error \n");
        	 for (int i = 0; i < m_PackageLength; i++) {
                DEBUG_LOG(DEBUG_LEVEL_ERR, "0x%x ", buffer[i]);
        	 }
         return false ;
	    }
    	recv->function = buffer[4];
    	recv->data = &buffer[5];
    	protocol_data_len = m_PackageLength - 8;
    	recv->end_code = buffer[m_RecvDataIndex];
    	DEBUG_LOG(DEBUG_LEVEL_INFO, "\nRecevPackage end \n");
    	return true;
	}
    return false;
}

bool ProtocolParser::RecevData(void)
{
   // DEBUG_LOG(DEBUG_LEVEL_INFO, "RecevData start \n");

    static bool avilable = false;
    byte preRecvLen = 0;
    byte dat;

    while (Serial.available() > 0) {
        dat = Serial.read();
        // DEBUG_LOG(DEBUG_LEVEL_INFO, "\n");
       // Serial.println(dat, HEX);
        delay(2);
        if (avilable == false && dat == m_StartCode) {
              for (int i = 0; i < BUFFER_SIZE; i++) {
                 buffer[i] = 0;
             }
            preRecvLen = 0;
            m_pHeader = buffer;
            *m_pHeader++ = dat;
            m_RecvDataIndex = 0;
            avilable = true;
            // Serial.println(dat, HEX);
            DEBUG_LOG(DEBUG_LEVEL_INFO, "aviable\n");
            continue;
        }
        if (avilable) {
            if (dat == m_EndCode && preRecvLen == m_RecvDataIndex) {
                avilable = false;
                *m_pHeader = dat;
                m_RecvDataIndex++;
                m_PackageLength = m_RecvDataIndex + 1;
                m_recv_flag = true;
                DEBUG_LOG(DEBUG_LEVEL_INFO, "RecevData end \n");
                return true;
           } else {
                //Serial.println(dat, HEX);
                *m_pHeader++ = dat;
                m_RecvDataIndex++;
                if (m_RecvDataIndex == 1) {
                   DEBUG_LOG(DEBUG_LEVEL_INFO, "m_RecvDataIndex %d\n", m_RecvDataIndex);
                   preRecvLen = dat;
                }
                if ( preRecvLen > BUFFER_SIZE || (m_RecvDataIndex > preRecvLen && preRecvLen != 0)) {
                        for (int i = 0; i < BUFFER_SIZE; i++) {
                            DEBUG_LOG(DEBUG_LEVEL_INFO, "%x ", buffer[i]);
                        }
                        preRecvLen = 0;
                        m_pHeader = buffer;
                        avilable = false;
                        m_recv_flag = false;
                        DEBUG_ERR("preRecvLen\n");
                        return false;
                }

                if (m_RecvDataIndex >= BUFFER_SIZE - 1) {
                    for (int i = 0; i < BUFFER_SIZE; i++) {
                        DEBUG_LOG(DEBUG_LEVEL_ERR, "%x ", buffer[i]);
                    }
                    DEBUG_ERR("buffer is error\n");
                    preRecvLen = 0;
                    m_pHeader = buffer;
                    avilable = false;
                    m_recv_flag = false;
                    return false;
                 }
            }
        }
    }
    return avilable;
}

#if ARDUINO > 10609
bool ProtocolParser::RecevData(char *data=NULL, size_t len=0)
#else
bool ProtocolParser::RecevData(char *data, size_t len)
#endif
{
    DEBUG_LOG(DEBUG_LEVEL_INFO, "RecevData start \n");
    static bool avilable = false;
    byte preRecvLen = 0;
    byte dat;
    memset(buffer, 0, BUFFER_SIZE);

    for (byte i = 0; i < len; i++) {
        dat = data[i];
        if (avilable == false && dat == m_StartCode) {
            preRecvLen = 0;
            m_pHeader = buffer;
            *m_pHeader++ = dat;
            m_RecvDataIndex = 0;
            avilable = true;
            DEBUG_LOG(DEBUG_LEVEL_INFO, "aviable\n");
            continue;
        }
        if (avilable) {
            if (dat == m_EndCode && preRecvLen == m_RecvDataIndex) {
                avilable = false;
                *m_pHeader = dat;
                m_RecvDataIndex++;
                m_PackageLength = m_RecvDataIndex + 1;
                m_recv_flag = true;
                DEBUG_LOG(DEBUG_LEVEL_INFO, "RecevData end \n");
                return true;
           } else {
                //Serial.println(dat, HEX);
                *m_pHeader++ = dat;
                m_RecvDataIndex++;
                if (m_RecvDataIndex == 1) {
                   DEBUG_LOG(DEBUG_LEVEL_INFO, "m_RecvDataIndex %d\n", m_RecvDataIndex);
                   preRecvLen = dat;
                }
                if ( preRecvLen > BUFFER_SIZE || (m_RecvDataIndex > preRecvLen && preRecvLen != 0)) {
                        for (int i = 0; i < BUFFER_SIZE; i++) {
                            DEBUG_LOG(DEBUG_LEVEL_INFO, "%x ", buffer[i]);
                        }
                        preRecvLen = 0;
                        m_pHeader = buffer;
                        avilable = false;
                        m_recv_flag = false;
                        DEBUG_ERR("Send length > BUFFER_SIZE\n");
                        return false;
                }

                if (m_RecvDataIndex >= BUFFER_SIZE - 1) {
                    for (int i = 0; i < BUFFER_SIZE; i++) {
                        DEBUG_LOG(DEBUG_LEVEL_ERR, "%x ", buffer[i]);
                    }
                    DEBUG_ERR("buffer is error\n");
                    preRecvLen = 0;
                    m_pHeader = buffer;
                    avilable = false;
                    m_recv_flag = false;
                    return false;
                 }
            }
        }
    }
    return avilable;
}


E_TYPE ProtocolParser::GetRobotType()
{
    return (E_TYPE)recv->type;
}

uint8_t ProtocolParser::GetRobotAddr()
{
    return recv->addr;
}

E_CONTOROL_FUNC ProtocolParser::GetRobotControlFun()
{
    return (E_CONTOROL_FUNC)recv->function;
}

int ProtocolParser::GetRobotSpeed()
{
    if (recv->function == E_ROBOT_CONTROL_SPEED) {
        return (int)(*(recv->data));
    } else {
        return 0;
    }
}

int ProtocolParser::GetRobotDegree()
{
    if (recv->function == E_ROBOT_CONTROL_DIRECTION) {
        return ((int)(*(recv->data)<< 8) | (int)(*(recv->data+1)));
    } else {
        return 0;
    }
}

// up 0 down 1 left 2 right 3 speeddown 4 speedup 5
bool ProtocolParser::GetBluetoothButton(byte button) {
    int dat = 0xFF;
	static int pre_speed = 0;
    if (button < 4) {
        if (recv->function == E_ROBOT_CONTROL_DIRECTION) {
            dat = (int)(*(recv->data)<< 8) | (int)(*(recv->data+1));
            if ((dat == 0 || dat == 360 ) && button == 3) {
                return true;
            } else if (dat == 90 && button == 0) {
                return true;
            } else if (dat == 180 && button == 2) {
                return true;
            } else if (dat == 270  && button == 1) {
                return true;
            }
        }
    } else if (button >3 && button <= 5) {
        if (recv->function == E_ROBOT_CONTROL_SPEED) {
            dat = (int)(*(recv->data));
            if ((dat < pre_speed) && button == 4) {
                    pre_speed = dat;
                    return true;
                } else if (dat > pre_speed && button == 5) {
                    pre_speed = dat;
                    return true;
            }
        }
    }
    return false;
}


E_SMARTCAR_CONTROL_MODE ProtocolParser::GetControlMode(void)
{
    if (((E_CONTOROL_FUNC)recv->function) == E_CONTROL_MODE) {
        return (E_SMARTCAR_CONTROL_MODE)(*(recv->data));
    } else {
        return (E_SMARTCAR_CONTROL_MODE)0;
    }
}

uint8_t ProtocolParser::GetProtocolDataLength()
{
    return protocol_data_len;
}

uint8_t ProtocolParser::GetPackageLength()
{
    return m_PackageLength;
}

uint16_t ProtocolParser::GetCheckSum(void)
{
    return ((buffer[m_PackageLength - 3] << 8 ) |  buffer[m_PackageLength - 2]);
}

// len : protocol data length
bool ProtocolParser::SendPackage(ST_PROTOCOL *send_dat,int len)
{
    if( send_dat == NULL || len > BUFFER_SIZE) {
        DEBUG_ERR("SendPackage error");
        return false;
    }
    unsigned short checksum = 0;
    byte *p_data = &buffer[5];
    protocol_data_len = len;
    buffer[0] = send_dat->start_code;
    buffer[1] = send_dat->len;
    buffer[2] = send_dat->type;
    buffer[3] = send_dat->addr;
    buffer[4] = send_dat->function;
    checksum = buffer[1] + buffer[2] + buffer[3] + buffer[4];

  //  Serial.println(*send_dat->data);
   // Serial.println(*(send_dat->data + 1 ));
    for(int i = 0; i < len; i++) {
       *(p_data+i) = *(send_dat->data + i);
    //   Serial.println(*(p_data+i) );
       checksum += *(send_dat->data + i);
    }
    *(p_data + len) = (checksum >> 8) & 0xFF;
    *(p_data + len + 1) = checksum & 0xFF;
    *(p_data + len + 2) = send_dat->end_code;

    Serial.write(buffer,len+8);
    Serial.flush();
    delay(200);
    return true;
}
