#include "model.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <algorithm> 

static int temp_buff[9] = {};
static float temp_buff_f[3] = {};



Model::Model(const char *filename,bool hasTextrures,bool normalized): m_hasTextrures(hasTextrures), m_normalized(normalized), stride(0)
{
    if (!filename || !strlen(filename))
    {
        std::cerr << "bad filename" << std::endl;
        return;
    }

    std::ifstream in(filename);

    if (!in)
    {
        std::cerr << "can'not read file" << std::endl;
        return;
    }

    std::string line;

    while(in && !in.eof())
    {
        std::getline(in,line);

        if (!line.size())
            continue;

        std::stringbuf sbuff(line);
        std::istream buff (&sbuff);  // associate stream buffer to stream

        std::string type;

        buff >> type;

        if (type == "v" )
        {
            Vecf temp;

            buff >> temp_buff_f[0] >> temp_buff_f[1] >> temp_buff_f[2];

			verts_.emplace_back(Vecf{ temp_buff_f[0],temp_buff_f[1],temp_buff_f[2]});
			
        }
		else if (type == "f")
		{

			char delim;

			if (m_hasTextrures)
			{			
				buff >> temp_buff[0] >> delim >> temp_buff[1] >> delim >> temp_buff[2] >> temp_buff[3] >> delim >> temp_buff[4] >> delim >> temp_buff[5] >> temp_buff[6] >> delim >> temp_buff[7] >> delim >> temp_buff[8];
				textures_.emplace_back(std::vector<int>{ temp_buff[1], temp_buff[4], temp_buff[7] });
			}
			else
			{
				buff >> temp_buff[0] >> delim  >> delim >> temp_buff[2] >> temp_buff[3] >> delim >> delim >> temp_buff[5]  >> temp_buff[6] >> delim >> delim >> temp_buff[8];
			}

            faces_.emplace_back(std::vector<int>{ temp_buff[0],temp_buff[3],temp_buff[6], temp_buff[2], temp_buff[5], temp_buff[8]});
            
        }
        else if (type == "vt")
        {
            
            buff >> temp_buff_f[0] >> temp_buff_f[1];

			texturesCoords_.emplace_back(Vecf{ temp_buff_f[0],temp_buff_f[1]});
        }
        else if (type == "vn")
        {

			buff >> temp_buff_f[0] >> temp_buff_f[1] >> temp_buff_f[2];

            norms_.push_back(Vecf{ temp_buff_f[0],temp_buff_f[1],temp_buff_f[2] });
        }
    }

	//hasTextrures = texturesCoords_.size();

	if (!m_normalized)
		normalizeVertex();

	//float maxV = *std::max_element(verts_.begin(), verts_.end(), [](auto el1,auto el2) {return abs(el1) < abs(el2);});

	//std::transform(verts_.begin(), verts_.end(), verts_.begin(), [=](auto el) {return el / maxV; });

	stride = (3 + 3 + (m_hasTextrures ? 2 : 0));

	int vboSize = stride * verts_.size();

	vbo.reserve(vboSize);

	ibo.reserve(faces_.size()*3);


	auto it_faces    = faces_.begin();
	auto it_textures = textures_.begin();

	while (it_faces != faces_.end()) {

		const std::vector<int>& vertindecies = *(it_faces);

		ibo.insert(ibo.end(), vertindecies.begin(), vertindecies.end());

		
		if (m_hasTextrures)
		{
			const std::vector<int>& textindecies = *(it_faces);

			fillVbo(vertindecies[0], vertindecies[3], textindecies[0]);
			fillVbo(vertindecies[1], vertindecies[4], textindecies[1]);
			fillVbo(vertindecies[2], vertindecies[5], textindecies[2]);

			it_faces++;
			it_textures++;

			continue;
		}

		fillVbo(vertindecies[0], vertindecies[3], -1);
		fillVbo(vertindecies[1], vertindecies[4], -1);
		fillVbo(vertindecies[2], vertindecies[5], -1);

		it_faces++;				
	}

}

void Model::fillVbo(int vertexIndex,int normalIndex, int textIndex)
{
	Vecf vert = verts_[vertexIndex-1];
	Vecf norm = norms_[normalIndex -1];

	//Vecf norm = Vecf{1.0f,1.0f ,1.0f };

	vbo.insert(vbo.end(), vert.begin(),vert.end());
	vbo.insert(vbo.end(), norm.begin(), norm.end());


	if (textIndex != -1) {
		Vecf text = texturesCoords_[textIndex-1];
		vbo.insert(vbo.end(), text.begin(), text.end());
	}

}

void Model::normalizeVertex()
{
	auto it = verts_.begin();

	bool isFirst = true;
	float maxF;

	while (it < verts_.end()) {

		auto it_f = (*it).begin();


		while (it_f < (*it).end()) {
			
			float curr = (*it_f);

			if (isFirst) {
				isFirst = false;
				maxF = curr;
			}
			else {
				if (abs(curr) > maxF)
					maxF = abs(curr);
			}

			it_f++;
		}

		it++;
	}

	it = verts_.begin();

	while (it < verts_.end()) {

		Vecf& currVert = (*it);

		std::transform(currVert.begin(), currVert.end(), currVert.begin(), [=](auto el) {return el / maxF; });

		it++;
	}

}


Model::~Model()
{
}

int Model::nverts() const
{
    return verts_.size();
}

int Model::nfaces() const
{
    return faces_.size();
}

int Model::getStride() const
{
	return stride;
}

const Vecf& Model::getVbo() const {
	return vbo;
	//return debugTriangle;
}

const std::vector<int>& Model::getIbo() const {
	return ibo;
	//return debugIbo;
}
