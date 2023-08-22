//
//  solver.cpp
//  TestMovingHead
//
//  Created by admin on 2022-08-22.
//

#ifndef solver_cpp
#define solver_cpp

#include <stdio.h>
#include "ofMain.h"

#include "ofxGui.h"

#define N_OBS 4

class Solver{public:
  class Obs{public:
    float pan;
    float tlt;
    ofVec3f trg;
  };
  class Sol{public:
    ofVec3f pos;
    ofVec3f dir;
    
    ofVec3f pmin;
    ofVec3f pmax;
    ofVec3f dmin;
    ofVec3f dmax;
    float prange;
    float drange;
    
    float rss;
  };
  
  ofVec3f fpos;
  ofVec3f fdir;

  ofParameter<float> xmin = {"xmin", -100.0, -100.0, 100.0};
  ofParameter<float> xmax = {"xmax",  100.0, -100.0, 100.0};
  ofParameter<float> ymin = {"ymin",   20.0,    0.0, 200.0};
  ofParameter<float> ymax = {"ymax",  200.0,    0.0, 200.0};
  ofParameter<float> zmin = {"zmin", -100.0, -100.0, 100.0};
  ofParameter<float> zmax = {"zmax",  100.0, -100.0, 100.0};
  
//  ofParameter<float> pan0 = {"pan0",-171.829,-270, 270};
//  ofParameter<float> tlt0 = {"tlt0",79.8038 ,-135, 135};
  
  ofParameter<float> pan0 = {"pan0",2.50482 ,-270, 270};
  ofParameter<float> tlt0 = {"tlt0",-78.5835,-135, 135};
  
  ofParameter<float> tgx0 = {"tgx0",-61.8922, -100.0, 100.0};
  ofParameter<float> tgy0 = {"tgy0",31.5432 ,-100.0, 100.0};
  ofParameter<float> tgz0 = {"tgz0",78.0199 ,-100.0, 100.0};
  
//  ofParameter<float> pan1 = {"pan1",-163.812,-270, 270};
//  ofParameter<float> tlt1 = {"tlt1",79.8038 ,-135, 135};
  ofParameter<float> pan1 = {"pan1",10.2548  ,-270, 270};
  ofParameter<float> tlt1 = {"tlt1",-78.3335 ,-135, 135};
  
  ofParameter<float> tgx1 = {"tgx1",-62.9855, -100.0, 100.0};
  ofParameter<float> tgy1 = {"tgy1",33.77083,-100.0, 100.0};
  ofParameter<float> tgz1 = {"tgz1",40.46749,-100.0, 100.0};
  
//  ofParameter<float> pan2 = {"pan2",-112.812,-270, 270};
//  ofParameter<float> tlt2 = {"tlt2",67.8038 ,-135, 135};
  ofParameter<float> pan2 = {"pan2",60.4376,-270, 270};
  ofParameter<float> tlt2 = {"tlt2",-60.8568,-135, 135};
  
  ofParameter<float> tgx2 = {"tgx2",-21.9589,-100.0, 100.0};
  ofParameter<float> tgy2 = {"tgy2",15.9777 ,-100.0, 100.0};
  ofParameter<float> tgz2 = {"tgz2",-86.1859,-100.0, 100.0};
  
//  ofParameter<float> pan3 = {"pan3",127.402 ,-270, 270};
//  ofParameter<float> tlt3 = {"tlt3",75.8038 ,-135, 135};
  
  ofParameter<float> pan3 = {"pan3",-54.8757,-270, 270};
  ofParameter<float> tlt3 = {"tlt3",-76.4695,-135, 135};
  ofParameter<float> tgx3 = {"tgx3",99.1163 ,-100.0, 100.0};
  ofParameter<float> tgy3 = {"tgy3",10.1095 ,-100.0, 100.0};
  ofParameter<float> tgz3 = {"tgz3",30.4699 ,-100.0, 100.0};
  
  
  ofParameter<float> fpan = {"fpan",      0, -270, 270};
  ofParameter<float> ftlt = {"ftlt",      0, -135, 135};
  ofParameter<float> fpsx = {"fpsx",      0,-100.0, 100.0};
  ofParameter<float> fpsy = {"fpsy",    100,   0.0, 200.0};
  ofParameter<float> fpsz = {"fpsz",      0,-100.0, 100.0};
  ofParameter<float> fdrx = {"fdrx",      0,-360, 360};
  ofParameter<float> fdry = {"fdry",      0,-360, 360};
  ofParameter<float> fdrz = {"fdrz",      0,-360, 360};
  
  
  
