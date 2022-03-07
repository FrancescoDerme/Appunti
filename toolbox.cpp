#include "Header.h"
//Counts the number of words starting with each letter of the alphabet present in the database.
void Analyzer(int language){ std::ifstream Database; std::ofstream Data;
if(language == 0){ //English. Database.open("Resources/Database/ENG.txt"); Data.open("Resources/Languagedata/ENG.txt");
}
else if(language == 1){ //Italian.
Database.open("Resources/Database/ITA.txt");
Data.open("Resources/Languagedata/ITA.txt"); }
std::string word; int count=0;
char initial = 'a';
for(; getline(Database, word) ;){
if(initial == word[0]) count++; if(initial != word[0]){
Data << count << std::endl; initial = word[0];
count = 1;
} }
//Splits the database into 15 files based on words' length.
void Filer(int language){ std::ifstream Database; std::ofstream oneletter; std::ofstream twoletters; std::ofstream threeletters; std::ofstream fourletters; std::ofstream fiveletters; std::ofstream sixletters; std::ofstream sevenletters; std::ofstream eightletters; std::ofstream nineletters; std::ofstream tenletters; std::ofstream elevenletters; std::ofstream twelveletters; std::ofstream thirteenletters; std::ofstream fourteenletters; std::ofstream fifteenletters;
if(language == 0){ //English.
Database.open("Resources/Database/ENG.txt"); oneletter.open("Resources/Wordsbylength/ENG/Oneletter.txt"); twoletters.open("Resources/Wordsbylength/ENG/Twoletters.txt"); threeletters.open("Resources/Wordsbylength/ENG/Threeletters.txt"); fourletters.open("Resources/Wordsbylength/ENG/Fourletters.txt"); fiveletters.open("Resources/Wordsbylength/ENG/Fiveletters.txt"); sixletters.open("Resources/Wordsbylength/ENG/Sixletters.txt"); sevenletters.open("Resources/Wordsbylength/ENG/Sevenletters.txt"); eightletters.open("Resources/Wordsbylength/ENG/Eightletters.txt"); nineletters.open("Resources/Wordsbylength/ENG/Nineletters.txt"); tenletters.open("Resources/Wordsbylength/ENG/Tenletters.txt"); elevenletters.open("Resources/Wordsbylength/ENG/Elevenletters.txt"); twelveletters.open("Resources/Wordsbylength/ENG/Twelveletters.txt"); thirteenletters.open("Resources/Wordsbylength/ENG/Thirteenletters.txt"); fourteenletters.open("Resources/Wordsbylength/ENG/Fourteenletters.txt"); fifteenletters.open("Resources/Wordsbylength/ENG/Fifteenletters.txt");
}
else if(language == 1){ //Italian.
Database.open("Resources/Database/ITA.txt"); oneletter.open("Resources/Wordsbylength/ITA/Oneletter.txt"); twoletters.open("Resources/Wordsbylength/ITA/Twoletters.txt"); threeletters.open("Resources/Wordsbylength/ITA/Threeletters.txt"); fourletters.open("Resources/Wordsbylength/ITA/Fourletters.txt"); fiveletters.open("Resources/Wordsbylength/ITA/Fiveletters.txt"); sixletters.open("Resources/Wordsbylength/ITA/Sixletters.txt"); sevenletters.open("Resources/Wordsbylength/ITA/Sevenletters.txt"); eightletters.open("Resources/Wordsbylength/ITA/Eightletters.txt"); nineletters.open("Resources/Wordsbylength/ITA/Nineletters.txt"); tenletters.open("Resources/Wordsbylength/ITA/Tenletters.txt"); elevenletters.open("Resources/Wordsbylength/ITA/Elevenletters.txt"); twelveletters.open("Resources/Wordsbylength/ITA/Twelveletters.txt"); thirteenletters.open("Resources/Wordsbylength/ITA/Thirteenletters.txt"); fourteenletters.open("Resources/Wordsbylength/ITA/Fourteenletters.txt"); fifteenletters.open("Resources/Wordsbylength/ITA/Fifteenletters.txt");
}
std::string word;
int margin = 1;
for(int i=0; i <= margin; i++){
for(; getline(Database, word); ){
int length = (int) word.length();
if(length == 1-i || length == 1+i) oneletter << word << std::endl; if(length == 2-i || length == 2+i) twoletters << word << std::endl; if(length == 3-i || length == 3+i) threeletters << word << std::endl; if(length == 4-i || length == 4+i) fourletters << word << std::endl;
                           count; Database.close(); Data.close();
}
Data <<
          
  if(length if(length if(length if(length if(length if(length if(length if(length if(length if(length if(length
== == == == == == == == == == ==
5-i || length == 5+i) fiveletters << word << std::endl;
6-i || length == 6+i) sixletters << word << std::endl;
7-i || length == 7+i) sevenletters << word << std::endl;
8-i || length == 8+i) eightletters << word << std::endl;
9-i || length == 9+i) nineletters << word << std::endl;
10-i || length == 10+i) tenletters << word << std::endl;
11-i || length == 11+i) elevenletters << word << std::endl; 12-i || length == 12+i) twelveletters << word << std::endl; 13-i || length == 13+i) thirteenletters << word << std::endl; 14-i || length == 14+i) fourteenletters << word << std::endl; 15-i || length == 15+i) fifteenletters << word << std::endl;
 }
 Database.clear();
Database.seekg(0); }
  Database.close(); oneletter.close(); twoletters.close(); threeletters.close(); fourletters.close(); fiveletters.close(); sixletters.close(); sevenletters.close(); eightletters.close(); nineletters.close(); tenletters.close(); elevenletters.close(); twelveletters.close(); thirteenletters.close(); fourteenletters.close(); fifteenletters.close();
}
 //Calculates the length of a
