#include "FileObj2.h"

using namespace std;

FileObj2::FileObj2(char * fileName)
{
	model2world.identity();

	FILE *file = fopen(fileName, "r");

	parse(fileName);
	fclose(file);

	Matrix4 temp;
	temp.makeTranslate(-adjustX, -adjustY, -adjustZ);

	temp.print("Translation Matrix:\n");

	model2world = model2world * temp;

	float angle1 = 30 / 180.0 * M_PI;
	float angle2 = 180 / 180.0 * M_PI;
	float final3 = angle1 / angle2;

	float scale = ((40 * tan(final3*3.14)) / (maxX - minX)) * 2;

	temp.makeScale(scale, scale, scale);
	temp.print("Scaling Matrix:\n");

	//model2world = temp * model2world;
}


FileObj2::~FileObj2()
{
}


//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
vector<string> &split(const string &s, char delim, vector<string> &elems)
{
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

vector<string> split(const string &s, char delim)
{
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

void FileObj2::parse(char * fileName){
	string name = string(fileName);

	//int test = 0;
	int pInfo = 0;

	ifstream infile(name);
	string line;
	vector<string> tokens;
	string token;

	string line2;
	vector<string> tokens2;
	string token2;

	double x, y, z, r, g, b;
	int p, q, s;

	Vector3 temp;

	//While all your lines are belong to us
	while (getline(infile, line))
	{
		if (line == ""){
			if(pInfo == 0) cout << "Hold on little buddy. We're halfway done parsing!" <<endl;
			if (pInfo == 1) cout << "We dund it!!\n" << endl;
			//if (pInfo == 1) cout << "The last values for p and q added: "<< p << ' ' << q << endl;
			pInfo++;
			continue;
		}

		//Split a line into tokens by delimiting it on spaces
		tokens = split(line, ' ');

		if (tokens.at(0).compare("#") == 0);

		//If first token is a v then it gots to be a vertex
		else if (tokens.at(0).compare("v") == 0)
		{
			//test++;

			//Parse rest of tokens into doubles
			x = stod(tokens.at(1));
			y = stod(tokens.at(2));
			z = stod(tokens.at(3));

			vertex.push_back(x);
			vertex.push_back(y);
			vertex.push_back(z);

			if (tokens.size() == 7){
				r = stod(tokens.at(4));
				g = stod(tokens.at(5));
				b = stod(tokens.at(6));

				vertexColors.push_back(r);
				vertexColors.push_back(g);
				vertexColors.push_back(b);
			}

			//cout << "Printing line " << test << ": " << x << ' ' << y << ' ' << z << ' ' << r << ' ' << g << ' ' << b << endl;

			//if (test > 10) while (1);

		}

		else if (tokens.at(0).compare("vn") == 0)
		{
			//Parse rest of tokens into doubles
			x = stod(tokens.at(1));
			y = stod(tokens.at(2));
			z = stod(tokens.at(3));

			temp = Vector3(x, y, z);
			temp.normalize();

			vertexNormals.push_back(temp.get(0));
			vertexNormals.push_back(temp.get(1));
			vertexNormals.push_back(temp.get(2));
		}

		else if (tokens.at(0).compare("f") == 0)
		{
			for (int i = 1; i < tokens.size(); i++){
				line2 = tokens.at(i);
				tokens2 = split(line2, '//');

				p = stoi(tokens2.at(0));
				//cout << p << endl;
				//for (int p = 0; p < tokens2.size(); p++) cout << tokens2.at(p) << endl;
				//cout << tokens2.size() << endl;
				q = stoi(tokens2.at(2));

				facesv.push_back(p);
				facesn.push_back(q);

				//cout << "Printing line " << test << ": " << p << ' ' << q << endl;
			}

			//test++;
			//if (test > 10) while (1);
		}

	
	}

	findMax();

	adjustX = (maxX + minX) / 2.0;
	adjustY = (maxY + minY) / 2.0;
	adjustZ = (maxZ + minZ) / 2.0;

}

void FileObj2::draw(){

	Matrix4 glMatrix;
	glMatrix = model2world;
	glMatrix.transpose();
	glLoadMatrixd(glMatrix.getPointer());

	//glLoadMatrixd(model2world.getPointer());

	//model2world.print("");

	//glPointSize(2);

	int test = 1;

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < facesn.size(); i++)
	{
		//cout << vertexNormals.at(facesn.at(i) - 1) << vertexNormals.at(facesn.at(i + 1) - 1) << vertexNormals.at(facesn.at(i + 2) - 1) << endl;
		//cout << vertex.at(facesv.at(i) - 1) << vertex.at(facesv.at(i + 1) - 1) << vertex.at(facesv.at(i + 2) - 1) << endl;

		//cout << facesv.at(i) << "//" << facesn.at(i) << " " << facesv.at(i + 1) << "//" << facesn.at(i + 1) << " " << facesv.at(i + 2) << "//" << facesn.at(i + 2) << endl;

		//if (test == 10) while (1);
		double verI = (facesv.at(i) - 1) * 3;
		double vernI = (facesn.at(i) - 1) * 3;
		
		glNormal3f(vertexNormals.at(vernI), vertexNormals.at(vernI+1), vertexNormals.at(vernI+2));
		glVertex3f(vertex.at(verI), vertex.at(verI + 1), vertex.at(verI + 2));
		//test++;
	}
	glEnd();

	//cout << "Vertex : " << vertex.size() << " Vertex Normals : " << vertexNormals.size() << " Facesn: " << facesn.size() << " Facesv: " << facesv.size() << endl;

}

Matrix4& FileObj2::getMatrix()
{
	return model2world;
}

void FileObj2::findMax(){
	for (int i = 0; i < vertex.size(); i += 3){
		if (vertex[i] > maxX) maxX = vertex[i];
		if (vertex[i] < minX) minX = vertex[i];
	}
	cout << minX << endl;
	cout << maxX << endl;

	for (int i = 1; i < vertex.size(); i += 3){
		if (vertex[i] > maxY) maxY = vertex[i];
		if (vertex[i] < minY) minY = vertex[i];
	}
	cout << minY << endl;
	cout << maxY << endl;

	for (int i = 2; i < vertex.size(); i += 3){
		if (vertex[i] > maxZ) maxZ = vertex[i];
		if (vertex[i] < minZ) minZ = vertex[i];
	}

	cout << minZ << endl;
	cout << maxZ << endl;
}