  ofParameter<float> minpos = {"minpos",      1,   0, 50 };
  ofParameter<float> mindir = {"mindir",      8,   0, 45 };
  ofParameter<float> shrpsa = {"shrpsa",      0,   0, 20 };
  ofParameter<float> shrpsm = {"shrpsm",  0.998,0.95, 1.0};
  ofParameter<float> shrdra = {"shrdra",    0.1,   0, 5  };
  ofParameter<float> shrdrm = {"shrdrm",    1.0,0.95, 1.0};
  ofParameter<float> grwpsa = {"grwpsa",     25,   0, 100};
  ofParameter<float> grwpsm = {"grwpsm",   1.25, 1.0, 4  };
  ofParameter<float> grwpsr = {"grwpsr",  0.002, 0.0,0.02};
  ofParameter<float> grwdra = {"grwdra",     20,   0, 100};
  ofParameter<float> grwdrm = {"grwdrm",    1.2, 1.0, 4  };
  ofParameter<float> grwdrr = {"grwdrr",  0.002, 0.0,0.02};


  
  ofParameterGroup inputs = {"inputs",
    xmin, xmax, ymin, ymax, zmin, zmax, pan0, tlt0, tgx0, tgy0, tgz0, pan1, tlt1, tgx1, tgy1, tgz1, pan2, tlt2, tgx2, tgy2, tgz2, pan3, tlt3, tgx3, tgy3, tgz3
  };
    
  ofParameterGroup freehand = {"freehand",
    fpan, ftlt, fpsx, fpsy, fpsz, fdrx, fdry, fdrz
  };
  
  ofParameterGroup params = {"params",
    minpos,mindir,shrpsa,shrpsm,shrdra,shrdrm,
    grwpsa,grwpsm,grwpsr,grwdra,grwdrm,grwdrr
  };
  
  Obs obss[N_OBS];
  vector<Sol> sols;
  
  bool isConcave;
  
  float det(ofVec3f a, ofVec3f b, ofVec3f c){
    return ofVec3f(a).cross(b).dot(c);
  }
  
  bool rayHitTriangle(ofVec3f o, ofVec3f d, ofVec3f p0, ofVec3f p1, ofVec3f p2, float* u, float* v){
    ofVec3f e1 = p1 - p0;
    ofVec3f e2 = p2 - p0;
    ofVec3f s = o - p0;

    ofVec3f _d = d * (-1.0);
    float denom = det(e1,e2,_d);
    if (denom == 0){
      return false;
    }
    ofVec3f uvt(det(s,e2,_d),det(e1,s,_d),det(e1,e2,s));
    uvt *= (1/denom);
    *u = uvt.x;
    *v = uvt.y;
    float t = uvt.z;
    if (t < 0){
      return false;
    }
    return true;
  }
  
  ofMatrix4x4 mrotx(float a){
    a *= M_PI/180.0;
    return ofMatrix4x4(1,0,0,0, 0,cos(a),-sin(a),0, 0,sin(a),cos(a),0, 0,0,0,1);
  }
  ofMatrix4x4 mroty(float a){
    a *= M_PI/180.0;
    return ofMatrix4x4(cos(a),0,sin(a),0, 0,1,0,0, -sin(a),0,cos(a),0, 0,0,0,1);
  }
  ofMatrix4x4 mrotz(float a){
    a *= M_PI/180.0;
    return ofMatrix4x4(cos(a),-sin(a),0,0, sin(a),cos(a),0,0, 0,0,1,0, 0,0,0,1);
  }
  
  ofVec3f isectYPlane(ofVec3f pos, ofVec3f dir){
    float t = - pos.y / dir.y;
    return pos + dir * t;
  }
  
