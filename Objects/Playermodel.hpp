#pragma once

#define PLAYERMODEL

const glm::vec3 color = glm::vec3(0.5, 0.5, 0.5);

const float cutoff = 0.05;
const float headX = 0.2;
const float headY = 0.2;
const float headZ = 0.2;


std::vector<Vert2v3> Pvertices =
{//						X									Y						Z					/V3 color
																														//HEAD FRONT
	Vert2v3{glm::vec3(	0.0,								0.0,				headZ),						color},		//[0] FRONT middle

	Vert2v3{glm::vec3(	0.0,								headY,				headZ - cutoff),			color},		//[1] FRONT top 
	Vert2v3{glm::vec3(	0.0,								-headY,				headZ - cutoff),			color},		//[2] FRONT bottom
	Vert2v3{glm::vec3(	-headX,								0.0,				headZ - cutoff),			color},		//[3] FRONT left
	Vert2v3{glm::vec3(  headX,								0.0,				headZ - cutoff),			color},		//[4] FRONT right

	Vert2v3{glm::vec3(	cutoff - headX,						headY - cutoff,		headZ - cutoff),			color},		//[5] FRONT top left
	Vert2v3{glm::vec3(	headX - cutoff,						headY - cutoff,		headZ - cutoff),			color},		//[6] FRONT top right
	Vert2v3{glm::vec3(	cutoff - headX,						cutoff - headY,		headZ - cutoff),			color},		//[7] FRONT bottom left
	Vert2v3{glm::vec3(  headX - cutoff,						cutoff - headY,		headZ - cutoff),			color},		//[8] FRONT bottom right

	// 																													// HEAD MIDDLE
	Vert2v3{glm::vec3(	0.0,								headY + cutoff,		0),			color},						//[9] MID top 
	Vert2v3{glm::vec3(	0.0,								-headY - cutoff,	0),			color},						//[10] MID bottom
	Vert2v3{glm::vec3(	-headX - cutoff,					0.0,				0),			color},						//[11] MID left
	Vert2v3{glm::vec3(  headX + cutoff,						0.0,				0),			color},						//[12] MID right

	// 																													// HEAD BACK
	Vert2v3{glm::vec3(	0.0,								0.0,				-headZ),					color},		//[13] BACK middle

	Vert2v3{glm::vec3(	0.0,								headY,				cutoff - headZ),			color},		//[14] BACK top 
	Vert2v3{glm::vec3(	0.0,								-headY,				cutoff - headZ),			color},		//[15] BACK bottom
	Vert2v3{glm::vec3(	-headX,								0.0,				cutoff - headZ),			color},		//[16] BACK left
	Vert2v3{glm::vec3(  headX,								0.0,				cutoff - headZ),			color},		//[17] BACK right

	Vert2v3{glm::vec3(	cutoff - headX,						headY - cutoff,		cutoff - headZ),			color},		//[18] BACK top left
	Vert2v3{glm::vec3(	headX - cutoff,						headY - cutoff,		cutoff - headZ),			color},		//[19] BACK top right
	Vert2v3{glm::vec3(	cutoff - headX,						cutoff - headY,		cutoff - headZ),			color},		//[20] BACK bottom left
	Vert2v3{glm::vec3(  headX - cutoff,						cutoff - headY,		cutoff - headZ),			color},		//[21] BACK bottom right
};

// #define POINTS
// std::vector<GLuint> Pindices =
// {
// 	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
// };

std::vector<GLuint> Pindices =
{
																//Could be a helmet segment
	//Front face
	0, 5, 6, //Front mid->top
	0, 7, 8, //Front mid-bot
	0, 3, 5, //Front mid->left->top
	0, 3, 7, //Front mid-left->bot
	0, 4, 6, //Front mid->right->top
	0, 4, 8, //Front mid->right->bot
	1, 5, 6, //Front top
	2, 7, 8, //Front bottom

	//Back face
	13, 18, 19, //Back mid->top
	13, 20, 21, //Back mid-bot
	13, 16, 18, //Back mid->left->top
	13, 16, 20, //Back mid-left->bot
	13, 17, 19, //Back mid->right->top
	13, 17, 21, //Back mid->right->bot
	14, 18, 19, //Back top
	15, 20, 21, //Back bottom

	//Side connects TOP
	5, 18, 9, //Top lefts to mid top
	6, 19, 9, //Top rights to mid top
	5, 18, 11, //Top lefts to mid left
	6, 19, 12, //Top rights to mid right

	5, 1, 9, //front topleft->top to top
	6, 1, 9, //front topright->top to top
	18, 14, 9, //back topleft->top to top
	19, 14, 9, //back topright->top to top
	
	5, 3, 11, //front topleft->left to left
	6, 4, 12, //front topright->right to right
	18, 16, 11, //back topleft->left to left
	19, 17, 12, //back topright->right to right
																//Helmet ends here
	//Side connects BOT
	7, 20, 10, //Bot lefts to mid bot
	8, 21, 10, //Bot rights to mid bot
	7, 20, 11, //Bot lefts to mid left
	8, 21, 12, //Bot rights to mid right

	7, 2, 10, //Bot botleft->top to bot
	8, 2, 10, //Bot botright->top to bot
	20, 15, 10, //Bot botleft->top to bot
	21, 15, 10, //Bot botright->top to 
	
	7, 3, 11, //Bot botleft->left to left
	8, 4, 12, //Bot botright->right to right
	20, 18, 11, //Bot botleft->left to left
	21, 19, 12, //Bot botright->right to right

};