file.
int FileLength(std::string directory){
std::ifstream file(directory);
file.unsetf(std::ios_base::skipws);
unsigned line_count = (int) std::count(std::istream_iterator<char>(file), std::istream_iterator<char>(), '\n'); return line_count+1;
}
//Builds the dictionary of words that input is going to be compared against.
void BuildDictionary(std::vector<std::vector<std::string>>& Dictionary, int language){ int initials; std::string dataDirectory;
if(language == 0) dataDirectory = "Resources/Languagedata/ENG.txt";
else if(language == 1) dataDirectory = "Resources/Languagedata/ITA.txt";
initials = FileLength(dataDirectory); Dictionary.reserve(initials);
std::ifstream Data; Data.open(dataDirectory);
std::string word; std::vector<std::string> Temp;
for(int i=0; getline(Data, word); i++){
Temp.reserve(stoi(word)); Dictionary.emplace_back(Temp); Temp.shrink_to_fit();
} Data.close();
std::ifstream Database;
if(language == 0) Database.open("Resources/Database/ENG.txt"); else if(language == 1)Database.open("Resources/Database/ITA.txt");
char initial = '\0';
for(int i=0; getline(Database, word); ){
           if(initial == if(initial == else {initial
Database.close(); }
'\0') initial = word[0];
word[0]) Dictionary[i].push_back(word);
= word[0]; i++; Dictionary[i].push_back(word);}
}
  //If missing, add a full stop (works both for end of paragraph cases when called by the Separator, and for within-text cases when called by the Corrector).
