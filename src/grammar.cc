/**
 * @file grammar.cc
 * @author Samuel Martín Morales (alu0101359526@ull.edu.es)
 * @brief This file contains the implementation of the different methods of the
 * Grammar class.
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
  setNumberOfTerminalSymbols(
      std::stoi(grammar_file_lines_vector[0]));  /// Number of terminal symbols
  for (int i = 1; i < number_of_terminal_symbols_ + 1; i++) {
    terminal_symbols_.push_back(
        grammar_file_lines_vector[i]);  /// Terminal symbols
  }
  setNumberOfNonTerminalSymbols(std::stoi(
      grammar_file_lines_vector[number_of_terminal_symbols_ +
                                1]));  /// Number of non-terminal symbols
  for (int i = number_of_terminal_symbols_ + 2;
       i < number_of_terminal_symbols_ + number_of_non_terminal_symbols_ + 2;
       i++) {
    non_terminal_symbols_.push_back(
        grammar_file_lines_vector[i]);  /// non-terminal symbols
  }
  setInitialSymbol(grammar_file_lines_vector[number_of_terminal_symbols_ +
                                             number_of_non_terminal_symbols_ +
                                             2]);  /// Initial symbol
  setNumberOfProductions(
      std::stoi(grammar_file_lines_vector[number_of_terminal_symbols_ +
                                          number_of_non_terminal_symbols_ +
                                          3]));  /// Number of productions
  for (int i =
           number_of_terminal_symbols_ + number_of_non_terminal_symbols_ + 4;
       i < number_of_terminal_symbols_ + number_of_non_terminal_symbols_ +
               number_of_productions_ + 4;
       i++) {
    std::pair<std::string, std::string> production;
    production.first = grammar_file_lines_vector[i].substr(
        0, 1);  /// Non terminal symbols of the production
    production.second = grammar_file_lines_vector[i].substr(
        6, grammar_file_lines_vector[i].size() -
               3);                       /// Terminal symbols of the production
    productions_.push_back(production);  /// Productions
  }

  if (ProductionsComprobation() == false) {
    std::cout << "ERROR >>> La gramática no es correcta, por favor, revise el "
                 "fichero de entrada."
              << std::endl;
    std::cout << "Compruebe que no hay producciones vacías, ni unitarias."
              << std::endl;
    std::cout
        << "Para más información, haga uso de: ./grammar2CNF (--help | -h)"
        << std::endl;
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
 * @param number_of_non_terminal_symbols Is the number of non terminal symbols
 * to add.
 */
void Grammar::setNumberOfNonTerminalSymbols(
    int number_of_non_terminal_symbols) {
  number_of_non_terminal_symbols_ = number_of_non_terminal_symbols;
};

/**
 * @brief This method adds the terminal symbols to the grammar.
 *
 * @param terminal_symbols Is the vector that contains the different terminal
 * symbols.
 */
void Grammar::setTerminalSymbols(std::vector<std::string> terminal_symbols) {
  terminal_symbols_ = terminal_symbols;
};

/**
 * @brief This method adds the non terminal symbols to the grammar.
 *
 * @param non_terminal_symbols Is the vector that contains the different non
 * terminal symbols.
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
void Grammar::setProductions(
    std::vector<std::pair<std::string, std::string>> productions) {
  productions_ = productions;
};

/**
 * @brief This method returns if the introduced grammar have any definition
 * problem
 *
 * @return true if the grammar is correct
 * @return false if the grammar is incorrect
 */
bool Grammar::ProductionsComprobation() {
  for (int i = 0; i < productions_.size(); i++) {
    std::string production_auxiliary = productions_[i].second;
    if (production_auxiliary[0] == '&' &&
        productions_[i].first[0] != initial_symbol_[0]) {
      return false;
    }
    for (int j = 0; j < non_terminal_symbols_.size(); j++) {
      if (production_auxiliary[0] == non_terminal_symbols_[j][0] &&
          production_auxiliary.size() == 1) {
        return false;
      }
    }
  }
  return true;
};

/**
 * @brief This method converts any grammar at Chomsky Normal Form grammar.
 *
 */
