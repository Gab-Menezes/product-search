//std includes
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <random>

//library includes
#include "rapidfuzz/fuzz.hpp"
#include "nlohmann/json.hpp"

constexpr int map_size = 20;

/**
 * @brief calculate a string proximity based on fuzzy matching
 * @param s1 first string
 * @param s2 second string
 * @return normalized score
 */
double calculate_score(const std::string& s1, const std::string& s2) {
    double score = 0.f;
    //partial string matching
    score += rapidfuzz::fuzz::partial_ratio(s1, s2);
    //discards string difference
    score += rapidfuzz::fuzz::token_set_ratio(s1, s2);
    //looks for out of order
    score += rapidfuzz::fuzz::partial_token_sort_ratio(s1, s2);
    //weight based on different algorithms
    score += rapidfuzz::fuzz::WRatio(s1, s2);
    score /= 4.f;
    return score;
}

/**
 * @brief creates a std::map using nlohmann::json, where the key is "id" and value is "name"
 * @param multimap multimap containing the score and json
 * @return created map
 */
std::map<std::string, std::string> create_map(const std::multimap<double, nlohmann::json&>& multimap) {
    std::map<std::string, std::string> output;
    for (auto& element : multimap)
        output.emplace(element.second["id"], element.second["name"]);
    return output;
}

/**
 * @brief prints a std::map<std::string, std::string>
 * @param map
 * @return
 */
void print(std::map<std::string, std::string>&& map) {
    int i = 1;
    for (auto it = map.begin(); it != map.end(); it++) {
        std::cout << "#" << i << " - " << it->first << " - " << it->second << "\n";
        i++;
    }
    std::cout << "\n\n"; 
}

/**
 * @brief add a entry to the multimap limiting it's size to 20 and checking for score
 * @param multimap multimap containing the score and json
 * @param score
 * @param element json element to be added
 * @return
 */
void add_multimap(std::multimap<double, nlohmann::json&>& multimap, double score, nlohmann::json& element) {
    if (multimap.size() < map_size) {
        multimap.emplace(score, element);
    } else {
        auto it = multimap.begin();
        if (score >= it->first) {
            multimap.erase(it);
            multimap.emplace(score, element);
        }
    }
}

int main() {
    //random setup
    std::random_device rd;
    std::mt19937 randGen(rd());
    std::uniform_int_distribution distrib(1, 10);

    //file setup
    std::ifstream file("./catalogo_produtos.json");
    nlohmann::json json;
    file >> json;

    while (true) {
        std::cout << "Digite aqui sua consulta: ";
        std::string search;
        std::cin >> search;

        std::multimap<double, nlohmann::json&> scoreJson;
        for (auto& element : json) {
            //used to change the results on each run
            if (distrib(randGen) > 6) continue;

            //transforms both the search and product in lower case for better score calculation
            std::string product = element["name"];
            std::transform(search.begin(), search.end(), search.begin(), ::tolower);
            std::transform(product.begin(), product.end(), product.begin(), ::tolower);

            add_multimap(scoreJson, calculate_score(product, search), element);
        }
        
        print(create_map(scoreJson));
    }

    return 0;
}
