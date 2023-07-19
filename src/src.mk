CXX = g++
CXXFLAGS += -std=c++20 -g -Wall
CXXFLAGS += `pkg-config --cflags --libs Qt6Widgets` -fPIC
INCPATH = -I. -I../include

INCLUDE = ../include
ROOT = ../

HEADERS = $(INCLUDE)/run_speed_converter.h
SOURCES = main.cpp run_speed_converter.cpp
TARGET = run_speed_converter

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCPATH) $^ -o $@
	mv $@ $(ROOT)
.PHONY: clean
clean:
	rm -f $(ROOT)/$(TARGET)
