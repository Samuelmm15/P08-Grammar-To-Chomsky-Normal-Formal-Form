/**
 * @file grammar.cc
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

#include "../include/grammar.h"

/**
 * @brief This is the constructor of the object grammar.
 * 
 */
Grammar::Grammar(std::vector<std::string> grammar_file_lines_vector) {
  /// TENER EN CUENTA QUE LA GRAMÁTICA NO PUEDE TENER PRODUCCIONES VACÍAS, NI UNITARIAS, SI LAS TIENE, TERMINAR EL PROGRAMA
//   for (int i = 0; i < grammar_file_lines_vector.size(); i++) {
//     std::cout << grammar_file_lines_vector[i] << std::endl;
//   }
    setNumberOfTerminalSymbols(std::stoi(grammar_file_lines_vector[0])); /// Número de símbolos terminales
    for (int i = 1; i < number_of_terminal_symbols_ + 1; i++) {
      terminal_symbols_.push_back(grammar_file_lines_vector[i]); /// Símbolos terminales
    }
    setNumberOfNonTerminalSymbols(std::stoi(grammar_file_lines_vector[number_of_terminal_symbols_ + 1])); /// Número de símbolos no terminales
    for (int i = number_of_terminal_symbols_ + 2; i < number_of_terminal_symbols_ + number_of_non_terminal_symbols_ + 2; i++) {
      non_terminal_symbols_.push_back(grammar_file_lines_vector[i]); /// Símbolos no terminales
    }
    setInitialSymbol(grammar_file_lines_vector[number_of_terminal_symbols_ + number_of_non_terminal_symbols_ + 2]); /// Símbolo inicial
    setNumberOfProductions(std::stoi(grammar_file_lines_vector[number_of_terminal_symbols_ + number_of_non_terminal_symbols_ + 3])); /// Número de producciones
    for (int i = number_of_terminal_symbols_ + number_of_non_terminal_symbols_ + 4; i < number_of_terminal_symbols_ + number_of_non_terminal_symbols_ + number_of_productions_ + 4; i++) {
      std::pair<std::string, std::string> production;
      production.first = grammar_file_lines_vector[i].substr(0, 1); /// Símbolo no terminal de la producción
      production.second = grammar_file_lines_vector[i].substr(6, grammar_file_lines_vector[i].size() - 3); /// Símbolo terminal de la producción
      productions_.push_back(production); /// Producciones
    }
    
    if (ProductionsComprobation() == false) {
      std::cout << "ERROR >>> La gramática no es correcta, por favor, revise el fichero de entrada." << std::endl;
      std::cout << "Compruebe que no hay producciones vacías, ni unitarias." << std::endl;
      std::cout << "Para más información, haga uso de: ./grammar2CNF (--help | -h)" << std::endl;
      exit(1);
    }
};

/**
 * @brief This method adds the number of terminal symbols of the grammar.
 * 
 * @param number_of_terminal_symbols Is the number of terminal symbols to add.
 */
void Grammar::setNumberOfTerminalSymbols(int number_of_terminal_symbols) {
  number_of_terminal_symbols_ = number_of_terminal_symbols;
};

/**
 * @brief This method adds the number of non terminal symbols of the grammar.
 * 
 * @param number_of_non_terminal_symbols Is the number of non terminal symbols to add.
 */
void Grammar::setNumberOfNonTerminalSymbols(
    int number_of_non_terminal_symbols) {
  number_of_non_terminal_symbols_ = number_of_non_terminal_symbols;
};

/**
 * @brief This method adds the terminal symbols to the grammar.
 * 
 * @param terminal_symbols Is the vector that contains the different terminal symbols.
 */
void Grammar::setTerminalSymbols(std::vector<std::string> terminal_symbols) {
  terminal_symbols_ = terminal_symbols;
};

/**
 * @brief This method adds the non terminal symbols to the grammar.
 * 
 * @param non_terminal_symbols Is the vector that contains the different non terminal symbols.
 */
void Grammar::setNonTerminalSymbols(
    std::vector<std::string> non_terminal_symbols) {
  non_terminal_symbols_ = non_terminal_symbols;
};

/**
 * @brief This method adds the initial symbol to the grammar.
 * 
 * @param initial_symbol Is the initial symbol of the grammar.
 */
