#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

//FOR SHADER
struct VertexFormat{
	float position_x, position_y, position_z;
	float normal_x, normal_y, normal_z;
	float texcoord_x, texcoord_y;
	VertexFormat(){
		position_x = position_y = position_z = 0;
		normal_x = normal_y = normal_z = 0;
		texcoord_x = texcoord_y = 0;
	}
	VertexFormat(float px, float py, float pz){
		position_x = px;		position_y = py;		position_z = pz;
		normal_x = normal_y = normal_z = 0;
		texcoord_x = texcoord_y = 0;
	}
	VertexFormat(float px, float py, float pz, float nx, float ny, float nz){
		position_x = px;		position_y = py;		position_z = pz;
		normal_x = nx;		normal_y = ny;		normal_z = nz;
		texcoord_x = texcoord_y = 0;
	}
	VertexFormat(float px, float py, float pz, float tx, float ty){
		position_x = px;		position_y = py;		position_z = pz;
		texcoord_x = tx;		texcoord_y = ty;
		normal_x = normal_y = normal_z = 0;
	}
	VertexFormat(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty){
		position_x = px;		position_y = py;		position_z = pz;
		normal_x = nx;		normal_y = ny;		normal_z = nz;
		texcoord_x = tx;		texcoord_y = ty;
	}
	VertexFormat operator=(const VertexFormat &rhs){
		position_x = rhs.position_x;	position_y = rhs.position_y;	position_z = rhs.position_z;
		normal_x = rhs.normal_x;		normal_y = rhs.normal_y;		normal_z = rhs.normal_z;
		texcoord_x = rhs.texcoord_x;	texcoord_y = rhs.texcoord_y;
		return (*this);
	}

};


#endif // !VERTEXFORMAT_H

