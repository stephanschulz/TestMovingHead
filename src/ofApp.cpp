#include "ofApp.h"


#define HEAD 0
#define SOULDERLT 1
#define SOULDERLB 2
#define SOULDERRT 3
#define SOULDERRB 4
#define HIPL 5
#define HIPR 6
#define LEGL 7
#define LEGR 8

//--------------------------------------------------------------
void ofApp::setup(){

    dmx = make_unique<ofxDmx>();
    dmx->connect(0);
    dmx->setChannels(512);
    names = {
        "Head",
        "SoulderLT",
        "SoulderLB",
        "SoulderRT",
        "SoulderRB",
        "HipL",
        "HipR",
        "LegL",
        "LegR"
    };
    
    gui.setup();
    numHeads = 9;
    heads.resize(numHeads);
    for(size_t i = 0; i < numHeads; i++){
        heads[i] = make_unique<MovingHead>();
        int startAddress = 1 + (20 *i);
        heads[i]->setup(dmx.get(), names[i], startAddress);
        cout << "Head : " << names[i] << "  startAddress: " << startAddress << endl;
            
        gui.add(heads[i]->parameters);
        
        
        listeners.push(heads[i]->pan.sendDmxEvent.newListener( this , &ofApp::updateDmx));
        listeners.push(heads[i]->tilt.sendDmxEvent.newListener(  this , &ofApp::updateDmx));
        listeners.push(heads[i]->sendDmxEvent.newListener(  this , &ofApp::updateDmx));
        
//        listeners.push(cyan.newListener(  this , &ofApp::updateConlors));
//        listeners.push(magenta.newListener(  this , &ofApp::updateConlors));
//        listeners.push(yellow.newListener(  this , &ofApp::updateConlors));
    }
    
    gui_all.setup();
    gui_all.setName("all fixtures");
    gui_all.setPosition(250,10);
    gui_all.add(cyan);
    gui_all.add(magenta);
    gui_all.add(yellow);
    
    gui_all.add(colorWheel);
    gui_all.add(rotatingGobo);
    gui_all.add(rotatingGoboIndex);
    gui_all.add(staticGobo);
    gui_all.add(rotatingPrism);
    gui_all.add(rotatingPrismIndex);
    gui_all.add(focus);
    gui_all.add(zoom);
    gui_all.add(shutter);
    gui_all.add(dimmer);
    gui_all.add(frost);
    
    gui_all.add(allMotorReset);
    gui_all.add(moveReset);
    gui_all.add(colorReset);
    gui_all.add(goboReset);
    gui_all.add(dimmerReset);
    gui_all.add(otherMotorReset);
  
  gui_all.add(ikOffsetY);
    
//    listeners.push(cyan.sendDmxEvent.newListener( this , 
//    {for(size_t i = 0; i < numHeads; i++){
//        heads[i].cyan = 255;
//    }}));
//
//    listeners.push(cyan.newListener(  this , &ofApp::updateCyan));
    
    old_cyan = cyan;
    old_magenta = magenta;
    old_yellow = yellow;
    
    old_colorWheel = colorWheel;
    old_rotatingGobo = rotatingGobo;
    old_rotatingGoboIndex = rotatingGoboIndex;
    old_staticGobo = staticGobo;
    old_rotatingPrism = rotatingPrism;
    old_rotatingPrismIndex = rotatingPrismIndex;
    old_focus = focus;
    old_zoom = zoom;
    old_shutter = shutter;
    old_dimmer = dimmer;
    old_frost = frost;

  
  
//  gui_sol.setup();
//  gui_sol.setPosition(ofGetWindowWidth()-200,1);
//  gui_sol.add(heads[curr_head_idx]->solver.inputs);
//  gui_sol.add(heads[curr_head_idx]->solver.freehand);
//  gui_sol.add(heads[curr_head_idx]->solver.params);
  
  
  ptcld.load("ELB_simplified.ply");
  for (int i = 0; i < ptcld.getNumVertices(); i++){
    ofVec3f v = ptcld.getVertex(i);
    
    v *= 10;
    v += ofVec3f(17.674908638000488,21.9171404838562,112.59054183959961);
    
    ptcld.setVertex(i,v);
  }
  
  heads[SOULDERLB]->include = true;
//  heads[SOULDERLB]->solver.fpsx =63.4296;
//  heads[SOULDERLB]->solver.fpsy =37.0729;
//  heads[SOULDERLB]->solver.fpsz =-77.1264;
//  heads[SOULDERLB]->solver.fdrx =-94.7694;
//  heads[SOULDERLB]->solver.fdry =-149.199;
//  heads[SOULDERLB]->solver.fdrz =173.7;
//  heads[SOULDERLB]->solver.fpsx =49.8028;
//  heads[SOULDERLB]->solver.fpsy =35.5786;
//  heads[SOULDERLB]->solver.fpsz =-82.9949;
//  heads[SOULDERLB]->solver.fdrx =262.997;
//  heads[SOULDERLB]->solver.fdry =207.022;
//  heads[SOULDERLB]->solver.fdrz =-184.292;
//  heads[SOULDERLB]->solver.pan0 =-171.829;
//  heads[SOULDERLB]->solver.tlt0 =79.8038 ;
//  heads[SOULDERLB]->solver.pan1 =-163.812;
//  heads[SOULDERLB]->solver.tlt1 =79.8038 ;
//  heads[SOULDERLB]->solver.pan2 =-112.812;
//  heads[SOULDERLB]->solver.tlt2 =67.8038 ;
////  heads[SOULDERLB]->solver.pan3 =-54.8757;
////  heads[SOULDERLB]->solver.tlt3 =-76.4695;
//
//  heads[SOULDERLB]->solver.pan3 =-51.6257;
//  heads[SOULDERLB]->solver.tlt3 =-72.4695;
//  heads[SOULDERLB]->solver.update();
  
//  heads[SOULDERLB]->solver.fpsx =68.40160370;
//  heads[SOULDERLB]->solver.fpsy =41.71481705;
//  heads[SOULDERLB]->solver.fpsz =-74.73695374;
//  heads[SOULDERLB]->solver.fdrx =265.68798828;
//  heads[SOULDERLB]->solver.fdry =211.90959167;
//  heads[SOULDERLB]->solver.fdrz =-184.56391907;
  
  heads[SOULDERLB]->solver.fpsx =69.81494141;
  heads[SOULDERLB]->solver.fpsy =43.15738297;
  heads[SOULDERLB]->solver.fpsz =-73.64495850;
  heads[SOULDERLB]->solver.fdrx =265.73587036;
  heads[SOULDERLB]->solver.fdry =211.93142700;
  heads[SOULDERLB]->solver.fdrz =-188.485153201;
  heads[SOULDERLB]->solver.pan0 =8.22038;
  heads[SOULDERLB]->solver.tlt0 =-76.8041;
  heads[SOULDERLB]->solver.pan1 =16.7937;
  heads[SOULDERLB]->solver.tlt1 =-76.5905;
  heads[SOULDERLB]->solver.pan2 =67.0306;
  heads[SOULDERLB]->solver.tlt2 =-64.2082;
  heads[SOULDERLB]->solver.pan3 =-51.6257;
  heads[SOULDERLB]->solver.tlt3 =-72.4695;
  heads[SOULDERLB]->solver.update();
  
  heads[SOULDERRB]->include = true;
  heads[SOULDERRB]->solver.fpsx =35.8529;
  heads[SOULDERRB]->solver.fpsy =38.4483;
  heads[SOULDERRB]->solver.fpsz =-91.9911;
  heads[SOULDERRB]->solver.fdrx =-97.1149;
  heads[SOULDERRB]->solver.fdry =-153.737;
  heads[SOULDERRB]->solver.fdrz =175.222;
  heads[SOULDERRB]->solver.pan0 =2.50482 ;
  heads[SOULDERRB]->solver.tlt0 =-78.5835;
  heads[SOULDERRB]->solver.pan1 =10.2548 ;
  heads[SOULDERRB]->solver.tlt1 =-78.3335;
  heads[SOULDERRB]->solver.pan2 =60.4376 ;
  heads[SOULDERRB]->solver.tlt2 =-60.8568;
  heads[SOULDERRB]->solver.pan3 =-54.8757;
  heads[SOULDERRB]->solver.tlt3 =-76.4695;
  heads[SOULDERRB]->solver.update();

//
//  heads[SOULDERRT]->include = true;
//  heads[SOULDERRT]->solver.fpsx =35.8529;
//  heads[SOULDERRT]->solver.fpsy =38.4483;
//  heads[SOULDERRT]->solver.fpsz =-91.9911;
//  heads[SOULDERRT]->solver.fdrx =-97.1149;
//  heads[SOULDERRT]->solver.fdry =-153.737;
//  heads[SOULDERRT]->solver.fdrz =175.222;
//  heads[SOULDERRT]->solver.pan0 =-177.95;
//  heads[SOULDERRT]->solver.tlt0 =95.4107;
//  heads[SOULDERRT]->solver.pan1 =-184.95;
//  heads[SOULDERRT]->solver.tlt1 =96.4107;
//  heads[SOULDERRT]->solver.pan2 =-235.45;
//  heads[SOULDERRT]->solver.tlt2 =118.411;
//  heads[SOULDERRT]->solver.pan3 =-118.73;
//  heads[SOULDERRT]->solver.tlt3 =99.6607;
//  heads[SOULDERRT]->solver.update();
  
  
  
  heads[SOULDERRT]->include = true;
  heads[SOULDERRT]->solver.fpsx =63.6045240;
  heads[SOULDERRT]->solver.fpsy =50.70677948;
  heads[SOULDERRT]->solver.fpsz =-76.95076752;
  heads[SOULDERRT]->solver.fdrx =265.2897492;
  heads[SOULDERRT]->solver.fdry =139.87881470;
  heads[SOULDERRT]->solver.fdrz =346.51489258;
  heads[SOULDERRT]->solver.pan0 =2.83069;
  heads[SOULDERRT]->solver.tlt0 =-99.2229;
  heads[SOULDERRT]->solver.pan1 =-5.25355;
  heads[SOULDERRT]->solver.tlt1 =-100.251;
  heads[SOULDERRT]->solver.pan2 =-54.0594;
  heads[SOULDERRT]->solver.tlt2 =-121.738;
  heads[SOULDERRT]->solver.pan3 =61.5018;
  heads[SOULDERRT]->solver.tlt3 =-103.344;
  heads[SOULDERRT]->solver.update();
  
 

  heads[SOULDERLT]->include = true;
  heads[SOULDERLT]->solver.fpsx =63.6045240;
  heads[SOULDERLT]->solver.fpsy =50.70677948;
  heads[SOULDERLT]->solver.fpsz =-76.95076752;
  heads[SOULDERLT]->solver.fdrx =265.2897492;
  heads[SOULDERLT]->solver.fdry =139.87881470;
  heads[SOULDERLT]->solver.fdrz =346.51489258;
  heads[SOULDERLT]->solver.pan0 = -5.77551;
  heads[SOULDERLT]->solver.tlt0 = -97.9666;
  heads[SOULDERLT]->solver.pan1 = 13.7755;
  heads[SOULDERLT]->solver.tlt1 = -98.7166;
  heads[SOULDERLT]->solver.pan2 = -64.8725;
  heads[SOULDERLT]->solver.tlt2 = -113.945;
  heads[SOULDERLT]->solver.pan3 = 53.597;
  heads[SOULDERLT]->solver.tlt3 = -105.867;
  heads[SOULDERLT]->solver.update();
}