  ofVec3f getDir(ofVec3f dir, float pan, float tlt){
    return mrotz(dir.z) * mroty(dir.y) * mrotx(dir.x) * mrotz(pan) * mrotx(tlt) * ofVec3f(0,0,1);
  }
  
  ofVec2f ik(ofVec3f pos, ofVec3f dir, ofVec3f q){
    ofVec3f d = q-pos;
    d.normalize();
    ofVec3f dd = mrotx(-dir.x) * mroty(-dir.y) * mrotz(-dir.z) * d;
    float pan = -atan2(dd.x,dd.y)*180/M_PI;
    ofVec3f ddd = mrotz(-pan) * dd;
    float tlt = -atan2(ddd.y,ddd.z)*180/M_PI;
    ofVec3f e = getDir(dir,pan,tlt);
    return ofVec2f(pan,tlt);
  }
  
  ofVec3f rayHitTrigs(ofVec3f pos, ofVec3f d){
    float u,v;
    bool hit0 = rayHitTriangle(pos, d, obss[0].trg, obss[1].trg, obss[2].trg, &u, &v);

    ofVec3f p0 = obss[1].trg * u + obss[2].trg * v + obss[0].trg * (1-u-v);
    
    bool hit1 = rayHitTriangle(pos, d, obss[0].trg, obss[2].trg, obss[3].trg, &u, &v);

    ofVec3f p1 = obss[2].trg * u + obss[3].trg * v + obss[0].trg * (1-u-v);
    
    if (hit0){
      if (hit1){
        if (isConcave){
          if (p0.y > p1.y){
            return p0;
          }else{
            return p1;
          }
        }else{
          if (p0.y < p1.y){
            return p0;
          }else{
            return p1;
          }
        }
      }else{
        return p0;
      }
    }else{
      if (hit1){
        return p1;
      }else{
        return ofVec3f(INFINITY,INFINITY,INFINITY);
      }
    }
  }
  
  ofVec3f shoot(ofVec3f pos, ofVec3f dir, float pan, float tlt){
    
    ofVec3f d = getDir(dir, pan, tlt);
    
//    cout << d << endl;
    
//    return isectYPlane(pos,d);
    return rayHitTrigs(pos,d);
    
  }
  
  void updateRanges(Sol& sol){
    sol.pmin.x = fmax(xmin, sol.pos.x - sol.prange);
    sol.pmin.y = fmax(ymin, sol.pos.y - sol.prange);
    sol.pmin.z = fmax(zmin, sol.pos.z - sol.prange);
    sol.pmax.x = fmin(xmax, sol.pos.x + sol.prange);
    sol.pmax.y = fmin(ymax, sol.pos.y + sol.prange);
    sol.pmax.z = fmin(zmax, sol.pos.z + sol.prange);
    
    sol.dmin.x = fmax(-360, sol.dir.x - sol.drange);
    sol.dmin.y = fmax(-360, sol.dir.y - sol.drange);
    sol.dmin.z = fmax(-360, sol.dir.z - sol.drange);
    sol.dmax.x = fmin( 360, sol.dir.x + sol.drange);
    sol.dmax.y = fmin( 360, sol.dir.y + sol.drange);
    sol.dmax.z = fmin( 360, sol.dir.z + sol.drange);
  
  }
  
  float calcRSS(ofVec3f p, ofVec3f d){
    float s = 0;
    for (int j = 0; j < N_OBS; j++){
      Obs o = obss[j];
      ofVec3f q = shoot(p, d, o.pan, o.tlt);
      float dx =(q.x - o.trg.x);
      float dy =(q.y - o.trg.y);
      float dz =(q.z - o.trg.z);
      s += dx*dx+dy*dy+dz*dz;
    }
    return s;
  }
  
