#ifndef RELATIVE_FREQUENCIES_H
#define RELATIVE_FREQUENCIES_H

class Relative_frequencies
{
public:
    Relative_frequencies(std::string corpus_path);

    // The maps used for relative frequency storage
    map<string, double> cipher;
    map<string, double> corpus;
};

#endif // RELATIVE_FREQUENCIES_H
