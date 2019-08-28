/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#ifndef DYNAMIXEL_SLAVE_H_
#define DYNAMIXEL_SLAVE_H_

#include "protocol.h"
#include "port_handler.h"

#define CONTROL_ITEM_MAX         64
#define CONTROL_ITEM_ADDR_LIMIT (DXL_BUF_LENGTH-11)


namespace DYNAMIXEL{

typedef void (*userCallbackFunc)(uint16_t addr, uint8_t &dxl_err_code);

typedef struct ControlItem{
  uint16_t start_addr;
  uint16_t length;
  uint8_t* p_data;
} ControlItem_t;


class Slave
{
  public:
    Slave(PortHandler &port, const uint16_t model_num, float protocol_ver = DXL_PACKET_VER_2_0);
    Slave(const uint16_t model_num, float protocol_ver = DXL_PACKET_VER_2_0);      

    uint16_t getModelNumber() const;
    
    bool setID(uint8_t id);
    uint8_t getID() const;

    void setFirmwareVersion(uint8_t version);
    uint8_t getFirmwareVersion() const;
    
    bool setPort(PortHandler &port);
    bool setPortProtocolVersion(float version);
    float getPortProtocolVersion();

    void setWriteCallbackFunc(userCallbackFunc callback_func);
    void setReadCallbackFunc(userCallbackFunc callback_func);

    void processPacket();
    
    uint8_t getLastStatusPacketError() const;
    lib_err_code_t getLastLibErrCode() const;

    uint8_t addControlItem(uint16_t start_addr, uint8_t* p_data, uint16_t length);
    uint8_t addControlItem(uint16_t start_addr, bool &data);
    uint8_t addControlItem(uint16_t start_addr, uint8_t &data);
    uint8_t addControlItem(uint16_t start_addr, uint16_t &data);
    uint8_t addControlItem(uint16_t start_addr, uint32_t &data);
    uint8_t addControlItem(uint16_t start_addr, uint64_t &data);
    uint8_t addControlItem(uint16_t start_addr, int8_t &data);
    uint8_t addControlItem(uint16_t start_addr, int16_t &data);
    uint8_t addControlItem(uint16_t start_addr, int32_t &data);
    uint8_t addControlItem(uint16_t start_addr, int64_t &data);
    uint8_t addControlItem(uint16_t start_addr, float &data);
    uint8_t addControlItem(uint16_t start_addr, double &data);


  private:
    PortHandler *p_port_;
    
    const uint16_t model_num_;
    uint8_t firmware_ver_;
    uint8_t id_;

    uint8_t registered_item_cnt_;
    ControlItem_t control_table_[CONTROL_ITEM_MAX];
    
    userCallbackFunc user_write_callback_;
    userCallbackFunc user_read_callback_;

    dxl_t packet_;

    uint8_t last_status_packet_error_; 
    lib_err_code_t last_lib_err_code_;

    virtual bool processInstPing();
    virtual bool processInstRead();
    virtual bool processInstWrite();
    
    bool processInst(uint8_t inst_idx);
    bool addDefaultControlItem();
};

} // namespace DYNAMIXEL

#endif /* DYNAMIXEL_SLAVE_H_ */