  void bruteIteration(Sol& sol){
    for (int i = 0; i < 6000; i++){
      float s = 0;
      ofVec3f p, d;
      p.x = ofRandom(sol.pmin.x, sol.pmax.x);
      p.y = ofRandom(sol.pmin.y, sol.pmax.y);
      p.z = ofRandom(sol.pmin.z, sol.pmax.z);
      d.x = ofRandom(sol.dmin.x, sol.dmax.x);
      d.y = ofRandom(sol.dmin.x, sol.dmax.x);
      d.z = ofRandom(sol.dmin.z, sol.dmax.z);
      
//      d.normalize();

      s = calcRSS(p,d);
      if (s < sol.rss){
        sol.pos = p;
        sol.dir = d;
        sol.rss = s;
      }
    }
    
    if (sol.prange > minpos){
      sol.prange *= shrpsm;
      sol.prange -= shrpsa;
    }
    if (sol.drange > mindir){
      sol.drange *= shrdrm;
      sol.drange -= shrdra;
    }
    if (ofRandom(1.0) < grwpsr){
      sol.prange*=grwpsm;
      sol.prange+=grwpsa;
    }
    if (ofRandom(1.0) < grwdrr){
      sol.drange*=grwdrm;
      sol.drange+=grwdra;
      if (sol.drange > 180){
        sol.drange = 180;
      }
    }
    updateRanges(sol);
  }
  
  void update(){
    obss[0].pan   = pan0;
    obss[0].tlt   = tlt0;
    obss[0].trg.x = tgx0;
    obss[0].trg.y = tgy0;
    obss[0].trg.z = tgz0;
    
    obss[1].pan   = pan1;
    obss[1].tlt   = tlt1;
    obss[1].trg.x = tgx1;
    obss[1].trg.y = tgy1;
    obss[1].trg.z = tgz1;
    
    obss[2].pan   = pan2;
    obss[2].tlt   = tlt2;
    obss[2].trg.x = tgx2;
    obss[2].trg.y = tgy2;
    obss[2].trg.z = tgz2;
    
    obss[3].pan   = pan3;
    obss[3].tlt   = tlt3;
    obss[3].trg.x = tgx3;
    obss[3].trg.y = tgy3;
    obss[3].trg.z = tgz3;

    fdir.x = fdrx;
    fdir.y = fdry;
    fdir.z = fdrz;
    
    fpos.x = fpsx;
    fpos.y = fpsy;
    fpos.z = fpsz;
    
    //
    //    1  .--2
    //      /
    //  0--'     3
    ofVec3f e0 = obss[0].trg - obss[2].trg;
    ofVec3f e1 = obss[3].trg - obss[2].trg;
    ofVec3f nm = ofVec3f(e0).cross(e1);
    float u,v;
    isConcave = true;
    if (rayHitTriangle(obss[3].trg, nm, obss[0].trg, obss[1].trg, obss[2].trg, &u,&v) ){
      isConcave ^= 1;
    }
    
  }
  
  void begin(int n){
    update();
    sols.clear();
    for (int i = 0; i < n; i++){
      Sol sol;
      sol.pos.x = (xmin+xmax)/2;
      sol.pos.y = (ymin+ymax)/2;
      sol.pos.z = (zmin+zmax)/2;
      sol.dir.x = ofRandom(-360,360);
      sol.dir.y = ofRandom(-360,360);
      sol.dir.z = ofRandom(-360,360);
      sol.rss = INFINITY;
      sol.prange = fmax(fmax(xmax-xmin,ymax-ymin),zmax-zmin)/2;
      sol.drange = 180;
      updateRanges(sol);
      sols.push_back(sol);
      
      if (i < 1){
        sols[i].pos.x = fpos.x;
        sols[i].pos.y = fpos.y;
        sols[i].pos.z = fpos.z;
        sols[i].dir.x = fdir.x;
        sols[i].dir.y = fdir.y;
        sols[i].dir.z = fdir.z;
        sols[i].rss = calcRSS(fpos,fdir);
      }
    }
//    sols[0].pos.x = 63.4296;
//    sols[0].pos.y = 37.0729;
//    sols[0].pos.z = -77.1264;
//    sols[0].dir.x = -94.7694;
//    sols[0].dir.y = -149.199;
//    sols[0].dir.z = 173.7;
//    sols[0].rss = 9.55914;
  }
  
  void drawTarg(ofVec3f p){
    ofDrawBox(p.x,p.y,p.z,5,5,5);
    ofPushMatrix();
    ofTranslate(p.x,p.y,p.z);
    ofRotateXDeg(90);
    ofDrawCircle(0,0,10);
    ofPopMatrix();
  }
  
