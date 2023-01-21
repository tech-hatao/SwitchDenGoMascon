#ifndef SWITCH_DEN_GO_MASCON
#define SWITCH_DEN_GO_MASCON

#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>

const uint16_t SWITCH_DEN_GO_VID = 0x0F0D;
const uint16_t SWITCH_DEN_GO_PID = 0x00C1;

enum GetMasonType {
  HandlePosition,
  PowerLevel,
  BrakeLevel
};

enum BtnNum {
  BtnL,
  BtnR,
  BtnZl,
  BtnZr,
  BtnB,
  BtnA,
  BtnX,
  BtnY,
  
  BtnCapture,
  BtnHome,
  Dummy1,
  Dummy2,
  BtnPlus,
  BtnMinus,
  Dummy3,
  Dummy4,
  
  HatUp,
  HatUpRight,
  HatRight,
  HatDownRight,
  HatDown,
  HatDownLeft,
  HatLeft,
  HatUpLeft,
};

const uint8_t MASCON_BUTTONS[] = {
  0x10, // L
  0x20, // R
  0x40, // ZL
  0x80, // ZR
  0x02, // B
  0x04, // A
  0x08, // X
  0x01, // Y
  
  0x20, // Capture
  0x10, // HOME
  0x00, // dummy
  0x00, // dummy
  0x02, // PLUS
  0x01, // MINUS
  0x00, // dummy
  0x00, // dummy
  
  0x00, // Hat UP
  0x01, // Hat UP + RIGHT
  0x02, // Hat RIGHT
  0x03, // Hat RIGHT + DOWN
  0x04, // Hat DOWN
  0x05, // Hat DOWN + LEFT
  0x06, // Hat LEFT
  0x07, // Hat LEFT + UP
};

class SwitchDenGoMascon : public HIDUniversal {
private:
  bool buttonValues[24]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  bool readedButtonValues[24]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  unsigned long pressTime[24]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  bool readedPressedFor[24]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  uint8_t masconValue; 
public:
  SwitchDenGoMascon(USB *p) : HIDUniversal(p){};
  bool connected();
  uint8_t getMascon(GetMasonType type = HandlePosition);
  bool isPressed(BtnNum btn);
  bool wasPressed(BtnNum btn);
  bool isPressedFor(BtnNum btn,int time);
  bool wasPressedFor(BtnNum btn,int time);
protected:
  void ParseHIDData(USBHID *hid __attribute__((unused)), bool is_rpt_id __attribute__((unused)), uint8_t len, uint8_t *buf) {
    if (HIDUniversal::VID == SWITCH_DEN_GO_VID && HIDUniversal::PID == SWITCH_DEN_GO_PID){
      SwitchDenGoMascon::parse(hid,is_rpt_id,len, buf);
    }
  };
  void parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
  void printBuf(uint8_t *buf);
  
};
  
#endif 
