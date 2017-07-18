#include "ofMain.h"
#include "ofAppGLFWWindow.h"
#include "ofProjectorApp.h"
#include "ofViewApp.h"


//========================================================================
int main() {
	
#ifdef PROJECTION_MODE
	ofGLFWWindowSettings settings_;
	//Projection Window
	settings_.width = cProjectionWindowWidth;
	settings_.height = cProjectionWindowHeight;
	settings_.setPosition(ofVec2f(1920, 0));
	settings_.resizable = false;
	shared_ptr<ofAppBaseWindow> _projectionWindow = ofCreateWindow(settings_);

	//View Window
	settings_.width = cViewWindowWidth;
	settings_.height = cViewWindowHeight;
	settings_.setPosition(ofVec2f(0, 0));
	settings_.shareContextWith = _projectionWindow;
	shared_ptr<ofAppBaseWindow> _viewWindow = ofCreateWindow(settings_);

	shared_ptr<ofProjectorApp> projectorApp_(new ofProjectorApp);
	shared_ptr<ofViewApp> viewApp_(new ofViewApp);

	ofRunApp(_viewWindow, viewApp_);
	ofRunApp(_projectionWindow, projectorApp_);

	ofRunMainLoop();
#else //PROJECTION_MODE
	//ofGLFWWindowSettings settings;
	//settings.width = cViewWindowWidth;
	//settings.height = cViewWindowHeight;
	//settings.windowMode = OF_WINDOW;
	//settings.setGLVersion(4,3);

	//shared_ptr<ofAppBaseWindow> viewWindow = ofCreateWindow(settings);
	//shared_ptr<ofViewApp> viewApp(new ofViewApp);
	//ofRunApp(viewWindow, viewApp);
	//ofRunMainLoop();

	ofSetupOpenGL(cViewWindowWidth, cViewWindowHeight, OF_WINDOW);
	ofRunApp(new ofViewApp());

#endif //PROJECTION_MODE




}
