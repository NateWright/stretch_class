// Reference: https://learnopencv.com/edge-detection-using-opencv/
// https://wiki.ros.org/cv_bridge/Tutorials/UsingCvBridgeToConvertBetweenROSImagesAndOpenCVImages

#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <ros/ros.h>

using cv::Mat;

class ImageManipulator {
   private:
    ros::NodeHandlePtr nh_;
    ros::Subscriber sub_;
    ros::Publisher pub_;

    void callback(const sensor_msgs::ImageConstPtr& msg);

   public:
    ImageManipulator(ros::NodeHandlePtr nh);
    ~ImageManipulator();
};

ImageManipulator::ImageManipulator(ros::NodeHandlePtr nh) : nh_(nh) {
    sub_ = nh_->subscribe("/camera/color/image_raw", 10, &ImageManipulator::callback, this);
    pub_ = nh_->advertise<sensor_msgs::Image>("/example_pub/sobel", 10, true);
}

ImageManipulator::~ImageManipulator() {
}

void ImageManipulator::callback(const sensor_msgs::ImageConstPtr& msg) {
    cv_bridge::CvImagePtr cv_ptr;
    cv_bridge::CvImage output;
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

    // Convert to grayscale
    Mat img_gray;
    cv::cvtColor(cv_ptr->image, img_gray, CV_8UC1);
    // Blur image for better edge detection
    Mat img_blur;
    cv::GaussianBlur(img_gray, img_blur, cv::Size(3, 3), 0);
    // Sobel edge detection
    Mat sobel;
    cv::Sobel(img_blur, sobel, CV_64F, 1, 0, 5);  // Sobel in x direction
    // cv::Sobel(img_blur, sobel, CV_64F, 0, 1, 5); // Sobel in y direction
    // cv::Sobel(img_blur, sobel, CV_64F, 1, 1, 5); // Sobel in xy direction

    // Placeholder mat
    Mat temp;
    // Converts cv mat from CV_64F to CV_8U
    sobel.convertTo(temp, CV_8U);
    // Removes BGRA channels to become a grayscale image
    cv::cvtColor(temp, output.image, CV_BGRA2GRAY);
    // Using original message header as header for converted image
    output.header = msg->header;
    // Set encoding type to mono
    output.encoding = sensor_msgs::image_encodings::MONO8;
    // Publishes image
    pub_.publish(output.toImageMsg());
}
int main(int argc, char** argv) {
    ros::init(argc, argv, "image_sub");
    ros::NodeHandlePtr nh(new ros::NodeHandle);

    ImageManipulator im(nh);

    ros::spin();

    return 0;
}
