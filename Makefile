build: 
	g++ -o projekt projekt.cpp imageExporter.h imageExporter.cpp -Wall -I. -I/usr/local/include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

clean:
	rm projekt