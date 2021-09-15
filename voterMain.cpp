#include "voterClassifier.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    voterClassifier voter;
    voter.setNumOfClassifiers(stoi(argv[1]));
    voter.getResultFromLinearClassifier();
    voter.setNumOfClasses();
    voter.setFinalClasses();
    voter.sendFinalClasseToEnsemble();
}