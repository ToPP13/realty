//
// Created by kirill on 13.12.2020.
//

#pragma once

#include "user_data.h"

typedef radial_basis_kernel<userData> kernelType;


class Classifier{
public:
    Classifier(std::string file_name): _file_name(file_name){pKmean_cluster = nullptr;};

    void create_clusters(std::vector<userData> & samples, int cnum);
    bool dump_cluster();
    bool load_cluster();
    std::vector<userData> get_close_data(userData & sample);
private:
    std::string _file_name;
    std::shared_ptr<kkmeans<kernelType> > pKmean_cluster;
};

