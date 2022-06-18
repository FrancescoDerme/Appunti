#pragma once

#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>

//Toolbox.
void Filer(int language);
void Analyzer(int language);
int FileLength(std::string directory);
void Capitalizer(std::vector<std::string>& Text, int size, int *corrections);
void FullStop(std::vector<std::string>& Text, int position, int *corrections);
void Abbreviator(std::vector<std::string>& Text, int language, int *corrections);
void BuildDictionary(std::vector<std::vector<std::string>>& Dictionary, int language);

//Separator.
void Separator(std::vector<std::string>& Text, std::string line, int *corrections);

//Searcher.
int BinarySearch(std::string key, std::vector<std::string>& Vector, int left, int right);
int BinarySearch(std::string key, std::vector<std::vector<std::string>>& Dictionary, int left, int right, int initial);

//Corrector.
void Corrector(std::vector<std::string>& Text, std::vector<std::vector<std::string>>& Dictionary, int language, int *corrections);

//Evaluator.
std::string Evaluator(std::string word, int language);
