//
//  main.cpp
//  PDFToCV
//
//  Created by zhoushiwei on 15/5/12.
//  Copyright (c) 2015年 zhoushiwei. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-page-renderer.h>
#include <poppler-image.h>
using namespace  cv;
using namespace std;
using namespace poppler;

Mat PDFToCV(const string &filename,int DPI)
{
    document* mypdf = document::load_from_file(filename);
    if(mypdf == NULL) {
        cerr << "couldn't read pdf\n";
        return Mat();
    }
    cout << "pdf has " << mypdf->pages() << " pages\n";
    page* mypage = mypdf->create_page(0);
    
    page_renderer renderer;
    renderer.set_render_hint(page_renderer::text_antialiasing);
    image myimage = renderer.render_page(mypage,DPI,DPI);
    cout << "created image of  " << myimage.width() << "x"<< myimage.height() << "\n";
    
    Mat cvimg;
    if(myimage.format() == image::format_rgb24) {
        Mat(myimage.height(),myimage.width(),CV_8UC3,myimage.data()).copyTo(cvimg);
    } else if(myimage.format() == image::format_argb32) {
        Mat(myimage.height(),myimage.width(),CV_8UC4,myimage.data()).copyTo(cvimg);
    } else {
        cerr << "PDF format no good\n";
        return Mat();
    }
    return cvimg;
}
int main(int argc, const char * argv[]) {
    Mat img=  PDFToCV("/Users/zhoushiwei/Dropbox/PDFToCV/EyeSVM.pdf",100);
    imshow("img", img);
    waitKey();
    return 0;
}
