//
// Created by kirill on 12.12.2020.
//

#include <string>

#include "csvreader.h"
#include "classifier.h"
#include "datapreprocessor.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;

    std::string file_name = argv[1];

    // read
    CSVReader reader;

    DataPreProcessor dpp(file_name);
    dpp.load_normalization_values();

    Classifier cl(file_name);
    cout << "load cluster" << endl;
    cl.load_cluster();
    cout << "loaded cluster" << endl;

    std::string line;
    userData sample;
    while(cin)
    {
        std::getline(cin,line);

        if (!reader.get_sample(sample, line))
        {
            cout << "Wrong input data" << endl;
            continue;
        }

        auto normalized_sample = dpp.normalize_sample(sample);
        int sample_class = cl.classify(normalized_sample);
        cout << "recognized cluster: " << sample_class << endl;
    }

}