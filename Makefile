# PROJECT FOLDERS
BLD       := build
IMG       := images
INC       := include
PUB       := public
SRC       := src

# FILE TYPES
SOURCE    := $(SRC)/AccRotateAble.cpp $(SRC)/AccTransAble.cpp $(SRC)/Actor.cpp $(SRC)/Asteroid.cpp $(SRC)/Background.cpp $(SRC)/Camera.cpp $(SRC)/CollideAble.cpp $(SRC)/Config.cpp $(SRC)/Controller.cpp $(SRC)/KeyAble.cpp $(SRC)/Laser.cpp $(SRC)/Main.cpp $(SRC)/Math.cpp $(SRC)/Model.cpp $(SRC)/ModelAble.cpp $(SRC)/MouseAble.cpp $(SRC)/MVC.cpp $(SRC)/Player.cpp $(SRC)/RotateAble.cpp $(SRC)/TranslateAble.cpp $(SRC)/Vec2f.cpp $(SRC)/Vec2i.cpp $(SRC)/View.cpp $(SRC)/ViewAble.cpp $(SRC)/World.cpp
IMAGES    := 'png', 'jpg'

#EXPORTED FUNCTIONS
FUNCS     := '_resize', '_main'
EXTRA     := 'cwrap', 'ccall'

# INCLUDED FILES
EM_       := C:/Users/gcyua/OneDrive/Documents/Projects/WebAssemblyProjects/emsdk/upstream/emscripten
EM_SDL2   := $(EM_)/cache/sysroot/include
EM_EMSC   := $(EM_)/system/include
INCLUDE   := -I $(INC) -I $(EM_SDL2) -I $(EM_EMSC)

# COMPILER DETAILS
COMPILER  := em++
STANDARD  := -Wall -Wextra -std=c++17 -ggdb

# HTML SHELL
HTML      := --shell-file $(BLD)/index-shell.html

# SETTINGS
PRELOAD   := --preload-file images
EMRUN     := --emrun
USES      := -s USE_WEBGL2=1 \
             -s USE_SDL=2 \
						 -s USE_SDL_IMAGE=2
FORMATS   := -s SDL2_IMAGE_FORMATS="[$(IMAGES)]"
EXPORTS   := -s EXPORTED_FUNCTIONS="[$(FUNCS)]" \
             -s EXPORTED_RUNTIME_METHODS="[$(EXTRA)]"
MEMORY    := -s ALLOW_MEMORY_GROWTH=1
SETTINGS  := $(PRELOAD) $(EMRUN) $(USES) $(FORMATS) $(EXPORTS) $(MEMORY) -s LLD_REPORT_UNDEFINED

# OUTPUT FILE
NAME			:= index
LOC				:= $(PUB)/$(NAME)
OUT       := -o $(LOC).html

# MAKE
all : 
	$(COMPILER) $(SOURCE) $(INCLUDE) $(STANDARD) $(HTML) $(SETTINGS) $(OUT)

# CLEAN
clean :
	rm $(LOC).html $(LOC).data $(LOC).js $(LOC).wasm

# RUN
run :
	emrun --browser chrome --kill_start $(LOC).html
