#include "ensembleClassifier.hpp"

using namespace std;

void ensembleClassifier::setPaths(std::string vPath,std::string wPath)
{
    validationPath = vPath;
    weightVectorsPath = wPath;
    dataSetPath = validationPath + "/" + "dataset.csv"; 
    labelPath = validationPath + "/" + "labels.csv";
}

void ensembleClassifier::setClassifiersFile()
{
    DIR *directory;
    struct dirent *file;
    if ((directory = opendir(weightVectorsPath.c_str())) != NULL) 
    {
        while ((file = readdir (directory)) != NULL) 
        {
            if(strcmp("." , file->d_name) && strcmp(".." , file->d_name))
            {
                classifiersFile.push_back(file->d_name);
            }
        }
        closedir (directory);
    }
    else 
    {
        perror ("Can Not Open Directory.\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<classifiersFile.size(); i++)
    {
        classifiersFile[i] = "classifier_" + to_string(i) + ".csv";
    } 
}

void ensembleClassifier::setNumOfLinearClassifier()
{
    numOfLinearClassifier = classifiersFile.size();
}

void ensembleClassifier::makeNamedPipe()
{
   // int fd = open("ensembleVoter", O_CREAT, S_IRWXU);
   // close(fd);
    string fileName;
    for(int i = 0; i<numOfLinearClassifier; i++)
    {   
        fileName = "linearVoter" + to_string(i);
        int fd = open(fileName.c_str(), O_CREAT, S_IRWXU);
        close(fd);
        mkfifo(fileName.c_str(),0666);
    }
    mkfifo("ensembleVoter",0666);
}

void ensembleClassifier::makeLinearClassifiers()
{
    int p[numOfLinearClassifier][2];

    for (int i = 0; i < numOfLinearClassifier; i++)
    {
        if (pipe(p[i])== -1)
        {
            perror("Using Pipe Failed.\n");
            exit(EXIT_FAILURE);
        }
         
        if(fork() > 0)
        {
            close(p[i][0]);
            string message = weightVectorsPath + "/" + classifiersFile[i] + "$" + dataSetPath;
            write(p[i][1], message.c_str(), message.length());
            close(p[i][1]);
        }
        else
        {
            close(p[i][1]);
            char message[500];
            read(p[i][0], message, 500);
            close(p[i][0]);
            execl("/Users/zahra/Desktop/zahra/university/term5/OS/project2/LinearClassifier","LinearClassifier",message, NULL);
        }
    }
}

void ensembleClassifier::makeVoterClassifier()
{
    int p[1][2];
    if (pipe(p[0])== -1)
    {
        perror("Using Pipe Failed.\n");
        exit(EXIT_FAILURE);
    }
    if(fork() > 0)
    {
        close(p[0][0]);
        string message = to_string(classifiersFile.size());
        write(p[0][1], message.c_str(), message.length());
        close(p[0][1]);
    }
    else
    {
        close(p[0][1]);
        char message[10];
        read(p[0][0], message, 10);
        message[strlen(message)] = '\0';
        close(p[0][0]);
        execl("/Users/zahra/Desktop/zahra/university/term5/OS/project2/VoterClassifier","VoterClassifier",message,NULL);
    }
}

void ensembleClassifier::waitForChilds()
{
    for (int i = 0; i < numOfLinearClassifier+1  ; i++)
    {
        wait(NULL);
    }
}

void ensembleClassifier::getFinalClassesFromVoter()
{
    fstream f;
    f.open("ensembleVoter", ios::in);
    string message;
    f >> message;
    f.close();
    finalClasses = splitByChar(message, ',');
}

vector<int> ensembleClassifier::splitByChar(string data, char c)
{
    vector<int> result;
    string part;
    for(int i=0; i<data.length(); i++)
    {
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

void ensembleClassifier::getLabelsFromCSV()
{
    fstream f;
    f.open(labelPath, ios::in);
    string data;
    f >> data;
    f >> data;
    while(f >> data)
    {
       labels.push_back(stoi(data));
    }
    f.close();
}

void ensembleClassifier::calcuteAccuracy()
{
    float correctClass = 0;
    float allClass = finalClasses.size();
    for(int i=0; i<allClass; i++)
    {
        if(finalClasses[i] == labels[i])
        {
            correctClass++;
        }
    }
    accuracy = (correctClass/allClass)*100;
    printf("Accuracy: %.2f",accuracy);
    cout<<"%\n";
}