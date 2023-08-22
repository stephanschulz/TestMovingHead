//
//  MovingHead.hpp
//  LidarOnMovingHead
//
//  Created by Roy Macdonald on 6/5/22.
//

#pragma once
#include "MovingAxis.h"
#include "solver.cpp"

class MovingHead: public ofNode{
public:
    
    enum Model{
        SMARTY_HYBRID,
        POINTE
    } model = SMARTY_HYBRID;
    
    void setup(ofxDmx* _dmx, string name, size_t startDmxChannel = 1);
    
    void draw();
    
    MovingAxis pan;
    MovingAxis tilt;
        
    
    ofNode node, offsetNode;
    
    ofParameterGroup parameters;
    
    void sendDmx();
    
    ofParameter<bool> lamp = {"lamp", true};
    ofParameter<int>  dimmer = {"dimmer", 0, 50, 255};
    ofParameter<int>  focus = {"focus", 0, 0, 255};
    ofParameter<int>  zoom = {"zoom", 255, 0, 255};
    ofParameterGroup  params = {"params"};
    
    ofEvent<void> sendDmxEvent;
    
    int cyan = 0;
    int magenta = 0;
    int yellow = 0;
    
    int colorWheel = 0;
    int rotatingGobo = 0;
    int rotatingGoboIndex = 190;
    int staticGobo = 0;
    int rotatingPrism = 0;
    int rotatingPrismIndex = 190;
    int frost = 0;
    int shutter = 255;
    
    int allMotorReset = 80;
    int moveReset = 85;
    int colorReset = 88;
    int goboReset = 91;
    int dimmerReset = 94;
    int otherMotorReset = 97;
    
    ofxDmx* _dmx = nullptr;
    size_t _startDmxChannel;
    
  Solver solver;
  ofxPanel gui_sol;
  ofParameter<bool> include = {"include",false};
  ofParameterGroup misc = {"misc",include};
  
private:
   
    ofEventListeners listeners;

    void updateNode(float&);
    
};
