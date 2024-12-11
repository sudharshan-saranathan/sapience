# Makefile (Sapience)
#------------------------------
# Qt version: 6.8.0
# Author: Sudharshan Saranathan
#------------------------------

# Define project home:
  PROJECT_PATH = $${PWD}

# Default config options:
  CONFIG += debug warn_on c++20 ampl

# Default defines:
  DEFINES += QT_VERSION_6 QT_WITH_LOGGING

# Directory to store main executable:
  DESTDIR = bin
  TARGET  = sapience-debug

# Include directories:
  INCLUDEPATH += $${PROJECT_PATH}/include
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

  HEADERS +=	include/core/core_gui.h	\
                include/core/core_qss.h  \

  HEADERS +=    include/schematic/schema_viewer.h    \
                include/schematic/schema_canvas.h

  HEADERS +=    include/node/node_ctrl.h             \
                include/node/node_svg.h              \
                include/node/node_handle.h           \
                include/node/node_params.h           \
                include/node/node_group.h            \
                include/node/node_connect.h

  HEADERS +=    include/optim/optim_ctrl.h           \
                include/optim/optim_data.h

  HEADERS +=    include/custom/custom_editor.h       \
                include/custom/custom_dialog.h

#----------------------------------------
# Project source files:
#----------------------------------------

  SOURCES += 	src/core/main.cpp	                \
		src/core/core_gui.cpp	            	\
		src/core/core_qss.cpp

  SOURCES +=	src/schematic/schema_viewer.cpp      	\
                src/schematic/schema_canvas.cpp

  SOURCES +=    src/node/node_ctrl.cpp               	\
                src/node/node_svg.cpp                	\
                src/node/node_handle.cpp        	\
		src/node/node_params.cpp             	\
                src/node/node_group.cpp              	\
                src/node/node_actions.cpp	 	\
		src/node/node_connect.cpp		

  SOURCES +=    src/optim/optim_ctrl.cpp             	\
                src/optim/optim_data.cpp

  SOURCES +=    src/custom/custom_editor.cpp         	\
                src/custom/custom_dialog.cpp

# Qt Resource files:
  RESOURCES +=  resources/sapience.qrc

# Additional Qt flags:
  QMAKE_CXXFLAGS    += -std=c++20 -O3 -ftree-vectorize -flto -ffast-math
  QT 		        += core gui widgets svgwidgets
