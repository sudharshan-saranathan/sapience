# Makefile (Sapience)
#------------------------------
# Qt version: 6.8.0
# Author: Sudharshan Saranathan
#------------------------------

# Default config options:
  CONFIG += debug warn_on c++20

# Default defines:
  DEFINES += QT_VERSION_6 QT_WITH_LOGGING

# Directory to store main executable:
  DESTDIR = bin
  TARGET  = sapience

# Include directories:
  INCLUDEPATH += ./include /opt/qt/6.8.0/macos/lib/

  ampl {
      INCLUDEPATH += /Applications/AMPL/amplapi/include/
  }

# Default temporary files location:
  OBJECTS_DIR += lib
  MOC_DIR     += moc

# Library directories:
  LIBS += -L/usr/local/lib

#----------------------------------------
# Project header files:
#----------------------------------------

  HEADERS +=	include/core/coreGUI.h	\
		        include/core/coreQSS.h  \

  HEADERS +=    include/schematic/schemaViewer.h    \
                include/schematic/schemaCanvas.h

  HEADERS +=    include/node/nodeCtrl.h             \
                include/node/nodeSVG.h              \
                include/node/nodeVar.h

  HEADERS +=    include/path/pathElement.h          \

  HEADERS +=    include/ampl/amplSolver.h

#----------------------------------------
# Project source files:
#----------------------------------------

  SOURCES += 	src/core/main.cpp	    \
		        src/core/coreGUI.cpp	\
		        src/core/coreQSS.cpp

  SOURCES +=	src/schematic/schemaViewer.cpp  \
                src/schematic/schemaCanvas.cpp

  SOURCES +=    src/node/nodeCtrl.cpp           \
                src/node/nodeSVG.cpp            \
                src/node/nodeVar.cpp            \
                src/node/nodeActions.cpp

  SOURCES +=    src/path/pathElement.cpp

  SOURCES +=    src/ampl/amplSolver.cpp

# Qt Resource files:
  RESOURCES         += resources/sapience.qrc

# Additional Qt flags:
  QMAKE_CXXFLAGS    += -std=c++20 -Wno-uninitialized
  QT 		        += core gui widgets svgwidgets
