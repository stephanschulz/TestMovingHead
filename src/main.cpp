#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3,2);
    settings.setSize(1050,1050);
    auto window = ofCreateWindow(settings);
    
    
    ofRunApp(new ofApp());

}
