#include "ensembleClassifier.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    string vPath, wPath;
    if(argc < 3)
    {
        perror("Not Enough Arguments.\n");
        exit(EXIT_FAILURE);
    }
    vPath = argv[1];
    wPath = argv[2];
    ensembleClassifier ensemble;
    ensemble.setPaths(vPath, wPath); 
    ensemble.getLabelsFromCSV();
    ensemble.setClassifiersFile(); 
    ensemble.setNumOfLinearClassifier();
    ensemble.makeNamedPipe();
    ensemble.makeLinearClassifiers();
    ensemble.waitForChilds();
    ensemble.makeVoterClassifier();
    ensemble.getFinalClassesFromVoter();
    wait(NULL);
    ensemble.calcuteAccuracy();    
}
