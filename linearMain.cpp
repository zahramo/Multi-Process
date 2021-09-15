#include "linearClassifier.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        perror("Not Enough Arguments.\n");
        exit(EXIT_FAILURE);
    }
    string path;
    path = argv[1];
    linearClassifier linear;
    linear.setPaths(path);
    linear.getDataFromCSV();
    linear.getWeightFromCSV();
    linear.classify();
    linear.setClassifierId();
    linear.sendResultToVoter();
}