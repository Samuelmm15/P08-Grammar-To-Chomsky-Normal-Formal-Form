/**
 * @file Grammar2CNF.cc
 * @author Samuel Martín Morales (alu0101359526@ull.edu.es)
 * @brief 
 * @version 0.1
 * @date 2022-11-17
 * @signature Computabilidad y Algoritmia.
 * @course 2022-2023.
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>

#include "../include/grammar.h"

std::istream& operator>>(std::istream& input, std::vector<std::string>& vector_chains) {
  std::string line;
  while (std::getline(input, line)) {
    vector_chains.push_back(line);
  }
  return input;
}

int main(int argc, char** argv) {
  if (argc == 3) {
    std::string input_file_name = argv[1];
    std::string output_file_name = argv[2];
    
    /// Comprobación del formato de los ficheros introducidos
    std::regex files_format(".*\\.gra");
    if (!std::regex_match(input_file_name, files_format) || !std::regex_match(output_file_name, files_format)) {
      std::cout << std::endl;
      std::cout << "ERROR >>> Los ficheros introducidos no tienen el formato correcto." << std::endl;
      std::cout << "El formato correcto de los ficheros es `*.gra`" << std::endl;
      std::cout << "Para más información, haga uso de: ./grammar2CNF (-h || --help)" << std::endl;
      return 2; /// Error de tipo 2
    }

    /// Lectura del fichero de entrada
    std::ifstream input_file(input_file_name);
    std::vector<std::string> grammar_file_lines_vector;
    input_file >> grammar_file_lines_vector;
    input_file.close();
    Grammar newGrammar(grammar_file_lines_vector);
    newGrammar.CNFGrammarConvertor();
    newGrammar.PrintGrammar();
  } else {
    std::string option = argv[1];
    if (option == "--help" || option == "-h") {
      std::cout << std::endl;
      std::cout << "Usage: ./Grammar2CNF [inputFile.gra] [outputFile.gra]" << std::endl;
      return 0;
    } else {
      std::cout << std::endl;
      std::cout << "ERROR >>> Opción no soportada. Haga uso de la opción --help o -h para obtener más información." << std::endl;
      return 1; /// Error de tipo 1
    }
    /// Opción por defecto de error.
    std::cout << std::endl;
    std::cout << "ERROR >>> Opción no soportada. Haga uso de la opción --help o -h para obtener más información." << std::endl;
    return 1;
  }
};