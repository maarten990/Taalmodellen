#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>

#include "languagemodel.h"
#include "relative_frequencies.h"

using namespace std;


string viterbi(string obs, LanguageModel &lang_model,
               Relative_frequencies &task_model)
{
    // the collection of possible states is equal to the alphabet
    vector<string> states = LanguageModel::alphabet;

    // V and path are the T1 and T2 matrices from wikipedia's pseudocode
    vector< map<string, double> > V = { map<string, double>() };
    map<string, vector<string> > path;

    // initialization (t = 0)
    for (string &state : states) {
        V[0][state] = task_model.compute_lettermapping(state, obs.substr(0, 1));
        path[state].push_back(state);
    }

    // main loop for t > 0
    map<string, vector<string> > newpath;
    for (int t = 1; t < obs.size(); ++t) {
        V.push_back(map<string, double>());
        newpath.clear();

        for (string &y : states) {
            double temp_prob = 0;
            double max_prob = 0;
            string max_state;

            for (string &y0 : states) {
                temp_prob = (V[t-1][y0] *
                             lang_model.get_probability(y0, y) *
                             task_model.compute_lettermapping(y0, obs.substr(t, 1)));
                //cout << "V[t-1][y0]: " << V[t-1][y0] << endl;
                //cout << "lang_model.get_probability(y0, y): " << lang_model.get_probability(y0, y) << endl;
                //cout << "task_model.compute_lettermapping(y0, obs.substr(t, 1)): " << task_model.compute_lettermapping(y0, obs.substr(t, 1)) << endl << endl;
                if (temp_prob > max_prob) {
                    max_prob = temp_prob;
                    max_state = y0;
                }
            }

            V[t][y] = max_prob;
            newpath[y] = path[max_state];
            (--newpath.end())->second.push_back(y);
        }

        path = newpath;
    }

    // now we look for the most likely path
    double temp_prob = 0;
    double max_prob = 0;
    string max_state;

    for (string &y : states) {
        temp_prob = V[obs.size() - 1][y];
        if (temp_prob > max_prob) {
            max_prob = temp_prob;
            max_state = y;
        }
    }

    stringstream output_str;
    vector<string> debug = path[max_state];
    for (string &letter : path[max_state])
        output_str << letter;

    return output_str.str();
}
