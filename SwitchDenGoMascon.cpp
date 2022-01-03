#include "SwitchDenGoMascon.h"

bool SwitchDenGoMascon::connected(){
  return HIDUniversal::isReady() && HIDUniversal::VID == SWITCH_DEN_GO_VID && HIDUniversal::PID == SWITCH_DEN_GO_PID;
};


void SwitchDenGoMascon::parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {   
  //printBuf(buf);
  
  for(uint8_t i = 0;i < 14;i++){  
    uint8_t index = i / 8;
    SwitchDenGoMascon::buttonValues[i] = (bool)(buf[index] & BUTTONS[i]);
    SwitchDenGoMascon::pressedButtonValues[i] = (bool)(buf[index] & BUTTONS[i]);
  } 
  
  if(buf[2] == BUTTONS[HatUp] || buf[2] == BUTTONS[HatUpRight] || buf[2] == BUTTONS[HatUpLeft]){
    SwitchDenGoMascon::buttonValues[HatUp] = true;
  }else{
    SwitchDenGoMascon::buttonValues[HatUp] = false;
    SwitchDenGoMascon::readedButtonValues[HatUp] = false;
  }
  
  if(buf[2] == BUTTONS[HatRight] || buf[2] == BUTTONS[HatUpRight] || buf[2] == BUTTONS[HatDownRight]){
    SwitchDenGoMascon::buttonValues[HatRight] = true; 
  }else{
    SwitchDenGoMascon::buttonValues[HatRight] = false;
    SwitchDenGoMascon::readedButtonValues[HatRight] = false;
  }
  
  if(buf[2] == BUTTONS[HatDown] || buf[2] == BUTTONS[HatDownRight] || buf[2] == BUTTONS[HatDownLeft]){
    SwitchDenGoMascon::buttonValues[HatDown] = true; 
  }else{
    SwitchDenGoMascon::buttonValues[HatDown] = false;
    SwitchDenGoMascon::readedButtonValues[HatDown] = false;
  }
  
  if(buf[2] == BUTTONS[HatLeft] || buf[2] == BUTTONS[HatUpLeft] || buf[2] == BUTTONS[HatDownLeft]){
    SwitchDenGoMascon::buttonValues[HatLeft] = true;  
  }else{
    SwitchDenGoMascon::buttonValues[HatLeft] = false; 
    SwitchDenGoMascon::readedButtonValues[HatLeft] = false;
  }
  
  SwitchDenGoMascon::masconValue = buf[4];
}

uint8_t SwitchDenGoMascon::getMascon(GetMasonType type){ 
  uint8_t masconPosition;

  switch (SwitchDenGoMascon::masconValue){
    case 0:
      masconPosition = 0;
      break;
    case 5:
      masconPosition = 1;
      break;
    case 19:
      masconPosition = 2;
      break;
    case 32:
      masconPosition = 3;
      break;
    case 46:
      masconPosition = 4;
      break;
    case 60:
      masconPosition = 5;
      break;
    case 73:
      masconPosition = 6;
      break;
    case 87:
      masconPosition = 7;
      break;
    case 101:
      masconPosition = 8;
      break;
    case 128:
      masconPosition = 9;
      break;
    case 159:
      masconPosition = 10;
      break;
    case 183:
      masconPosition = 11;
      break;
    case 206:
      masconPosition = 12;
      break;
    case 230:
      masconPosition = 13;
      break;
    case 255:
      masconPosition = 14;
  }

  if(type == HandlePosition){
    return masconPosition;
  }else if(type == PowerLevel){
    return max(masconPosition - 9,0);
  }else if(type == BrakeLevel){
    return max(9 - masconPosition,0);
  }
}


bool SwitchDenGoMascon::isPressed(BtnNum b){
  return SwitchDenGoMascon::buttonValues[(uint8_t)b];
}


bool SwitchDenGoMascon::wasPressed(BtnNum b){
  if(SwitchDenGoMascon::readedButtonValues[(uint8_t)b]){
    return false;
  }

  if(SwitchDenGoMascon::buttonValues[(uint8_t)b]){
    SwitchDenGoMascon::readedButtonValues[(uint8_t)b] = true;
  }
  
  return SwitchDenGoMascon::buttonValues[(uint8_t)b];
}


void SwitchDenGoMascon::printBuf(uint8_t *buf){
  for(uint8_t i = 0;i < 8;i++){ 
    String s = String(buf[i],BIN);

    while(s.length() < 8){
      s = "0" + s;
    }
    Serial.print(s); 
    Serial.print(" "); 
  } 
  Serial.println(" ");
}
