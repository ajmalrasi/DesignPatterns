/**
 * *****************************************
 * @brief seperation of concerns, a class can have only one
 * responsibility, seperate persistance code to another class
 * @author Ajmal Rasi - mail@ajmalrasi.com
 * @version 0.1
 * @date 2020-01-23
 * *****************************************
 * 
 */

#include<iostream>
#include<fstream>
#include<vector>
#include<boost/lexical_cast.hpp>

/**
 * @brief Journal class
 * 
 */
struct Journal {
    std::string title;
    std::vector<std::string> entries;

    Journal(const std::string &title)
        :title{title}{
        }
    
    /**
     * @brief add entry to Journal
     * 
     * @param entry string
     */
    void add_entry(const std::string &entry) {
        static int count = 1;
        entries.push_back(boost::lexical_cast<std::string>(count++) + " : "+entry);
    }
};

/**
 * @brief Save Items to disk 
 * 
 */
struct PersistanceManager{
    static void save(const Journal &j, const std::string &filename) {
        std::ofstream ofs(filename);
        for (auto &e: j.entries) {
            ofs << e << std::endl;
        }
    }
};


int main() {

    Journal journal {"Dear Diary"};
    journal.add_entry("I ate a bug");
    journal.add_entry("i crited today");

    PersistanceManager pm;
    pm.save(journal, "data/diary.txt");

    return 0;
}
