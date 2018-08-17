#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>

typedef std::vector<float> Vecf;

class Model {
private:
    std::vector<Vecf> verts_;
    std::vector<std::vector<int> > faces_;
    std::vector<Vecf> texturesCoords_;
    std::vector<std::vector<int> > textures_;
    std::vector<Vecf> norms_;

	Vecf vbo;
	std::vector<int> ibo;
	bool m_hasTextrures;
	bool m_normalized;

	unsigned int stride;

	void fillVbo(int vertexIndex,int normalIndex, int textIndex = -1);

	void normalizeVertex();

public:    
    Model(const char *filename,bool hasTextrures,bool normalized);
    ~Model();

    int nverts() const;

    int nfaces() const;

	int getStride() const;

	const Vecf& getVbo() const;

	const std::vector<int>& getIbo() const;

};

#endif //__MODEL_H__
