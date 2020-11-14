#include <starfall_app.h>

using ideal_gas::StarfallApp;

void prepareSettings(StarfallApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(StarfallApp, ci::app::RendererGl, prepareSettings);