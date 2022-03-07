#include "Header.h"

void Separator(std::vector<std::string>& Text, std::string line, int *corrections){
    int csum = 0; std::string filler = "";
    
    //Recognise ENTER KEYS.
    if(line.length() == 0) {
        FullStop(Text, (int) Text.size()-1, corrections);
        Text.emplace_back("\n\n");
    }
    
    //Add a space at the end of every line in order to recognise the last word.
    line+=' ';
    
    for(int i=0; i<line.length()+1; i++){
        
        /*
        //Unite the words that in the original text were separated because of a new paragraph. Only useful with certain kinds of OCR-generated input.
        if(line[i]=='-' && line[i+1]==' ' && line[i-1]!=' '){
            line.erase(i, 2);
            (*corrections)++;
        }
        */

        //If 2 strong punctuation marks are found together, replace one with a space.
        if(((line[i] == ';' || line[i] == ',' || line[i] == '!' || line[i] == '?' || line[i] == ':') &&
            (line[i+1] == ';' || line[i+1] == ',' || line[i+1] == '!' || line[i+1] == '?' || line[i+1] == ':')) ||
            (line[i] == '.' && line[i+1] == '.' && line[i+2] != '.' && line[i-1] != '.')){
            line[i+1]=' '; (*corrections)++;
        }

        //Add spaces in between punctuation marks.
        //UNICODE value of strong punctuation marks: full stop(\u002E), comma(\u002C), semicolon(\u003B),
        //right parenthesis(\u0029), exclamation mark(\u0021), question mark(\u003F), colon(\u003A), quotation mark(\u0022).
        if((line[i] == '.' || line[i] == ',' || line[i] == ';' || line[i] == ')' || line[i] == '!' || line[i] == '?' || line[i] == ':' || line[i] == '"') &&
           line[i+1] != ' '){
            switch(line[i]){
                case '.':
                    csum = 2;
                    break;
                case ',':
                    csum = 2;
                    break;
                case ';':
                    csum = 2;
                    break;
                case ')':
                    csum = 2;
                    break;
                case '!':
                    csum = 2;
                    break;
                case '?':
                    csum = 2;
                    break;
                case ':':
                    csum = 2;
                    break;
                case '"':
                    csum += 1;
                    break;
                default:
                    break;
            }
            
            //CASE 1: No need to add a space.
            if(((line[i] == '.' && line[i+1] == '.' && line[i+2] == '.') || (line[i-1] == '.' && line[i] == '.' && line[i+1] == '.') ||
                (line[i-2] == '.' && line[i-1] == '.' && line[i] == '.')) || (line[i] == '"' && (line[i+1] == '.' || line[i+1] == ';' ||
                line[i+1] == ',' || line[i+1] == ')' || line[i+1] == '!' || line[i+1] == '?' || line[i+1] == ':') && line[i+2] == ' ') ||
                (line[i+1] == ' ' && (line[i] == '.' || line[i] == ';' || line[i] == ',' || line[i] == ')' || line[i] == '!' || line[i] == '?' ||
                line[i] == ':')) || (line[i] == ')' && (line[i+1] == ' ' || line[i+2] == ' ')) ||
                ((line[i+1] > 47) && (line[i+1] < 58))) {csum = 0;}
            
            //CASE 2: Need to add a space.
            else if(csum == 2 && line[i+1] != ' '){
                filler += line[i];
                Text.push_back(filler);
                line.erase(i, 1);
                (*corrections)++;
                filler = "";
                csum = 0;
            }
        }
        
        //Apostrophe(\u0027).
        //Fill the array with the single words.
        if(line[i] != ' ' && csum != 2) filler += line[i];
        if(line[i+1] == ' '|| line[i] == '\'' || line[i] == '\u0027') {Text.push_back(filler); filler = "";}
    }
}
