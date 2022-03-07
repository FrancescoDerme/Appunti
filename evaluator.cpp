#include "Header.h"

int countDisparities(std::string word1, std::string word2, int i, int maxl);
std::string reverse(std::string word, int length);

std::string Evaluator(std::string word, int language){
    //Candidate is the word being evaluated, result is what's going to be passed back to the corrector.
    std::ifstream Candidatefile;
    std::string candidate, result = "\0";
    
    //Get rid of accent-related edge-cases.
    //UNICODE values of accents: è(\u00E8), é(\u00E9), ò(\u00F2), à(\u00E0), ù(\u00F9) ì(\u00EC).
    if(word == "\u00E8" || word == "\u00E9" || word == "\u00F2" || word == "\u00E0" || word == "\u00F9" || word == "\u00EC") return word;
    
    int length = (int) word.length();
    
    if(language == 0){
        if(length == 1) Candidatefile.open("Resources/Wordsbylength/ENG/Oneletter.txt");
        else if(length == 2) Candidatefile.open("Resources/Wordsbylength/ENG/Twoletters.txt");
        else if(length == 3) Candidatefile.open("Resources/Wordsbylength/ENG/Threeletters.txt");
        else if(length == 4) Candidatefile.open("Resources/Wordsbylength/ENG/Fourletters.txt");
        else if(length == 5) Candidatefile.open("Resources/Wordsbylength/ENG/Fiveletters.txt");
        else if(length == 6) Candidatefile.open("Resources/Wordsbylength/ENG/Sixletters.txt");
        else if(length == 7) Candidatefile.open("Resources/Wordsbylength/ENG/Sevenletters.txt");
        else if(length == 8) Candidatefile.open("Resources/Wordsbylength/ENG/Eightletters.txt");
        else if(length == 9) Candidatefile.open("Resources/Wordsbylength/ENG/Nineletters.txt");
        else if(length == 10) Candidatefile.open("Resources/Wordsbylength/ENG/Tenletters.txt");
        else if(length == 11) Candidatefile.open("Resources/Wordsbylength/ENG/Elevenletters.txt");
        else if(length == 12) Candidatefile.open("Resources/Wordsbylength/ENG/Tweleveletters.txt");
        else if(length == 13) Candidatefile.open("Resources/Wordsbylength/ENG/Thirteenletters.txt");
        else if(length == 14) Candidatefile.open("Resources/Wordsbylength/ENG/Fourteenletters.txt");
        else if(length == 15) Candidatefile.open("Resources/Wordsbylength/ENG/Fifteenletters.txt");
    }
    else if(language == 1){
        if(length == 1) Candidatefile.open("Resources/Wordsbylength/ITA/Oneletter.txt");
        else if(length == 2) Candidatefile.open("Resources/Wordsbylength/ITA/Twoletters.txt");
        else if(length == 3) Candidatefile.open("Resources/Wordsbylength/ITA/Threeletters.txt");
        else if(length == 4) Candidatefile.open("Resources/Wordsbylength/ITA/Fourletters.txt");
        else if(length == 5) Candidatefile.open("Resources/Wordsbylength/ITA/Fiveletters.txt");
        else if(length == 6) Candidatefile.open("Resources/Wordsbylength/ITA/Sixletters.txt");
        else if(length == 7) Candidatefile.open("Resources/Wordsbylength/ITA/Sevenletters.txt");
        else if(length == 8) Candidatefile.open("Resources/Wordsbylength/ITA/Eightletters.txt");
        else if(length == 9) Candidatefile.open("Resources/Wordsbylength/ITA/Nineletters.txt");
        else if(length == 10) Candidatefile.open("Resources/Wordsbylength/ITA/Tenletters.txt");
        else if(length == 11) Candidatefile.open("Resources/Wordsbylength/ITA/Elevenletters.txt");
        else if(length == 12) Candidatefile.open("Resources/Wordsbylength/ITA/Tweleveletters.txt");
        else if(length == 13) Candidatefile.open("Resources/Wordsbylength/ITA/Thirteenletters.txt");
        else if(length == 14) Candidatefile.open("Resources/Wordsbylength/ITA/Fourteenletters.txt");
        else if(length == 15) Candidatefile.open("Resources/Wordsbylength/ITA/Fifteenletters.txt");
    }
    
    for(; getline(Candidatefile, candidate) ;){
        
        //Evaluation: candidates are examined, if one reaches the required score, it's chosen to replace the original word.
        int clength = (int) candidate.length();
        int wlength = (int) word.length();
        int maxl = (clength > wlength) ? clength : wlength;
        
        //Rule 1: f the candidate is too different from the word, it's skipped.
        int top_disparities = countDisparities(word, candidate, 0, maxl);
        int bot_disparities = countDisparities(reverse(word, wlength), reverse(candidate, clength), 0, maxl);
        if((top_disparities > wlength / 3 || top_disparities > 2) && (bot_disparities > wlength / 3 || bot_disparities > 2)) continue;
        
        //Rule 2 (word is longer): if the candidate equals the word apart for his initial or final character it's considered correct.
        //Useful with OCR-generated input.
        if(clength == wlength - 1 && wlength > 2 && (top_disparities == 1 || bot_disparities == 1)){
            std::string buffer1 = word;
            std::string buffer2 = word;
            buffer1.erase(0, 1);
            buffer2.erase(buffer2.length()-1, 1);
            if(buffer1 == candidate || buffer2 == candidate){
                result = candidate;
                break;
            }
        }
        
        //Rule 3 (candidate is longer): if the candidate equals the word apart for a doubled consonant it's considered correct.
        //Useful with human-generated input in most languages.
        std::string str = "";
        if(language >= 0 && language <= 1 && wlength == clength - 1){
            std::string buffer = word;
            for(int i=0; i<wlength; i++){
                if(buffer[i] > 96 && buffer[i] < 123 && buffer[i] != 'a' && buffer[i] != 'e' && buffer[i] != 'i' && buffer[i] != 'o' &&
                   buffer[i] != 'u' && buffer[i] != 'y' && i != 0 && i != clength - 1 && i != wlength - 1){
                    str += word[i];
                    buffer.insert(i, str);
                    if(buffer == candidate){
                        result = candidate;
                        break;
                    }
                    else str = "";
                }
            }
            
            if(str != "") break;
        }
    }
    
    if(result == "\0"){
        Candidatefile.clear();
        Candidatefile.seekg(0);
        int score = 0;
    
        //Second phase of research is entered if all precedent rule have failed.
        for(; getline(Candidatefile, candidate) ;){
            
            int clength = (int) candidate.length();
            int wlength = (int) word.length();
            int maxl = (clength > wlength) ? clength : wlength;
            int top_disparities = countDisparities(word, candidate, 0, maxl);
            int bot_disparities = countDisparities(reverse(word, wlength), reverse(candidate, clength), 0, maxl);
            if((top_disparities > wlength / 3 || top_disparities > 2) && (bot_disparities > wlength / 3 || bot_disparities > 2)) continue;
            
            int streak = 0, streak_default = 0;
            
            //Setup for rule 4: if more than half of the candidate equals the word, streak values is boosted.
            if((top_disparities < maxl / 2 || top_disparities <= 1) || (bot_disparities < maxl / 2 || bot_disparities <= 1)){
                streak += 2;
                streak_default = 2;
            }
            
            //Rule 4: characters making up candidate are examined separately, streak value rewards candidates wich present several correct characters in a row.
            for(int i=0; i < clength; i++){
                if(candidate[i] == word[i]){
                    score += 300 + clength * 50;
                    streak++;
                    score *= streak;
                }
                else if(candidate[i] == word[i+1] || candidate[i] == word[i-1]){
                    score += 200 + clength * 50;
                    //streak++;
                    //score *= streak;
                }
                else streak = streak_default;
            }
            
            if(score >= wlength * wlength * 2500){
                result = candidate;
                break;
            }
            
            score = 0;
        }
    }
    
    Candidatefile.close();
    return result;
}

//Counts disparities between 2 words.
int countDisparities(std::string word1, std::string word2, int i, int maxl){
    if(i > maxl - 1) return 0;
    if(word1[i] != word2[i]) return 1 + countDisparities(word1, word2, i+1, maxl);
    return countDisparities(word1, word2, i+1, maxl);
}

//Flips a string.
std::string reverse(std::string word, int length){
    if(length == 0) return "\0";
    return word[length-1] + reverse(word, length-1);
}