  void drawGround(){
    ofPushStyle();
    
    ofSetColor(255, 100);
    for (int i = (int)zmin; i <= (int)zmax; i+=10){
      ofDrawLine(xmin,0,i,xmax,0,i);
    }
    for (int i = xmin; i <= xmax; i+=10){
      ofDrawLine(i,0,zmin,i,0,zmax);
    }
    ofSetLineWidth(3);
    ofSetColor(255,0,0);
    ofDrawLine(0,0,0, 20,0,0);
    ofSetColor(0,255,0);
    ofDrawLine(0,0,0, 0,20,0);
    ofSetColor(0,0,255);
    ofDrawLine(0,0,0, 0,0,20);
    
    ofPopStyle();
  }
  
  float ptDistToLine(ofVec3f x0, ofVec3f x1, ofVec3f x2){
    return (x0-x1).cross(x0-x2).length() / (x2-x1).length();
  }
  
  ofVec3f rayHitPtcld(ofVec3f pos, ofVec3f d, ofMesh* ptcld){
    float md = INFINITY;
    ofVec3f mv;
    for (int i = 0; i < ptcld->getNumVertices(); i++){
      ofVec3f v = ptcld->getVertex(i);
      float dst = ptDistToLine(v, pos, pos+d);
      if (dst < md){
        md = dst;
        mv = v;
      }
//      if (md < 1){
//        break;
//      }
    }
    return mv;
  }
  
  
  void mouseIK(ofCamera& cam, void* mode, ofVec3f offset){
    ofPushStyle();
    ofVec3f p = cam.screenToWorld(ofVec3f(ofGetMouseX(),ofGetMouseY()));
    ofVec3f r = p-cam.getPosition();
    
    
    ofVec3f q;
    if (mode == NULL){
      q= isectYPlane(p, r);
    }else if (mode == &obss){
      q = rayHitTrigs(p,r);
    }else{
      q = rayHitPtcld(p, r, (ofMesh*)mode);
    }
    q += offset;
    ofVec2f pt = ik(fpos,fdir,q);
    fpan = pt.x;
    ftlt = pt.y;
    ofNoFill();
    drawTarg(q);
    ofPopStyle();
  }
  
  void keypressEmbody(){
    for (int i = 0; i < sols.size(); i++){
      if(ofGetKeyPressed(ofToChar(ofToString(i)))) {
        fdrx = sols[i].dir.x;
        fdry = sols[i].dir.y;
        fdrz = sols[i].dir.z;
        fpsx = sols[i].pos.x;
        fpsy = sols[i].pos.y;
        fpsz = sols[i].pos.z;
        update();
      }
    }
  }
  
  ofColor getColor(int i){
    if (sols.size() < 7){
      return ofColor( (((i+1)>>2)&1)*255, (((i+1)>>1)&1)*255, (((i+1)>>0)&1)*255);
    }else if (sols.size() < 13){
      if (i < 6){
        return ofColor( (((i+1)>>2)&1)*255, (((i+1)>>1)&1)*255, (((i+1)>>0)&1)*255);
      }else{
        return ofColor( (((i-5)>>2)&1)*127+127, (((i-5)>>1)&1)*127+127, (((i-5)>>0)&1)*127+127);
      }
    }else{
      i = 61-i;
      return ofColor( (((i+1)>>4)&3)*85, (((i+1)>>2)&3)*85, (((i+1)>>0)&3)*85);
    }
  }
  
  void drawFreehand(){
    ofPushMatrix();
    ofTranslate(fpos.x,fpos.y,fpos.z);
    
    ofRotateZDeg(fdir.z);
    ofRotateYDeg(fdir.y);
    ofRotateXDeg(fdir.x);
    
    ofRotateZDeg(fpan);
    ofDrawBox(0,0,0,20,20,2);
    ofRotateXDeg(ftlt);
    ofDrawBox(0,0,0,10,10,20);
    ofDrawBox(0,0,10,2,2,2);
    
    ofPopMatrix();
    
    ofVec3f d = getDir(fdir,fpan,ftlt);
    ofDrawLine(fpos,fpos+d*200);
  }
  
