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
Grammar::Grammar(){};

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
void Grammar::setProductions(std::vector<std::string> productions) {
  productions_ = productions;
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
    std::cout << productions_[i] << std::endl;
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
  for (int i = 0; i < number_of_terminal_symbols_; i++) {
    output_file << terminal_symbols_[i] << std::endl;
  }
  output_file << number_of_non_terminal_symbols_ << std::endl;
  for (int i = 0; i < number_of_non_terminal_symbols_; i++) {
    output_file << non_terminal_symbols_[i] << std::endl;
  }
  output_file << initial_symbol_ << std::endl;
  output_file << number_of_productions_ << std::endl;
  for (int i = 0; i < productions_.size(); i++) {
    output_file << productions_[i] << std::endl;
  }
  output_file.close();
};