#include "dl_list.h"
#include "blockpng.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace cs225;

dl_list<epng::rgba_pixel> list_from_image(const epng::png& img,
                                          bool reverse = false)
{
    dl_list<epng::rgba_pixel> list;
    for (size_t i = 0; i < img.width(); i++)
    {
        for (size_t j = 0; j < img.height(); j++)
        {
            if (reverse)
                list.push_front(*img(i, j));
            else
                list.push_back(*img(i, j));
        }
    }
    return list;
}

epng::png image_from_list(const dl_list<epng::rgba_pixel>& lst, size_t width,
                          size_t height)
{
    epng::png ret{width, height};
    std::vector<epng::rgba_pixel> v(lst.begin(), lst.end());
    size_t x = 0;
    size_t y = 0;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        *ret(x, y) = v[i];
        y++;
        if (y == height)
        {
            y = 0;
            x++;
        }
    }
    return ret;
}

void checkSoln(const std::string& test, const epng::png& out,
               const std::string& soln_file)
{
    epng::png soln{soln_file};

    if (!(soln == out))
        std::cerr << "[" << test << "]: Image does not match " << soln_file
                  << std::endl;
}

void test_inserts()
{
    std::cout << "[main]: " << __func__ << "()" << std::endl;
    dl_list<int> lst;

    // test push_front
    for (int i = 1; i <= 10; i++)
        lst.push_front(i);

    std::cout << "[test_inserts]: " << lst << std::endl;
    std::cout << "[test_inserts]: size: " << lst.size() << std::endl;
    if (lst.size() != 10)
        std::cout << "[test_inserts]: Incorrect size" << std::endl;

    dl_list<int> lst2;

    // test push_back
    for (int i = 1; i <= 10; i++)
        lst2.push_back(i);
	
    std::cout << "[test_inserts]: " << lst2 << std::endl;
    std::cout << "[test_inserts]: size: " << lst2.size() << std::endl;
    if (lst2.size() != 10)
        std::cout << "[test_inserts]: Incorrect size" << std::endl;
}

void test_reverse()
{
    std::cout << "[main]: " << __func__ << "()" << std::endl;
    epng::png in{"in_02.png"};

    auto lst = list_from_image(in);
    lst.reverse();

    auto out = image_from_list(lst, in.width(), in.height());
    out.save("reverse.png");

    checkSoln(__func__, out, "soln_reverse.png");
}

void test_reverse_nth()
{
    std::cout << "[main]: " << __func__ << "()" << std::endl;
    epng::png in{"in_03.png"};

    auto lst = list_from_image(in);
    lst.reverse_nth(in.height() * 20);

    auto out = image_from_list(lst, in.width(), in.height());
    out.save("reverseNth_01.png");

    checkSoln(__func__, out, "soln_reverseNth_01.png");

    in.load("in_04.png");
    lst = list_from_image(in);
    lst.reverse_nth(in.height() * 61);
    out = image_from_list(lst, in.width(), in.height());
    out.save("reverseNth_02.png");

    checkSoln(__func__, out, "soln_reverseNth_02.png");

}

void test_waterfall()
{
    std::cout << "[main]: " << __func__ << "()" << std::endl;
    epng::png in{"in_05.png"};

    auto list = list_from_image(in);
    list.waterfall();

    auto out = image_from_list(list, in.width(), in.height());
    out.save("waterfall_01.png");

    checkSoln(__func__, out, "soln_waterfall_01.png");

    in.load("in_06.png");
    list = list_from_image(in);
    list.waterfall();
    out = image_from_list(list, in.width(), in.height());
    out.save("waterfall_02.png");

    checkSoln(__func__, out, "soln_waterfall_02.png");
}

void test_split()
{
    std::cout << "[main]: " << __func__ << "()" << std::endl;

    epng::png in{"in_07.png"};
    dl_list<epng::rgba_pixel> list1;
    for (size_t i = 0; i < in.width(); i++)
        for (size_t j = 0; j < in.height(); j++)
            list1.push_back(*in(i, j));
    auto list2 = list1.split(400 * 240);
    auto list3 = list2.split(400 * 240);

    std::vector<epng::rgba_pixel> im1vect{list1.begin(), list1.end()};
    std::vector<epng::rgba_pixel> im2vect{list2.begin(), list2.end()};
    std::vector<epng::rgba_pixel> im3vect{list3.begin(), list3.end()};

    epng::png out1{400, 240};
    size_t x = 0;
    for (size_t i = 0; i < im1vect.size(); i++)
    {
        size_t y = i % 240;
        *out1(x, y) = im1vect[i];
        if (y == 239)
            x++;
    }
    out1.save("split_01.png");
    checkSoln(__func__, out1, "soln_split_01.png");

    epng::png out2(400, 240);
    x = 0;
    for (size_t i = 0; i < im2vect.size(); i++)
    {
        size_t y = i % 240;
        *out2(x, y) = im2vect[i];
        if (y == 239)
            x++;
    }
    out2.save("split_02.png");
    checkSoln(__func__, out2, "soln_split_02.png");

    epng::png out3(400, 240);
    x = 0;
    for (size_t i = 0; i < im3vect.size(); i++)
    {
        size_t y = i % 240;
        *out3(x, y) = im3vect[i];
        if (y == 239)
            x++;
    }
    out3.save("split_03.png");
    checkSoln(__func__, out3, "soln_split_03.png");
}

