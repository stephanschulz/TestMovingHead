//
//  MovingAxis.cpp
//  LidarOnMovingHead
//
//  Created by Roy Macdonald on 6/4/22.
//

#include "MovingAxis.h"
   
   void MovingAxis::valueChanged(uint16_t&){
       if(!bIsSettingValueAngle){
           bIsSettingValueAngle = true;
           angle = getAngle();
//           sendDmx();
           ofNotifyEvent(sendDmxEvent, this);
           bIsSettingValueAngle = false;
       }
   }
   void MovingAxis::angleChanged(float&){
       if(!bIsSettingValueAngle){
       bIsSettingValueAngle = true;
           value = (uint16_t)ofMap(angle.get(), min_angle, max_angle, 0, 65535);
//           sendDmx();
           ofNotifyEvent(sendDmxEvent, this);
           bIsSettingValueAngle = false;
       }
       
   }
   
   void MovingAxis::setup(ofxDmx* _dmx, string name, uint8_t _coarseChan, uint8_t _fineChan, float _min_angle, float _max_angle)
   {
       dmx = _dmx;
       min_angle = _min_angle;
       max_angle = _max_angle;
       
       coarseChan = _coarseChan;
       fineChan = _fineChan;
       
       value.set(name, 32768, 0, 65535);
       angle.set(name + " angle", 0, min_angle, max_angle);
       
       listeners.push( value.newListener(this, &MovingAxis::valueChanged));
       listeners.push( angle.newListener(this, &MovingAxis::angleChanged));
   }

   uint8_t MovingAxis::get16bitMSB(){
       return (uint8_t)(value.get() >> 8);
   }
   uint8_t MovingAxis::get16bitLSB(){
       return (uint8_t)(value.get() % 256);
   }
   
   
   
   float MovingAxis::getAngle(){
       return ofMap(value.get(), 0, 65535, min_angle, max_angle);
   }
   
void MovingAxis::sendDmx(){
//    cout << "MovingAxis::sendDmx" <<endl;
    if(dmx != nullptr){
//        cout <<" !!! " <<endl;
        dmx->setLevel(coarseChan, get16bitMSB());
        dmx->setLevel(fineChan, get16bitLSB());
//        dmx->update();
    }
}
