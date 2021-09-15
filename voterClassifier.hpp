#ifndef VOTERCLASSIFIER
#include <vector>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>

class voterClassifier
{
    private:
        int numOfLinearClassifier;
        std::vector<std::vector<int> > results;
        std::vector<std::string> classifiersFile;
        std::vector<int> finalClasses;
        std::string dataIn;
        int numOfClasses;
        int numOfSamples;
         
    public:
        void setNumOfClassifiers(int n);
        void getResultFromLinearClassifier();
        void readDatas();
        void setFinalClasses();
        std::vector<int> splitByChar(std::string data, char c);
        void sendFinalClasseToEnsemble();
        void setNumOfClasses();
};

#endif