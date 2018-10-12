#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <pthread.h>
#include <ctime>
#include <iomanip>
#include <stdexcept>

#define LEVELS 256

using namespace std;
using namespace cv;

class Image {
private:
	Mat dat_src, dst;
	double hist[LEVELS];

	// private helper methods
	void initHist() {
		for(int i=0; i<LEVELS; i++)
			hist[i] = 0;
	}
	
	void calcHist() {
		for(int i=0; i<dat_src.cols; i++)
			for(int j=0; j<dat_src.rows; j++)
				hist[dat_src.at<uchar>(i, j)]++;
	}

	void dispImage(Mat &image, string title) {
		// display the image on screen
		namedWindow(title, CV_WINDOW_AUTOSIZE);
		imshow(title, image);

	}

	void he_compute() {
		int total = dat_src.rows * dat_src.cols;		
	
		for(int i=1; i<LEVELS; i++)
			hist[i] = hist[i-1] + hist[i];

		for(int i=0; i<LEVELS; i++) {
			hist[i] = (hist[i] / total) * (LEVELS - 1);
			hist[i] = (int) (hist[i] + (0.5));
		}
	}	
	
public:
	~Image();
	Image(string);
	void histogram_equalize_multithreaded(int);
	friend void *hist_equal_partial(void *);
};


class Limits_extended {
private: 
	int start;
	int end;
	Image *img;		

public:
	Limits_extended(int a, int b, Image *abc) {
		start = a;
		end  = b;
		img = abc;
	}
	friend void *hist_equal_partial(void*); 	
};



void *hist_equal_partial(void *limits) {

	Limits_extended *l = static_cast<Limits_extended *>(limits);		
			
	// run the loop for changing the image into a hist_equalized version
	for(int i=0; i<l->img->dst.cols; i++)
		for(int j=l->start; j<l->end; j++)
			l->img->dst.at<uchar>(i, j) = l->img->hist[l->img->dat_src.at<uchar>(i, j)];
}



Image :: Image(string filename) {
	dat_src = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
	
	if(!dat_src.data) throw invalid_argument("File cannot be opened or it doesn't exist");	

	// initialize the histogram
	initHist();

	// create a new image now
	dst = Mat(dat_src.rows, dat_src.cols, CV_8UC1, Scalar::all(0));

	// display the image now
	dispImage(dat_src, "Source Image");
}

Image :: ~Image() {
	waitKey(0); // do not destroy the object until a key is pressed
}



void Image :: histogram_equalize_multithreaded(int noThreads) {
	// calculate histogram	
	calcHist();
	
	// call he_compute
	he_compute();

	// Thread Arithmetic
	if(dat_src.cols < noThreads)
		noThreads = dat_src.cols;
	
	pthread_t Thread[noThreads]; // array of threads 

	int step = dat_src.cols / noThreads;
	int s, e;
	
	cout << "\n\nDimensions:\nrows = " << dat_src.rows << endl;
	cout << "columns = " << dat_src.cols << endl << endl;

	clock_t startTime = clock();
	for(int i=0; i<noThreads; i++) {
		s = (i * step);
		
		if(i == noThreads) e = dat_src.cols;
		else e = s + step;

		cout << "Thread No: " << i << "\tstart = " << s << "\t end = " << e << endl;

		pthread_create(&Thread[i], NULL, hist_equal_partial, (new Limits_extended(s, e, this)));
	}

	for(int i=0; i<noThreads; i++)
		pthread_join(Thread[i], NULL);


	cout << fixed << setprecision(17);
	cout << "\nExecution time: " << (double( clock() - startTime ) / (double)CLOCKS_PER_SEC) / 1000 << " seconds." << endl;	


	// display the so formed image
	dispImage(dst, "Histogram Equalized Image");
}

int main(int argc, char *argv[]) {

	if(argc != 3) {
		cout << "Usage is: ./OUT <image file path> <no of threads to be spwaned> " << endl;
	} else {
		try {
			Image i1(argv[1]);
			i1.histogram_equalize_multithreaded(atoi(argv[2]));
		} catch(invalid_argument e) {
			cout << "\n\nError occured: " << e.what() << endl << endl;
		}
	}
	return 0;
}





// Sample Output

// botman@botmatrix:~/Programming/Image_processing/Histogram_Equalization$ ./OUT 1.tif 6
// init done
// opengl support available


// Dimensions:
// rows = 396
// columns = 396

// Thread No: 0	start = 0	 end = 66
// Thread No: 1	start = 66	 end = 132
// Thread No: 2	start = 132	 end = 198
// Thread No: 3	start = 198	 end = 264
// Thread No: 4	start = 264	 end = 330
// Thread No: 5	start = 330	 end = 396

// Execution time: 0.00000051900000000 seconds.
// botman@botmatrix:~/Programming/Image_processing/Histogram_Equalization$