void Grammar::setInitialSymbol(std::string initial_symbol) {
  initial_symbol_ = initial_symbol;
};

/**
 * @brief This method adds the number of productions of the grammar.
 * 
 * @param number_of_productions 
 */
void Grammar::setNumberOfProductions(int number_of_productions) {
  number_of_productions_ = number_of_productions;
};

/**
 * @brief This method adds the productions to the grammar.
 * 
 * @param productions Is the different productions of the grammar.
 */
void Grammar::setProductions(std::vector<std::pair<std::string, std::string>> productions) {
  productions_ = productions;
};

bool Grammar::ProductionsComprobation() {
  /// Comprobación de que no hay producciones vacías ni unitarias
    for (int i = 0; i < productions_.size(); i++) {
        std::string production_auxiliary = productions_[i].second;
        // for (int j = 0; j < production_auxiliary.size(); j++) {
        //   std::cout << production_auxiliary[j] << std::endl;
        // }
        if (production_auxiliary[0] == '&' && productions_[i].first[0] != initial_symbol_[0]) {
            return false;
        }
        for (int j = 0; j < non_terminal_symbols_.size(); j++) {
            if (production_auxiliary[0] == non_terminal_symbols_[j][0]) {
                return false;
            }
        }
    }
    return true;
};

void Grammar::CNFGrammarConvertor() {
  /// Transformación de una CFG a su Forma Normal de Chomsky
  /// Transformación de los símbolos terminales en no terminales
  std::string non_terminal_symbols_auxiliary = "SABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::vector<std::pair<std::string, std::string>> new_productions_auxiliary;
  int number_of_new_productions = 0;
  for (int i = 0; i < productions_.size(); i++) {
    std::string auxiliary_production = productions_[i].second;
    std::pair<std::string, std::string> new_production;
    for (int j = 0; j < auxiliary_production.size(); j++) {
      if (j >= 0) {
        for (int k = 0; k < terminal_symbols_.size(); k++) {
          if (auxiliary_production[j] == terminal_symbols_[k][0]) {
            int counter = 0;
            for (int l = 0; l < non_terminal_symbols_auxiliary.size(); l++) {
              if (non_terminal_symbols_auxiliary[l] == non_terminal_symbols_[counter][0]) {
                counter++;
              } else {
                new_production.first = non_terminal_symbols_auxiliary[l];
                non_terminal_symbols_.push_back(new_production.first);
                number_of_non_terminal_symbols_++;
                non_terminal_symbols_auxiliary.erase(l, 1);
                new_production.second = terminal_symbols_[k][0];
                new_productions_auxiliary.push_back(new_production);
                number_of_new_productions++;
                break;
              }
            }
          }
        }
      }
    }
    if (number_of_new_productions == terminal_symbols_.size()) {
      i = productions_.size();
    }
  }
  for (int i = 0; i < new_productions_auxiliary.size(); i++) {
    productions_.push_back(new_productions_auxiliary[i]);
  }
  /// En el punto anterior, se tienen las nuevas producciones con los símbolos terminales

  /// Transformación de las producciones con símbolos terminales en los nuevos simbolos no terminales
  for (int i = 0; i < productions_.size(); i++) {
    std::string auxiliary_production = productions_[i].second;
    for (int j = 0; j < auxiliary_production.size(); j++) {
      for (int k = 0; k < terminal_symbols_.size(); k++) {
        if (auxiliary_production[j] == terminal_symbols_[k][0]) {
          for (int l = 0; l < productions_.size(); l++) {
            if (productions_[l].second[0] == terminal_symbols_[k][0] && productions_[l].first[0] != productions_[i].first[0]) {
              std::string new_production;
              new_production.push_back(productions_[l].first[0]);
              productions_[i].second.replace(j, 1, new_production);
            }
          }
        }
      }
    }
  }

  /// En este punto anterior, se tiene la transformación de todas las producciones de manera que los terminales tienen estados no terminales y los terminales de las producciones son nuevos no terminales

  /// Transformación de las producciones con más de dos símbolos no terminales
  for (int i = 0; i < productions_.size(); i++) {
    std::string auxiliary_production = productions_[i].second;
    if (auxiliary_production.size() > 2) {
      std::pair<std::string, std::string> new_production;
      int counter = 2;
      for (int j = 0; j < auxiliary_production.size(); j++) {
        std:: string new_production_auxiliary;
        for (int k = 0; k < counter; k++) {
          new_production_auxiliary.push_back(auxiliary_production[j]);
          if (k == 0) {
            j++;
          }
        }
        /// Una vez tenemos el par de no terminal, generamos los nuevos no terminales
        int counter_auxiliary = 0;
        for (int l = 0; l < non_terminal_symbols_auxiliary.size(); l++) {
          if (non_terminal_symbols_auxiliary[l] == non_terminal_symbols_[counter_auxiliary][0]) {
            counter_auxiliary++;
          } else {
            new_production.first = non_terminal_symbols_auxiliary[l];
            non_terminal_symbols_.push_back(new_production.first);
            number_of_non_terminal_symbols_++;
            non_terminal_symbols_auxiliary.erase(l, 1);
            new_production.second = new_production_auxiliary;
            bool comprobation_flag = false;
            for (int m = 0; m < productions_.size(); m++) {
              if (productions_[m].second == new_production.second) {
                comprobation_flag = true;
              }
            }
            if (comprobation_flag == false) {
              productions_.push_back(new_production);
              number_of_productions_++;
            }
            break;
          }
        }
      }
    }
  }

  /// En este punto anterior, se tienen todas las producciones de tamaño dos
  for (int i = 0; i < productions_.size(); i++) {
    std::string auxiliary_production = productions_[i].second;
    if (auxiliary_production.size() > 2) {
      int counter = 2;
      bool initial_comprobation_flag = false;
      for (int j = 0; j < auxiliary_production.size(); j++) {
        std::string auxiliary_sub_production;  
        for (int k = 0; k < counter; k++) {
          auxiliary_sub_production.push_back(auxiliary_production[j]);
          if (k == 0) {
            j++;
          }
        }
        for (int l = 0; l < productions_.size(); l++) {
          if (productions_[l].second == auxiliary_sub_production) {
            std::string new_production;
            new_production.push_back(productions_[l].first[0]);
            productions_[i].second.erase(j - 1, 1);
            if (initial_comprobation_flag == false) {
              productions_[i].second.replace(j - 1, 1, new_production);
            } else {
              productions_[i].second.replace(j - 2, 1, new_production);
            }
            initial_comprobation_flag = true;
          }
        }
      }
    }
  }
};

