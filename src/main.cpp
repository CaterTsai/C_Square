#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

	ofGLFWWindowSettings settings_;

	//Projection Window
	settings_.width = cProjectionWindowWidth;
	settings_.height = cProjectionWindowHeight;
	settings_.resizable = false;
	shared_ptr<ofAppBaseWindow> _projectionWindow = ofCreateWindow(settings_);
	
	//View Window
	settings_.width = cViewWindowWidth;
	settings_.height = cViewWindowHeight;
	settings_.shareContextWith = _projectionWindow;
	shared_ptr<ofAppBaseWindow> _viewWindow = ofCreateWindow(settings_);
	
	_viewWindow->setVerticalSync(false);

	shared_ptr<ofApp> app_(new ofApp);
	ofAddListener(_viewWindow->events().draw, app_.get(), &ofApp::drawView);

	ofRunApp(_projectionWindow, app_);
	ofRunMainLoop();

}
