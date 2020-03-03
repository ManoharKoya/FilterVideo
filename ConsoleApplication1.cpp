// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

bool login() {
    cout << "Login..\nEnter Username: ";
    string name, passcode;
    cin >> name;
    cout << "Enter passocode: ", cin >> passcode;
    if (name == "name" && passcode == "passcode") return true;
    return false;
}
void test() {
    Mat img = imread("C:\\Users\\MK\\Desktop\\Desk\\CompProg\\internship\\ci1.jpg");
    if (!img.data)                              // Check for invalid input
    {
        cout << "Could not open or find the image\n" << std::endl;
        return;
    }
    namedWindow("image", WINDOW_NORMAL);
    imshow("image", img);
    waitKey(0);
    return;
}
void record10sec() {
    VideoCapture cap(0);
    
    if (!cap.isOpened()) {cout << "Camera Not working";  return;}
    Mat frame;
    int frameWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

    VideoWriter output("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 24.0, Size(frameWidth, frameHeight), true);

    while (1){
        cap.read(frame);
        imshow("camera", frame);
        output.write(frame);
        if (waitKey(30) == 's') break;

    }
    output.release();
    cap.release();
    destroyAllWindows();
    return;
}
void extractRedAndSmooth() {
    VideoCapture cap("C:\\Users\\MK\\source\\repos\\ConsoleApplication1\\output.avi");
    if (!cap.isOpened()) { cout << "NO file"; return; }
    VideoWriter outputR("res_red.avi", cap.get(CAP_PROP_FOURCC), 24.0, Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT)), true);
    Mat frame, res;
    vector<Mat> spl;
    int channel = 2; // for red c=2;
    while (1) {
        cap >> frame;
        if (!frame.data) break;
        imshow("camera", frame);
        if(waitKey(30) == 's') destroyAllWindows();
        split(frame, spl);
        for (int i = 0; i < 3; ++i)
            if (i != channel) 
                spl[i] = Mat::zeros(Size(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT)), spl[0].type());
        merge(spl, res);
        outputR << res;
    }
    cout << "DONE..";
    outputR.release();
    cap.release();
    destroyAllWindows();
    return;
}
void solve() {
    // 1. login , logout.
    // test();
    if (!login()) return;
    record10sec();
    extractRedAndSmooth();
    return;
}

int main() {
    solve();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
