OPTION=-Wall -Werror -ansi -pedantic -O2

oList=backgroundMusic.o fallingBlock.o laserTurret.o ressource.o block.o finishBlock.o levelListLoader.o sauvegarde.o cloneur.o forme.o main.o collision.o glass.o movableBlock.o teleporter.o staticMiroir.o creeper.o hero.o movingBlock.o decor.o invisibleBlock.o niveau.o electricity.o lang.o particule.o arrow.o arrowLauncher.o arrowLauncherDetector.o pincette.o textpopup.o special.o detector.o pic.o accelerateur.o bouton.o

SFML=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: application
	./application
	
application: $(oList) $(SFML)
	g++ -o $@ $^ $(OPTION) -Wl,-rpath,./lib

%.o: %.cpp
	g++ -c $^ $(OPTION)
	
clean:
	rm *.o
	rm *~


