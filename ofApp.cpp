#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	auto rotate_y = ofGetFrameNum() * 2;
	for (int x = -600; x <= 600; x += 600) {

		for (int y = -600; y <= 600; y += 600) {

			for (int z = -600; z <= 600; z += 600) {

				auto noise_seed = ofRandom(1000);
				auto rotation_y = glm::rotate(glm::mat4(), rotate_y * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				for (float scale = 4; scale <= 12; scale += 4) {

					auto start_index = this->face.getNumVertices();
					auto scale_param = ofMap(ofNoise(noise_seed, scale * 0.05 + ofGetFrameNum() * 0.05), 0, 1, -1.5, 1.5);
					for (int deg = 0; deg < 360; deg += 10) {

						auto tmp_scale = scale + scale_param;

						vector<glm::vec3> vertices;
						vertices.push_back(glm::vec3(x, y, z) + glm::vec4(this->make_point(deg * DEG_TO_RAD) * scale, -15, 0) * rotation_y);
						vertices.push_back(glm::vec3(x, y, z) + glm::vec4(this->make_point(deg * DEG_TO_RAD) * (scale + 2.5), -15, 0) * rotation_y);
						vertices.push_back(glm::vec3(x, y, z) + glm::vec4(this->make_point((deg + 10) * DEG_TO_RAD) * (scale + 2.5), -15, 0) * rotation_y);
						vertices.push_back(glm::vec3(x, y, z) + glm::vec4(this->make_point((deg + 10) * DEG_TO_RAD) * scale, -15, 0) * rotation_y);

						vertices.push_back(glm::vec3(x, y, z) + glm::vec4(this->make_point(deg * DEG_TO_RAD) * scale, 15, 0) * rotation_y);
						vertices.push_back(glm::vec3(x, y, z) + glm::vec4(this->make_point(deg * DEG_TO_RAD) * (scale + 2.5), 15, 0) * rotation_y);
						vertices.push_back(glm::vec3(x, y, z) + glm::vec4(this->make_point((deg + 10) * DEG_TO_RAD) * (scale + 2.5), 15, 0) * rotation_y);
						vertices.push_back(glm::vec3(x, y, z) + glm::vec4(this->make_point((deg + 10) * DEG_TO_RAD) * scale, 15, 0) * rotation_y);

						for (int i = 0; i < vertices.size(); i++) {

							auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(vertices[i].y * 0.0002 + ofGetFrameNum() * 0.008), 0, 1, PI * -2.5, PI * 2.5), glm::vec3(0, 1, 0));
							auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(vertices[i].x * 0.0002 + ofGetFrameNum() * 0.008), 0, 1, PI * -2.5, PI * 2.5), glm::vec3(1, 0, 0));

							vertices[i] = glm::vec4(vertices[i], 0) * rotation_y * rotation_x;
						}

						auto index = this->face.getNumVertices();
						this->face.addVertices(vertices);
						this->frame.addVertices(vertices);

						this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
						this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);
						this->face.addIndex(index + 4); this->face.addIndex(index + 5); this->face.addIndex(index + 6);
						this->face.addIndex(index + 4); this->face.addIndex(index + 6); this->face.addIndex(index + 7);
						this->face.addIndex(index + 0); this->face.addIndex(index + 4); this->face.addIndex(index + 1);
						this->face.addIndex(index + 4); this->face.addIndex(index + 5); this->face.addIndex(index + 1);
						this->face.addIndex(index + 1); this->face.addIndex(index + 5); this->face.addIndex(index + 6);
						this->face.addIndex(index + 6); this->face.addIndex(index + 2); this->face.addIndex(index + 1);
						this->face.addIndex(index + 2); this->face.addIndex(index + 6); this->face.addIndex(index + 7);
						this->face.addIndex(index + 7); this->face.addIndex(index + 3); this->face.addIndex(index + 2);
						this->face.addIndex(index + 3); this->face.addIndex(index + 7); this->face.addIndex(index + 4);
						this->face.addIndex(index + 4); this->face.addIndex(index + 0); this->face.addIndex(index + 3);

						this->frame.addIndex(index + 0); this->frame.addIndex(index + 3);
						this->frame.addIndex(index + 1); this->frame.addIndex(index + 2);
						this->frame.addIndex(index + 4); this->frame.addIndex(index + 7);
						this->frame.addIndex(index + 5); this->frame.addIndex(index + 6);
					}
				}

				rotate_y += 40;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	ofSetColor(235, 110, 160);
	this->face.draw();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
// Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec2 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec2(x, -y);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}