//void ofApp::updateConlors(){
//    //how do i know which variable caused the listener to call this function?
//}
void ofApp::checkGui(){
    if(old_cyan != cyan){
        old_cyan = cyan;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->cyan = cyan;
        }
    }
    if(old_magenta != magenta){
        old_magenta = magenta;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->magenta = magenta;
        }
    }
    if(old_yellow != yellow){
        old_yellow = yellow;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->yellow = yellow;
        }
    }
    
    if(old_colorWheel != colorWheel){
        old_colorWheel = colorWheel;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->colorWheel = colorWheel;
          
        }
    }
    
    if(old_rotatingGobo != rotatingGobo){
        old_rotatingGobo = rotatingGobo;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->rotatingGobo = rotatingGobo;
        }
    }
    if(old_rotatingGoboIndex != rotatingGoboIndex){
        old_rotatingGoboIndex = rotatingGoboIndex;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->rotatingGoboIndex = rotatingGoboIndex;
        }
    }
    if(old_staticGobo != staticGobo){
        old_staticGobo = staticGobo;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->staticGobo = staticGobo;
        }
    }
    if(old_rotatingPrism != rotatingPrism){
        old_rotatingPrism = rotatingPrism;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->rotatingPrism = rotatingPrism;
        }
    }
    if(old_rotatingPrismIndex != rotatingPrismIndex){
        old_rotatingPrismIndex = rotatingPrismIndex;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->rotatingPrismIndex = rotatingPrismIndex;
        }
    }
    if(old_focus != focus){
        old_focus = focus;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->focus = focus;
        }
    }
    if(old_zoom != zoom){
        old_zoom = zoom;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->zoom = zoom;
        }
    }
    if(old_shutter != shutter){
        old_shutter = shutter;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->shutter = shutter;
        }
    }
    if(old_dimmer != dimmer){
        old_dimmer = dimmer;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->dimmer = dimmer;
        }
    }
    if(old_frost != frost){
        old_frost = frost;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->frost = frost;
        }
    }
    
    if(allMotorReset){
        allMotorReset = false;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->_dmx->setLevel( FUNCTION_CHAN + heads[i]->_startDmxChannel - 1,FUNCT_allMotorReset);
        }
    }
    if(moveReset){
        moveReset = false;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->_dmx->setLevel( FUNCTION_CHAN + heads[i]->_startDmxChannel - 1,FUNCT_moveReset);
        }
    }
    if(colorReset){
        colorReset = false;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->_dmx->setLevel( FUNCTION_CHAN + heads[i]->_startDmxChannel - 1,FUNCT_colorReset);
        }
    }
    if(goboReset){
        goboReset = false;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->_dmx->setLevel( FUNCTION_CHAN + heads[i]->_startDmxChannel - 1,FUNCT_goboReset);
        }
    }
    if(dimmerReset){
        dimmerReset = false;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->_dmx->setLevel( FUNCTION_CHAN + heads[i]->_startDmxChannel - 1,FUNCT_dimmerReset);
        }
    }
    if(otherMotorReset){
        otherMotorReset = false;
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->_dmx->setLevel( FUNCTION_CHAN + heads[i]->_startDmxChannel - 1,FUNCT_otherMotorReset);
        }
    }
}
//--------------------------------------------------------------
void ofApp::updateDmx(){
    
    
    for(auto&h: heads){
        h->sendDmx();
    }
    checkGui();
    dmx->update();
//    for(int i=1; i<=40; i++){
//        ofLog()<<i<<" : "<<int(dmx->getLevel(i));
//        if(i % 20 == 0) ofLog()<<"----";
//    }
}

