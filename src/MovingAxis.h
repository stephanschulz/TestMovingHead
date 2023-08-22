//
//  MovingAxis.hpp
//  LidarOnMovingHead
//
//  Created by Roy Macdonald on 6/4/22.
//

#pragma once

#include "ofMain.h"

#include "ofxDmx.h"

class MovingAxis{
public:
    MovingAxis(){}
    
    
    void setup(ofxDmx* _dmx, string name, uint8_t _coarseChan, uint8_t _fineChan, float _min_angle, float _max_angle);

    uint8_t get16bitMSB();
    uint8_t get16bitLSB();
    
    
    ofParameter<uint16_t> value;
    ofParameter<float> angle;
    
    float getAngle();
    
    void valueChanged(uint16_t&);
    void angleChanged(float&);
    
    void sendDmx();
    
    ofEvent<void> sendDmxEvent;
    
    
protected:
    
    
    float min_angle;
    float max_angle;
    
    ofxDmx* dmx = nullptr;
    uint8_t coarseChan, fineChan;
    ofEventListeners listeners;
    
private:
    
    
    bool bIsSettingValueAngle = false;
    
};


