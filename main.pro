# Makefile (Sapience)
#------------------------------
# Qt version: 6.8.0
# Author: Sudharshan Saranathan
#------------------------------

# Default config options:
  CONFIG += debug warn_on c++20

# Default defines:
  DEFINES += QT_VERSION_6 QT_WITH_OPENMP QT_WITH_LOGGING

  optim {

      DEFINES += QT_WITH_OPTIMIZER

  }

# Directory to store main executable:
  DESTDIR = bin
  TARGET  = sapience

# Include directories:
  INCLUDEPATH += ./include /opt/qt/6.8.0/macos/lib/

  optim {
      INCLUDEPATH += /opt/local/include/optim
      INCLUDEPATH += /opt/local/include/eigen3
  }

  ampl {
      INCLUDEPATH += /opt/local/include/ampl

  }

# Default temporary files location:
  OBJECTS_DIR += lib
  MOC_DIR     += moc

# Library directories:
  LIBS += -L/usr/local/lib

#----------------------------------------
# Project header files:
#----------------------------------------

  HEADERS +=	include/core/coreIOF.h		\
		include/core/coreGUI.h		\
		include/core/coreQSS.h		\

  HEADERS +=    include/schematic/schemaViewer.h	\
		include/schematic/schemaCanvas.h	\
		include/schematic/schemaGrid.h		\

  HEADERS +=	include/node/nodeControl.h

  optim {

      HEADERS += include/optim/qMatrix.h	\

  }

#----------------------------------------
# Project source files:
#----------------------------------------

  SOURCES += 	src/core/main.cpp		\
		src/core/coreGUI.cpp		\
		src/core/coreIOF.cpp		\
		src/core/coreQSS.cpp		\

  SOURCES +=	src/schematic/schemaViewer.cpp	\
		src/schematic/schemaCanvas.cpp	\
		src/schematic/schemaGrid.cpp	\

  SOURCES +=	src/node/nodeControl.cpp

  optim {

      SOURCES += src/optim/qMatrix.cc

  }

# Qt Resource files:
  RESOURCES       += resources/sapience.qrc

# Additional Qt flags:
  QMAKE_CXXFLAGS += -std=c++20
  QT 		 += core gui widgets svgwidgets
