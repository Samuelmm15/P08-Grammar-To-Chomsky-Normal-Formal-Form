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

int main(int argc, char** argv) {
  if (argc == 3) {

  } else {
    std::string option = argv[1];
    if (option == "--help" || option == "-h") {
      std::cout << std::endl;
      std::cout << "Usage: ./Grammar2CNF [inputFile.gra] [outputFile.gra]" << std::endl;
      return 0;
    } else {
      std::cout << std::endl;
      std::cout << "ERROR >>> Opción no soportada. Haga uso de la opción --help o -h para obtener más información." << std::endl;
      return 1;
    }
    /// Opción por defecto de error.
    std::cout << std::endl;
    std::cout << "ERROR >>> Opción no soportada. Haga uso de la opción --help o -h para obtener más información." << std::endl;
    return 1;
  }
};