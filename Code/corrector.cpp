#include "header.h"

inline void clearArray(char Array[], int size);
inline bool isNumber(const std::string& str);
inline bool isAbbreviation(const std::string& str);
std::string RemovePunctuation(char Punctuation[], std::string word);
std::string AddPunctuation(char Punctuation[], std::string word);

void Corrector(std::vector<std::string>& Text, std::vector<std::vector<std::string>>& Dictionary, int language, int *corrections){
    std::string word;
    int size = (int) Text.size();
    
    //Initial is used to determine which vector within the Dictionary the word is to be searched in based on its first letter,
    //Dicsize is the size of said vector.
    int initial = 0, Dicsize = 0;
    
    //Punctuation is an array used to store punctuation data.
    char Punctuation[5] = {'\0'};
    
    //Names_vec is a vector used to recognise names (personal or not).
    std::ifstream Names;
    std::string line;
    if(language == 0) Names.open("Resources/Names/ENG.txt");
    else if(language == 1) Names.open("Resources/Names/ITA.txt");
    
    std::vector<std::string> Names_vec;
    Names_vec.reserve(100);
    
    for(; getline(Names, line) ;) Names_vec.emplace_back(line);
    Names.close();
    
    for(int i=0; i<size; i++){
        word = Text[i];
        
        //Addressing punctuation.
        clearArray(Punctuation, 4);
        word = RemovePunctuation(Punctuation, word);
        
        //If a capital letter isn't preceded by a strong punctuation mark, verify that is belongs to a name (personal or not).
        if(word[0] > 64 && word[0] < 91){
            
            //Find the last useful word
            std::string last = "";
            
            if(i != 0)
                for(int it=1; last == "" && i-it >= 0; it++){
                    int length = (int) Text[i-it].length() - 1;
                    if(Text[i-it] != "\0" && Text[i-it][length] != '\n'){
                        last = Text[i-it];
                        break;
                    }
                }
            
            int llength = (int) last.length()-1;
            if((last != "" && last[llength] != '.' && last[llength] != '!' && last[llength] != '?') || i == 0){
                if(BinarySearch(word, Names_vec, 0, (int) Names_vec.size()-1) == -1){
                    
                    //Solution 1: adding a full stop to the preceding word.
                    //FullStop(Text, i-1, corrections);
                    
                    //Solution 2 (preferred): lowering it
                    if(i != 0){
                        word[0] += 32;
                        (*corrections)++;
                    }
                }
                
                //Iteration is skipped if the word is a name.
                else continue;
            }
        }
        
        //Iteration is skipped if the word is either a line break, a number or an abbreviation.
        if(word == "\n\n" || isNumber(word) == true || isAbbreviation(word) == true) continue;
        
        //Lower capital letters in order to analize them.
        bool capital = false;
        if(language >= 0 && language <= 1)
            if(word[0] > 63 && word[0] < 91){
                word[0] += 32;
                capital = true;
            }
        
        int initials = 99;
        if(language == 0) initials = FileLength("Resources/Languagedata/ENG.txt");
        else if(language == 1) initials = FileLength("Resources/Languagedata/ITA.txt");
        
        for(int ii=0; ii<initials; ii++){
            if(word[0] == Dictionary[ii][0][0]){
                initial = ii;
                
                //Dicsize will be used as the right end bracket for binary search, hence subtracting one is necessary to
                //go from the number of elements in the array (starts with 1) to the final position of the array (starts with 0).
                Dicsize = (int) Dictionary[ii].size() - 1;
                break;
            }
        }
        
        //If a word isn't present in the dictionary, start the process of evaluating similar words.
        //If a succesful substitute is found, add back characters from the Punctuation array, if not, try other methods.
        if(BinarySearch(word, Dictionary, 0, Dicsize, initial) == -1){
            
            word = Evaluator(word, language);
            
            if(word != "\0"){
                word = AddPunctuation(Punctuation, word);
                if(capital == true) word[0] -= 32;
                Text[i] = word;
                (*corrections)++;
            }
            //If no substitute is found, maybe the original word was split in half.
            //Only useful with certain kinds of OCR-generated input.
            else if(i != size - 1){
                std::string united = word + Text[i+1];
                char Punctuation2[5] = {'\0'};
                
                for(int ii=0; ii<3; ii++){
                    int length = (int) word.length();
                    if((united[ii] == '(' || united[ii] == '"' || united[ii] == '\'' || word[ii] == '\u0027') && i<2){
                        Punctuation2[ii] = united[ii];
                        united.erase(ii, 1);
                    }
                    if((united[length+ii] == '(' || united[length+ii] == '\"' || united[length+ii] == '-') && i<2){
                        united.erase(word.length()+ii, 1);
                    }
                    
                    int ulength = (int) united.length();
                    if(united[ulength-ii-1] == ')' || united[ulength-ii-1] == '\"' || united[ulength-ii-1] == '.' || united[ulength-ii-1] == ';' ||
                       united[ulength-ii-1] == ',' || united[ulength-ii-1] == ':' || united[ulength-ii-1] == '!' || united[ulength-ii-1] == '?' ||
                       united[ulength-ii-1] == '\'' || united[ulength-ii-1] == '-'){
                        Punctuation2[ii+2] = united[ulength-ii-1];
                        united.erase(ulength-ii-1, 1);
                    }
                }
                
                //Check to see if "united" is present in the dictionary. If so, add back characters from the Punctuation array
                if(BinarySearch(united, Dictionary, 0, Dicsize, initial) != -1){
                    word = AddPunctuation(Punctuation2, united);
                    
                    if(capital == true) united[0] -= 32;
                    Text[i] = united;
                    (*corrections)++;
                    Text.erase(Text.begin()+i+1);
                    continue;
                } //If nothing was found just leave the word as-is.
            }
        }
    }
    
    //Remove leftovers corrector might leave at the end of the text.
    for(int i=0; i<2; i++) if(Text[size-1][0] == '\n' || Text[size-1][0] == '\0' || Text[size-1][0] == ' ') Text.erase(Text.end()-1);
}

