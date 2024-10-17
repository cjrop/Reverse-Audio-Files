//  Main program
//		Reverse an audio file.
// Name: Chris Padilla
// Description: Refactored the code to split the main logic into separate functions for better readability and maintainability.
// Used Exceptions to handle errors and print error messages to the console.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "linkedStack.h"
#include "linkedQueue.h"

// using namespace std;
void checkArguments(int argc);
void processFiles(const std::string& inputFile, const std::string& outputFile);
void handleHeaders(std::ifstream& inf, std::ofstream& ofs, unsigned int& sampleRate);
void processAudioData(std::ifstream& inf, std::ofstream& ofs, unsigned int sampleRate);

int main(int argc, char *argv[]) {
    /* Here we are checking the number of arguments passed to the program
     * if the number of arguments is less than 3, we throw an exception
     * else we process the files
     */
	try {
        checkArguments(argc);
        processFiles(argv[1], argv[2]);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl; // print the error message
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void checkArguments(int argc){
    /* We are checking the number of arguments passed to the program
     */
	if (argc == 1) {
        throw std::invalid_argument("Usage: ./reverse <inputFile> <outputFile>");
    }
    if (argc != 3) {
        throw std::invalid_argument("Error, must provide input and output file names.");
    }
}

void processFiles(const std::string& inputFile, const std::string& outputFile){
    // Open the input file
    std::ifstream inf(inputFile);
    if (!inf.is_open()) {
        throw std::runtime_error("Error, unable to open input file: " + inputFile);
    }
    // Open the output file
    std::ofstream ofs(outputFile);
    if (!ofs.is_open()) {
        throw std::runtime_error("Error, unable to open output file: " + outputFile);
    }

    unsigned int sampleRate; // hold the sample rate
    handleHeaders(inf, ofs, sampleRate);
    processAudioData(inf, ofs, sampleRate);
}

void handleHeaders(std::ifstream& inf, std::ofstream& ofs, unsigned int& sampleRate) {
    std::string check = "; Sample Rate";
    std::string holdString;
    std::getline(inf, holdString); // read the first line

    if (holdString.find(check) == std::string::npos) { // check if the first line contains the sample rate
        // usin npos to check if the string is not found
        throw std::runtime_error("Invalid audio data file");
    }

    std::stringstream ss(holdString);
    ss >> sampleRate;
    ofs << holdString << std::endl;

    std::getline(inf, holdString);
    ofs << holdString << std::endl;
}

void processAudioData(std::ifstream& inf, std::ofstream& ofs, unsigned int sampleRate) {
    linkedQueue<double> dQueue(sampleRate / 2);
    linkedStack<double> dStack(sampleRate / 2);

    double sample1 = 0.0, sample2 = 0.0;
    std::string holdString;

    while (std::getline(inf, holdString)) {
        std::stringstream iss(holdString);
        iss >> sample1 >> sample2;
        dStack.push(sample2);
        dQueue.addItem(sample1);
    }

    std::cout << "Count = " << dQueue.queueCount() << std::endl;
	while (!dQueue.isEmptyQueue() && !dStack.isEmptyStack()) {
		sample1 = dQueue.front();
		dQueue.deleteItem();
		sample2 = dStack.top();
		dStack.pop();
        ofs << sample1 << " " << sample2 << std::endl;
    }
}