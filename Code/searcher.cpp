#include "header.h"

int BinarySearch(std::string key, std::vector<std::vector<std::string>>& Dictionary, int left, int right, int initial){
    if (left > right) return -1;
    
    int mid = left + (right - left) / 2;
    if(Dictionary[initial][mid] == key) return mid;
    
    else if(Dictionary[initial][mid] < key) return BinarySearch(key, Dictionary, mid + 1, right, initial);
    else return BinarySearch(key, Dictionary, left, mid - 1, initial);
}

int BinarySearch(std::string key, std::vector<std::string>& Vector, int left, int right){
    if (left > right) return -1;
    
    int mid = left + (right - left) / 2;
    if(Vector[mid] == key) return mid;
    else if(Vector[mid] < key) return BinarySearch(key, Vector, mid + 1, right);
    else return BinarySearch(key, Vector, left, mid - 1);
}
