# Makefile (Sapience)
#------------------------------
# Qt version: 6.8.0
# Author: Sudharshan Saranathan
#------------------------------

# Default config options:
  CONFIG += debug warn_on c++20 ampl

# Default defines:
  DEFINES += QT_VERSION_6 QT_WITH_LOGGING

# Directory to store main executable:
  DESTDIR = bin
  TARGET  = sapience-debug

# Include directories:
  INCLUDEPATH += include
  INCLUDEPATH += /usr/local/include/
  INCLUDEPATH += /opt/qt/6.8.0/macos/lib/
  INCLUDEPATH += /Applications/AMPL/amplapi/include/

# Default temporary files location:
  OBJECTS_DIR += lib
  MOC_DIR     += moc

# Library directories:
  LIBS = -L/usr/local/lib -L/Applications/AMPL/amplapi/lib -lampl -lfmt

#----------------------------------------
# Project header files:
#----------------------------------------

  HEADERS +=	include/core/coreGUI.h	\
                include/core/coreQSS.h  \

  HEADERS +=    include/schematic/schemaViewer.h    \
                include/schematic/schemaCanvas.h

  HEADERS +=    include/node/nodeCtrl.h             \
                include/node/nodeSVG.h              \
                include/node/nodeHandle.h           \
                include/node/nodeParams.h           \
                include/node/nodeGroup.h            \
                include/node/nodeConnect.h

  HEADERS +=    include/ampl/amplDatabase.h         \

  HEADERS +=    include/optim/optimCtrl.h           \

  HEADERS +=    include/custom/customEditor.h       \
                include/custom/customDialog.h

#----------------------------------------
# Project source files:
#----------------------------------------

  SOURCES += 	src/core/main.cpp	                \
		        src/core/coreGUI.cpp	            \
		        src/core/coreQSS.cpp

  SOURCES +=	src/schematic/schemaViewer.cpp      \
                src/schematic/schemaCanvas.cpp

  SOURCES +=    src/node/nodeCtrl.cpp               \
                src/node/nodeSVG.cpp                \
                src/node/nodeHandle.cpp             \
		        src/node/nodeParams.cpp             \
                src/node/nodeGroup.cpp              \
                src/node/nodeActions.cpp	        \
		        src/node/nodeConnect.cpp

  SOURCES +=    src/ampl/amplDatabase.cpp           \

  SOURCES +=    src/optim/optimCtrl.cpp             \

  SOURCES +=    src/custom/customEditor.cpp         \
                src/custom/customDialog.cpp

# Qt Resource files:
  RESOURCES         += resources/sapience.qrc

# Additional Qt flags:
  QMAKE_CXXFLAGS    += -std=c++20 -O3 -ftree-vectorize -flto -ffast-math
  QT 		        += core gui widgets svgwidgets
