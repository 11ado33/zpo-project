build: 
	g++ -oprojekt projekt.cpp -Wall -I. -I/usr/local/include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

clean:
	rm projekt