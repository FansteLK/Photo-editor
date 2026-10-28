# make          build the C++ engine and the Java GUI
# make run      start the GUI
# make demo     run the engine on a generated sample image (results in build/demo/)

CXX      ?= c++
CXXFLAGS ?= -std=c++17 -O2 -w
ENGINE   := build/photo-engine
JAR      := build/photo-editor.jar
SOURCES  := c++/Main.cpp c++/Layer.cpp c++/Operations.cpp c++/CompositeOperation.cpp c++/Formatter.cpp

all: $(ENGINE) $(JAR)

$(ENGINE): $(SOURCES) $(wildcard c++/*.h)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)

$(JAR): $(wildcard java/*.java)
	@rm -rf build/classes && mkdir -p build/classes
	javac -nowarn -d build/classes java/*.java
	jar cfe $@ obrada_slika.Main -C build/classes .

run: all
	java -Dphotoeditor.engine=$(ENGINE) -jar $(JAR)

demo: $(ENGINE)
	@mkdir -p build/demo
	python3 scripts/make_sample.py build/demo/sample.bmp
	echo "build/demo/sample.bmp 100" > build/demo/layers.txt
	: > build/demo/none.txt
	echo "40 30 140 90" > build/demo/selection.txt
	printf 'greyscale;0;\n'               > build/demo/greyscale.ops
	printf 'inverzija;0;\n'               > build/demo/invert.ops
	printf 'black&white;0;\n'             > build/demo/bw.ops
	printf 'sabiranje;60;\n'              > build/demo/brighten.ops
	printf 'medijana;0;\n'                > build/demo/median.ops
	printf 'greyscale;0;\ninverzija;0;\n' > build/demo/selection.ops
	for op in greyscale invert bw brighten median; do \
		$(ENGINE) build/demo/layers.txt build/demo/$$op.ops build/demo/none.txt build/demo/$$op > /dev/null || exit 1; \
	done
	$(ENGINE) build/demo/layers.txt build/demo/selection.ops build/demo/selection.txt build/demo/selection > /dev/null
	@ls build/demo/*.bmp

clean:
	rm -rf build

.PHONY: all run demo clean
