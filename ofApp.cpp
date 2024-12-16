#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 220, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	ofFbo fbo;
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofClear(0);
	ofSetColor(0);

	font.drawString("8888", font.stringWidth("8888") * -0.5, font.stringHeight("8888") * -0.25);
	font.drawString("8888", font.stringWidth("8888") * -0.5, font.stringHeight("8888") * 1.25);

	fbo.end();

	ofPixels pixels;
	fbo.readToPixels(pixels);

	float span = 1;
	for (float x = 0; x < fbo.getWidth(); x += span) {

		for (float y = 0; y < fbo.getHeight(); y += span) {

			auto len = glm::distance(glm::vec2(x, y), ofGetWindowSize() * 0.5);
			auto noise_value = ofMap(ofNoise(x * 0.0025, y * 0.0025, len * 0.005 - ofGetFrameNum() * 0.025), 0, 1, 0, 10);
			if ((int)noise_value % 2 == 0) {

				continue;
			}

			ofColor color = pixels.getColor((int)x, (int)y);
			if (color == ofColor(0, 0)) {

				continue;
			}

			this->mesh.addVertex(glm::vec3(x, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
			this->mesh.addVertex(glm::vec3(x, y + span, 0));

			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);

			color.setHsb((int)ofMap((int)noise_value, 0, 10, 128, 255 + 128) % 255, 180, 255);

			for (int i = 0; i < 4; i++) {

				this->mesh.addColor(color);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();

	/*
	int start = 25;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}