void test_merge()
{
    std::cout << "[main]: " << __func__ << "()" << std::endl;

    epng::png im1{"in_08.png"};
    epng::png im2{"in_09.png"};
    epng::png out{600, 400};

    std::cout<<__LINE__<<std::endl;
    std::vector<epng::rgba_pixel> v1;
    for (size_t i = 0; i < im1.width(); i++)
        for (size_t j = 0; j < im1.height(); j++)
            v1.push_back(*im1(i, j));
    std::vector<epng::rgba_pixel> v2;
    for (size_t i = 0; i < im2.width(); i++)
        for (size_t j = 0; j < im2.height(); j++)
            v2.push_back(*im2(i, j));

    std::cout<<__LINE__<<std::endl;
    dl_list<epng::rgba_pixel> l1(v1.begin(), v1.end());
    dl_list<epng::rgba_pixel> l2(v2.begin(), v2.end());
    l1.merge(l2);
    std::cout<<__LINE__<<std::endl;
    std::vector<epng::rgba_pixel> merged(l1.begin(), l1.end());
    size_t x = 0;
    std::cout<<__LINE__<<std::endl;
	for (size_t i = 0; i < merged.size(); i++)
    {
        int y = i % 400;
        *out(x, y) = merged[i];
        if (y == 399)
            x++;
    }
    out.save("merge.png");

    checkSoln(__func__, out, "soln_merge.png");
}

inline std::vector<int> build_vector(const epng::png& b, int d)
{
    std::vector<int> v;
    for (size_t i = 1; i <= (b.width() * b.height()) / (d * d); i++)
        v.push_back(i);

    return v;
}

void test_sort()
{
    std::cout << "[main]: " << __func__ << "()" << std::endl;

    srand(225);

    // read in image to be shuffled
    epng::png b{"in_01.png"};

    int d = 60;
    auto v = build_vector(b, d);
    std::random_shuffle(v.begin(), v.end());

    // generate shuffled image (done for you already)
    /*
       PNG b2 = b.genImg(v, d);
       b2.writeToFile("in_01_shuffled_60.png");
    */

    // make list and sort it
    dl_list<int> img_srt(v.begin(), v.end());
    img_srt.sort();

    // vectorize and rebuild image
    std::vector<int> v2(img_srt.begin(), img_srt.end());

    auto b3 = blockpng::generate(b, v2, d);
    b3.save("unshuffled_60.png");

    checkSoln("test_sort", b3, "in_01.png");

    d = 1;
    v = build_vector(b, d);
    std::random_shuffle(v.begin(), v.end());

    /*
       PNG q = b.genImg(v, d);
       q.writeToFile("in_01_shuffled_1.png");
    */

    dl_list<int> q_srt(v.begin(), v.end());
    q_srt.sort();

    v2 = std::vector<int>(q_srt.begin(), q_srt.end());

    b3 = blockpng::generate(b, v2, d);
    b3.save("unshuffled_1.png");

    checkSoln("test_sort", b3, "in_01.png");
}

void test_mp_list_1()
{
    test_inserts();
    test_reverse();
    test_reverse_nth();
    test_waterfall();
}

void test_mp_list_2()
{
    test_split();
    test_merge();
    test_sort();
}

int main(int argc, char** argv)
{
    std::vector<std::string> args{argv, argv + argc};

    if (argc == 1 || args[1] == "all")
    {
        test_mp_list_1();
        test_mp_list_2();
    }
    else
    {
        if (args[1] == "mp_list.1" || args[1] == "mp_list1")
            test_mp_list_1();
        else if (args[1] == "mp_list.2" || args[1] == "mp_list2")
            test_mp_list_2();
        else if (args[1] == "inserts")
            test_inserts();
        else if (args[1] == "reverse")
        {
            test_reverse();
            test_reverse_nth();
        }
        else if (args[1] == "waterfall" || args[1] == "waterFall")
            test_waterfall();
        else if (args[1] == "split")
            test_split();
        else if (args[1] == "merge")
            test_merge();
        else if (args[1] == "sort" || args[1] == "mergesort" ||
                 args[1] == "mergeSort")
            test_sort();
    }

    return 0;
}
