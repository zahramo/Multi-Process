#include "voterClassifier.hpp"

using namespace std;

void voterClassifier::setNumOfClassifiers(int n)
{
    numOfLinearClassifier = n;
}


void voterClassifier::getResultFromLinearClassifier()
{
    string fileName;
    char message[2000];
    for(int i=0; i<numOfLinearClassifier; i++)
    {
        vector<int> temp;
        fileName = "linearVoter" + to_string(i);
        int f = open(fileName.c_str(), O_RDONLY);
        read(f, message, 5000);
        temp = splitByChar(message, ',');
        results.push_back(temp);
        numOfSamples = temp.size();
        close(f);
    }
}

void voterClassifier::readDatas()
{
    for(int i=0; i<numOfLinearClassifier; i++)
    {
        vector<int> temp;
        string namev = "classifier_out_"+ to_string(i);
        fstream f;
        f.open(namev, ios::in);
        string data;
        while(f >> data)
        {
            temp.push_back(stoi(data));
        }
        results.push_back(temp);
        numOfSamples = temp.size();
        f.close();

    }
}

void voterClassifier::setFinalClasses()
{
    int ficl[numOfSamples];
    for(int i=0; i<numOfSamples; i++)
    {
        vector<int> row;
        for(int j=0; j<numOfLinearClassifier; j++)
        {
            row.push_back(results[j][i]);
        }
        int k = 0;
        int finalClass;
        int maxCount = 0;
        int curCount =0;
        while(k < numOfClasses)
         {
            curCount = count(row.begin(), row.end(), k);
            if(curCount > maxCount)
            {
                maxCount = curCount;
                finalClass = k;
            }
             k++;
         }
         ficl[i] = finalClass;
    }
    for(int i=0; i<numOfSamples;i++)
    {
        finalClasses.push_back(ficl[i]);
    }
}

vector<int> voterClassifier::splitByChar(string data, char c)
{
    vector<int> result;
    string part;
    for(int i=0; i<data.length(); i++)
    {
        if(data[i] == '$') break;
        if(data[i] != c)
        {
            part = part + data[i];
        }
        else
        {
            if(part.length() > 0) 
            {
                result.push_back(stoi(part));
                part = "";
            }
        }
    }
    if (part != "")
    {
        result.push_back(stoi(part));
    }
    return result;
}

void voterClassifier::sendFinalClasseToEnsemble()
{
    int f = open("ensembleVoter", O_RDWR);
    string message;
    for(int i=0; i<finalClasses.size(); i++)
    {
        message = message + to_string(finalClasses[i]) + ',';
    }
    message[message.length()] = '\n';
    write(f, message.c_str(), message.length());
    close(f);
}

void voterClassifier::setNumOfClasses()
{
    int maxClass = 0;
    for(int i=0; i<numOfSamples; i++)
    {
        for(int j=0; j<numOfLinearClassifier; j++)
        {
            if(results[j][i] > maxClass)
            {
                maxClass = results[j][i];
            }
        }
    }
    numOfClasses = maxClass + 1;
}