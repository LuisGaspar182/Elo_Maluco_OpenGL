#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

std::vector<std::vector<int>> lerXmlParaMatriz(const std::string& arquivoXml) {
    std::unordered_map<std::string, int> mapaIndices = {
        {"vms", 0}, {"brs", 1}, {"vrs", 2}, {"ams", 3},
        {"vmm", 4}, {"brm", 5}, {"vrm", 6}, {"amm", 7},
        {"vmi", 8}, {"bri", 9}, {"vri", 10}, {"ami", 11}, {"vzo", 20}
    };

    std::ifstream arquivo(arquivoXml);
    std::string linha;
    std::vector<std::vector<int>> matriz;
    std::vector<int> linhaAtual;

    while (std::getline(arquivo, linha)) {
        if (linha.find("<col>") != std::string::npos) {
            size_t inicio = linha.find("<col>") + 5;
            size_t fim = linha.find("</col>");
            std::string valor = linha.substr(inicio, fim - inicio);
            
            if (mapaIndices.find(valor) != mapaIndices.end()) {
                linhaAtual.push_back(mapaIndices[valor]);
            }
        } else if (linha.find("</row>") != std::string::npos && !linhaAtual.empty()) {
            matriz.push_back(linhaAtual);
            linhaAtual.clear();
        }
    }

    return matriz;
}

std::vector<std::vector<int>> obterMatrizDoXml(std::string arquivoXml) {
    return lerXmlParaMatriz(arquivoXml);
}