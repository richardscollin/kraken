#include "NodeTree.h"
#include "Parser.h"
#include <string>
#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {
	
	std::ifstream inFile;
	std::ofstream outFile;

	inFile.open(argv[1]);
	if (!inFile.is_open()) {
		std::cout << "Problem opening input file " << argv[1] << "\n";
		return(1);
	}

	outFile.open(argv[2]);
	if (!outFile.is_open()) {
		std::cout << "Probelm opening output file " << argv[2] << "\n";
		return(1);
	}

	NodeTree root;
	root.setName("Root");
	root.addChild(new NodeTree("SomeChild"));
	root.addChild(new NodeTree("SomeOtherChild"));
	root.get(0)->addChild(new NodeTree("Grandchildren"));

	//outFile << root.DOTGraphString() << std::endl;


	//Read the input file into a string
	std::string inputFileString;
	std::string line;
	while(inFile.good()) {
		getline(inFile, line);
		inputFileString.append(line+"\n");
	}

	Parser parser;
	parser.loadGrammer(inputFileString);

	std::cout << inputFileString << std::endl;
	std::cout << parser.grammerToString() << std::endl;
	std::cout << parser.grammerToDOT() << std::endl;

	outFile << parser.grammerToDOT() << std::endl;

	inFile.close();
	outFile.close();

	return(0);
}
 