  void writeResults(){
    ofBuffer buf;
    stringstream ss;
    for (int i = 0; i < sols.size(); i++){
      ss << ofToString(sols[i].pos) + "\t" + ofToString(sols[i].dir) << endl;
    }
    buf.set(ss);
    ofBufferToFile("results_"+ofGetTimestampString()+".txt",buf);
  }
  
  static bool compareSol(Sol s0, Sol s1){
    return s0.rss < s1.rss;
  }
  
  void sortSols(){
    sort(sols.begin(),sols.end(),compareSol);
  }
  
  
  void draw(){
    ofPushStyle();
    ofSetColor(255);
    
    ofNoFill();
    drawGround();
    ofSetColor(255);
    ofDrawBox((xmin+xmax)/2,(ymin+ymax)/2,(zmin+zmax)/2,
              (xmax-xmin),  (ymax-ymin),  (zmax-zmin));
    
    ofDrawLine(obss[0].trg,obss[1].trg);
    ofDrawLine(obss[1].trg,obss[2].trg);
    ofDrawLine(obss[2].trg,obss[3].trg);
    ofDrawLine(obss[3].trg,obss[0].trg);
    
    ofDrawLine(obss[0].trg,obss[2].trg);
    
    
    drawFreehand();
    
    ofVec3f p = shoot(fpos,fdir,fpan,ftlt);
//    cout << p << endl;
//    drawTarg(p);
    
    for (int i = 0; i < sols.size(); i++){
      Sol sol = sols[i];
      
      ofColor rgb = getColor(i);
      
      ofPushStyle();
      ofSetColor(rgb);
      ofNoFill();
      ofDrawBox((sol.pmin.x+sol.pmax.x)/2,(sol.pmin.y+sol.pmax.y)/2,(sol.pmin.z+sol.pmax.z)/2,
                (sol.pmax.x-sol.pmin.x),(sol.pmax.y-sol.pmin.y),(sol.pmax.z-sol.pmin.z));
      ofDrawBox(sol.pos.x,sol.pos.y,sol.pos.z,5,5,5);
      ofSetLineWidth(3);
      ofVec3f d = getDir(sol.dir,0,0);
      ofDrawLine(sol.pos,sol.pos+d*50);
      
      ofPushMatrix();
      ofTranslate(sol.pos.x,sol.pos.y,sol.pos.z);
      ofRotateZDeg(sol.dir.z);
      ofRotateYDeg(sol.dir.y);
      ofRotateXDeg(sol.dir.x);
      ofSetLineWidth(1);
//      float rat = tan(fmin(sol.drange,89.99)*M_PI/180);
      float rat = fabs(tan(sol.drange*M_PI/180));
      float r,h;
      if (fabs(rat) > 1){
        r = 20;
        h = r/rat;
      }else{
        h = 20;
        r = h*rat;
      }
      if (sol.drange > 90){
        h *= -1;
      }
      ofRotateXDeg(90);
      ofSetConeResolution(7, 1, 1);
      ofDrawCone(0,h/2,0,r,h);
      ofPopMatrix();
      
      ofPopStyle();
      
      ofPushStyle();
      ofNoFill();
      for (int j = 0; j < N_OBS; j++){
        Obs o = obss[j];
        ofVec3f q = shoot(sol.pos,sol.dir,o.pan,o.tlt);
        ofVec3f p = obss[j].trg;
        ofSetColor(rgb);
        drawTarg(q);
        ofSetColor(255);
        drawTarg(p);
      }
      ofPopStyle();
    }
    ofPopStyle();
  }
  
  void drawStats(){
    for (int i = 0; i < sols.size(); i++){
      Sol sol = sols[i];
      ofColor rgb = getColor(i);
      ofDrawBitmapStringHighlight("RSS="+ofToString(sol.rss,8)+
                                  ", POS=["+ofToString(sol.pos,8)+
                                  "], DIR=["+ofToString(sol.dir,8)+
                                  "]"/*+", DRANGE="+ofToString(sol.drange)*/,
                                  5,ofGetWindowHeight()-sols.size()*16+i*16,ofColor::black,rgb);
    }
  }
  
};


#endif
