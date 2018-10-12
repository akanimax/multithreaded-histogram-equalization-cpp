# multithreaded-histogram-equalization-cpp
Explanatory Code for performing Histogram Equalization on Images for contrast improvement. The code uses OpenCV in C++ for image read/write and uses pthread for multithreading


### Running the code:
Just use the following commands for running the code. I have already complied it in binary.

OUT without any command line args shows the usage message

	$ ./OUT
	Usage is: ./OUT <image file path> <no of threads to be spwaned> 

For running an example try:

	$ ./OUT 4.bmp 32
	init done
	opengl support available


	Dimensions:
	rows = 512
	columns = 512

	Thread No: 0	start = 0	 end = 16
	Thread No: 1	start = 16	 end = 32
	Thread No: 2	start = 32	 end = 48
	Thread No: 3	start = 48	 end = 64
	Thread No: 4	start = 64	 end = 80
	Thread No: 5	start = 80	 end = 96
	Thread No: 6	start = 96	 end = 112
	Thread No: 7	start = 112	 end = 128
	Thread No: 8	start = 128	 end = 144
	Thread No: 9	start = 144	 end = 160
	Thread No: 10	start = 160	 end = 176
	Thread No: 11	start = 176	 end = 192
	Thread No: 12	start = 192	 end = 208
	Thread No: 13	start = 208	 end = 224
	Thread No: 14	start = 224	 end = 240
	Thread No: 15	start = 240	 end = 256
	Thread No: 16	start = 256	 end = 272
	Thread No: 17	start = 272	 end = 288
	Thread No: 18	start = 288	 end = 304
	Thread No: 19	start = 304	 end = 320
	Thread No: 20	start = 320	 end = 336
	Thread No: 21	start = 336	 end = 352
	Thread No: 22	start = 352	 end = 368
	Thread No: 23	start = 368	 end = 384
	Thread No: 24	start = 384	 end = 400
	Thread No: 25	start = 400	 end = 416
	Thread No: 26	start = 416	 end = 432
	Thread No: 27	start = 432	 end = 448
	Thread No: 28	start = 448	 end = 464
	Thread No: 29	start = 464	 end = 480
	Thread No: 30	start = 480	 end = 496
	Thread No: 31	start = 496	 end = 512

	Execution time: 0.00000167400000000 seconds.

### Other links:
link to blog -> 

### Thanks!
Please feel free to provide feedback / suggestions and to open PR for improvement.<br> <br>

Cheers :beers:! <br>
@akanimax
