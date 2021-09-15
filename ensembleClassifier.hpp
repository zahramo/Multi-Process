#ifndef ENSEMBLECLASSIFIER
#include <iostream>
#include <dirent.h>
#include <vector>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>

class ensembleClassifier
{
    private:
        std::string validationPath;
        std::string weightVectorsPath;
        std::string dataSetPath;
        std::string labelPath;
        std::vector<std::string> classifiersFile;
        int numOfLinearClassifier;
        std::vector<int> finalClasses;
        std::vector<int> labels;
        float accuracy;

    public:
        void setPaths(std::string vPath,std::string wPath);
        void setClassifiersFile();
        void setNumOfLinearClassifier();
        void makeNamedPipe();
        void makeLinearClassifiers();
        void makeVoterClassifier();
        void waitForChilds();
        void getFinalClassesFromVoter();
        std::vector<int> splitByChar(std::string data, char c);
        void getLabelsFromCSV();
        void calcuteAccuracy();
};

#endif