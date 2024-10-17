//  Main program
//		Reverse an audio file.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "linkedStack.h"
#include "linkedQueue.h"

using namespace std;

int main(int argc, char *argv[])
{
// *****************************************************************
//	Check and process command line arguments.
//		Usage: ./reverse <inputFile> <outputFile>
//	 NOTE:	Must exit with "return EXIT_SUCCESS" even if there
//			is an error.

	// Error message std::strings provided below

	std::ifstream inf;
	std::ofstream ofs; 
	if(argc == 1){
	// no arguments -> usage message
		std::cerr << "Usage: ./reverse <inputFile> <outputFile>" << std::endl;
		return EXIT_SUCCESS;
	}
	if (argc != 3){ 
	// incorrect number of arguments, just error out.
		std::cerr << "Error, must provide input and output file names." << std::endl;
		return EXIT_SUCCESS;
	} 
	if(argc > 1 && argc == 3) { //was else before clang tidy error

	// check argument 1, input file, by attempting to open, read access
		inf.open(argv[1]);
		if(!inf.is_open()){
			std::cerr << "Error, unable to open input file: " << argv[1] << std::endl;
				return EXIT_SUCCESS;
		}
	// check argument 2, output file, by attempting to open, write access
		ofs.open(argv[2]);
		if(!ofs.is_open()){
			std::cout << "Error, unable to open output file: " << argv[2] << std::endl;
				return EXIT_SUCCESS;
		}
	}

//  Headers...
	std::string	bars(50, '-');
	std::cout << "Audio Reversal Program" << std::endl << std::endl;

//	Handle audio file header lines
//		read initial header line
//			verify format (i.e, "; Sample Rate" is present)
//			write to output file.
//		extract sample rate, convert to integer
	std::string check = "; Sample Rate";
	std::string holdString;
	std::getline(inf, holdString);

	// Error message std::string - place as appropriate
	// ensure header has correct title
	//	if not, not a audio data file
	if(holdString.find(check)== std::string::npos){
		std::cout << "Invalid audio data file" << std::endl;
		return EXIT_SUCCESS;
	}
	
	//tokenize holdString
	std::stringstream ss (holdString); 
	
	// get sample rate from header
	unsigned int sampleRate; 
	ss >> sampleRate;
	ofs << holdString << std::endl;	

	// read second header line and write to output file.
	getline(inf, holdString);
	ofs << holdString << std::endl;

	//	Process and audio data file.
	// declare linked stack and linked queue
	//	use to sampleRate/2 for the node array sizes
	linkedQueue<double> dQueue(sampleRate/2);
	linkedStack<double> dStack(sampleRate/2);
	double	sample1 = 0.0, sample2 = 0.0;

	// read input file, store samples
	while(std::getline(inf, holdString)){
		std::stringstream iss (holdString);
		iss >> sample1 >> sample2;
		dStack.push(sample2);
		dQueue.addItem(sample1);
	}

	// show count of all samples
	std::cout << "Count = " << dQueue.queueCount() << std::endl;

	// get samples, write to output file
	//	output format:
	//		outFile << "  " << sample1 << "  " << sample2 << std::endl;

	while(!dStack.isEmptyStack() && !dQueue.isEmptyQueue()){
		ofs << " " << dQueue.front() << " " << dStack.top() << std::endl;
		dQueue.deleteItem();
		dStack.pop();
	}
//  All done.
//		close file and show final message.

	inf.close();
	ofs.close();

	std::cout << bars << std::endl << "Reversal completed." << std::endl;

	return	EXIT_SUCCESS;
}