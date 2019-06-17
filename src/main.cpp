#include "genetic.hpp"
#include "aco.hpp"
#include "timer.hpp"
#include "common.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <functional>
#include <vector>

// Use genetic algorithm or ant colony optimization?
constexpr bool USE_GENETIC_ALGO = true;

int main(int argc, char* argv[]) {
    // Try to get file name
    if (argc != 2) {
        std::cerr << "Fail to get file name." << std::endl;
        return EXIT_FAILURE;
    }

    // Fila to open
    const std::string filename = argv[1];
    
    std::ifstream infile(filename);

    // Check if the file is open
    if (!infile.is_open()) {
        std::cerr << "Fail to open the file." << std::endl;
        return EXIT_FAILURE;
    }

    // Read file line by line unitl line == "SECTION Graph"
    std::string line;
    while (std::getline(infile, line) && line != "SECTION Graph") {
        // Continue to read
    }

    // Read the number of nodes
    std::string nodes_str;
    int V;
    if (std::getline(infile, line)) {
        std::istringstream iss(line);
        iss >> nodes_str >> V;
    }
    else {
        std::cerr << "Fail to read nodes from file." << std::endl;
        return EXIT_FAILURE;
    }

    // Read the number of edges
    std::string edges_str;
    int E;
    if (std::getline(infile, line)) {
        std::istringstream iss(line);
        iss >> edges_str >> E;
    }
    else {
        std::cerr << "Fail to read edges from file." << std::endl;
        return EXIT_FAILURE;
    }

    // Create graph and initialize it
    std::vector<std::vector<int>> graph(V, std::vector<int>(V, 0));

    // Read all edges from file
    while (std::getline(infile, line) && line != "END") {
        char edge_ch;
        int nodeA, nodeB, distance;
        std::istringstream iss(line);
        iss >> edge_ch >> nodeA >> nodeB >> distance;
        // Update graph
        nodeA -= 1;
        nodeB -= 1;
        graph[nodeA][nodeB] = distance;
        graph[nodeB][nodeA] = distance;
    }

    // Read file line by line unitl line == "SECTION Terminals"
    while (std::getline(infile, line) && line != "SECTION Terminals") {
        // Continue to read
    }

    // Read the number of terminals
    std::string term_str;
    int T;
    if (std::getline(infile, line)) {
        std::istringstream iss(line);
        iss >> term_str >> T;
    }
    else {
        std::cerr << "Fail to read terminals from file." << std::endl;
        return EXIT_FAILURE;
    }

    // Read all terminals from file
    std::vector<int> terminals;
    while (std::getline(infile, line) && line != "END") {
        char term_ch;
        int term;
        std::istringstream iss(line);
        iss >> term_ch >> term;
        term -= 1;
        terminals.push_back(term);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////

    // Choose an algorithm for Steiner Tree Problem
    std::function<int(const std::vector<std::vector<int>>&, const std::vector<int>&)> SteinerProblemAlgo;
    if (USE_GENETIC_ALGO) {
        SteinerProblemAlgo = GA::GeneticAlgo;
    }
    else {
        SteinerProblemAlgo = ACO::AntColonyAlgo;
    }

    Timer timer;
    int result = SteinerProblemAlgo(graph, terminals);
    double time = timer.elapsed() / 1000.0;
    if (result == INF) {
        std::cout << "[Fail to find result]" << std::endl;
    }
    else {
        std::cout << "[Result] : " << result << std::endl;
    }
    std::cout << "[Running Time] : " << time << " s" << std::endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////

    // Close the file
    infile.close();

    return EXIT_SUCCESS;
}
