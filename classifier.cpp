//
// Created by kirill on 13.12.2020.
//

#include "classifier.h"

void Classifier::create_clusters(std::vector<userData> & samples, int cnum)
{
    std::vector<userData> initial_centers;
//    kcentroid<kernel_type> kc(kernel_type(0.1),0.01, 8)
    kcentroid<kernelType> kc(kernelType(0.1),0.01, 8);
    // Now we make an instance of the kkmeans object and tell it to use kcentroid objects
    // that are configured with the parameters from the kc object we defined above.

    pKmean_cluster = std::make_shared<kkmeans<kernelType>>(kc);
    pKmean_cluster->set_number_of_centers(cnum);
    pick_initial_centers(cnum, initial_centers, samples, pKmean_cluster->get_kernel());
    pKmean_cluster->train(samples, initial_centers);

    for (int i=0;i<cnum;i++)
    {
        auto centroid = pKmean_cluster->get_kcentroid(i);
    }


}


bool Classifier::dump_cluster()
{
    kcentroid<kernelType> kc(kernelType(0.1),0.01, 8);
    // Now we make an instance of the kkmeans object and tell it to use kcentroid objects
    // that are configured with the parameters from the kc object we defined above.

    auto newCluster = std::make_shared<kkmeans<kernelType>>(kc);
    if (pKmean_cluster != nullptr)
    {
        string classificator_file = _file_name + ".cls";
        std::ofstream outClass(classificator_file, ofstream::out);
        if (outClass)
            serialize(*pKmean_cluster, outClass);
        outClass.close();
        return true;
    }
    return false;
}


bool Classifier::load_cluster()
{

    kcentroid<kernelType> kc(kernelType(0.1),0.01, 8);
    pKmean_cluster = std::make_shared<kkmeans<kernelType>>(kc);

    try
    {
        string classificator_file = _file_name + ".cls";
        std::ifstream outClass(classificator_file, ifstream::in);
        if (outClass)
            deserialize(*pKmean_cluster, outClass);
        outClass.close();
        return true;
    }
    catch (exception & e)
    {
        cout << "Error during load " << e.what() << endl;
        return false;
    }

}


int Classifier::classify(userData & sample)
{
    int result_class = -1;
    if (pKmean_cluster != nullptr)
    {
        result_class = (*pKmean_cluster)(sample);
    }
    else
    {
        std::cout << "not loaded" << endl;
    }
    return result_class;
}