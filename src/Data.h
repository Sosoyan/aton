/*
Copyright (c) 2016,
Dan Bethell, Johannes Saam, Vahan Sosoyan, Brian Scherbinski.
All rights reserved. See COPYING.txt for more details.
*/

#ifndef ATON_DATA_H_
#define ATON_DATA_H_

#include <vector>

// Represents image information passed from Client to Server
// This class wraps up the data sent from Client to Server. When calling
// Client::openImage() a Data object should first be constructed that
// specifies the full image dimensions.
// E.g. Data( 0, 0, 320, 240, 3 );
// When sending actually pixel information it should be constructed using
// values that represent the chunk of pixels being sent.
// E.g. Data( 15, 15, 16, 16, 3, myPixelPointer );
class Data
{
    
friend class Client;
friend class Server;
    
public:
    Data();
    ~Data();
    
    // The 'type' of message this Data represents
    // 0: image open
    // 1: pixels
    // 2: image close
    const int type() const { return mType; }
    
private:
    // What type of data is this?
    int mType;
};


class DataHeader: public Data
{
    
friend class Client;
friend class Server;
    
public:
    
    DataHeader(const int& xres = 0,
               const int& yres = 0,
               const long long& rArea = 0,
               const int& version = 0,
               const float& currentFrame = 0.0f,
               const float& cam_fov = 0.0f,
               const float* cam_matrix = NULL);
   
    ~DataHeader();
    
    // Get x resolution
    const int& xres() const { return mXres; }
    
    // Get y resolution
    const int& yres() const { return mYres; }
    
    // Get area of the render region
    const long long& rArea() const { return mRArea; }
    
    // Version number
    const int& version() const { return mVersion; }
    
    // Current frame
    const float& currentFrame() const { return mCurrentFrame; }
    
    // Camera Fov
    const float& camFov() const { return mCamFov; }
    
    // Camera matrix
    const std::vector<float>& camMatrix() const { return mCamMatrixStore; }

private:
    
    // Resolution, X & Y
    int mXres, mYres;
    
    // Version number
    int mVersion;
    
    // Region area
    long long mRArea;
    
    // Current frame
    float mCurrentFrame;
    
    // Camera Field of View
    float mCamFov;
    
    // Camera Matrix pointer, storage
    float* mCamMatrix;
    std::vector<float> mCamMatrixStore;
};


class DataPixels: public Data
{
    
friend class Client;
friend class Server;

public:
    DataPixels(const int& xres = 0,
               const int& yres = 0,
               const int& bucket_xo = 0,
               const int& bucket_yo = 0,
               const int& bucket_size_x = 0,
               const int& bucket_size_y = 0,
               const int& spp = 0,
               const long long& ram = 0,
               const int& time = 0,
               const char* aovName = NULL,
               const float* data = NULL);
    
    ~DataPixels();
    
    // Get x resolution
    const int& xres() const { return mXres; }
    
    // Get y resolution
    const int& yres() const { return mYres; }
    
    // Get y position
    const int& bucket_xo() const { return mBucket_xo; }
    
    // Get y position
    const int& bucket_yo() const { return mBucket_yo; }
    
    // Get width
    const int& bucket_size_x() const { return mBucket_size_x; }
    
    // Get height
    const int& bucket_size_y() const { return mBucket_size_y; }
    
    // Samples-per-pixel, aka channel depth
    const int& spp() const { return mSpp; }
    
    // Taken memory while rendering
    const long long& ram() const { return mRam; }
    
    // Taken time while rendering
    const unsigned int& time() const { return mTime; }
    
    // Get Aov name
    const char* aovName() const { return mAovName; }
    
    // Pointer to pixel data owned by the display driver (client-side)
    const float* data() const { return mpData; }
    
    // Reference to pixel data owned by this object (server-side)
    const float& pixel(int index = 0) { return mPixelStore[index]; }
    
    // Deallocate Aov name
    void free();
    
private:
    // Resolution, X & Y
    int mXres, mYres;
    
    // Bucket origin X and Y, Width, Height
    int mBucket_xo,
        mBucket_yo,
        mBucket_size_x,
        mBucket_size_y;
    
    // Sample Per Pixel
    int mSpp;
    
    // Memory
    long long mRam;
    
    // Time
    unsigned int mTime;
    
    // AOV Name
    const char *mAovName;
    
    // Our pixel data pointer (for driver-owned pixels)
    float *mpData;
    
    // Our persistent pixel storage (for Data-owned pixels)
    std::vector<float> mPixelStore;
};
    

#endif // ATON_DATA_H_
