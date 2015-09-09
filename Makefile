all: postlab wordenum

postlab: postlab.cpp
	g++ postlab.cpp -o postlab
wordenum: wordenum.cpp
	g++ wordenum.cpp -o wordenum

clean:
	rm postlab wordenum
