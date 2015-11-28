#include "OBJObject.h"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>

#define deleteVector(__type__, __vect__) do {\
                                   std::vector<__type__>::iterator iter; \
                                   std::vector<__type__>::iterator end; \
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)


bool first;
OBJObject::OBJObject(std::string filename) : Drawable()
{
    this->vertices = new std::vector<Vector3*>();
	this->colors = new std::vector<Vector3*>();
    this->normals = new std::vector<Vector3*>();
    this->faces = new std::vector<Face*>();
    
	first = true;

    parse(filename);
}

OBJObject::~OBJObject()
{
    //Delete any dynamically allocated memory/objects here
    
    deleteVector(Vector3*, vertices);
	deleteVector(Vector3*, colors);
    deleteVector(Vector3*, normals);
    deleteVector(Face*, faces);
}

void OBJObject::draw(DrawData& data)
{
    material.apply();
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    glBegin(GL_TRIANGLES);
    
    
    //Loop through the faces
    //For each face:
    //  Look up the vertices, normals (if they exist), and texcoords (if they exist)
    //  Draw them as triplets:
    
    //      glNorm(normals->at(face.normalIndices[0]))
    //      glVert(vertices->at(face.vertexIndices[0]))
    //      Etc.
    //
	Face face;
	//Vector3 colorVec;
	Vector3 *normalVec;
	Vector3 vertexVec;
	for (int i = 0; i < faces->size(); i++) {
		face = *(faces->at(i));
		//colorVec = *colors->at(face.vertexIndices[0]);
		normalVec = (normals->at(face.normalIndices[0]));
		vertexVec = *(vertices->at(face.vertexIndices[0]));
		//glColor3f(colorVec[0], colorVec[1], colorVec[2]);
		glNormal3f((*normalVec)[0], (*normalVec)[1], (*normalVec)[2]);
		glVertex3f(vertexVec[0], vertexVec[1], vertexVec[2]);

		//colorVec = *colors->at(face.vertexIndices[0]);
		normalVec = (normals->at(face.normalIndices[1]));
		vertexVec = *(vertices->at(face.vertexIndices[1]));
		//glColor3f(colorVec[0], colorVec[1], colorVec[2]);
		glNormal3f((*normalVec)[0], (*normalVec)[1], (*normalVec)[2]);
		glVertex3f(vertexVec[0], vertexVec[1], vertexVec[2]);

		//colorVec = *colors->at(face.vertexIndices[0]);
		normalVec = (normals->at(face.normalIndices[2]));
		vertexVec = *(vertices->at(face.vertexIndices[2]));
		//glColor3f(colorVec[0], colorVec[1], colorVec[2]);
		glNormal3f((*normalVec)[0], (*normalVec)[1], (*normalVec)[2]);
		glVertex3f(vertexVec[0], vertexVec[1], vertexVec[2]);

	}
    
    glEnd();
    
    glPopMatrix();
}

void OBJObject::update(UpdateData& data)
{
    //
}


bool static checkSyntax(std::string butt) {
	

	return true;
}

void OBJObject::parse(std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::string> tokens;
    std::string token;
    
    int lineNum = 0;
    
    
    std::cout << "Starting parse..." << std::endl;
    
    //While all your lines are belong to us
    while (std::getline(infile, line))
    {
        //Progress
        
        //Split a line into tokens by delimiting it on spaces
        //"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
        tokens.clear();
        tokens = split(line, ' ', tokens);
        
		if (tokens.size() <= 0) {
			continue;
		}

		/*if (++lineNum % 10000 == 0) {
			std::cout << "At line " << lineNum << std::endl;
			std::cout << tokens.at(0) << std::endl;
		}*/

        //If first token is a v then it gots to be a vertex
        if(tokens.at(0).compare("v") == 0)
        {
            //Parse the vertex line
            float x = std::stof(tokens.at(1));
            float y = std::stof(tokens.at(2));
            float z = std::stof(tokens.at(3));

			/*
			if (tokens.size() > 4) {
				float r = std::stof(tokens.at(4));
				float g = std::stof(tokens.at(5));
				float b = std::stof(tokens.at(6));
				colors->push_back(new Vector3(r, g, b));
			} */
            
            vertices->push_back(new Vector3(x, y, z));

			if (first) {
				this->minX = this->maxX = x;
				this->minY = this->maxY = y;
				this->minZ = this->maxZ = z;
				first = false;
			}
			else {
				if (minX > x) minX = x;
				if (minY > y) minY = y;
				if (minZ > z) minZ = z;
				if (maxX < x) maxX = x;
				if (maxY < y) maxY = y;
				if (maxZ < z) maxZ = z;
			}
        }
        else if(tokens.at(0).compare("vn") == 0)
        {
            //Parse the normal line
			float x = std::stof(tokens.at(1));
			float y = std::stof(tokens.at(2));
			float z = std::stof(tokens.at(3));

			normals->push_back(new Vector3(x, y, z));
        }
        else if(tokens.at(0).compare("f") == 0)
        {
            Face* face = new Face;
			std::string currString;

            //Parse the face line
			for (int i = 1; i < 4; i++) {
				currString = tokens.at(i);

				face->vertexIndices[i - 1] = std::stoi(currString.substr(0, currString.find('/', 0))) - 1;
				face->normalIndices[i - 1] = std::stoi(currString.substr(currString.find('/', 0) + 2, std::string::npos)) - 1;
			}
            
            faces->push_back(face);
        }
        else if(tokens.at(0).compare("How does I are C++?!?!!") == 0)
        {
            //Parse as appropriate
            //There are more line types than just the above listed
            //See the Wavefront Object format specification for details
        }
        
    }
    
    std::cout << "Done parsing." << std::endl;
	std::cout << "There are " << (*vertices).size() << " vertices and " << (*faces).size() << " faces and " << (*normals).size() << " normals." << std::endl;
	std::cout << checkSyntax("butt");
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}






void OBJObject::myParse(std::string& filename)
{
	FILE* fp = fopen(filename.c_str(), "rb");
	char* empty = "0";
	float x, y, z;
	float r, g, b;
	int v1, vn1, v2, vn2, v3, vn3;
	int c1, c2;

	if (fp == NULL) {
		std::cerr << "error loading file" << std::endl;
		exit(-1);
	}

	while (c1 = fgetc(fp) != EOF) {
		c2 = fgetc(fp);

		if (c1 == 'v') {
			if (c2 == ' ') {
				fscanf(fp, "%f %f %f %f %f %f\n", &x, &y, &z, &r, &g, &b);
				vertices->push_back(new Vector3(x, y, z));
				colors->push_back(new Vector3(r, g, b));
			}
			else if (c2 == 'n') {
				fscanf(fp, " %f %f %f\n", &x, &y, &z);
				normals->push_back(new Vector3(x, y, z));
			}

		}
		else if (c1 == 'f' && c2 == ' ') {
			fscanf(fp, "%i//%i %i//%i %i//%i\n", &v1, &vn1, &v2, &vn2, &v3, &vn3);
			Face face;
			face.vertexIndices[0] = v1;
			face.vertexIndices[1] = v2;
			face.vertexIndices[2] = v3;
			face.normalIndices[0] = vn1;
			face.normalIndices[1] = vn2;
			face.normalIndices[2] = vn3;
			faces->push_back(&face);
		}
		else {
			fscanf(fp, "\n");
		}

	}

	fclose(fp);
}