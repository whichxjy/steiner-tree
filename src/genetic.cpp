#include "genetic.hpp"
#include "solution.hpp"
#include "common.hpp"
#include <memory>
#include <array>
#include <queue>
#include <algorithm>
#include <functional>

namespace GA {
    // The size of population
    constexpr int POP_SIZE = 20;
    // How many bad results you can endure?
    constexpr int BAD_ENDURE_TIMES = 20;
    // How many times to do for the genetic operation?
    constexpr int GENETIC_OPER_TIMES = 3;
    // How many contestants to be chose from population?
    constexpr int CONTESTANT_NUM = 4;
}

// Genetic Algorithm
int GA::GeneticAlgo(const std::vector<std::vector<int>>& graph, const std::vector<int>& terminals) {
    // [Initialize population]
    std::vector<solution_ptr> population(POP_SIZE);
    // Create random solutions
    for (int i = 0; i < POP_SIZE - 1; i++) {
        population[i] = get_random_solution(graph);
        // All terminals must be chose
        for (int term : terminals) {
            population[i]->chose[term] = true;
        }
    }
    // Create a solution for the MST of the entire graph
    population[POP_SIZE - 1] = get_full_solution(graph);
    // Minimun cost
    int min_cost = INF;
    // Bad result counter
    int bad_count = 0;
    // Continue Loop until there are too many bad results
    while (bad_count <= BAD_ENDURE_TIMES) {
        for (int round = 0; round < GENETIC_OPER_TIMES; round++) {
            // [Choose some contestants from population to select parents]
            // Parents
            std::array<solution_ptr, 2> parents;
            for (int i = 0; i < 2; i++) {
                // Shuffle the population
                shuffle_vector(population);
                // Choose some contestants from the front of population, and
                // then push then into the priority queue.
                std::priority_queue<solution_ptr, std::vector<solution_ptr>, std::greater<solution_ptr>> contestants;
                for (int j = 0; j < CONTESTANT_NUM; j++) {
                    contestants.push(population[j]);
                }
                // Choose the solution with the least cost to become one of the parents
                parents[i] = contestants.top();
            }

            // [Crossover to generate offspring]
            crossover(parents[0], parents[1]);

            // [Mutation for some solutions]
            mutation(population, terminals);
        }

        // Update min_cost: choose the best solution from polution
        solution_ptr best_solution = population[0];
        for (int i = 1; i < POP_SIZE; i++) {
            if (population[i] < best_solution) {
                best_solution = population[i];
            }
        }

        // [Check whether the result is good or not]
        if (best_solution->cost < min_cost) {
            // It's a good result
            min_cost = best_solution->cost;
            bad_count = 0;
        }
        else {
            // It's a bad result
            bad_count += 1;
        }
    }
    return min_cost;
}

// Uniform Crossover to generate offspring
void GA::crossover(solution_ptr lhs, solution_ptr rhs) {
    // The number of all nodes
    int V = (lhs->chose).size();
    // Uniform crossover
    for (int i = 0; i < V; i++) {
        if (random_boolean()) {
            std::swap(lhs->chose[i], rhs->chose[i]);
        }
    }
    // Update offspring
    lhs->update();
    rhs->update();
}

// Mutation for some solutions
void GA::mutation(const std::vector<solution_ptr>& population, const std::vector<int>& terminals) {
    // Probability: 1%
    if (random_int(0, 99) == 1) {
        // Choose a solution from population randomly
        solution_ptr sol = population[random_int(0, POP_SIZE - 1)];
        // The number of all nodes
        int V = (sol->chose).size();
        // Change one of the chose nodes
        while (true) {
            int rand_node = random_int(0, V - 1);
            // Check if rand_node is a terminal
            auto equal_to_rand_node = [rand_node](const int term) {
                return term == rand_node;
            };
            if (std::any_of(terminals.cbegin(), terminals.cend(), equal_to_rand_node)) {
                // rand_node is a terminal
                continue;
            }
            else {
                // If rand_node isn't a terminal, then change the rand_node
                sol->chose[rand_node] = !sol->chose[rand_node];
                break;
            }
        }
        // Update the solution
        sol->update();
    }
}