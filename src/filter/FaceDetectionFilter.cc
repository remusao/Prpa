#include "FaceDetectionFilter.hh"

FaceDetectionFilter::FaceDetectionFilter(char* haar)
  : filter (/* is_serial */ false),
    haar_ (haar)
{
}

void*
FaceDetectionFilter::operator()(void* elt)
{
    IplImage* img = static_cast<IplImage*> (elt);
    if (!img)
        printf("img null in face detection filter\n");
    // Create memory for calculations
    static CvMemStorage* storage = 0;

    // Create a new Haar classifier
    static CvHaarClassifierCascade* cascade = 0;

    int scale = 1;

    // Create a new image based on the input image
    IplImage* temp = cvCreateImage( cvSize(img->width/scale,img->height/scale), 8, 3 );

    // Create two points to represent the face locations
    CvPoint pt1, pt2;
    int i;

    // Load the HaarClassifierCascade
    cascade = (CvHaarClassifierCascade*)cvLoad(haar_, 0, 0, 0 );

    // Check whether the cascade has loaded successfully. Else report and error and quit
    if (!cascade)
    {
        fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        return 0;
    }

    // Allocate the memory storage
    storage = cvCreateMemStorage(0);

    // Clear the memory storage which was used before
    cvClearMemStorage( storage );

    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( cascade )
    {

        // There can be more than one face in an image. So create a growable sequence of faces.
        // Detect the objects and store them in the sequence
        CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,
                1.1, 2, CV_HAAR_DO_CANNY_PRUNING | CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_DO_ROUGH_SEARCH,
                cvSize(40, 40) );

        // Loop the number of faces found.
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x*scale;
            pt2.x = (r->x+r->width)*scale;
            pt1.y = r->y*scale;
            pt2.y = (r->y+r->height)*scale;

            // Draw the rectangle in the input image
            cvRectangle( img, pt1, pt2, CV_RGB(255,0,0), 3, 8, 0 );
        }
    }

    // Release the temp image created.
    cvReleaseImage(&temp);
    return img;
}

    std::string
FaceDetectionFilter::get_name ()
{
    return "Face Detection filter";
}
