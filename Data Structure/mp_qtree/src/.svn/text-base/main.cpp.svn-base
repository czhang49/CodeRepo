/**
 * @file main.cpp
 * Contains code to test your quadtree implementation.
 */

#include <iostream>
#include "epng.h"
#include "quadtree.h"

using std::cout;
using std::endl;

int main()
{
    using namespace cs225;

    epng::png imgIn, imgOut, imgOut2;
    imgIn.load("in.png");

    // test constructor, decompress
    quadtree halfTree(imgIn, 128);
    imgOut = halfTree.decompress();
    imgOut.save("outHalf.png");

    // now for the real tests
    quadtree fullTree;
    fullTree.build_tree(imgIn, 256);

    imgOut2 = fullTree.decompress();
    imgOut2.save("outFull.png"); 
   // you may want to experiment with different commands in this section

    // test pruned_size and ideal_prune (slow in valgrind, so you may want to
    // comment these out when doing most of your testing for memory leaks)
 /*   cout << "fullTree.pruned_size(0) = " << fullTree.pruned_size(0) << endl;
    cout << "fullTree.pruned_size(100) = " << fullTree.pruned_size(100) << endl;
    cout << "fullTree.pruned_size(1000) = " << fullTree.pruned_size(1000) << endl;
    cout << "fullTree.pruned_size(100000) = " << fullTree.pruned_size(100000)
         << endl;

    cout << "fullTree.ideal_prune(1000) = " << fullTree.ideal_prune(1000) << endl;
    cout << "fullTree.ideal_prune(10000) = " << fullTree.ideal_prune(10000)
         << endl;
*/
    // Test some creation/deletion functions
//    quadtree fullTree2;
//    fullTree2 = fullTree;
 //   imgOut = fullTree2.decompress();
//    imgOut.save("outCopy.png");

    // test clockwiseRotate
    fullTree.rotate_clockwise();
    imgOut = fullTree.decompress();
    imgOut.save("outRotated.png");

    // test prune
 /*   fullTree = fullTree2;
    fullTree.prune(1000);
    imgOut = fullTree.decompress();
    imgOut.save("outPruned.png");

    // test several functions in succession
    quadtree fullTree3(fullTree2);
    fullTree3.rotate_clockwise();
    fullTree3.prune(10000);
    fullTree3.rotate_clockwise();
    fullTree3.rotate_clockwise();
    fullTree3.rotate_clockwise();
    imgOut = fullTree3.decompress();
    imgOut.save("outEtc.png");

    // ensure that printTree still works
    quadtree tinyTree(imgIn, 32);
    cout << "Printing tinyTree:\n";
    tinyTree.prune(100);
    tinyTree.print();
*/
    return 0;
}