void Grammar::CNFGrammarConvertor() {
  /// @brief Transformation of the terminal symbols into non-terminal symbols
  std::string non_terminal_symbols_auxiliary = "SABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::vector<std::pair<std::string, std::string>> new_productions_auxiliary;
  int number_of_new_productions = 0;
  for (int i = 0; i < productions_.size(); i++) {
    std::string auxiliary_production = productions_[i].second;
    std::pair<std::string, std::string> new_production;
    if (auxiliary_production.size() > 1) {
      for (int j = 0; j < auxiliary_production.size(); j++) {
        if (j >= 0) {
          for (int k = 0; k < terminal_symbols_.size(); k++) {
            if (auxiliary_production[j] == terminal_symbols_[k][0]) {
              int counter = 0;
              for (int l = 0; l < non_terminal_symbols_auxiliary.size(); l++) {
                if (non_terminal_symbols_auxiliary[l] ==
                    non_terminal_symbols_[counter][0]) {
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
    }
    if (number_of_new_productions == terminal_symbols_.size()) {
      i = productions_.size();
    }
  }
  for (int i = 0; i < new_productions_auxiliary.size(); i++) {
    productions_.push_back(new_productions_auxiliary[i]);
  }

  /// @brief Transformation of productions with terminal symbols into the new
  /// ones
  for (int i = 0; i < productions_.size(); i++) {
    std::string auxiliary_production = productions_[i].second;
    if (auxiliary_production.size() > 1) {
      for (int j = 0; j < auxiliary_production.size(); j++) {
        for (int k = 0; k < terminal_symbols_.size(); k++) {
          if (auxiliary_production[j] == terminal_symbols_[k][0]) {
            for (int l = 0; l < productions_.size(); l++) {
              if (productions_[l].second[0] == terminal_symbols_[k][0] &&
                  productions_[l].first[0] != productions_[i].first[0]) {
                std::string new_production;
                new_production.push_back(productions_[l].first[0]);
                productions_[i].second.replace(j, 1, new_production);
              }
            }
          }
        }
      }
    }
  }

  /// @brief Transformation of productions with more than two non-terminal
  /// symbols
  bool repeat_flag = true;
  while (repeat_flag == true) {
    for (int i = 0; i < productions_.size(); i++) {
      std::string auxiliary_production = productions_[i].second;
      if (auxiliary_production.size() > 2) {
        std::pair<std::string, std::string> new_production;
        int counter = 2;
        for (int j = 0; j < auxiliary_production.size(); j++) {
          std::string new_production_auxiliary;
          for (int k = 0; k < counter; k++) {
            new_production_auxiliary.push_back(auxiliary_production[j]);
            if (k == 0) {
              j++;
            }
          }

          int counter_auxiliary = 0;
          for (int l = 0; l < non_terminal_symbols_auxiliary.size(); l++) {
            if (non_terminal_symbols_auxiliary[l] ==
                non_terminal_symbols_[counter_auxiliary][0]) {
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
                std::string new_production_auxiliary;
                for (int m = 0; m < new_production.second.size(); m++) {
                  for (int n = 0; n < non_terminal_symbols_.size(); n++) {
                    if (new_production.second[m] ==
                        non_terminal_symbols_[n][0]) {
                      new_production_auxiliary.push_back(
                          non_terminal_symbols_[n][0]);
                    }
                  }
                }
                new_production.second = new_production_auxiliary;
                std::cout << new_production.second.size() << std::endl;
                if (new_production.second.size() == 2) {
                  productions_.push_back(new_production);
                  number_of_new_productions++;
                }
              }
              break;
            }
          }
        }
      }
    }
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

    /// @brief  Comprobation if the production has more than two non-terminal
    /// symbols
    for (int i = 0; i < productions_.size(); i++) {
      if (productions_[i].second.size() > 2) {
        repeat_flag = true;
        break;
      } else {
        repeat_flag = false;
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
  std::fstream output_file;
  output_file.open(file_name, std::ios::out);
  output_file << number_of_terminal_symbols_ << std::endl;
  for (int i = 0; i < terminal_symbols_.size(); i++) {
    output_file << terminal_symbols_[i] << std::endl;
  }
  output_file << number_of_non_terminal_symbols_ << std::endl;
  for (int i = 0; i < non_terminal_symbols_.size(); i++) {
    output_file << non_terminal_symbols_[i] << std::endl;
  }
  output_file << initial_symbol_ << std::endl;
  output_file << productions_.size() << std::endl;
  for (int i = 0; i < productions_.size(); i++) {
    output_file << productions_[i].first << " --> " << productions_[i].second
                << std::endl;
  }
  output_file.close();
};