inline void clearArray(char Array[], int size){
    for(int i=0; i < size; i++) Array[i] = '\0';
}

inline bool isNumber(const std::string& str){
    for(char const &c : str) if(std::isdigit(c) == 0) return false;
    return true;
}

inline bool isAbbreviation(const std::string& str){
    for(int i=0; i < str.length(); i++) if(str[i] == '.' && i != 0 && i != str.length() - 1) return true;
    return false;
}

std::string RemovePunctuation(char Punctuation[], std::string word){
    for(int ii=0; ii<3; ii++){
        
        //Front punctuation. Apostrophe(\u0027).
        if((word[ii] == '(' || word[ii] == '\"' || word[ii] == '\u0027') && ii<2){
            Punctuation[ii] = word[ii];
            word.erase(ii, 1);
        }
        //Back punctuation.
        if(word[word.length()-1] == ')' || word[word.length()-1] == '\"' || word[word.length()-1] == '.' ||
           word[word.length()-1] == ';' || word[word.length()-1] == ',' || word[word.length()-1] == ':' ||
           word[word.length()-1] == '!' || word[word.length()-1] == '?' || word[word.length()-1] == '\''){
            Punctuation[ii+2] = word[word.length()-1];
            word.erase(word.length()-1, 1);
        }
    }
    
    return word;
}

std::string AddPunctuation(char Punctuation[], std::string word){
    if(Punctuation[1] != '\0') word = Punctuation[1] + word;
    if(Punctuation[0] != '\0') word = Punctuation[0] + word;
    if(Punctuation[4] != '\0') word = word + Punctuation[4];
    if(Punctuation[3] != '\0') word = word + Punctuation[3];
    if(Punctuation[2] != '\0') word = word + Punctuation[2];
    return word;
}
