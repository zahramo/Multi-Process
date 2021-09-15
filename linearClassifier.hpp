#ifndef LINEARCLASSIFIER
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

class linearClassifier
{
    private:
        std::string weightVectorPath;
        std::string dataSetPath;
        std::string outFileName;
        std::vector<double> widths;
        std::vector<double> lengths;
        std::vector<double> betha0;
        std::vector<double> betha1;
        std::vector<double> bias;
        std::vector<int> classes;
        int classifierId;
    public:
        void setPaths(std::string path);
        void getDataFromCSV();
        void getWeightFromCSV();
        std::vector<std::string> splitByChar(std::string s, char c);
        void classify();
        double score(int i, int k);
        void setClassifierId();
        void writeClassesInFile();
        void sendResultToVoter();
};

#endif