//Project UID db1f506d06d84ab787baf250c265e24e
#include <iostream>
#include <string>
#include<map>
#include<set>
#include<fstream>
#include<sstream>
#include"csvstream.h"
#include<cmath>
using namespace std;
class Classifier{
public:
    void update (set<string> &words, string label){
        for (auto elt: words){
            numPostsWithWord[elt] += 1;
            vocab[elt] += 1;
            specWordspecLabel[label][elt] += 1;
        }
    }
    void print_log_prior_debug(){
        for (auto elt: labels){
            cout << "  " << elt.first << ", " << elt.second << " examples, log-prior = ";
            double log_prior = (double) elt.second / (double) totalPosts;
            log_prior = log(log_prior);
            cout << log_prior << endl;
        }
    }
    void print_log_like_debug(){
        for (auto tag: specWordspecLabel){
            for (auto content: specWordspecLabel[tag.first]){
                double log_like = 0;
                cout <<  "  " << tag.first << ":" << content.first;
                cout << ", count = " << content.second << ", log-likelihood = ";
                if (labels[tag.first] == 0){
                    log_like = (double) numPostsWithWord[content.first]
                    / (double) totalPosts;
                    log_like = log(log_like);
                    cout << log_like << endl;
                    continue;
                }
                else if (numPostsWithWord[content.first] == 0){
                    log_like = 1/ (double) totalPosts;
                    cout << log_like << endl;
                    continue;
                }
                log_like = log((double) content.second/ (double) labels[tag.first]);
                cout << log_like << endl;
            }
        }
    }
    void debug(csvstream &is){
        cout.precision(3);
        cout << "training data:" << endl;
        set<string> words;
        map<string, string> currRow;
        int totalVocab = 0;
        // Read word by word from the stringstream and insert into the set
        while (is >> currRow) {
            cout << "  label = " << currRow["tag"] << ", ";
            cout << "content = " << currRow["content"] << endl;
            words = unique_words(currRow["content"]);
            labels[currRow["tag"]] += 1;
            update(words, currRow["tag"]);
            totalPosts += 1;
            currRow.clear();
        }
        for (auto elt: vocab){
            totalVocab += 1;
        }
        cout << "trained on " << totalPosts << " examples" << endl;
        cout << "vocabulary size = " << totalVocab << endl << endl;
        cout << "classes:" << endl;
        print_log_prior_debug();
        cout << "classifier parameters:" << endl;
        print_log_like_debug();
        return;
    }
    void no_debug(csvstream &is){
        cout.precision(3);
        set<string> words;
        map<string, string> currRow;
        int totalVocab = 0;
        // Read word by word from the stringstream and insert into the set
        while (is >> currRow) {
            words = unique_words(currRow["content"]);
            labels[currRow["tag"]] += 1;
            update(words, currRow["tag"]);
            totalPosts += 1;
            currRow.clear();
        }
        for (auto elt: vocab){
            totalVocab += 1;
        }
        cout << "trained on " << totalPosts << " examples" << endl;
        return;
    }
    void predict(csvstream &is2){
        map<string, string> currRow;
        cout << endl << "test data:" << endl;
        map<string, double> log_probs;
        int predicted = 0;
        int total_test = 0;
        set<string> words_test;
        while (is2 >> currRow){
            words_test = unique_words(currRow["content"]);
            for (auto elt: labels){
                log_probs[elt.first] += log_prob(words_test, elt.first);
            }
            double max = -INFINITY;
            string max_label;
            for (auto elt: log_probs){
                if (max < elt.second){
                    max = elt.second;
                    max_label = elt.first;
                }
            }
            cout << "  correct = " << currRow["tag"] << ", predicted = " << max_label
            << ", log-probability score = " << max << endl;
            cout << "  content = " << currRow["content"] << endl << endl;
            if (max_label == currRow["tag"]){
                predicted += 1;
            }
            total_test += 1;
            currRow.clear();
            log_probs.clear();
        }
        cout << "performance: " << predicted
        << " / " << total_test
        << " posts predicted correctly" << endl;
    }
    double log_prob(set<string> words, string label){
        double sum = 0;
        double log_like = 0;
        double log_prior = (double) labels[label] / (double) totalPosts;
        log_prior = log(log_prior);
        for (auto word: words){
            if (numPostsWithWord[word] == 0){
                log_like = (double) 1 / (double) totalPosts;
                log_like = log(log_like);
                sum += log_like;
                continue;
            }
            else if (specWordspecLabel[label][word] == 0){
                log_like = (double) numPostsWithWord[word]
                / (double) totalPosts;
                log_like = log(log_like);
                sum += log_like;
                continue;
            }
            
            
            log_like = log((double) specWordspecLabel[label][word] / (double) labels[label]);
            sum += log_like;
        }
        return log_prior + sum;
    }
    // EFFECTS: Returns a set containing the unique "words" in the original
    //          string, delimited by whitespace.
    set<string> unique_words(const string &str) {
     istringstream source(str);
     set<string> words;
     string word;

     // Read word by word from the stringstream and insert into the set
     while (source >> word) {
       words.insert(word);
     }
     return words;
    }
private:
    map<string, int> vocab;
    map<string, int> labels;
    int totalPosts = 0;
    map<string, int> numPostsWithWord;
    map<string, map<string, int>> specWordspecLabel;
};

int main (int argc, char **argv) {
//    csvstream is("w14-f15_instructor_student.csv");
//    csvstream is2("w16_instructor_student.csv");
    string debug = "";
    cout.precision(3);
    if (argc != 3){
        if (argc != 4){
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return 1;
        }
        else {
            debug = argv[3];
            if (debug != "--debug"){
                cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
                return 1;
            }
        }
    }
    Classifier test;
    csvstream is(argv[1]);
    csvstream is2(argv[2]);
    if (!is){
        cout << "Error opening file: " << argv[1] << endl;
    }
    else if (!is2){
        cout << "Error opening file: " << argv[2] << endl;
    }
    if (debug == "--debug"){
        test.debug(is);
        test.predict(is2);
    }
    else {
        test.no_debug(is);
        test.predict(is2);
    }
    return 0;
}

