#pragma once

#include <iostream>

class Model;

void print_bones(const Model& model){
	for (auto i = 0; i < model.bones.size(); ++i){
	std::cout << model.bones[i].name << std::endl;
	std::cout << "N positions: " << model.bones[i].positions.size()
		<< " - N rotations: " << model.bones[i].rotations.size()
		<< " - N scales: " << model.bones[i].scales.size() << std::endl;
	std::cout << "\nPOSITIONS: " << std::endl;
	for (auto j = 0; j < model.bones[i].positions.size(); ++j)
		std::cout << model.bones[i].positions[j].timestamp
			<< " - " << model.bones[i].positions[j].position.x << ' '
			<< model.bones[i].positions[j].position.y << ' '
			<< model.bones[i].positions[j].position.z << std::endl;
	std::cout << "\nSCALES: " << std::endl;
	for (auto j = 0; j < model.bones[i].scales.size(); ++j)
		std::cout << model.bones[i].scales[j].timestamp
			<< " - " << model.bones[i].scales[j].scale.x << ' '
			<< model.bones[i].scales[j].scale.y << ' '
			<< model.bones[i].scales[j].scale.z << std::endl;
	std::cout << "\nROTATIONS: " << std::endl;
	for (auto j = 0; j < model.bones[i].rotations.size(); ++j)
		std::cout << model.bones[i].rotations[j].timestamp
			<< " - " << model.bones[i].rotations[j].rotation.x << ' '
			<< model.bones[i].rotations[j].rotation.y << ' '
			<< model.bones[i].rotations[j].rotation.z << ' '
			<< model.bones[i].rotations[j].rotation.w << std::endl;
	}
}