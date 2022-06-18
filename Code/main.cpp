#include "header.h"
#include <chrono>

inline bool exists(const std::string& name);

int main() {
    
    //Keep track of how long program takes to execute.
    auto start = std::chrono::high_resolution_clock::now();
    
    bool database_update = false; //Simulate database updates.
    int language = 1; //Simulate different language settings (0 = English, 1 = Italian).
    
    //All components needed to run are examined.
    //If something is found missing, the issue is either resolved or an error code is generated.
    if (exists("Input.txt") == 0){std::cout << "Input file not found" << std::endl; return 1;}
    
    if(language == 0){
        if (exists("Resources/Names/ENG.txt") == 0){std::cout << "Names file not found" << std::endl; return 2;}
        if (exists("Resources/Database/ENG.txt") == 0){std::cout << "Database not found" << std::endl; return 3;}
        if (exists("Resources/Abbreviations/ENG.txt") == 0){std::cout << "Abbreviations file not found" << std::endl; return 4;}
        if(exists("Resources/Languagedata/ENG.txt") == 0 || database_update == true) Analyzer(language);
        
        if (exists("Resources/Wordsbylength/ENG/Oneletter.txt") == 0 || exists("Resources/Wordsbylength/ENG/Twoletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ENG/Threeletters.txt") == 0 || exists("Resources/Wordsbylength/ENG/Fourletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ENG/Fiveletters.txt") == 0 || exists("Resources/Wordsbylength/ENG/Sixletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ENG/Sevenletters.txt") == 0 || exists("Resources/Wordsbylength/ENG/Eightletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ENG/Nineletters.txt") == 0 || exists("Resources/Wordsbylength/ENG/Tenletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ENG/Elevenletters.txt") == 0 || exists("Resources/Wordsbylength/ENG/Twelveletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ENG/Thirteenletters.txt") == 0 || exists("Resources/Wordsbylength/ENG/Fourteenletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ENG/Fifteenletters.txt") == 0 || database_update == true) Filer(language);
    }
    else if(language == 1){
        if (exists("Resources/Names/ITA.txt") == 0){std::cout << "Names file not found" << std::endl; return 2;}
        if (exists("Resources/Database/ITA.txt") == 0){std::cout << "Database not found" << std::endl; return 3;}
        if (exists("Resources/Abbreviations/ITA.txt") == 0){std::cout << "Abbreviations file not found" << std::endl; return 4;}
        if(exists("Resources/Languagedata/ITA.txt") == 0 || database_update == true) Analyzer(language);
        
        if (exists("Resources/Wordsbylength/ITA/Oneletter.txt") == 0 || exists("Resources/Wordsbylength/ITA/Twoletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ITA/Threeletters.txt") == 0 || exists("Resources/Wordsbylength/ITA/Fourletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ITA/Fiveletters.txt") == 0 || exists("Resources/Wordsbylength/ITA/Sixletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ITA/Sevenletters.txt") == 0 || exists("Resources/Wordsbylength/ITA/Eightletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ITA/Nineletters.txt") == 0 || exists("Resources/Wordsbylength/ITA/Tenletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ITA/Elevenletters.txt") == 0 || exists("Resources/Wordsbylength/ITA/Twelveletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ITA/Thirteenletters.txt") == 0 || exists("Resources/Wordsbylength/ITA/Fourteenletters.txt") == 0 ||
            exists("Resources/Wordsbylength/ITA/Fifteenletters.txt") == 0 || database_update == true) Filer(language);
    }
    
    //Setup
    std::vector<std::vector<std::string>> Dictionary;
    BuildDictionary(Dictionary, language);
    
    //Immediately after initialisation, 100 spaces are reserved for the Text vector in order to diminish the chances it needs to resize.
    //It is expected that the program will almost never be tasked to work with a text shorter than that.
    std::vector<std::string> Text;
    Text.reserve(100);
    
    //Count how many times the program edits the input.
    int corrections = 0;
    int *p = &corrections;
    
    //Input & Separation.
    std::string line; std::ifstream Input("Input.txt");
    while(getline(Input, line)) Separator(Text, line, p);
    Input.close();
    
    //Reunite abbreviations that were divided by the separator.
    Abbreviator(Text, language, p);
    
    //General corrections using Dictionary.
    Corrector(Text, Dictionary, language, p);
    
    //Language-specific corrections.
    if(language >= 0 && language <= 1){
        FullStop(Text, (int) Text.size()-1, p);
        Capitalizer(Text, (int) Text.size()-1, p);
    }
    
    //Output
    std::ofstream Output("Output.txt");
    for(std::string& s : Text){
        int length = (int) s.length();
        if(s[length-1] != '\'' && s[length-1] != '\0' && s[length-1] != '\n') Output << s << " ";
        else Output << s;
     }
    
    Output.close();
    
    //Print run info to the console.
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    float t = (float)duration.count()/1000000;
    
    printf("%d ", corrections);
    (corrections == 1) ? std::cout << "correction " : std::cout << "corrections ";
    printf("in %.3f ", t);
    (t == 1) ? std::cout << "second.\n" : std::cout << "seconds.\n";
    return 0;
}

//Checks if a file exists.
inline bool exists(const std::string& name){
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}