/**
 * @brief This method prints the grammar in the console.
 * 
 */
void Grammar::PrintGrammar() {
  std::cout << "Grmática generada a partir del DFA introducido:" << std::endl;
  std::cout << "Nº de símbolos terminales: " << number_of_terminal_symbols_
            << std::endl;

  std::cout << "Símbolos terminales: ";
  for (int i = 0; i < number_of_terminal_symbols_; i++) {
    std::cout << terminal_symbols_[i] << " ";
  }

  std::cout << std::endl;
  std::cout << "Nº de símbolos no terminales: "
            << number_of_non_terminal_symbols_ << std::endl;

  std::cout << "Símbolos no terminales: ";
  for (int i = 0; i < number_of_non_terminal_symbols_; i++) {
    std::cout << non_terminal_symbols_[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "Símbolo inicial: " << initial_symbol_ << std::endl;

  std::cout << "Producciones: " << std::endl;
  ;
  for (int i = 0; i < productions_.size(); i++) {
    std::cout << productions_[i].first << " --> " << productions_[i].second
              << std::endl;
  }
};

/**
 * @brief This method prints the grammar into an output file.
 * 
 * @param file_name Is the name of the output file.
 */
void Grammar::PrintGrammarToFile(std::string file_name) {
  // std::fstream output_file;
  // output_file.open(file_name, std::ios::out);
  // output_file << number_of_terminal_symbols_ << std::endl;
  // for (int i = 0; i < number_of_terminal_symbols_; i++) {
  //   output_file << terminal_symbols_[i] << std::endl;
  // }
  // output_file << number_of_non_terminal_symbols_ << std::endl;
  // for (int i = 0; i < number_of_non_terminal_symbols_; i++) {
  //   output_file << non_terminal_symbols_[i] << std::endl;
  // }
  // output_file << initial_symbol_ << std::endl;
  // output_file << number_of_productions_ << std::endl;
  // for (int i = 0; i < productions_.size(); i++) {
  //   output_file << productions_[i] << std::endl;
  // }
  // output_file.close();
};