void FullStop(std::vector<std::string>& Text, int position, int *corrections){ int length = (int) Text[position].length() - 1;
int plength = (int) Text[position-1].length() - 1;
if(Text[position][length] != '.' && Text[position][length] != '!' && Text[position][length] != '?'){
//CASE 1: there's a comma or a semicolon instead of the period.
if(Text[position][length] == ',' || Text[position][length] == ';'){ Text[position][length] = '.';
(*corrections)++;
}
//CASE 2: there's a comma or a semicolon instead of the period + an extra space at the end of the text.
else if(Text[position] == "\0" && (Text[position-1][plength] == ',' || Text[position-1][plength] == ';')){ Text[position-1][plength] = '.';
(*corrections)++;
}
//CASE 3: the period is simply missing.
else if(Text[position][length] > 96 && Text[position][length] < 123){ Text[position] += '.';
(*corrections)++;
}
//CASE 4: the period is missing + an extra space at the end of the text.
                  else if(Text[position][length] Text[position-1]+='.'; (*corrections)++;
} }
//CASE 5: the period is there, but
if(Text[position][0] == '.'){ Text[position-1] += '.'; Text.erase(Text.end()-1); (*corrections)++;
}
else if(Text[position][0] == '!'){
Text[position-1] += '!'; Text.erase(Text.end()-1); (*corrections)++;
}
else if(Text[position][0] == '?'){
Text[position-1] += '?'; Text.erase(Text.end()-1);
== ' '){
separated from the word by an extra space.
          
  (*corrections)++; }
//If missing, add a capital letter at the start of the text.
void Capitalizer(std::vector<std::string>& Text, int size, int *corrections){ for(int i = 0; i <= size; i++){
int plength = (int) Text[i-1].length() - 1;
if((i == 0 && Text[i][0] > 96 && Text[i][0] < 123) ||
(Text[i][0] > 96 && Text[i][0] < 123 && (Text[i-1][plength] == '.' || Text[i-1][plength] == '!' || Text[i-1][plength] == '?' || Text[i-1] == "\n\n"))){ Text[i][0] -= 32;
(*corrections)++;
}
else if((i == 0 && Text[i][0] == 34 && Text[i][1] > 96 && Text[i][1] < 123) ||
(Text[i][1] > 96 && Text[i][1] < 123 && Text[i][0] == '"' && (Text[i-1][plength] == '.' || Text[i-1][plength] == '!' || Text[i-1][plength] == '?' || Text[i-1] == "\n\n"))){ Text[i][1] -= 32;
(*corrections)++;
} }
}
//Account for abbreviations in the text.
void Abbreviator(std::vector<std::string>& Text, int language, int *corrections){ std::string line, candidate;
std::ifstream Abbreviations;
if(language == 0) Abbreviations.open("Resources/Abbreviations/ENG.txt"); else if(language == 1) Abbreviations.open("Resources/Abbreviations/ITA.txt");
//Punctuations are used to account for cases where either the first part of an abbreviation starts with a punctuation mark or the second one ends with one.
char punctuation1 = '\0', punctuation2 = '\0'; for(int i=0; i < Text.size()-1; i++){
int length = (int) Text[i].length() - 1, slength = (int) Text[i+1].length() - 1;
//Finding possible abbreviations.
if(Text[i][length] == '.' && Text[i+1] != "\0" && Text[i+1] != "\n\n"){ candidate = Text[i];
candidate += Text[i+1];
//Accounting for punctuation-mark related edge-cases.
if(Text[i][0] == '.' || Text[i][0] == '!' || Text[i][0] == '?' || Text[i][0] == '"'){ punctuation1 = Text[i][0];
candidate.erase(0, 1);
}
if(Text[i+1][slength] == '.' || Text[i+1][slength] == '!' || Text[i+1][slength] == '?' || Text[i+1][slength] == '"'){ punctuation2 = Text[i+1][slength];
candidate.erase(candidate.length()-1, 1);
}
//Reset the getline function.
Abbreviations.clear(); Abbreviations.seekg(0);
//Binary search might be implement here instead of linear search at the cost of having to load abbreviations into a vector. //It is not worth while working with a small number of abbreviations.
while(getline(Abbreviations, line)){
if(line == candidate){
Text[i] = candidate; Text.erase(Text.begin()+i+1);
//Diminishes the value of "corrections" to account for an error generated in the Separator upon finding an abbreviation.
(*corrections)--;
if(punctuation1 != '\0' || punctuation2 != '\0'){ std::string passer = Text[i];
Text[i] = punctuation1 + passer; punctuation1 = '\0';
}
if(punctuation1 != '\0' || punctuation2 != '\0'){
Text[i] += punctuation2;
punctuation2 = '\0'; }
} }
} }
}
