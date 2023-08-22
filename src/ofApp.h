#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#define FUNCT_allMotorReset 80
#define FUNCT_moveReset 85
#define FUNCT_colorReset 88
#define FUNCT_goboReset 91
#define FUNCT_dimmerReset 94
#define FUNCT_otherMotorReset 97
#define FUNCTION_CHAN 20

#include "ofxDmx.h"
#include "MovingHead.hpp"

#include "solver.cpp"

//
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    unique_ptr<ofxDmx> dmx = nullptr;
    size_t numHeads;
    
    ofxPanel gui;
    bool bShowGui = true;
    
    vector<unique_ptr<MovingHead>> heads;
    
    ofEventListeners listeners;
    
    ofEasyCam cam;
    
    void updateDmx();
    
    void checkGui();
    
    ofxPanel gui_all;
    ofParameter<int> cyan = {"cyan", 0, 0, 255}; //5
    int old_cyan;
    ofParameter<int> magenta = {"magenta", 0, 0, 255}; //6
    int old_magenta;
    ofParameter<int> yellow = {"yellow", 0, 0, 255}; //7
    int old_yellow;
    ofParameter<int> colorWheel = {"colorWheel", 0, 0, 255}; //8
    int old_colorWheel;
    ofParameter<int> rotatingGobo = {"rotGobo", 0, 0, 21}; //9
    int old_rotatingGobo;
    ofParameter<int> rotatingGoboIndex = {"rotGoboIndex", 190, 190, 190}; //10
    int old_rotatingGoboIndex;
    ofParameter<int> staticGobo = {"staticGobo", 0, 0, 255}; //11
    int old_staticGobo;
    ofParameter<int> rotatingPrism = {"rotPrism", 0, 0, 255}; //12
    int old_rotatingPrism;
    ofParameter<int> rotatingPrismIndex = {"rotPrismIndex", 190, 190, 190}; //13
    int old_rotatingPrismIndex;
    ofParameter<int> focus = {"focus", 0, 0, 255}; //14
    int old_focus;
    ofParameter<int> zoom = {"zoom", 0, 0, 255}; //15
    int old_zoom;
    ofParameter<int> shutter = {"shutter", 0, 0, 255}; //16
    int old_shutter;
    ofParameter<int> dimmer = {"dimmer", 0, 0, 255}; //17
    int old_dimmer;
//    ofParameter<int> dimmerFine = {"dimmerFine", 0, 0, 255}; //18
    ofParameter<int> frost = {"frost", 0, 0, 255}; //19
    int old_frost;
    ofParameter<bool> allMotorReset = {"allMotorReset", false}; //20 - 80
    ofParameter<bool> moveReset = {"moveReset", false}; //20 - 85
    ofParameter<bool> colorReset = {"colorReset", false}; //20 - 88
    ofParameter<bool> goboReset = {"goboReset", false}; //20 - 91
    ofParameter<bool> dimmerReset = {"dimmerReset", false}; //20 - 94
    ofParameter<bool> otherMotorReset = {"otherMotorReset", false}; //20 - 97
    
    float functionTimer;
  vector<string> names;
  int curr_head_idx = 0;
  
//  ofxPanel gui_sol;
//  Solver solver;
  bool isSolving = false;
  
  int pointMode = 0;
  
  ofParameter<float> ikOffsetY = {"ikOffsetY", 0, 0.0, 1000.0};
  
  ofMesh ptcld;
};
