//
// Created by kirill on 12.12.2020.
//

#include <string>

#include <iostream>


#include "csvreader.h"
#include "classifier.h"
#include "datapreprocessor.h"

using namespace std;
using namespace dlib;

int main(int argc, char *argv[]) {
    if (argc < 3)
        return -1;

    int cluster_num = std::atoi(argv[1]);
    std::string file_name = argv[2];


    // read
    CSVReader reader;
    std::string samples_file_name = "dataset.csv";
    if (argc >= 4)
        samples_file_name = argv[3];
    auto samples = reader.get_samples(samples_file_name);


    DataPreProcessor dpp(file_name);
    dpp.calculate_normalization_values(samples);
    dpp.dump_normalization_values();
    dpp.load_normalization_values();
    auto normalized_samples = dpp.normalize_samples(samples);

    Classifier cl(file_name);
    cl.create_clusters(normalized_samples, cluster_num);
    cout << "dump clusters: " << cl.dump_cluster() << endl;



    int i = 0;
    for (auto sample: normalized_samples)
    {
        i++;
        if (i>10)
            break;
        cl.get_close_data(sample);
    }

}