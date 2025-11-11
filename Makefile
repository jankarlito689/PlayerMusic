# =========================================
# 📒 Proyecto: MusicPlayer
# =========================================

# Compilador y banderas
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I.

DEBUG_FLAGS = -g
RELEASE_FLAGS = -O3

# Directorios
SRC_DIR = .
FILE_DIR = File
LIST_DIR = List
PLAYER = Player
UI_DIR = Ui
UTILS_DIR = Utils

# Archivos fuente
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
        	$(wildcard $(FILE_DIR)/*.cpp) \
			$(wildcard $(LIST_DIR)/*.cpp) \
			$(wildcard $(PLAYER)/*.cpp) \
        	$(wildcard $(UI_DIR)/*.cpp) \
        	$(wildcard $(UTILS_DIR)/*.cpp)

# Archivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Ejecutable final
TARGET = MusicPlayer

# =========================================
# 🧱 Reglas principales
# =========================================

all: debug

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

LIBS = -lsfml-audio -lsfml-system
$(TARGET): $(OBJECTS)
	@echo "🔗 Enlazando $(TARGET)..."
	$(CXX) $(OBJECTS) -o $@ $(LIBS)
	@echo "✅ Compilación completa."

# =========================================
# 🔧 Reglas por carpeta
# =========================================

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(CONTACTOS_DIR)/%.o: $(CONTACTOS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(UI_DIR)/%.o: $(UI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(UTILS_DIR)/%.o: $(UTILS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# =========================================
# 🧹 Utilidades
# =========================================

clean:
	@echo "🧹 Limpiando archivos compilados..."
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

run: debug
	@echo "🚀 Ejecutando..."
	./$(TARGET)

help:
	@echo "Targets disponibles:"
	@echo "  all/debug  -> Compila en modo debug (por defecto)"
	@echo "  release    -> Compila en modo optimizado"
	@echo "  clean      -> Elimina binarios y objetos"
	@echo "  rebuild    -> Limpia y recompila todo"
	@echo "  run        -> Compila y ejecuta el programa"

.PHONY: all debug release clean rebuild run help
