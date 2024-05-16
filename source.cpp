#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/core/core.hpp" 
#include "opencv2/opencv.hpp"
#include <iostream> 
#include <vector> 
using namespace cv; 
using namespace std;
int main() { 
 string pic = ""; 
 cout << "Nhap ten hinh ban muon detect: \n"; 
 cin >> pic; 
 Mat image = imread(pic, 1); 
 if (image.empty()) { 
 cout << "Không thể mở hoặc tìm thấy ảnh." << endl; 
 return -1; 
 } 
namedWindow("Original Image", WINDOW_NORMAL); 
 imshow("Original Image", image); 
 int numColors; 
 cout << "Nhap so luong mau ban muon detect: "; 
 cin >> numColors; 
vector<int> colorChoices; 
 vector<Mat> colorMasks; // Dùng để lưu trữ tất cả các mặt nạ màu 
 for (int i = 0; i < numColors; ++i) { 
 int choice; 
 cout << "Chon mau ban muon detect (1: Blue, 2: Red, 3: Green, 4: Purple, 5: 
Yellow\n): "; 
 cin >> choice; 
 colorChoices.push_back(choice); 
 } 
 for (size_t i = 0; i < colorChoices.size(); ++i) { 
 int choice = colorChoices[i]; 
 Mat colorMask;
switch (choice) { 
 case 1: 
 inRange(image, Scalar(100, 0, 0), Scalar(255, 100, 100), colorMask); // Blue 
 break; 
 case 2: 
 inRange(image, Scalar(0, 0, 150), Scalar(100, 100, 255), colorMask); // Red 
 break; 
 case 3: 
 inRange(image, Scalar(0, 100, 0), Scalar(100, 255, 100), colorMask); // Green 
 break; 
 case 4: 
 inRange(image, Scalar(100, 0, 100), Scalar(255, 50, 255), colorMask); // Purple 
 break; 
 case 5: 
 inRange(image, Scalar(0, 100, 100), Scalar(100, 255, 255), colorMask); // Yellow 
 break; 
 default: 
 cout << "Lua chon khong hop le." << endl; 
 return -1; 
 } 
 colorMasks.push_back(colorMask); 
 }
// Ghép nối tất cả các mặt nạ màu lại với nhau 
 Mat combinedMask = colorMasks[0]; 
 for (size_t i = 1; i < colorMasks.size(); ++i) { 
 bitwise_or(combinedMask, colorMasks[i], combinedMask); 
 } 
 // Hiển thị ảnh gốc với tất cả các màu đã detect 
 Mat resultImage = image.clone(); 
 resultImage.setTo(Scalar(255, 255, 255), ~combinedMask); 
 namedWindow("Colors Detected", WINDOW_NORMAL); 
 imshow("Colors Detected", resultImage); 
 // Chờ người dùng nhấn một phím trước khi thoát 
 waitKey(0); 
 return 0;
} 
}} 