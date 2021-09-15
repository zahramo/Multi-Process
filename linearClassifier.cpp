#include "linearClassifier.hpp"

using namespace std;
void linearClassifier::setPaths(string path)
{
    vector<string> result =splitByChar(path, '$');
    weightVectorPath = result[0];
    dataSetPath = result[1];
   // dataSetPath.pop_back();
   // dataSetPath.pop_back();
}

vector<string> linearClassifier::splitByChar(string s, char c)
{
    vector<string> result;
    string s1, s2;
    int flag = -1;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == c && flag == -1)
        {
            flag = 0;
        }
        if(flag == -1)
        {
            s1 = s1 + s[i];
        }
        else if(flag == 0)
        {
            flag = 1;
        }
        else if(flag == 1)
        {
            s2 = s2 + s[i];
        }
    }
    result.push_back(s1);
    result.push_back(s2);
    return result;
}

void linearClassifier::getDataFromCSV()
{
    fstream f;
    f.open(dataSetPath, ios::in);
    string data;
    f >> data;
    while(f >> data)
    {
        vector<string> result;
        result = splitByChar(data, ',');
        lengths.push_back(stod(result[0]));
        widths.push_back(stod(result[1]));
    }
    f.close();
}

void linearClassifier::getWeightFromCSV()
{
    fstream f;
    f.open(weightVectorPath, ios::in);
    string data;
    f >> data;
    while(f >> data)
    {
        vector<string> result;
        result = splitByChar(data, ',');
        betha0.push_back(stod(result[0]));
        result = splitByChar(result[1], ',');
        betha1.push_back(stod(result[0]));
        bias.push_back(stod(result[1]));
    }
    f.close();
}

void linearClassifier::classify()
{
    double maxScore;
    int bestClass;
    for(int i=0; i<lengths.size(); i++)
    {
        maxScore = score(i,0);
        bestClass = 0;

        for(int k=1; k<betha1.size(); k++)
        {
            double curScore = score(i, k);
            if(curScore > maxScore)
            {
                maxScore = curScore;
                bestClass = k;
            }
        }
        classes.push_back(bestClass);
    }
}

double linearClassifier::score(int i, int k)
{
    return betha0[k]*lengths[i] + betha1[k]*widths[i] + bias[k];
}

void linearClassifier::setClassifierId()
{
    vector<string> result;
    result = splitByChar(weightVectorPath, '/');
    result = splitByChar(result[1], '/');
    result = splitByChar(result[1], '_');
    classifierId = stoi(result[1]); 
}

void linearClassifier::writeClassesInFile()
{
    string data;
    for(int i=0; i<classes.size(); i++)
    {
        data = data + to_string(classes[i]) + "\n";
    }
    outFileName = "classifier_out_" + to_string(classifierId);
    ofstream outFile(outFileName);
    outFile<< data;
    outFile.close();
}


void linearClassifier::sendResultToVoter()
{
    string fileName = "linearVoter" + to_string(classifierId);
    
    int f = open(fileName.c_str(), O_RDWR);
    string message;
    for(int i=0; i<classes.size(); i++)
    {
        message = message + to_string(classes[i]) + ',';
    }
    message[message.length()-1] = '$';
    write(f, message.c_str(), message.length());
    close(f);
}