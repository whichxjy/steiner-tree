#ifndef _GENETIC_HPP_
#define _GENETIC_HPP_

#include "solution.hpp"
#include <vector>

namespace GA {
    // Genetic Algorithm
    int GeneticAlgo(const std::vector<std::vector<int>>& graph, const std::vector<int>& terminals);

    // Uniform Crossover to generate offspring
    void crossover(solution_ptr lhs, solution_ptr rhs);

    // Mutation for some solutions
    void mutation(const std::vector<solution_ptr>& population, const std::vector<int>& terminals);
}

#endif // !_GENETIC_HPP_
