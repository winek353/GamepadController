
LIBS       = -L/usr/lib/x86_64-linux-gnu -lXtst -lQtGui -lQtCore -lpthread -lX11
INCPATH    = -I Include -I Mock -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4

Objs+=Obj/main.o
Objs+=Obj/JoypadListener.o
Objs+=Obj/JoypadHandler.o
Objs+=Obj/JoypadButton.o
Objs+=Obj/QtJoypadListener.o
Objs+=Obj/PressedOrReleased.o
Objs+=Obj/JoypadAxis.o
Objs+=Obj/SystemController.o

TestObjs+=Obj/tests.o
TestObjs+=Obj/JoypadHandler.o
TestObjs+=Gtest/gtest-all.o
TestObjs+=Gtest/gtest_main.o
TestObjs+=Gtest/gmock-all.o
#TestObjs+=Gtest/gmock_main.o

Obj/%.o: Source/%.cpp
	g++ -o $@ $(INCPATH) -c $^

Obj/%.o: GeneratedSource/%.cpp
	g++ -o $@ $(INCPATH) -c $^

Obj/%.o: Test/%.cpp
	g++ -o $@ $(INCPATH) -c $^

clean:
	rm -f GamepadController Obj/*.o

all: GamepadController test

test: JoypadHandlerTest
	./JoypadHandlerTest

JoypadHandlerTest: $(TestObjs)
	g++ -o $@ $(INCPATH) $^ $(LIBS)  -pthread

GeneratedSource/QtJoypadListener.cpp: Include/JoypadListener.hpp
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(INCPATH) $^ -o $@

GamepadController: $(Objs)
	g++ -o $@ $(INCPATH) $^ $(LIBS)
