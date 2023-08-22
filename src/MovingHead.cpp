//
//  MovingHead.cpp
//  LidarOnMovingHead
//
//  Created by Roy Macdonald on 6/5/22.
//

#include "MovingHead.hpp"






#define LAMP_ON 40
#define LAMP_OFF 50

#define FUNCT_allMotorReset 80
#define FUNCT_moveReset 85
#define FUNCT_colorReset 88
#define FUNCT_goboReset 91
#define FUNCT_dimmerReset 94
#define FUNCT_otherMotorReset 97
#define FUNCTION_CHAN 20

#define CYAN 5
#define MAGENTA 6
#define YELLOW 7
#define COLORWHEEL 8
#define ROTATING_GOBO 9
#define ROTATINGINDEX_GOBO 10
#define STATIC_GOBO 11
#define ROTATING_PRISM 12
#define ROTATINGINDEX_PRISM 13
#define FOCUS_CHAN 14
#define ZOOM 15
#define SHUTTER 16
#define DIMMER_CHAN 17
#define DIMMER_FINE_CHAN 18
#define FROST 19
//#define FUNCTION_CHAN 20


void MovingHead::setup(ofxDmx* dmx, string name, size_t startDmxChannel){
    _dmx = dmx;
    _startDmxChannel = startDmxChannel;
    parameters.setName(name);
    
    pan.setup(dmx,"pan", startDmxChannel, startDmxChannel +1, -270, 270);
    tilt.setup(dmx,"tilt", startDmxChannel + 2, startDmxChannel + 3, -125, 125);

    params.add(lamp);
    params.add(dimmer);
    params.add(focus);
    params.add(zoom);
    
    parameters.add(pan.value);
    parameters.add(pan.angle);
    parameters.add(tilt.value);
    parameters.add(tilt.angle);
    parameters.add(params);

    node.setParent(*this);
    offsetNode.setParent(node);
    offsetNode.setPosition( 0, 0,-100);
    listeners.push(pan.angle.newListener(this, &MovingHead::updateNode));
    listeners.push(tilt.angle.newListener(this, &MovingHead::updateNode));
    
    listeners.push(lamp.newListener([&](bool&){ofNotifyEvent(sendDmxEvent, this);}));
    listeners.push(dimmer.newListener([&](int&){ofNotifyEvent(sendDmxEvent, this);}));
    listeners.push(focus.newListener([&](int&){ofNotifyEvent(sendDmxEvent, this);}));

    gui_sol.setup();
    gui_sol.setPosition(ofGetWindowWidth()-200,1);
    gui_sol.add(misc);
    gui_sol.add(solver.inputs);
    gui_sol.add(solver.freehand);
    gui_sol.add(solver.params);
}

void MovingHead::sendDmx(){
    _dmx->setLevel( FOCUS_CHAN + _startDmxChannel - 1, focus.get());
    _dmx->setLevel( DIMMER_CHAN + _startDmxChannel - 1, dimmer.get());
    _dmx->setLevel( DIMMER_FINE_CHAN+ _startDmxChannel - 1, 255);
      
    _dmx->setLevel( CYAN + _startDmxChannel - 1, cyan);
    _dmx->setLevel( MAGENTA + _startDmxChannel - 1, magenta);
    _dmx->setLevel( YELLOW + _startDmxChannel - 1, yellow);
    
    _dmx->setLevel( COLORWHEEL + _startDmxChannel - 1, colorWheel); // 0-10 open / white
    _dmx->setLevel( ROTATING_GOBO + _startDmxChannel - 1, rotatingGobo); //0);
    _dmx->setLevel( ROTATINGINDEX_GOBO + _startDmxChannel - 1, rotatingGoboIndex); // 190);
    _dmx->setLevel( STATIC_GOBO + _startDmxChannel - 1, staticGobo); //0);
    _dmx->setLevel( ROTATING_PRISM + _startDmxChannel - 1, rotatingPrism); //0);
    _dmx->setLevel( ROTATINGINDEX_PRISM + _startDmxChannel - 1, rotatingPrismIndex); //0);
    _dmx->setLevel( FROST + _startDmxChannel - 1, frost);
    _dmx->setLevel( ZOOM + _startDmxChannel - 1, zoom.get());
    _dmx->setLevel( SHUTTER + _startDmxChannel - 1, shutter); //0-31 shutter closed, 32 - 63 shutter open
    
    _dmx->setLevel( FUNCTION_CHAN + _startDmxChannel - 1, (lamp.get()?LAMP_ON:LAMP_OFF)); //40-49 lamp on, 50-50 lamp off

    
    tilt.sendDmx();
    pan.sendDmx();
    
 
    // _dmx->update();
}

void MovingHead::updateNode(float&){
    node.setOrientation({tilt.getAngle() +90 ,pan.getAngle(),  0});
}


void MovingHead::draw(){
    node.draw();

    ofDrawArrow({0,0,0}, node.getLookAtDir() * 50, 2);

    offsetNode.draw();
}
