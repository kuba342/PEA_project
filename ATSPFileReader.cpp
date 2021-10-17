#include "ATSPFileReader.h"

ATSPFileReader::ATSPFileReader()
{
	this->dimension = 0;
}

ATSPFileReader::~ATSPFileReader()
{
}


AdjMatrix* ATSPFileReader::readFile(std::string filename) {
	AdjMatrix* matrix = nullptr;
	std::ifstream stream;
	stream.open(filename);
	std::string buffer;
	this->dimension = 0;
	while (!stream.eof()) {
		stream >> buffer;
		if (buffer == "DIMENSION:") {
			stream >> this->dimension;
		}
		else if (buffer == "EDGE_WEIGHT_TYPE:"){
			stream >> this->typeOfEdge;
		}
		else if (buffer == "EDGE_WEIGHT_FORMAT:") {
			stream >> this->edgeFormat;
		}
		else if (buffer == "EDGE_WEIGHT_SECTION" && this->dimension) {
			int size = this->dimension * this->dimension;
			matrix = new AdjMatrix(dimension);
			for (int i = 0; i < this->dimension; i++) {
				for (int j = 0; j < this->dimension; j++) {
					int weight;
					stream >> weight;
					matrix->addDirectedEdge(i, j, weight);
				}
			}
		}
		else {
			std::getline(stream, buffer);
		}
	}
	return matrix;
}