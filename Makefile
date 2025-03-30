CXX=g++
CXXFLAGS=-std=c++11

jeu: *.cpp
	@$(CXX) $(CXXFLAGS) *.cpp -o jeu
	@echo -e '**** COMPILATION REUSSIE **** \n'
	@echo -e '********* EXECUTION ********* \n'
	@./jeu
	@echo -e '\n \n ******* FIN EXECUTION *******'
	@rm -f ./jeu

clean:
	rm -f *.o *~ core jeu




