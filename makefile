all: EnsembleClassifier.out
	 make LinearClassifier
	 make VoterClassifier
	 
EnsembleClassifier.out: main.o ensembleClassifier.o
					    g++ main.o ensembleClassifier.o -o EnsembleClassifier.out

main.o: main.cpp
		g++ -std=c++11 -c main.cpp

ensembleClassifier.o: ensembleClassifier.cpp
					  g++ -std=c++11 -c ensembleClassifier.cpp


LinearClassifier: linearMain.o linearClassifier.o
				  g++ linearMain.o linearClassifier.o -o LinearClassifier

linearMain.o: linearMain.cpp
			  g++ -std=c++11 -c linearMain.cpp	

linearClassifier.o: linearClassifier.cpp
					g++ -std=c++11 -c linearClassifier.cpp


VoterClassifier: voterMain.o voterClassifier.o
				  g++ voterMain.o voterClassifier.o -o VoterClassifier

voterMain.o: voterMain.cpp
			  g++ -std=c++11 -c voterMain.cpp	

voterClassifier.o: voterClassifier.cpp
					g++ -std=c++11 -c voterClassifier.cpp

clean:  rm *.o