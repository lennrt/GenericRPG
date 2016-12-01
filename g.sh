g++ -std=c++0x entity.cpp -c -o entity.o
g++ -std=c++0x monster.cpp -c -o monster.o
g++ -std=c++0x character.cpp -c -o character.o
g++ -std=c++0x tile.cpp -c -o tile.o
g++ -std=c++0x map.cpp -c -o map.o
g++ -std=c++0x spell.cpp -c -o spell.o
g++ -std=c++0x item.cpp -c -o item.o
g++ -std=c++0x mailbox.cpp -c -o mailbox.o
g++ -std=c++0x timetable.cpp -c -o timetable.o
g++ -std=c++0x driver.cpp -o driver mailbox.o timetable.o entity.o monster.o character.o tile.o spell.o item.o map.o -lcrypt -lrt -lpthread
chmod 0755 driver

g++ -std=c++0x accman.cpp -o accman.cgi -lcrypt -lrt -lpthread
chmod +s accman.cgi
rm *.o