//--------------------------------------------------------------
void ofApp::update(){
  
  heads[curr_head_idx]->solver.update();
  
  if (isSolving){
    for (int i = 0; i < heads[curr_head_idx]->solver.sols.size(); i++){
      heads[curr_head_idx]->solver.bruteIteration(heads[curr_head_idx]->solver.sols[i]);
    }
  }
  
    ofSetWindowTitle(ofToString(ofGetFrameRate(),1));
    updateDmx();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
//    ofDrawGrid(10, 10, true);
//
//    for(auto&h: heads){
//        h->draw();
//    }
  ofPushStyle();
  ofPushMatrix();
//  ofTranslate(17.674908638000488,21.9171404838562,112.59054183959961);
//  ofScale(10,10,10);
  ofSetColor(0);
  glPointSize(3);
  ptcld.setMode(OF_PRIMITIVE_POINTS);
  ptcld.draw();
  ofPopMatrix();
  ofPopStyle();
  
  ofPushStyle();
  ofNoFill();
  heads[curr_head_idx]->solver.draw();
  for (int i = 0; i < heads.size(); i++){
    if (!heads[i]->include && i != curr_head_idx){
      continue;
    }
    heads[i]->solver.drawFreehand();
  }
  ofPopStyle();
  
  if (pointMode == 0){
    for (int i = 0; i < heads.size(); i++){
      if (!heads[i]->include && i != curr_head_idx){
        continue;
      }
      heads[i]->solver.mouseIK(cam, &ptcld, ofVec3f(0, ikOffsetY,0 ));
    }
  }else{
//    ofVec2f pt = solver.ik(solver.fpos,solver.fdir,solver.obss[pointMode-1].trg);
//    solver.fpan = pt.x;
//    solver.ftlt = pt.y;
  }
  heads[curr_head_idx]->solver.keypressEmbody();

    cam.end();
  
  heads[curr_head_idx]->solver.drawStats();

    if(bShowGui){
      gui.draw();
        gui_all.draw();
    }
    
  
  heads[curr_head_idx]->gui_sol.setPosition(ofGetWindowWidth()-200,0);
  heads[curr_head_idx]->gui_sol.draw();
  
    stringstream ss;
    
    ss<<"key g to show/hide gui + save gui"<<endl;
//    ss<<"key l to load gui"<<endl;
//    ss<<"key m to load gui_me.xml"<<endl;
    ss<<"key z set all angles to 0"<<endl;
    ss<<"key u to send dmx values again"<<endl;
//    ss<<"key f to load gui_direction.xml"<<endl;
    ss<<"key b to begin solving"<<endl;
  ss << endl;
  ss << names[curr_head_idx] << endl;
  ss << "pan=" << heads[curr_head_idx]->pan.angle << " dmx=" << heads[curr_head_idx]->pan.value << endl;
  ss << "tilt=" << heads[curr_head_idx]->tilt.angle << " dmx=" << heads[curr_head_idx]->tilt.value << endl;
    
    
    ofSetColor(255);
    ofDrawBitmapString(ss.str(), ofGetWidth()/2,20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'u'){
        updateDmx();
    }
    if(key == 'z'){
        for(size_t i = 0; i < numHeads; i++){
            heads[i]->pan.angle = 0;
            heads[i]->tilt.angle = 0;
        }
    }
    
    if(key == 'g'){
        bShowGui = !bShowGui;
        if(bShowGui == false) gui.saveToFile("gui.xml");
    }
//    if(key == 'l'){
//        gui.loadFromFile("gui.xml");
//    }
//    if(key == 'm'){
//        gui.loadFromFile("gui_me.xml");
//    }
//    if(key == 'f'){
//        gui.loadFromFile("gui_direction.xml");
//    }
//
  if (key == 'a'){
      heads[curr_head_idx]->pan.angle-=0.25;
    
  }
  if (key == 'd'){

      heads[curr_head_idx]->pan.angle+=0.25;
    
  }
  
  if (key == 'w'){

      heads[curr_head_idx]->tilt.angle-=0.25;
    
  }
  if (key == 's'){

      heads[curr_head_idx]->tilt.angle+=0.25;
    
  }
  
  if (key == OF_KEY_TAB){
    curr_head_idx = (curr_head_idx+1) % heads.size();
  }
  
  
  if (key == 'b'){
    if (isSolving){
      heads[curr_head_idx]->solver.sols.clear();
      isSolving = false;
    }else{
      heads[curr_head_idx]->solver.begin(62);
      isSolving = true;
    }
  }
  
  if (key == 'p'){
    isSolving ^= 1;
  }
  
  if (key == ' '){
    for (int i = 0; i < heads.size(); i++){
      if (!heads[i]->include && i != curr_head_idx){
        continue;
      }
      heads[i]->pan.angle = heads[i]->solver.fpan;
      heads[i]->tilt.angle = heads[i]->solver.ftlt;
      heads[i]->dimmer = 255;
      heads[i]->focus = 255;
      heads[i]->zoom = 0;
    }
  }
  
  
  if (key == 'x'){
    pointMode = (pointMode + 1) % 5;
    
    for (int i = 0; i < heads.size(); i++){
      if (!heads[i]->include && i != curr_head_idx){
        continue;
      }
      if (pointMode){
        ofVec2f pt = heads[i]->solver.ik(heads[i]->solver.fpos,heads[i]->solver.fdir,heads[i]->solver.obss[pointMode-1].trg);
        heads[i]->solver.fpan = pt.x;
        heads[i]->solver.ftlt = pt.y;
      }
    }
    

  }
  
  if (key == 'y'){
    pointMode = (pointMode + 1) % 5;
    for (int i = 0; i < heads.size(); i++){
      if (!heads[i]->include && i != curr_head_idx){
        continue;
      }
      if (pointMode){
        heads[i]->solver.fpan = heads[i]->solver.obss[pointMode-1].pan;
        heads[i]->solver.ftlt = heads[i]->solver.obss[pointMode-1].tlt;
      }
    }
    
  }
  
  if (key == 'l'){
    heads[curr_head_idx]->solver.writeResults();
  }
  
  if (key == OF_KEY_UP){
    ikOffsetY += 1;
  }
  if (key == OF_KEY_DOWN){
    ikOffsetY -= 1;
  }
  
  if (key == 'j'){
    heads[curr_head_idx]->solver.sortSols();
  }
  if (key == 'k'){
    heads[curr_head_idx]->solver.sols.pop_back();
  }
  if (key == 'n'){
    Solver& solver = heads[curr_head_idx]->solver;
    Solver::Sol sol;
    sol.pos = ofVec3f(0,0,0);
    sol.dir = ofVec3f(0,0,0);
    int n = 0;
    for (n = 0; n < solver.sols.size(); n++){
      sol.pos += solver.sols[n].pos;
      if (!n || ofRandom(1.0) < 0.2){
        sol.dir = solver.sols[n].dir;
      }
      if (ofRandom(1.0) < 0.2){
        break;
      }
    }
    sol.pos /=(float)MAX(1,n);
    cout << sol.pos << " " << sol.dir << " " << n << endl;
    sol.rss = solver.calcRSS(sol.pos, sol.dir);
    sol.prange = fmax(fmax(solver.xmax-solver.xmin,solver.ymax-solver.ymin),solver.zmax-solver.zmin)/2;
    sol.drange = 180;
    solver.updateRanges(sol);
    solver.sols.push_back(sol);
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
 
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

