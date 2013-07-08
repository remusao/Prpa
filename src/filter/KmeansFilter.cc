#include "KmeansFilter.hh"
#include <cstdlib>
#include <math.h>
#include <Eigen/Dense>

namespace
{
     struct KMeansOptions
    {
        uint32_t k;
        uint32_t dim;
        uint32_t nbVectors;
    };

    template <typename Vector, typename Distance>
    bool par_cluster(
        const KMeansOptions& options,
        const Distance& distance,
        std::vector<uint32_t>& clusters,
        const std::vector<Vector>& centroids,
        const std::vector<Vector>& data)
    {
        bool hasChanged = false;
        for(size_t i = 0; i < options.nbVectors; ++i)
        {
            Vector min = centroids[0];
            double d, tmp, index;
            d = distance(min, data[i]);
            index = 0;
            for (uint64_t j = 1; j < options.k; ++j)
            {
                tmp = distance(data[i], centroids[j]);
                if (tmp < d)
                {
                    min = centroids[j];
                    d = tmp;
                    index = j;
                }
            }

            if (clusters[i] != index)
                hasChanged = true;
            clusters[i] = index;
        }

        return hasChanged;
    }


    template <typename Vector>
        void getCentroids(
                const KMeansOptions& options,
                const std::vector<unsigned>& clusters,
                const std::vector<Vector>& datas,
                std::vector<Vector>& centroids)
        {
            // Used to count the size of each cluster
            std::vector<uint64_t> sizes(options.k, 0);

            // Clear centroids before computing the mean
            for (uint32_t i = 0; i < options.k; ++i)
                centroids[i] = Vector::Zero(options.dim);

            // Sum vectors of each centroid
            for (uint64_t i = 0; i < options.nbVectors; ++i)
            {
                centroids[clusters[i]] += datas[i];
                ++sizes[clusters[i]];
            }

            // Divide by the number of element
            for (uint32_t i = 0; i < options.k; ++i)
            {
                if (sizes[i] != 0)
                    centroids[i] /= (double)sizes[i];
            }

        }
}


// KMeans clustering algorithm
template <typename Vector, typename Distance>
std::vector<uint32_t>
par_kmeans(KMeansOptions options,
    const Distance& dist,
    const std::vector<Vector>& data)
{
    std::vector<uint32_t>           clusters(options.nbVectors, 0);
    std::vector<Vector>    centroids;
    centroids.reserve(options.k);

    // init random centroids
    for (unsigned i = 0; i < options.k; ++i)
        centroids.emplace_back(Vector::Random(options.dim));

    // Main loop
    // While clustering is different, compute the centroids and
    // assign each vector to one of them
    while (par_cluster(options, dist, clusters, centroids, data))
        getCentroids(options, clusters, data, centroids);

    return clusters;
}


KmeansFilter::KmeansFilter()
  : filter (/* is_serial */ false)
{
}

void*
KmeansFilter::operator()(void* elt)
{
    using Vector = Eigen::Vector3i;

    auto* pair = static_cast<std::pair<IplImage*, IplImage*>*> (elt);
    IplImage* img = pair->first;
    if (!img)
        printf("img null in canny filter\n");
    //out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, img->nChannels);

    // Create the distance function
    auto distance = [](const Vector& v1, const Vector& v2)
    {
        return (v1 - v2).squaredNorm();
    };

    // First argument is K.
    uint32_t K = 3;
    // Second argument is Dim.
    uint32_t Dim = 3;

    static cv::Mat image(img);
    KMeansOptions options{K, Dim, (uint32_t)(image.rows * image.cols)};

    // Create vectors from image
    std::vector<Vector> data;
    data.reserve(options.nbVectors);

    for(int i = 0; i < image.rows; ++i)
        for(int j = 0; j < image.cols; ++j)
            data.emplace_back(
                    image.at<cv::Vec3b>(i, j)[0],
                    image.at<cv::Vec3b>(i, j)[1],
                    image.at<cv::Vec3b>(i, j)[2]);

    std::cout << "Clustering: " << data.size() << " " << Dim << "d vectors" << std::endl;
    auto res = par_kmeans(options, distance, data);

    static cv::Mat output = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);
    for (unsigned i = 0; i < data.size(); ++i)
    {
        unsigned x = i % image.cols;
        unsigned y = i / image.cols;
        output.at<cv::Vec3b>(y, x)[0] = 255 / (res[i] + 1);
        output.at<cv::Vec3b>(y, x)[1] = 255 / (res[i] + 1);
        output.at<cv::Vec3b>(y, x)[2] = 255 / (res[i] + 1);
    }

    return (new std::pair<IplImage*, IplImage*>(new IplImage(output), pair->second));
}

std::string
KmeansFilter::get_name()
{
    return "Kmeans filter";
}
