####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DUNICODE -D_UNICODE -DWIN32
CFLAGS        = -fno-keep-inline-dllexport -g -Wall -W -Wextra $(DEFINES)
CXXFLAGS      = -fno-keep-inline-dllexport -g -std=gnu++11 -Wall -W -Wextra -fexceptions -mthreads $(DEFINES)
LINK          = g++
LFLAGS        = -Wl,-subsystem,windows -mthreads
INCPATH       = -I.
VPATH	      = .
MINGW         = C:\Qt\Qt5.9.7\5.9.7\mingw53_32
LIBS          = -lmingw32 -L${MINGW}\lib
IDC           = idc
IDL           = midl
ZIP           = zip -r -9
DEF_FILE      = 
RES_FILE      = 
COPY          = copy /y
QMAKE         = ${MINGW}\bin\qmake.exe
SED           = $(QMAKE) -install sed
COPY_FILE     = copy /y
COPY_DIR      = xcopy /s /q /y /i
DEL_FILE      = del
DEL_DIR       = rmdir
MOVE          = move
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
INSTALL_FILE    = copy /y
INSTALL_PROGRAM = copy /y
INSTALL_DIR     = xcopy /s /q /y /i

####### Output directory

OBJECTS_DIR   = .\build
####### Files
SOURCES       = $(wildcard *.cpp)
SOURCEO       = $(SOURCES:.cpp=.o) 
OBJECTS       = $(addprefix $(OBJECTS_DIR)/,$(SOURCEO))
DEPS          = $(OBJECTS:.o=.d)
DESTDIR       = .
TARGET        = target
####### Customized Vars
INCPATH	     += 
VPATH        +=	
LIBS         += 
SOURCES	     += 
#########################################

####### Build rules
$(OBJECTS_DIR)/%.o:%.c
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@  $<

$(OBJECTS_DIR)/%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@  $<
#########################################

####### Targets

first: all

all: $(TARGET)


$(TARGET): Makefile  $(OBJECTS_DIR) $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(DESTDIR)/$(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

$(OBJECTS_DIR):
	$(MKDIR) $(OBJECTS_DIR)

clean: 
	$(DEL_FILE) $(OBJECTS) $(DEPS) $(DESTDIR)/$(TARGET)

env:
	@echo CC          : $(CC)
	@echo CFLAGS      : $(CFLAGS)
	@echo CXX         : $(CXX)
	@echo CXXFLAGS    : $(CXXFLAGS)
	@echo LINK        : $(LINK)
	@echo LFLAGS      : $(LFLAGS)
	@echo LIBS        : $(LIBS)
	@echo INCPATH     : $(INCPATH)
	@echo VPATH       : $(VPATH)
	@echo SOURCES     : $(SOURCES)
	@echo SOURCEO     : $(SOURCEO)
	@echo OBJECTS_DIR : $(OBJECTS_DIR)
	@echo OBJECTS     : $(OBJECTS)
	@echo DEPS     	  : $(DEPS)
	@echo DESTDIR     : $(DESTDIR)
	@echo TARGET      : $(TARGET)
	@echo OBJCOMP     : $(OBJCOMP)
	@echo Compile     : $(CXX) -c $(CXXFLAGS) $(INCPATH) -o
	@echo Link        : $(LINK) $(LFLAGS) -o $(DESTDIR)/$(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	@echo Clean       : $(DEL_FILE) $(OBJECTS) $(DEPS) $(DESTDIR)/$(TARGET)

-include $(DEPS)
