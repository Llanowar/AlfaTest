
#include "Graph.h"

#include <fstream>
#include <iostream>

namespace {
void printHelp(const char *program) {
    std::cout << "Usage: " << std::endl;
    std::cout << "       " << program << " <path to file with first and last words> <path to dictionary file>" << std::endl;
    std::cout << std::endl;
    std::cout << "First and last words should have the same length." << std::endl;
    std::cout << "Dictionary file should contain word per line." << std::endl;
}

}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printHelp(argv[0]);
        return 1;
    }

    std::fstream input(argv[1]);
    std::string firstLine;
    std::getline(input, firstLine);
    std::string lastLine;
    std::getline(input, lastLine);
    input.close();

    if (firstLine.length() != lastLine.length())
    {
        printHelp(argv[0]);
        std::cerr << "First and last lines should have the same length." << std::endl;
        return 1;
    }

    AlfaTest::Graph g;

    input.open(argv[2]);
    while (!input.eof()) {
        std::string line;
        std::getline(input, line);

        if (line.empty() || line.length() != firstLine.length()) continue;
        g.addVertex(line);
    }

    g.addVertex(firstLine);
    g.addVertex(lastLine);

    g.buildEdges();

    std::vector<std::string> path = g.findShortestPath(firstLine, lastLine);

    if (path.empty())
    {
        std::cout << "The problem could not be solved for this data." << std::endl;
    }
    else
    {
        std::cout << "Solution is following:" << std::endl;
    }


    for (size_t i(0); i != path.size(); i++)
    {
        std::cout << path[i] << std::endl;
    }

    return 0;
}
